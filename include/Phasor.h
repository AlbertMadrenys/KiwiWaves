/////////////////////////////////////////////////////////////////////
// Phasor class: phase signal generator
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _PHASOR_H_
#define _PHASOR_H_
#include "UGen.h"

namespace KiwiWaves
{

/** Phase signal (ramp) generator.
*/
class Phasor : public UGen
{
public:
	/** Phasor constructor. \n
		fr - frequency or velocity. \n
		ph - normalized phase offset. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Phasor(UGen& fr, double ph = 0., size_t vsiz = def_vsize, double sr = def_sr) :
		m_fr(fr), m_ph(ph), UGen(vsiz, sr) { };

	/** Phasor constructor. \n
		fr - frequency or velocity. \n
		ph - normalized phase offset. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Phasor(double fr, double ph = 0., size_t vsiz = def_vsize, double sr = def_sr) :
		m_fr(fr), m_ph(ph), UGen(vsiz, sr) { };

	void setFreq(double val) { m_fr.set(val); }
	void setFreq(UGen& modulator) { m_fr.set(modulator); }

protected:
	void dsp() override;

private:
	UGenParam m_fr;
	double m_ph;
};

}

#endif
