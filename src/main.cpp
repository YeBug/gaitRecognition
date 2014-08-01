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
#include "regSinThread.h"

#define FRAME_REINIT 2
#define FRAME_CORRECTOR 50

int main(int argc, char** argv)
{
	Tracker tracker;
	cv::VideoWriter out;
	cv::Size size;
	cv::VideoCapture cap("./data/GOPR0019.MP4");
	Corner corners,outCorners;
	int color;
	int cSize;
	cv::Mat toto;
	UnitVector x,y,t,t2;
	RegSinThread* xT;
	RegSinThread* yT;
	int nbFrame;

	if(!cap.isOpened())
	{
		std::cerr<<"Video File not Supported"<<std::endl;
		return -1;
	}

	x.resize(10000);
	y.resize(10000);
	t.resize(10000);
	t2.resize(10000);

	size = cv::Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH), (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));

	
	nbFrame = 3250;

 	out.open("./data/videoRec.avi",CV_FOURCC('P','I','M','1'),60,size,true);
	if (!out.isOpened())
	{
		std::cout<<"fail rec"<<std::endl;
		return -1;
	}


	for(int frameNumber=0;frameNumber<nbFrame;frameNumber++)
	{
		cv::Mat videoFrame, frame;
		double accX = 0;
		double accY = 0;
		
		if (frameNumber == 0 )
		{
			cap >> videoFrame;
			cvtColor(videoFrame, frame, CV_BGR2GRAY);
			cv::GaussianBlur(frame, frame, cv::Size(7,7), 1.5, 1.5);

			tracker.setInputImage1(frame);

		    tracker.setHeatMapImage(*(new cv::Mat(frame.size(),CV_8UC4)));

		}

		if( frameNumber%FRAME_REINIT == 0 ) 
		{
			tracker.reInit();
		}
		else 
		{
			cap >> videoFrame;
			cvtColor(videoFrame, frame, CV_BGR2GRAY);
			cv::GaussianBlur(frame, frame, cv::Size(7,7), 1.5, 1.5);

			tracker.setInputImage2(frame);

			tracker.runAlgos();

			corners = *tracker.getCorners();
			outCorners = *tracker.getOutCorners();
			tracker.reallocCorners();

			cSize = tracker.getCornerSize();

			cv::circle(videoFrame,corners[cSize+50],8,cv::Scalar(100,100,0),-1);

			for( size_t i = cSize; i < corners.size(); i++ )
	    	{
	 			tracker.plotField(videoFrame,corners[i],outCorners[i]);
	   		}

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
					cv::line( img,corners[(gSize+1)*i+j+cSize],corners[(gSize+1)*i+j+1+cSize],cv::Scalar(0,0,color,color),1,1,0);
					if ( i != gSize )
					{
						cv::line( img,corners[(gSize+1)*i+j+cSize],corners[(gSize+1)*i+j+(gSize+1)+cSize],cv::Scalar(0,0,color,color),1,1,0);
					}
				}
			}
			
			cv::addWeighted(img,0.3,videoFrame,1-0.3,0,videoFrame);

	   		
			cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
	    	cv::imshow( "Display window", videoFrame); 
	    	
	    	out.write(videoFrame);

			tracker.setInputImage1(frame);

		
			for(int i = 0;i<cSize;i++)
			{
				accX +=((outCorners)[i].x-(corners)[i].x);
			}
			accX /= cSize;

			for(int i = 0;i<cSize;i++)
			{
				accY +=((outCorners)[i].y-(corners)[i].x);
			}
			accY /= cSize;


			if(frameNumber>FRAME_CORRECTOR&& frameNumber<nbFrame)
			{
				x[frameNumber/2-FRAME_CORRECTOR] = accX;
				y[frameNumber/2-FRAME_CORRECTOR] = accY;
				t[frameNumber/2-FRAME_CORRECTOR] = (frameNumber/2-FRAME_CORRECTOR);
				t2[frameNumber/2-FRAME_CORRECTOR] = (frameNumber/2-FRAME_CORRECTOR);
 			}

 			if(frameNumber == nbFrame || frameNumber == nbFrame -1 )
 			{
 				std::cout<<"Computing Gait Print...."<<std::endl;
 				xT = new RegSinThread(x,t);
 				yT = new RegSinThread(y,t2);
 				xT->start();
 				yT->start();
 			}
/*
 			if( cv::waitKey(30) >= 0) 
			{
				break;
			}*/
		}
       
	}
	xT->join();
	yT->join();


	return 0;
}