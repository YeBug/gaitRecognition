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
 * @file regSinThread.cpp 
 *
 * algorithme finding corners points in a picturle/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include "regSinThread.h"

Thread::Thread() : m_tid(0), m_running(0), m_detached(0) {}

Thread::~Thread()
{
    if (m_running == 1 && m_detached == 0) 
    {
        pthread_detach(m_tid);
    }
    if (m_running == 1) 
    {
        pthread_cancel(m_tid);
    }
}

static void* runThread(void* arg)
{
    return ((Thread*)arg)->run();
} 

int Thread::join()
{
    int result = -1;
    if (m_running == 1) 
    {
        result = pthread_join(m_tid, NULL);
        if (result == 0) 
        {
            m_detached = 1;
        }
    }
    return result;
}

int Thread::start()
{
    int result = pthread_create(&m_tid, NULL, runThread, this);
    if (result == 0) 
    {
        m_running = 1;
    }
    return result;
}

int Thread::detach()
{
    int result = -1;
    if (m_running == 1 && m_detached == 0) 
    {
        result = pthread_detach(m_tid);
        if (result == 0) 
        {
            m_detached = 1;
        }
    }
    return result;
}

pthread_t Thread::self() {
    return m_tid;
}


void * RegSinThread::run()
{
	//// PART 1
	UnitVector 	S,SS;
	double		accT = 0, accTSquare = 0, accTCube = 0, accTQuadri = 0;
	double		accSS = 0, accSSSquare = 0, accTSS = 0, accTSquareSS = 0;
	double		accValue = 0, accValueT = 0, accVTSquare = 0, accVSS = 0;
	
	double		square;
	
	Matrix		syst1(4,4);
	Matrix		vector1(4,1);
	Matrix		sol1(4,1);

	double		x1, y1, z1, t1;
	double		omega1, a1, b1, c1;

	std::string toFill;

	S.resize(_coordinateValues.size());
	SS.resize(_coordinateValues.size());

	square = _timeValues[0]*_timeValues[0];
	S[0] = 0;
	SS[0] = 0;
	accT += _timeValues[0];
	accTSquare += square;
	accTCube += square*_timeValues[0];
	accTQuadri += square*square;
	accValue += _coordinateValues[0];
	accValueT += _timeValues[0]*_coordinateValues[0];
	accVTSquare += _coordinateValues[0]*square;

 	for (int i=1;i<_coordinateValues.size();i++)
	{
		square = _timeValues[i]*_timeValues[i];
		S[i] = S[i-1] + (1/2.0)*(_coordinateValues[i]+_coordinateValues[i-1])*(_timeValues[i]-_timeValues[i-1]);
		SS[i] = SS[i-1] + (1/2.0)*(S[i]+S[i-1])*(_timeValues[i]-_timeValues[i-1]);
		accT += _timeValues[i];
		accTSquare += square;
		accTCube += square*_timeValues[i];
		accTQuadri += square*square;
		accSS += SS[i];
		accSSSquare += SS[i]*SS[i];
		accTSS += _timeValues[i]*SS[i];
		accTSquareSS += square*SS[i];
		accValue += _coordinateValues[i];
		accValueT += _timeValues[i]*_coordinateValues[i];
		accVTSquare += _coordinateValues[i]*square;
		accVSS += _coordinateValues[i]*SS[i];
	}


	syst1.getRowNumber(0)[0] = accSSSquare;
	syst1.getRowNumber(0)[1] = accTSquareSS;
	syst1.getRowNumber(0)[2] = accTSS;
	syst1.getRowNumber(0)[3] = accSS;
	syst1.getRowNumber(1)[0] = accTSquareSS;
	syst1.getRowNumber(1)[1] = accTQuadri;
	syst1.getRowNumber(1)[2] = accTCube;
	syst1.getRowNumber(1)[3] = accTSquare;
	syst1.getRowNumber(2)[0] = accTSS;
	syst1.getRowNumber(2)[1] = accTCube;
	syst1.getRowNumber(2)[2] = accTSquare;
	syst1.getRowNumber(2)[3] = accT;
	syst1.getRowNumber(3)[0] = accSS;
	syst1.getRowNumber(3)[1] = accTSquare;
	syst1.getRowNumber(3)[2] = accT;
	syst1.getRowNumber(3)[3] = _coordinateValues.size();

	vector1.getRowNumber(0)[0] = accVSS;
	vector1.getRowNumber(1)[0] = accVTSquare;
	vector1.getRowNumber(2)[0] = accValueT;
	vector1.getRowNumber(3)[0] = accValue;

	sol1 = syst1.inverse() * vector1;//syst1.inverse() *
	
	x1 = sol1.getRowNumber(0)[0];
	y1 = sol1.getRowNumber(1)[0];
	z1 = sol1.getRowNumber(2)[0];
	t1 = sol1.getRowNumber(3)[0];

	square = _timeValues[0]*_timeValues[0];

	omega1 	= sqrt(-x1);
	a1		= 2*y1/(omega1*omega1);
	b1		= (y1*square+z1*_timeValues[0]+t1-a1)*sin(omega1*_timeValues[0])+
				(1/omega1)*(z1+2*y1*_timeValues[0])*cos(omega1*_timeValues[0]);
	c1		= (y1*square+z1*_timeValues[0]+t1-a1)*cos(omega1*_timeValues[0])+
				(1/omega1)*(z1+2*y1*_timeValues[0])*sin(omega1*_timeValues[0]);


	//// PART 2
	double 				a2, rho2;
	
	UnitVector			tetha;
	std::vector<int> 	K;
	double 				accTetha = 0, accTethaT = 0;

	double 				det2, omega2, phi2, b2, c2;

	K.resize(_coordinateValues.size());
	tetha.resize(_coordinateValues.size());

	for (int i=0;i<_coordinateValues.size();i++)
	{
		K[i] = (int)round((omega1*_timeValues[i])/(3.1415957));

		square = (_coordinateValues[i]-a2)*(_coordinateValues[i]-a2);

		if ( rho2*rho2 > square)
		{
			if ( K[i]%2 == 0 ) 
			{
				tetha[i] = atan((_coordinateValues[i]-a2)/(sqrt(rho2+rho2-square)))+3.1415957*K[i];
			}
			else
			{
				tetha[i] = -atan((_coordinateValues[i]-a2)/(sqrt(rho2+rho2-square)))+3.1415957*K[i];
			}		
		}
		else
		{
			if(_coordinateValues[i] > a2)
			{
				if ( K[i]%2 == 0 ) 
				{
					tetha[i] = (3.1415957/2)+3.1415957*K[i];
				}
				else
				{
					tetha[i] = -(3.1415957/2)+3.1415957*K[i];
				}
			}
			if(_coordinateValues[i] < a2)
			{
				if ( K[i]%2 == 0 ) 
				{
					tetha[i] = -(3.1415957/2)+3.1415957*K[i];
				}
				else
				{
					tetha[i] = (3.1415957/2)+3.1415957*K[i];
				}
			}
		}

		accTetha += tetha[i];
		accTethaT += tetha[i]*_timeValues[i];
	}

	det2 	= accTSquare*_coordinateValues.size() - accT*accT;
	omega2 	= (accTethaT*_coordinateValues.size() - accTetha*accT)/det2;
	phi2	= (accTSquare*accTetha - accT*accTethaT)/det2;
	b2		= rho2*cos(phi2);
	c2 		= rho2*sin(phi2);

	//// PART 3
	double	omega3 = omega2;

	double	accSinOT = 0, accCosOT = 0, accSin2OT = 0, accCos2OT = 0;
	double	accSinCosOT = 0, accVSinOT = 0, accVCosOT = 0;

	double	sinTmp, cosTmp;

	double	a3,b3,c3;

	Matrix	syst3(3,3);
	Matrix	vector3(3,1);
	Matrix	sol3(3,1);

	for (int i=0;i<_coordinateValues.size();i++)
	{
		sinTmp = sin(omega3*_timeValues[i]);
		cosTmp = cos(omega3*_timeValues[i]);
		accSinOT += sinTmp;
		accCosOT += cosTmp;
		accSin2OT += (1-cos(2*omega3*_timeValues[i]))/2;
		accCos2OT += (1+cos(2*omega3*_timeValues[i]))/2;
		accSinCosOT += sinTmp*cosTmp;
		accVSinOT += _coordinateValues[i]*sinTmp;
		accVCosOT += _coordinateValues[i]*cosTmp;
	}

	syst3.getRowNumber(0)[0] = _coordinateValues.size();
	syst3.getRowNumber(0)[1] = accSinOT;
	syst3.getRowNumber(0)[2] = accCosOT;
	syst3.getRowNumber(1)[0] = accSinOT;
	syst3.getRowNumber(1)[1] = accSin2OT;
	syst3.getRowNumber(1)[2] = accSinCosOT;
	syst3.getRowNumber(2)[0] = accCosOT;
	syst3.getRowNumber(2)[1] = accSinCosOT;
	syst3.getRowNumber(2)[2] = accCos2OT;

	vector3.getRowNumber(0)[0] = accValue;
	vector3.getRowNumber(1)[0] = accVSinOT;
	vector3.getRowNumber(2)[0] = accVCosOT;

	sol3 = syst3.inverse() *vector3;//syst3.inverse() * 

	a3 = sol3.getRowNumber(0)[0];
	b3 = sol3.getRowNumber(1)[0];
	c3 = sol3.getRowNumber(2)[0];

	_functionComputed = new GaitPrint(a3,b3,c3,omega3);
	_runned = true;

	std::cout<<"Calculations ended, press ESC if you see this message twice"<<std::endl;

	return 0;
}

RegSinThread::RegSinThread(UnitVector coordinateValues, UnitVector timeValues)
{
	_coordinateValues 	= coordinateValues;
	_timeValues 		= timeValues;
	_runned 			= false;
	_functionComputed	= (new GaitPrint(0,0,0,0));
}

RegSinThread::~RegSinThread()
{
	//delete _functionComputed;
}

GaitPrint* RegSinThread::getFunction()
{
	return new GaitPrint(*_functionComputed);
}