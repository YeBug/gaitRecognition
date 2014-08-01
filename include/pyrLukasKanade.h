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
 * algorithme computing to find the optical flow, using pyramidal approach
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include "opticalFlowCalculater.h"

/**
 * This Class define the algorithme to find in a second picture the corners calculated is the first one
 * It uses opencv LukasKanade alogrithm with the pyramidal approach
 * All parameters except _corners are the parameter set in opencv method and _outcorners in which will the output be saved
 * @version 1.0.0
 * @author Reynald Pereira
 */
class PyrLukasKanade : public OpticalFlowCalculater
{

private:
	int 				_count;
	int 				_level;
	double				_minEigThreshold;
	std::vector<uchar>	_status;
	std::vector<float>	_trackError;
	int					_flags;
	cv::TermCriteria 	_criteria;
	Corner* 			_corners;    /** set of corners that the algorithm must refind in the new picture */
	Corner 				_outCorners; /** set of corners that have been found */
public:
	/**
	 * @brief Create a Class of this algorithm using the array of pictures, and the corners to fill in, plus the maximum number of corners. It fixes all parameters to a basic value. 
	 * @param array Array of pictures (the one set in imageAlgorithme.h using the enum imageEnum.h)
	 * @param corners Corners to be find
	 * @param count maximum number of corners we want to find
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	PyrLukasKanade(cv::Mat* array, Corner* corners, int count);
    /**
     * @brief Basic destructor of the class.     
     * @version 1.0.0
     * @author Reynald Pereira
     */
	~PyrLukasKanade();
	/**
	 * @brief This function create a cvtermcriteria using the opencv class and set is in the class parameter.
	 * @param type type of opencv criteria, opencv argument
	 * @param max_iter opencv argument
	 * @param epsilon precision, opencv argument
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setCriteria(int type, int max_iter, double epsilon);
	/**
	 * @brief This setter will be used if the user wants to apply some flags.
	 * @param flags Flags to be applied
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setFlags(int flags);
	/**
	 * @brief This setter will be used if the user wants to change the number of corners that have been given as parameters
	 * @param value numbers of corners
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setCount(int value);
	/**
	 * @brief This setter will be used if the user wants to change the array of Corners in use.
	 * @param value Value to set to corners
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setCorner(Corner* value);
	/**
	 * @brief This setter will be used if the user wants to change the level from the basic value.
	 * @param value Value to set to level
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setLevel(int value);
	/**
	 * @brief This setter will be used if the user wants to change the minimum eigen threshold from the basic value.
	 * @param value Value to set to the minimum eigen threshold
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setMinEigThreshold(double value);
	/**
	 * @brief This getter send back the errors that could have oocured during the algoritme
	 * @return return a vector contaning all the reference number of the errors 
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	std::vector<float> getTrackError();
	/**
	 * @brief This getter send back the status of the alogrithm, if it has been done well or not
	 * @return return a vector containing all status from each part of the algorithm
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	std::vector<uchar> getStatus();
	/**
	 * @brief This getter send back the output corners that have been computed
	 * @return return the output corners
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	Corner* getOutCorners();
	/**
	 * @brief This function perform the algorithme she is associated with
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	virtual void perform();
};

#endif
