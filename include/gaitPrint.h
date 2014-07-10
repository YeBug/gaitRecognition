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
 * algorithme computing to find the optical flow, saved in vels img
 */

#include <iostream>
#include <sstream>
#include <string>

class GaitPrint
{
  private:
  	double 	_offset;
  	double	_sinOffset;
  	double	_cosinOffset;
  	double	_angularVelocity;
  public:
    GaitPrint(double offset, double sinOffset, double cosinOffset, double angularVelocity);
    GaitPrint(const GaitPrint& gp);
    ~GaitPrint();
	std::string toString();
};

#endif