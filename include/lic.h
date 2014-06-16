/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Wednesday June 03 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _LIC_H
#define _LIC_H

/**
 * @file lic.h 
 *
 * algoithme precize corners points found in a picture/image/frame
 */

#include <iostream>
#include "imageAlgorithme.h"
#include <cstdlib>
#include <cmath>
#include <cstdio>

class LIC : public virtual ImageAlgorithme
{

private:
	int 	_width;
	int 	_height;
	float* 	_field;
	float* 	_0LevelFilter;
	float*	_1LevelFilter;
	int 	_filterSize;
	float	_filterKernelLenght;
	float 	_vecMin;
	float 	_lineClipMax;
	char* 	_noise;
	Corner*	_inCorners;
	Corner*	_outCorners;

	void expandField(int times, int iteration);

public:
	LIC(cv::Mat* array, Corner* in, Corner* out);
	~LIC();
	void allocSize();
	void genField();
	void genNoiseInput();
	void refillDatas(Corner* in, Corner* out);
	void genFilter();
	void perform();
	void toPPM(unsigned char* image);
};

#endif
