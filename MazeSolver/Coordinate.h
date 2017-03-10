#ifndef COORDINATE_H
#define COORDINATE_H

/**
 * A structure representing X/Y coordinates.
 */
struct Coordinate {
	int x;
	int y;

	Coordinate(int x, int y) : x(x), y(y) {}
};

#endif
