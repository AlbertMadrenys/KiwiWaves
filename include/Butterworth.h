/////////////////////////////////////////////////////////////////////
// Butterworth: low-pass, high-pass, band-pass and
// band-reject filters using Butterworth design
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _BUTTERWORTH_H_
#define _BUTTERWORTH_H_
#include "Iir.h"

namespace KiwiWaves
{

/** 2nd-order Butterworth low-pass filter.
*/
class LowP : public Iir
{

public:
	/** LowP constructor. \n
		signalIn - input audio signal. \n
		cutFreq - cutoff frequency. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	LowP(UGen& signalIn, double cutFreq, size_t vsiz = def_vsize, double sr = def_sr)
		: m_cutFreq(cutFreq), m_freq(0.), Iir(signalIn, vsiz, sr)
	{
		update();
	};

	/** LowP constructor. \n
		signalIn - input audio signal. \n
		cutFreq - cutoff frequency. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	LowP(UGen& signalIn, UGen& cutFreq, size_t vsiz = def_vsize, double sr = def_sr)
		: m_cutFreq(cutFreq), m_freq(0.), Iir(signalIn, vsiz, sr)
	{
		update();
	};

	void setCutFreq(double val) { m_cutFreq.set(val); }
	void setCutFreq(UGen& modulator) { m_cutFreq.set(modulator); }

protected:
	double m_freq;
	UGenParam m_cutFreq;

	void update() override;
	virtual bool prepareUpdate(const size_t& indx) override;
};

/** 2nd-order Butterworth high-pass filter.
*/
class HighP : public LowP
{

public:
	/** HighP constructor. \n
		signalIn - input audio signal. \n
		cutFreq - cutoff frequency. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	HighP(UGen& signalIn, double cutFreq, size_t vsiz = def_vsize, double sr = def_sr)
		: LowP(signalIn, cutFreq, vsiz, sr)
	{
		update();
	};

	/** HighP constructor. \n
		signalIn - input audio signal. \n
		cutFreq - cutoff frequency. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	HighP(UGen& signalIn, UGen& cutFreq, size_t vsiz = def_vsize, double sr = def_sr)
		: LowP(signalIn, cutFreq, vsiz, sr)
	{
		update();
	};

protected:
	void update() override;
};

/** 2nd-order Butterworth band-pass filter.
*/
class BandP : public LowP
{

public:
	/** BandP constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	BandP(UGen& signalIn, double cenFreq, double band, size_t vsiz = def_vsize, double sr = def_sr)
		: m_band(band), m_bw(0.), LowP(signalIn, cenFreq, vsiz, sr)
	{
		update();
	};

	/** BandP constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	BandP(UGen& signalIn, UGen& cenFreq, double band, size_t vsiz = def_vsize, double sr = def_sr)
		: m_band(band), m_bw(0.), LowP(signalIn, cenFreq, vsiz, sr)
	{
		update();
	};

	/** BandP constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	BandP(UGen& signalIn, double cenFreq, UGen& band, size_t vsiz = def_vsize, double sr = def_sr)
		: m_band(band), m_bw(0.), LowP(signalIn, cenFreq, vsiz, sr)
	{
		update();
	};

	/** BandP constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	BandP(UGen& signalIn, UGen& cenFreq, UGen& band, size_t vsiz = def_vsize, double sr = def_sr)
		: m_band(band), m_bw(0.), LowP(signalIn, cenFreq, vsiz, sr)
	{
		update();
	};

	void setBand(double val) { m_band.set(val); }
	void setBand(UGen& modulator) { m_band.set(modulator); }

protected:
	double m_bw;

	virtual bool prepareUpdate(const size_t& indx) override;
	void update() override;

private:
	UGenParam m_band;
};

/** 2nd-order Butterworth band-reject filter.
*/
class BandR : public BandP
{

public:
	/** BandR constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	BandR(UGen& signalIn, double cenFreq, double band, size_t vsiz = def_vsize, double sr = def_sr)
		: BandP(signalIn, cenFreq, band, vsiz, sr)
	{
		update();
	};

	/** BandR constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	BandR(UGen& signalIn, UGen& cenFreq, double band, size_t vsiz = def_vsize, double sr = def_sr)
		: BandP(signalIn, cenFreq, band, vsiz, sr)
	{
		update();
	};

	/** BandR constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	BandR(UGen& signalIn, double cenFreq, UGen& band, size_t vsiz = def_vsize, double sr = def_sr)
		: BandP(signalIn, cenFreq, band, vsiz, sr)
	{
		update();
	};

	/** BandR constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	BandR(UGen& signalIn, UGen& cenFreq, UGen& band, size_t vsiz = def_vsize, double sr = def_sr)
		: BandP(signalIn, cenFreq, band, vsiz, sr)
	{
		update();
	};

protected:
	void update() override;
};

}

#endif

