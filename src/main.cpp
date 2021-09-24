#include "appSphere.hpp"

#include "rtMain.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

int main() {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


	// DO STUFF
	rt::World w = rt::get_default_world();
	rt::Ray r({ 0,0,-5 }, { 0,0,1 });
	auto shape = w.get_objects().at(0);

	//Assert::IsTrue(w.get_lights().at(0) == rt::PointLight({ -10,10,-10 }, { 1,1,1 }));
	

	rt::Intersection i(4, shape.get());
	rt::Computations comps = rt::prepare_computations(i, r);

	/*
	Assert::IsTrue(comps.t == i.t);
	Assert::IsTrue(comps.object == i.object);
	Assert::IsTrue(comps.point == rt::Point(0, 0, -1));
	Assert::IsTrue(comps.eyev == rt::Vector(0, 0, -1));
	Assert::IsTrue(comps.normalv == rt::Vector(0, 0, -1));
	*/

	rt::Material m = comps.object->material();
	m.color.debug_print();

	/*
	Assert::IsTrue(m.color == rt::Color(0.8f, 1.0f, 0.6f));
	Assert::IsTrue(m.diffuse == 0.7f);
	Assert::IsTrue(m.specular == 0.2f);
	*/

	rt::Color c = w.shade_hit(comps);
	
	c.debug_print();

	/*Assert::IsTrue(c == rt::Color(0.38066f, 0.47583f, 0.2855f));*/

	//Assert::IsTrue(c == rt::Color(0.38066f, 0.47583f, 0.2855f));

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Execution time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
	return 0;
}