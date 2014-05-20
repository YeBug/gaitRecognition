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
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "opticalFlowCalculater.h"

class PyrLukasKanade : public OpticalFlowCalculater
{

private:
	int 			_count;
	int 			_level;
	char*			_status;
	float*			_trackError;
	int				_flags;
	CvTermCriteria 	_criteria;
	Corner** 		_corners;
	Corner** 		_outCorners;
public:
	PyrLukasKanade(CvArr* array, Corner** corners, int count);
	~PyrLukasKanade();
	void setCriteria(int type, int max_iter, double epsilon);
	void setFlags(int flags);
	void setLevel(int value);
	char* getStatus();
	float* getTrackError();
	Corner* getOutCorners();
	virtual void perform();
};

#endif