/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Friday May 16 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _CORNERPRECIZER_H
#define _CORNERPRECIZER_H

/**
 * @file cornerPrecizer.h 
 *
 * algoithme precize corners points found in a picture/image/frame
 */

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "imageAlgorithme.h"

class CornerPrecizer : public virtual ImageAlgorithme
{

private:
	int				_count;
	Corner** 		_corners;
	CvSize			_windowSize;
	CvSize			_zeroZone;
	CvTermCriteria	_criteria;

public:
	CornerPrecizer(CvArr** array, Corner** corners, int count);
	~CornerPrecizer();
	void setCriteria(int type, int max_iter, double epsilon);
	void setWindowSize(CvSize value);
	void setZeroZone(CvSize value);
	virtual void perform();
};

#endif