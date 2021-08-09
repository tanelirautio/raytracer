#include "rtTuple.hpp"
#include "rtFile.hpp"
#include "rtCanvas.hpp"
#include "rtLog.hpp"

std::vector<std::string> split_string_by_newline(const std::string& str)
{
	auto result = std::vector<std::string>{};
	auto ss = std::stringstream{ str };

	for (std::string line; std::getline(ss, line, '\n');)
		result.push_back(line);

	return result;
}

struct Proj {
	Proj(rt::Point pos, rt::Vector vel) {
		this->pos = pos;
		this->vel = vel;
	}
	rt::Point pos;
	rt::Vector vel;
};

struct Env {
	Env(rt::Vector grav, rt::Vector wind) {
		this->grav = grav;
		this->wind = wind;
	}
	rt::Vector grav;
	rt::Vector wind;
};

Proj tick(Env& e, Proj& p) {
	auto pos = p.pos + p.vel;
	auto vel = p.vel + e.grav + e.wind;
	return Proj(pos, vel);
}

int main() {

	rt::Vector vel = rt::Vector(6, 6, 0);
	vel.normalize();
	//vel = vel * 11.25f;

	Proj p(rt::Point(0, 1, 0), vel);
	Env e(rt::Vector(0, -0.1f, 0), rt::Vector(-0.01f, 0, 0));

	rt::Canvas c(900, 550);

	LOG("P (x, y): (%f, %f) ", p.pos.x(), p.pos.y());
	c.write_pixel(p.pos.x(), p.pos.y(), rt::get_color_white());

	while (p.pos.y() > 0) {
		p = tick(e, p);
		LOG("P (x, y): (%f, %f) ", p.pos.x(), p.pos.y());
		c.write_pixel(p.pos.x(), c.get_height() - p.pos.y(), rt::get_color_white());
	}

	rt::File::write("plot.ppm", c.canvas_to_ppm());
	return 0;
}