/*
 * constructor for a Square object.
 * takes the color, top left point, and bottom right point.
 */
Square::Square(Color c, Point TL, Point BR) {
	qColor = c;
	pnts[0] = TL;
	pnts[1] = Point(BR.x, TL.y);
	pnts[2] = BR;
	pnts[3] = Point(TL.x, BR.y);
}

/*
 * toString() takes an fstream and parses information about the square into
 * string format, sending it to the fstream.
 *
 * asymptotic analysis: O(n) where n depends on the size of stringToColor
 */
void Square::toString(fstream& output) const {
	output << "square,";

	// get the color via the stringToColor map
	string color = "";
	unordered_map<string, Color>::iterator it;
	for (it = stringToColor.begin(); it != stringToColor.end(); it++)
	{
	    if (it->second == qColor) {
	    	color = it->first;
	    	break;
	    }
	}

	output << color << ",";
	output << pnts[0].x << "," << pnts[0].y;
	output << "," << pnts[2].x << "," << pnts[2].y << ",";
}

/*
 * loadLine() takes a string, assuming it is in parse-able format, and parses
 * it into a Square object, returning the Square object.
 *
 * asymptotic analysis: O(n) where n depends on number of commas. should be
 * constant time as long as file format is valid.
 */
Square loadLine(string input) {
	vector<string> row;

	string elem = "";
	for (char c : input) {
	// if the character is a comma...
		if (c == ',') {
			// add the elem string to the row vector
			row.push_back(elem);
			// then reset the elem string
			elem = "";
		}

		// if the character isn't a comma,
		// add the character to the elem string
		else {
			elem += c;
		}
	}

	// check validity
	if (elem.size() > 0) {
		throw string("invalid format, cannot parse file");
	}
	if (row.size() != 6 || row.at(0) != "square") {
		throw string("invalid format, not a square");
	}

	// parse the color
	Color c;
	try {
		c = stringToColor[row.at(1)];
	} catch (...) {
		throw string("cannot parse color");
	}

	// check validity and parse points
	int tlx, tly, brx, bry;
	try {
		tlx = stoi(row.at(2));
		tly = stoi(row.at(3));
		brx = stoi(row.at(4));
		bry = stoi(row.at(5));
	} catch (...) {
		throw string("invalid points, cannot parse into Square");
	}
	Square::Point tl = Square::Point(tlx, tly);
	Square::Point br = Square::Point(brx, bry);

	return Square(c, tl, br);
}

/* stream insertion operator overload, implementing toString()
 *
 * asymptotic analysis: O(n)
 */
fstream& operator<<(fstream& output, Square& input) {
	input.toString(output);
	return output;
}
