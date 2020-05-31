/**
@file Iterator2D.h

Special iteration in 2D grids

@author Ricardo Marmolejo García
@date 16/01/15
*/

#ifndef ITERATOR2D_H
#define ITERATOR2D_H

namespace dune {

class Iterator2D
{
public:
    explicit Iterator2D();
    ~Iterator2D();
    Iterator2D(const Iterator2D&) = delete;
    Iterator2D& operator=(const Iterator2D&) = delete;
protected:

#define NUMBER_OF_POINTS 100

	void spiral_iteration()
	{
		// (di, dj) is a vector - direction in which we move right now
		int di = 1;
		int dj = 0;
		// length of current segment
		int segment_length = 1;

		// current position (i, j) and how much of current segment we passed
		int i = 0;
		int j = 0;
		int segment_passed = 0;
		for (int k = 0; k < NUMBER_OF_POINTS; ++k) {
			// make a step, add 'direction' vector (di, dj) to current position (i, j)
			i += di;
			j += dj;
			++segment_passed;

			if (segment_passed == segment_length) {
				// done with current segment
				segment_passed = 0;

				// 'rotate' directions
				int buffer = di;
				di = -dj;
				dj = buffer;

				// increase segment length if necessary
				if (dj == 0) {
					++segment_length;
				}
			}
		}
	}

};

} // end namespace dune

#endif // ITERATOR2D_H

