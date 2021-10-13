#include "appSphere2.hpp"

#include "rtMain.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <string>


int main() {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	rt::TestShape s;
	rt::Ray r({ 0,0,-5 }, { 0,0,1 });
	s.transform() = rt::scaling(2, 2, 2);
	auto xs = s.intersect(r);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	auto time_str = rt::format_duration(ms);
	std::cout << time_str << std::endl;
	return 0;
}