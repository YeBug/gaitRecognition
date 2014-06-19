/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _SIFT_H
#define _SIFT_H

/**
 * @file lukasKanade.h 
 *
 * algorithme computing to find the optical flow, saved in vels img
 */

#include <iostream>
#include <opencv2/nonfree/features2d.hpp>
#include "opticalFlowCalculater.h"

class SIFT : public OpticalFlowCalculater
{

private:
	int 		_nbFeatures;
	int			_nbOctaveLayers;
	double		_contrastThreshold;
	double  	_edgeThreshold;
	double		_sigma;
	KeyPoint* 	_keypoints;
public:
	SIFT(cv::Mat* array, KeyPoint* _keypoints);
	~SIFT();
	virtual void perform();
};

#endif
