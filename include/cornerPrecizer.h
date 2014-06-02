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
#include <opencv2/highgui/highgui.hpp>
#include "imageAlgorithme.h"

class CornerPrecizer : public virtual ImageAlgorithme
{

private:
	Corner* 		_corners;
	Corner* 		_outCorners;
	cv::Size		_windowSize;
	cv::Size		_zeroZone;
	cv::TermCriteria	_criteria;

public:
	CornerPrecizer(cv::Mat* array, Corner* corners);
	~CornerPrecizer();
	void setCorner(Corner* value);
	void setCriteria(int type, int max_iter, double epsilon);
	void setWindowSize(CvSize value);
	void setZeroZone(CvSize value);
	virtual void perform();
};

#endif
