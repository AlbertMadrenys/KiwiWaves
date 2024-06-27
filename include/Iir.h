/////////////////////////////////////////////////////////////////////
// Iir class: generic second-order filter
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _IIR_H_
#define _IIR_H_

#include "UGen.h"

namespace KiwiWaves
{

/** General-purpose 2nd-order IIR filter section
	(Direct Form II).
 */
class Iir : public UGen
{

public:
	/** Iir constructor. \n
		signalIn - input audio signal. \n
		a - feedforward coefficients list (a0,a1,a2)
		b - feedback coefficients (b1, b2)
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Iir(UGen& signalIn, const double* a, const double* b, size_t vsiz = def_vsize, double sr = def_sr) :
		m_sigIn(signalIn), m_a{ a[0], a[1], a[2] }, m_b{ b[0], b[1] }, m_del{ 0., 0. }, m_scal(1.), UGen(vsiz, sr)
	{
		update();
	};

	/** Iir constructor with coefficients set to zero. \n
		signalIn - input audio signal. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Iir(UGen& signalIn, size_t vsiz = def_vsize, double sr = def_sr) :
		m_sigIn(signalIn), m_a{ 0., 0., 0. }, m_b{ 0., 0. }, m_del{ 0., 0. }, m_scal(1.), UGen(vsiz, sr)
	{
		update();
	};

protected:
	double m_del[2];
	double m_a[3];
	double m_b[2];
	double m_scal;
	UGen& m_sigIn;

	void dsp() override;

	/** True if the coefficients need update because some filter parameter has changed.
	*/
	virtual bool prepareUpdate(const size_t& indx) { return false; };

	/** Update filter coefficients.
	*/
	virtual void update() {};
};

}

#endif