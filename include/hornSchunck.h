/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _HORNKSCHUNCK_H
#define _HORNKSCHUNCK_H

/**
 * @file hornSchunck.h 
 *
 * algorithme computing to find the optical flow, saved in vels img
 */

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "opticalFlowCalculater.h"

class HornSchunck : public OpticalFlowCalculater
{

private:
	bool _usePrevious;
	double _lambda;
	CvTermCriteria _criteria;
public:
	HornSchunck(CvArr** array);
	~HornSchunck();
	void usePrevious();
	void doNotUsePrevious();
	void setCriteria(int type, int max_iter, double epsilon);
	void setLambda(double value);
	virtual void perform();
};

#endif