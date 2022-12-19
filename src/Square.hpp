/*
 * Square.hpp
 *
 *  Created on: Dec 10, 2022
 *      Author: angela
 */

#ifndef FINAL_PROJECT_ANGELAJT_SRC_SQUARE_HPP_
#define FINAL_PROJECT_ANGELAJT_SRC_SQUARE_HPP_
#include "Shape.hpp"

class Square : public Shape {
public:
    Point pnts[4]; // TL, TR, BR, BL

	Square() {}
    Square(Color, Point, Point);

    friend ostream& operator<<(ostream&, const Square&);

    void toString(fstream&) const;
};

Square loadLine(string);

#include "Square.cpp"

#endif /* FINAL_PROJECT_ANGELAJT_SRC_SQUARE_HPP_ */

