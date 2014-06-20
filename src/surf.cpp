/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Monday May 19 2014
 *
 * @todo create the class 
 * @bug check if simple Corner pointer is enough
 */

/**
 * @file surff.cpp 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include "surf.h"

SURF::SURF(cv::Mat* array,KeyPoint* kp) : OpticalFlowCalculater(array)
{
	_imageArray = array;
	_hessianThreshold = 400;
	_octaves = 3;
	_nbOctaveLayers = 4;
	_keypoints = kp;
}

SURF::~SURF() 
{
	_imageArray = NULL;
	_keypoints = NULL;
	delete _keypoints;
	delete _imageArray;
}

void SURF::perform()
{
	cv::Mat toPass;

	_imageArray[GR_SURF_IMAGE].copyTo(toPass);

	cv::FeatureDetector* detector = new cv::SurfFeatureDetector(
										_hessianThreshold,
										_octaves,
										_nbOctaveLayers);
	cv::DescriptorExtractor* extractor = new cv::SurfDescriptorExtractor();

	detector->detect(toPass,*(_keypoints));
	extractor->compute(toPass,
						*_keypoints,
						_imageArray[GR_SURF_IMAGE]);
	delete extractor;
}