/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _PYRLUKASKANADE_H
#define _PYRLUKASKANADE_H

/**
 * @file PyrLukasKanade.h 
 *
 * algorithme computing to find the optical flow, saved in vels img
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include "opticalFlowCalculater.h"

class PyrLukasKanade : public OpticalFlowCalculater
{

private:
	int 				_count;
	int 				_level;
	double				_minEigThreshold;
	std::vector<uchar>	_status;
	std::vector<float>	_trackError;
	int					_flags;
	cv::TermCriteria 	_criteria;
	Corner* 			_corners;
	Corner 				_outCorners;
public:
	PyrLukasKanade(cv::Mat* array, Corner* corners, int count);
	~PyrLukasKanade();
	void setCriteria(int type, int max_iter, double epsilon);
	void setFlags(int flags);
	void setLevel(int value);
	void setMinEigThreshold(double value);
	std::vector<float> getTrackError();
	std::vector<uchar> getStatus();
	Corner* getOutCorners();
	virtual void perform();
};

#endif
