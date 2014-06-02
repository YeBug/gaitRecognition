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
	cv::VideoWriter out;
	cv::Size size;
	cv::VideoCapture cap("./data/video1.avi");
	Corner corners,outCorners;
	int color;


	if(!cap.isOpened())
	{
		return -1;
	}


	size = cv::Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH), (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));

 	out.open("./data/videoRec.avi",CV_FOURCC('P','I','M','1'),30,size,true);
	if (!out.isOpened())
	{
		std::cout<<"fail rec"<<std::endl;
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

		    tracker.setHeatMapImage(*(new cv::Mat(frame.size(),CV_8UC4)));

		}

		if( i%FRAME_REINIT == 0 ) 
		{
			tracker.reInit();
			//corners.clear();
			//outCorners.clear();
		}
		else 
		{
			cap >> videoFrame;
			cvtColor(videoFrame, frame, CV_BGR2GRAY);
			cv::GaussianBlur(frame, frame, cv::Size(7,7), 1.5, 1.5);

			tracker.setInputImage2(frame);

			tracker.runAlgos();

			corners.insert(corners.end(),tracker.getCorners()->begin(),tracker.getCorners()->end());

			outCorners.insert(outCorners.end(),tracker.getOutCorners()->begin(),tracker.getOutCorners()->end());

			tracker.reallocCorners();

			for( size_t i = 0; i < corners.size(); i++ )
	    	{ 
	    		color = ((corners[i].x - outCorners[i].x)*255/frame.size().width + (corners[i].y - outCorners[i].y)*255/frame.size().height)/2 ;
	    		//std::cout<<"Color found : "<<color<<std::endl;
	    		/*if ( color < 0 ) 
	    		{
	    			color = -color;
	    		}
	    		if ( color > 45 && color < 85 )
	    		{
	 				cv::circle( videoFrame, corners[i], 1, cv::Scalar(85,0,0), -1, 8, 0 );
	    		}
	    		else if ( color > 85 && color < 170 )
	    		{
	 				cv::circle( videoFrame, corners[i], 1, cv::Scalar(0,color,color), -1, 8, 0 );
	    		}
	    		else  if ( color > 170 && color < 255 )
	    		{
	 				cv::circle( videoFrame, corners[i], 1, cv::Scalar(0,0,color), -1, 8, 0 );
	    		}*/
	 			tracker.plotField(videoFrame,corners[i],outCorners[i]);
	   		}
	   		for( size_t i = 0; i<tracker.getCorners()->size();i++)
	   		{
   				cv::line( videoFrame, (*tracker.getCorners())[i],(*tracker.getOutCorners())[i],cv::Scalar(128,128,128),1,1,0);
   			}

	   		
			//out << *tracker.getOutputFrame();
			cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
	    	cv::imshow( "Display window", videoFrame); 
			
	    	out.write(videoFrame);

			tracker.setInputImage1(frame);

			if( cv::waitKey(30) >= 0) 
			{
				break;
			}
		}
       
	}
	
	return 0;
}