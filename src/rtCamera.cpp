#include "rtCamera.hpp"
#include "rtRay.hpp"
#include <cmath>

namespace rt {

	Ray Camera::ray_for_pixel(i32 px, i32 py) const {

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
		auto inv = inverse(m_transform);
		if (inv.has_value()) {
			auto inv_transform = inv.value();
			auto pixel = inv_transform * Point(world_x, world_y, -1);
			origin = inv_transform * Point(0, 0, 0);
			direction = normalize(pixel - origin);
		}

		return Ray(origin, direction);	
	}

	Canvas Camera::render(const World& w) const {
		auto image = Canvas(m_hsize, m_vsize);

		for (i32 y = 0; y < m_vsize; y++) {
			for (i32 x = 0; x < m_hsize; x++) {
				Ray ray = ray_for_pixel(x, y);
				Color color = w.color_at(ray);
				image.write_pixel(x, y, color);
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
}