/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _GAITPRINT_H
#define _GAITPRINT_H

/**
 * @file gaitPrint.h 
 *
 * save and displays of someone's gait
 */

#include <iostream>
#include <sstream>
#include <string>

/** 
 * This class is designed to have the "gaitprint" in it. Its values represent the function of on person's gait.
 * Further implementations will display a polar representation with opencv.
 * f(t) = A + B.sin(w.t) + C.cos(w.t)
 * @version 1.0.0
 * @author Reynald Pereira.
 */
class GaitPrint
{
  private:
  	double 	_offset;			/** basic offset A */
  	double	_sinOffset;			/** sin offest B */
  	double	_cosinOffset;		/** cos offset C */
  	double	_angularVelocity;	/** angular velocity Omega w */
  public:
  	/**
  	 * @brief This constructor uses all for values of the function regressed
  	 * @param offset A basic offset
  	 * @param sinOffset B sin offset
  	 * @param cosOffset C cos offset
  	 * @param angulareVeloxity Omega w angular velocity
  	 * @version 1.0.0
  	 * @author Reynald Pereira
  	 */
    GaitPrint(double offset, double sinOffset, double cosinOffset, double angularVelocity);
  	/**
  	 * @brief This constructur copy a gaitprint into another one.
  	 * @param gp gaitprint to copy
  	 * @version 1.0.0
  	 * @author Reynald Pereira
  	 */
  	GaitPrint(const GaitPrint& gp);
  	/**
  	 * @brief This is the simple destructor
  	 * @version 1.0.0
  	 * @author Reynald Pereira
  	 */
    ~GaitPrint();
    /**
	 * @brief This function take the memeber values and tranforme it into a real mathematical function
	 * @return Return a string containing the function f(t) with its values set
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	std::string toString();
};

#endif