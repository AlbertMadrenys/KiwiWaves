/////////////////////////////////////////////////////////////////////
// Tone: first-order high-pass and low-pass filters
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _TONE_H_
#define _TONE_H_
#include "UGen.h"

namespace KiwiWaves
{

/** Simple first-order low-pass filter.
*/
class ToneLP : public UGen
{
public:
	/** ToneLP constructor. \n
		signalIn - input audio signal. \n
		cutFreq - cutoff frequency. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ToneLP(UGen& signalIn, double cutFreq, size_t vsiz = def_vsize, double sr = def_sr) :
		m_sigIn(signalIn), m_cutFreq(cutFreq), m_a(0.), m_b(0.), m_freq(0.), m_del(0.), UGen(vsiz, sr)
	{
		update();
	};

	/** ToneLP constructor. \n
		signalIn - input audio signal. \n
		cutFreq - cutoff frequency. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ToneLP(UGen& signalIn, UGen& cutFreq, size_t vsiz = def_vsize, double sr = def_sr) :
		m_sigIn(signalIn), m_cutFreq(cutFreq), m_a(0.), m_b(0.), m_freq(0.), m_del(0.), UGen(vsiz, sr)
	{
		update();
	};
	
	void setCutFreq(double val) { m_cutFreq.set(val); update(); }
	void setCutFreq(UGen& modulator) { m_cutFreq.set(modulator); update(); }

protected:
	UGen& m_sigIn;
	UGenParam m_cutFreq;
	double m_a, m_b, m_freq, m_del;

	void dsp() override;

	/** Update filter coefficients.
	*/
	virtual void update();
};

/** Simple first-order high-pass filter.
 */
class ToneHP : public ToneLP
{
public:
	/** ToneHP constructor. \n
		signalIn - input audio signal. \n
		cutFreq - cutoff frequency. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ToneHP(UGen& signalIn, UGen& cutFreq, size_t vsiz = def_vsize, double sr = def_sr) :
		ToneLP(signalIn, cutFreq, vsiz, sr) { };

	/** ToneHP constructor. \n
		signalIn - input audio signal. \n
		cutFreq - cutoff frequency. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ToneHP(UGen& signalIn, double cutFreq, size_t vsiz = def_vsize, double sr = def_sr) :
		ToneLP(signalIn, cutFreq, vsiz, sr) { };

protected:
	void update() override;
};

}

#endif