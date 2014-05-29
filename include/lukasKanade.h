/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _LUKASKANADE_H
#define _LUKASKANADE_H

/**
 * @file lukasKanade.h 
 *
 * algorithme computing to find the optical flow, saved in vels img
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/legacy.hpp>
#include "opticalFlowCalculater.h"

class LukasKanade : public OpticalFlowCalculater
{

private:

public:
	LukasKanade(cv::Mat* array);
	~LukasKanade();
	virtual void perform();
};

#endif
