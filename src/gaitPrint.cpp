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
 * @file gaitPrint.cpp 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include "gaitPrint.h"

GaitPrint::GaitPrint(double offset,
 					double sinOffset, 
 					double cosinOffset, 
 					double angularVelocity) : _offset(offset),
 											_sinOffset(sinOffset),
 											_cosinOffset(cosinOffset),
 											_angularVelocity(angularVelocity)
{

}

GaitPrint::GaitPrint(const GaitPrint& gp)
{
	_offset = gp._offset;
	_sinOffset = gp._sinOffset;
	_cosinOffset = gp._cosinOffset;
	_angularVelocity = gp._angularVelocity;  
}

GaitPrint::~GaitPrint()
{

}

std::string GaitPrint::toString()
{
	std::string ret;
	std::ostringstream strs;
	strs << "" <<
		 _offset <<
		" + " <<
		_sinOffset <<
		"sin(" <<
		_angularVelocity <<
		"t) +" <<
		_cosinOffset <<
		"cos(" <<
		_angularVelocity <<
		"t)";
	ret = strs.str();
	return ret;
}