#ifndef __RT_CAMERA_HPP__
#define __RT_CAMERA_HPP__

#include "rtDefs.hpp"
#include "rtMatrix.hpp"
#include "rtCanvas.hpp"
#include "rtWorld.hpp"

#include <functional>
#include <memory>

namespace rt {
	class Ray;
	class Canvas;
	class World;
	class Camera {
		public:
			Camera(i32 hsize, i32 vsize, f32 fov) : m_hsize(hsize), m_vsize(vsize), m_fov(fov), m_transform(get_identity_matrix4()) {
				calculate_pixel_size();
			}

			Ray ray_for_pixel(i32 px, i32 py) const;
			Canvas render(const World& w) const;

			i32 hsize() const { return m_hsize; }
			i32 vsize() const { return m_vsize; }
			f32 fov() const { return m_fov; }
			
			f32 half_width() const { return m_half_width; }
			f32 half_height() const { return m_half_height; }
			f32 pixel_size() const { return m_pixel_size; }
			
			const Matrix& transform() const { return m_transform; }
			Matrix& transform() { return m_transform; }

			using pixel_callback = std::function<void(i32, i32, f32, f32, f32)>;
			void set_pixel_callback(pixel_callback callback) {
				m_pixel_callback = std::move(callback);
			}


		private:
			void calculate_pixel_size();

			i32 m_hsize = 0;
			i32 m_vsize = 0;
			f32 m_fov = 0;
			f32 m_half_width = 0;
			f32 m_half_height = 0;
			f32 m_pixel_size = 0;
			Matrix m_transform;

			pixel_callback m_pixel_callback;
	};

	std::unique_ptr<Camera> make_camera(i32 width, i32 height, f32 fov);
}

#endif