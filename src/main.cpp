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

int main(int argc, char** argv)
{
	Tracker tracker;
	cv::VideoWriter out;
	cv::Size size;
	cv::VideoCapture cap(0);
	Corner corners,outCorners;
	int color;
	int cSize;
	cv::Mat toto;

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
			//tracker.setHeatMapImage(videoFrame);

			tracker.runAlgos();

			corners = *tracker.getCorners();
			outCorners = *tracker.getOutCorners();
			tracker.reallocCorners();

			cSize = tracker.getCornerSize();

			cv::circle(videoFrame,corners[cSize+50],8,cv::Scalar(100,100,0),-1);

			for( size_t i = cSize; i < corners.size(); i++ )
	    	{
	 			tracker.plotField(videoFrame,corners[i],outCorners[i]);
	   		}/*
	   		for( size_t i = 0; i<tracker.getCorners()->size();i++)
	   		{
   				cv::line( videoFrame, (*tracker.getCorners())[i],(*tracker.getOutCorners())[i],cv::Scalar(128,128,128),1,1,0);
   			}*/

   			cv::Mat img;
   			int gSize = GR_GRID_SIZE;

   			while ( videoFrame.size().width % gSize != 0
   					&& videoFrame.size().height % gSize != 0)
   			{
   				gSize--;
   			}

   			videoFrame.copyTo(img);

			for (int i = 0;i < gSize+1 ; i+=1)
			{
				for(int j = 0;j < gSize+1; j+=1)
				{
					if ( j == gSize )
					{
						continue;
					}
					//std::cout<<"i/j :"<<i<<"/"<<j<<"/"<<10*nbW<<std::endl;
					//cv::circle(img,corners[10*i+j+1],8,cv::Scalar(color,0,0,150),-1);
					cv::line( img,corners[(gSize+1)*i+j+cSize],corners[(gSize+1)*i+j+1+cSize],cv::Scalar(0,0,color,color),1,1,0);
					if ( i != gSize )
					{
						cv::line( img,corners[(gSize+1)*i+j+cSize],corners[(gSize+1)*i+j+(gSize+1)+cSize],cv::Scalar(0,0,color,color),1,1,0);
					}
				}
			}
			
			cv::addWeighted(img,0.3,videoFrame,1-0.3,0,videoFrame);

	   		
			//out << *tracker.getOutputFrame();
			//tracker.getOverlayFrame()->copyTo(videoFrame);
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