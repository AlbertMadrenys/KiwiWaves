/////////////////////////////////////////////////////////////////////
// Rms class: root-mean-square estimator
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _RMS_H_
#define _RMS_H_
#include "Tone.h"

namespace KiwiWaves
{

/** Estimate the root-means-square of a signal.
*/
class Rms : public ToneLP
{
public:
	/** Rms constructor. \n
		signalIn - input audio signal. \n
		cutFreq - cutoff frequency or half-power point of the low-pass filter. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Rms(UGen& signalIn, double cutFreq = 10., size_t vsiz = def_vsize, double sr = def_sr) :
		ToneLP(signalIn, cutFreq, vsiz, sr) { };

	/** Rms constructor. \n
		signalIn - input audio signal. \n
		cutFreq - cutoff frequency or half-power point of the low-pass filter. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Rms(UGen& signalIn, UGen& cutFreq, size_t vsiz = def_vsize, double sr = def_sr) :
		ToneLP(signalIn, cutFreq, vsiz, sr) { };

protected:
	void dsp() override;

private:
	/** Low-pass filter rectification for calculating the RMS (absolute value).
	*/
	double rect(double x);

};

}

#endif
