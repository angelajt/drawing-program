/*
 * Shape.hpp
 *
 *  Created on: Dec 10, 2022
 *      Author: angela
 */

#ifndef FINAL_PROJECT_ANGELAJT_SRC_SHAPE_HPP_
#define FINAL_PROJECT_ANGELAJT_SRC_SHAPE_HPP_

#include "adts.hpp"

class Shape {
public:
	Color qColor;

	struct Point {
		int x, y;

		Point() : x(0), y(0) {}

		Point(int xin, int yin)
		: x(xin),
		  y(yin) {}
	};

	Shape() {}
};

#endif /* FINAL_PROJECT_ANGELAJT_SRC_SHAPE_HPP_ */
