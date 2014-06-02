/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _CORNERFINDER_H
#define _CORNERFINDER_H

/**
 * @file cornerFinder.h 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "imageAlgorithme.h"

class CornerFinder : public virtual ImageAlgorithme
{

private:
	double 		_qualityLevel;
	double 		_minimumDistance;
	int			_blockSize;
	bool		_harrisUsed;
	double		_weightCoefficientForHarrisAutocorrelation;
	int			_count;
	Corner* 	_corners;

public:
	CornerFinder(cv::Mat* array, Corner* corners, int count);
	~CornerFinder();
	void setQualityLevel(double value);
	void setMinimumDistance(double value);
	void useHarris();
	void setCorner(Corner* value);
	void doNotUseHarris();
	void applyMask(cv::Mat* mask);
	void setBlockSize(int value);
	int  getCornersCount();
	virtual void perform();
};
#endif
