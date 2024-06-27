/////////////////////////////////////////////////////////////////////
// Balance class: balance the RMS amp of a signal with a
// comparator signal
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _BALANCE_H_
#define _BALANCE_H_
#include "Rms.h"

namespace KiwiWaves
{

/** Balance the RMS amp of a signal with a comparator signal.
*/
class Balance : public UGen
{
public:
	/** Balance constructor. \n
		signalIn - input audio signal. \n
		signalComp - comparator audio signal. \n
		cutFreq - cutoff frequency or half-power point of the low-pass filter. \n
		zeroHandling - how to handle a division by zero. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Balance(UGen& signalIn, UGen& signalComp, double cutFreq = 10.,
		ZeroHandlingMode zeroHandling = addSmallNumber, size_t vsiz = def_vsize, double sr = def_sr) :
		m_sigIn(signalIn), m_rmsSig(signalIn, cutFreq, vsiz, sr), m_rmsComp(signalComp, cutFreq, vsiz, sr),
		m_zeroHandling(zeroHandling), UGen(vsiz, sr) { };

	/** Balance constructor. \n
		signalIn - input audio signal. \n
		signalComp - comparator audio signal. \n
		cutFreq - cutoff frequency or half-power point of the low-pass filter. \n
		zeroHandling - how to handle a division by zero. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Balance(UGen& signalIn, UGen& signalComp, UGen& cutFreq,
		ZeroHandlingMode zeroHandling = addSmallNumber, size_t vsiz = def_vsize, double sr = def_sr) :
		m_sigIn(signalIn), m_rmsSig(signalIn, cutFreq, vsiz, sr), m_rmsComp(signalComp, cutFreq, vsiz, sr),
		m_zeroHandling(zeroHandling), UGen(vsiz, sr) { };

	void setCutFreq(double val) { m_rmsSig.setCutFreq(val); m_rmsComp.setCutFreq(val); }
	void setCutFreq(UGen& modulator) { m_rmsSig.setCutFreq(modulator); m_rmsComp.setCutFreq(modulator); }

protected:
	void dsp() override;

private:
	UGen& m_sigIn;
	Rms m_rmsSig, m_rmsComp;
	ZeroHandlingMode m_zeroHandling;
};

}

#endif