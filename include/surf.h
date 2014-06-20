/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _SURF_H
#define _SURF_H

/**
 * @file lukasKanade.h 
 *
 * algorithme computing to find the optical flow, saved in vels img
 */

#include <iostream>
#include <opencv2/nonfree/features2d.hpp>
#include "opticalFlowCalculater.h"

class SURF : public OpticalFlowCalculater
{

private:
	int 		_octaves;
	int			_nbOctaveLayers;
	double		_hessianThreshold;
	KeyPoint* 	_keypoints;
public:
	SURF(cv::Mat* array, KeyPoint* _keypoints);
	~SURF();
	virtual void perform();
};

#endif
