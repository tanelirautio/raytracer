#include "rtCamera.hpp"
#include "rtRay.hpp"
#include "rtDefs.hpp"
#include <algorithm>
#include <cmath>
#include <chrono>
#include <thread>
#include <vector>
#include <functional>

namespace rt {

	Ray Camera::ray_for_pixel(i32 px, i32 py) const {
		auto inv = inverse(m_transform);
		if (!inv.has_value()) {
			return Ray(Point(), Vector());
		}

		return ray_for_pixel(px, py, inv.value());
	}

	Ray Camera::ray_for_pixel(i32 px, i32 py, const Matrix& inverse_transform) const {
		Point origin;
		Vector direction;

		// The offset from the edge of the canvas to the pixel's center
		auto xoffset = (px + 0.5f) * m_pixel_size;
		auto yoffset = (py + 0.5f) * m_pixel_size;

		// The untransformed coordinates of the pixel in world space
		// (Remember that the camera looks toward -z, so +x is to the *left*)
		auto world_x = m_half_width - xoffset;
		auto world_y = m_half_height - yoffset;

		// Using the camera matrix, transform the canvas point and the origin,
		// and then compute the ray's direction vector
		// (remember that the canvas is at z = -1)
		auto pixel = inverse_transform * Point(world_x, world_y, -1);
		origin = inverse_transform * Point(0, 0, 0);
		direction = normalize(pixel - origin);

		return Ray(origin, direction);	
	}

	Canvas Camera::render(const World& w, cancel_callback should_cancel) const {
		auto image = Canvas(m_hsize, m_vsize);
		auto inverse_transform = inverse(m_transform);
		if (!inverse_transform.has_value()) {
			return image;
		}
		const Matrix cached_inverse_transform = inverse_transform.value();

		// hardware_concurrency() may return 0 when the implementation cannot determine a value.
		u32 num_threads = std::max(1u, std::thread::hardware_concurrency());

		// To keep track of threads
		std::vector<std::thread> threads;

		auto is_cancelled = [&should_cancel]() {
			return should_cancel && should_cancel();
		};

		// Split rendering work across threads
		auto render_part = [&](i32 start_row, i32 end_row) {
			for (i32 y = start_row; y < end_row && !is_cancelled(); y++) {
				for (i32 x = 0; x < m_hsize && !is_cancelled(); x++) {
					Ray ray = ray_for_pixel(x, y, cached_inverse_transform);
					Color color = w.color_at(ray);
					image.write_pixel(x, y, color);

					// Thread-safe callback
					if (m_pixel_callback) {
						m_pixel_callback(x, y, color.r(), color.g(), color.b());
						//std::this_thread::sleep_for(std::chrono::milliseconds(1));
					}
				}
			}
		};

		// Divide the image into parts for each thread
		i32 rows_per_thread = m_vsize / num_threads;
		i32 remaining_rows = m_vsize % num_threads;

		for (u32 i = 0; i < num_threads; ++i) {
			// Calculate the start and end row for this thread
			i32 start_row = static_cast<i32>(i) * rows_per_thread;
			i32 end_row = (i == num_threads - 1) ? (start_row + rows_per_thread + remaining_rows) : (start_row + rows_per_thread);

			// Launch a thread to render its part of the image
			threads.emplace_back(render_part, start_row, end_row);
		}

		// Wait for all threads to complete
		for (auto& t : threads) {
			if (t.joinable()) {
				t.join();
			}
		}

		return image;
	}


	void Camera::calculate_pixel_size() {

		f32 half_view = tan(m_fov / 2.f);
		f32 aspect = (f32)m_hsize / (f32)m_vsize;

		if (aspect >= 1.0f) {
			m_half_width = half_view;
			m_half_height = half_view / aspect;
		}
		else {
			m_half_width = half_view * aspect;
			m_half_height = half_view;
		}

		m_pixel_size = (m_half_width * 2.f) / m_hsize;	
	}

	std::unique_ptr<Camera> make_camera(i32 width, i32 height, f32 fov) {
		return std::make_unique<Camera>(width, height, fov);
	}
}
