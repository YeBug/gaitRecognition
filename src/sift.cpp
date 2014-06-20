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
 * @file sift.cpp 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include "sift.h"

SIFT::SIFT(cv::Mat* array,KeyPoint* kp) : OpticalFlowCalculater(array)
{
	_imageArray = array;
	_nbFeatures = 0;
	_nbOctaveLayers = 3;
	_contrastThreshold = 0.04;
	_edgeThreshold = 10;
	_sigma = 1.6;
	_keypoints = kp;
}

SIFT::~SIFT() 
{
	_imageArray = NULL;
	_keypoints = NULL;
	delete _keypoints;
	delete _imageArray;
}

void SIFT::perform()
{
	cv::FeatureDetector* detector = new cv::SiftFeatureDetector(_nbFeatures,
							_nbOctaveLayers,
							_contrastThreshold,
							_edgeThreshold,
							_sigma);
	cv::DescriptorExtractor* extractor = new cv::SiftDescriptorExtractor();

	detector->detect(_imageArray[GR_INPUT_IMAGE],*_keypoints);
	extractor->compute(_imageArray[GR_INPUT_IMAGE],
						*_keypoints,
						_imageArray[GR_VELY_IMAGE]);
	delete extractor;
}