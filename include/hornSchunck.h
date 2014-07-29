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
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/legacy.hpp>
#include "opticalFlowCalculater.h"

/**
 * This Class define the algorithme to find in a second picture the corners calculated is the first one
 * It uses opencv HornSchunck alogrithm
 * @version 1.0.0
 * @author Reynald Pereira
 */
class HornSchunck : public OpticalFlowCalculater
{

private:
	bool _usePrevious;
	double _lambda;
	CvTermCriteria _criteria;
public:
	/**
	 * @brief Create a Class of this algorithm. It fixes all parameters to a basic value. 
	 * @param array Array of pictures (the one set in imageAlgorithme.h using the enum imageEnum.h)
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	HornSchunck(cv::Mat* array);
    /**
     * @brief Basic destructor of the class.     
     * @version 1.0.0
     * @author Reynald Pereira
     */
	~HornSchunck();
	/**
	 * @brief This setter will be used if the user wants to change to true the use the previous step of the algotithm
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void usePrevious();
	/**
	 * @brief This setter will be used if the user wants to change to false the use the previous step of the algotithm
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void doNotUsePrevious();
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
	 * @brief This setter will be used if the user wants to change the lambda from the basic value.
	 * @param value Value to set to lambda
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setLambda(double value);
	/**
	 * @brief This function perform the algorithme she is associated with
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	virtual void perform();
};

#endif
