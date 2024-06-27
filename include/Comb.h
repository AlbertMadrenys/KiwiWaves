/////////////////////////////////////////////////////////////////////
// Comb: Comb filter using RT60
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _COMB_H_
#define _COMB_H_
#include "Delay.h"

namespace KiwiWaves
{

/** Comb filter using RT60.
*/
class Comb : public Delay
{
public:
	/** Comb constructor. \n
		signalIn - input audio signal. \n
		rt60 - reverberation time 60. \n
		maxDel - max value of delay. \n
		del - current value of delay. \n
		interpolate - allow for linear interpolation. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Comb(UGen& signalIn, double rt60, double maxDel, double del = -1., bool interpolate = false,
		size_t vsiz = def_vsize, double sr = def_sr) :
		m_currentRT60(-1.), m_currentDel(-1.), m_currentFb(-1.),
		Delay(signalIn, maxDel, del, rt60, interpolate, vsiz, sr) { };

	/** Comb constructor. \n
		signalIn - input audio signal. \n
		rt60 - reverberation time 60. \n
		maxDel - max value of delay. \n
		del - current value of delay. \n
		interpolate - allow for linear interpolation. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Comb(UGen& signalIn, double rt60, double maxDel, UGen& del, bool interpolate = true,
		size_t vsiz = def_vsize, double sr = def_sr) :
		m_currentRT60(-1.), m_currentDel(-1.), m_currentFb(-1.),
		Delay(signalIn, maxDel, del, rt60, interpolate, vsiz, sr) { };

	/** Comb constructor. \n
		signalIn - input audio signal. \n
		rt60 - reverberation time 60. \n
		maxDel - max value of delay. \n
		del - current value of delay. \n
		interpolate - allow for linear interpolation. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Comb(UGen& signalIn, UGen& rt60, double maxDel, double del = -1., bool interpolate = false,
		size_t vsiz = def_vsize, double sr = def_sr) :
		m_currentRT60(-1.), m_currentDel(-1.), m_currentFb(-1.),
		Delay(signalIn, maxDel, del, rt60, interpolate, vsiz, sr) { };

	/** Comb constructor. \n
		signalIn - input audio signal. \n
		rt60 - reverberation time 60. \n
		maxDel - max value of delay. \n
		del - current value of delay. \n
		interpolate - allow for linear interpolation. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Comb(UGen& signalIn, UGen& rt60, double maxDel, UGen& del, bool interpolate = true,
		size_t vsiz = def_vsize, double sr = def_sr) :
		m_currentRT60(-1.), m_currentDel(-1.), m_currentFb(-1.),
		Delay(signalIn, maxDel, del, rt60, interpolate, vsiz, sr) { };
	
private:
	double m_currentRT60, m_currentDel, m_currentFb;
	double getFb(size_t pos) override;
};

}
#endif