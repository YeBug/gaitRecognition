/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Tuesday May 20 2014
 *
 * @todo create the class 
 * @bug check if simple Corner pointer is enough
 */

/**
 * @file main.cpp 
 *
 * algorithme finding corners points in a picturle/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include "tracker.h"

#define FRAME_REINIT 10

int main(void)
{
	Tracker tracker;
	cv::VideoCapture cap("./data/video1.avi");
	if(!cap.isOpened())
	{
		return -1;
	}
	for(int i=0;;i++)
	{
		cv::Mat videoFrame, frame;
		
		if (i == 0 )
		{
			cap >> videoFrame;
			cvtColor(videoFrame, frame, CV_BGR2GRAY);
			cv::GaussianBlur(frame, frame, cv::Size(7,7), 1.5, 1.5);

			tracker.setInputImage1(frame);
		}

		if( i%FRAME_REINIT == 0 ) 
		{
			tracker.reInit();
		}

		cap >> videoFrame;
		cvtColor(videoFrame, frame, CV_BGR2GRAY);
		cv::GaussianBlur(frame, frame, cv::Size(7,7), 1.5, 1.5);

		tracker.setInputImage2(frame);

		tracker.runAlgos();

		tracker.setInputImage1(frame);

		if( cv::waitKey(30) >= 0) 
		{
			break;
		}
	}
	
	return 0;
}
