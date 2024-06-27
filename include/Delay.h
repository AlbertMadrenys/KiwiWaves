/////////////////////////////////////////////////////////////////////
// Delay: Variable delay line with optional feedback
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _DELAY_H_
#define _DELAY_H_
#include "UGen.h"

namespace KiwiWaves
{

/** Variable delay line with optional feedback
	(Delay, Comb filter, Flanger).
*/
class Delay : public UGen
{
public:
	/** Delay constructor. \n
		signalIn - input audio signal. \n
		maxDel - max value of delay. \n
		del - current value of delay. \n
		feedback - amount of feedback (should not exceed 1). \n
		interpolate - allow for linear interpolation. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Delay(UGen& signalIn, double maxDel, double del = -1., double feedback = 0., bool interpolate = false,
		size_t vsiz = def_vsize, double sr = def_sr) :
		m_sigIn(signalIn), m_delVal(del != -1 ? del : maxDel), m_delLine(maxDel >= 0. ? (size_t)std::ceil((maxDel * sr)) : 1),
		m_fb(feedback), m_interp(interpolate), m_writePos(0), UGen(vsiz, sr)
	{
		std::fill(m_delLine.begin(), m_delLine.end(), 0.);
	};

	/** Delay constructor. \n
		signalIn - input audio signal. \n
		maxDel - max value of delay. \n
		del - current value of delay. \n
		feedback - amount of feedback (should not exceed 1). \n
		interpolate - allow for linear interpolation. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Delay(UGen& signalIn, double maxDel, UGen& del, double feedback = 0., bool interpolate = true,
		size_t vsiz = def_vsize, double sr = def_sr) :
		m_sigIn(signalIn), m_delVal(del), m_delLine(maxDel >= 0. ? (size_t)std::ceil((maxDel * sr)) : 1),
		m_fb(feedback), m_interp(interpolate), m_writePos(0), UGen(vsiz, sr)
	{
		std::fill(m_delLine.begin(), m_delLine.end(), 0.);
	};

	/** Delay constructor. \n
		signalIn - input audio signal. \n
		maxDel - max value of delay. \n
		del - current value of delay. \n
		feedback - amount of feedback (should not exceed 1). \n
		interpolate - allow for linear interpolation. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Delay(UGen& signalIn, double maxDel, double del, UGen& feedback, bool interpolate = false,
		size_t vsiz = def_vsize, double sr = def_sr) :
		m_sigIn(signalIn), m_delVal(del != -1 ? del : maxDel), m_delLine(maxDel >= 0. ? (size_t)std::ceil((maxDel * sr)) : 1),
		m_fb(feedback), m_interp(interpolate), m_writePos(0), UGen(vsiz, sr)
	{
		std::fill(m_delLine.begin(), m_delLine.end(), 0.);
	};

	/** Delay constructor. \n
		signalIn - input audio signal. \n
		maxDel - max value of delay. \n
		del - current value of delay. \n
		feedback - amount of feedback (should not exceed 1). \n
		interpolate - allow for linear interpolation. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Delay(UGen& signalIn, double maxDel, UGen& del, UGen& feedback, bool interpolate = true,
		size_t vsiz = def_vsize, double sr = def_sr) :
		m_sigIn(signalIn), m_delVal(del), m_delLine(maxDel >= 0. ? (size_t)std::ceil((maxDel * sr)) : 1),
		m_fb(feedback), m_interp(interpolate), m_writePos(0), UGen(vsiz, sr)
	{
		std::fill(m_delLine.begin(), m_delLine.end(), 0.);
	};

	void setDel(double val) { m_delVal.set(val); }
	void setDel(UGen& modulator) { m_delVal.set(modulator); }

	void setFeedback(double val) { m_fb.set(val); }
	void setFeedback(UGen& modulator) { m_fb.set(modulator); }

	void setInterp(bool val) { m_interp = val; }

	/** Get the current write position.
	*/
	size_t getWritePos() const { return m_writePos; }

	/** Get the current state of the delay line.
	*/
	const std::vector<double>& getDelayline() const { return m_delLine; }

protected:
	UGenParam m_delVal;
	UGenParam m_fb;

	void dsp() override;

private:
	UGen& m_sigIn;
	std::vector<double> m_delLine;
	bool m_interp;
	size_t m_writePos;

	/** Get the corresponding sample of feedback on the position of the audio vector.
	*/
	virtual double getFb(size_t pos);
};

}
#endif