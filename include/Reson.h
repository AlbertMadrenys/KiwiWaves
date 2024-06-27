/////////////////////////////////////////////////////////////////////
// Reson: band-pass resonators
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _RESON_H_
#define _RESON_H_
#include "Butterworth.h"

namespace KiwiWaves
{

/** Band-pass resonator with better amplitude response at low frequencies.
*/
class ResonR : public BandP
{

public:
	/** ResonR constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ResonR(UGen& signalIn, double cenFreq, double band, size_t vsiz = def_vsize, double sr = def_sr)
		: BandP(signalIn, cenFreq, band, vsiz, sr)
	{
		update();
	};

	/** ResonR constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ResonR(UGen& signalIn, UGen& cenFreq, double band, size_t vsiz = def_vsize, double sr = def_sr)
		: BandP(signalIn, cenFreq, band, vsiz, sr)
	{
		update();
	};

	/** ResonR constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ResonR(UGen& signalIn, double cenFreq, UGen& band, size_t vsiz = def_vsize, double sr = def_sr)
		: BandP(signalIn, cenFreq, band, vsiz, sr)
	{
		update();
	};

	/** ResonR constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ResonR(UGen& signalIn, UGen& cenFreq, UGen& band, size_t vsiz = def_vsize, double sr = def_sr)
		: BandP(signalIn, cenFreq, band, vsiz, sr)
	{
		update();
	};

protected:
    void update() override;
};

/** Original band-pass resonator design.
*/
class Reson : public ResonR
{

public:
	/** Reson constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Reson(UGen& signalIn, double cenFreq, double band, size_t vsiz = def_vsize, double sr = def_sr)
		: ResonR(signalIn, cenFreq, band, vsiz, sr) { }

	/** Reson constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Reson(UGen& signalIn, UGen& cenFreq, double band, size_t vsiz = def_vsize, double sr = def_sr)
		: ResonR(signalIn, cenFreq, band, vsiz, sr) { }

	/** Reson constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Reson(UGen& signalIn, double cenFreq, UGen& band, size_t vsiz = def_vsize, double sr = def_sr)
		: ResonR(signalIn, cenFreq, band, vsiz, sr) { }

	/** Reson constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Reson(UGen& signalIn, UGen& cenFreq, UGen& band, size_t vsiz = def_vsize, double sr = def_sr)
		: ResonR(signalIn, cenFreq, band, vsiz, sr) { }

protected:
    void dsp() override;
};

/** Band-pass resonator with better amplitude response at low frequencies (alternative design).
*/
class ResonZ : public ResonR
{

public:
	/** ResonZ constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ResonZ(UGen& signalIn, double cenFreq, double band, size_t vsiz = def_vsize, double sr = def_sr)
		: ResonR(signalIn, cenFreq, band, vsiz, sr) { }

	/** ResonZ constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ResonZ(UGen& signalIn, UGen& cenFreq, double band, size_t vsiz = def_vsize, double sr = def_sr)
		: ResonR(signalIn, cenFreq, band, vsiz, sr) { }

	/** ResonZ constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ResonZ(UGen& signalIn, double cenFreq, UGen& band, size_t vsiz = def_vsize, double sr = def_sr)
		: ResonR(signalIn, cenFreq, band, vsiz, sr) { }

	/** ResonZ constructor. \n
		signalIn - input audio signal. \n
		cenFreq - center frequency. \n
		band - bandwidth. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ResonZ(UGen& signalIn, UGen& cenFreq, UGen& band, size_t vsiz = def_vsize, double sr = def_sr)
		: ResonR(signalIn, cenFreq, band, vsiz, sr) { }

protected:
    void update() override;
};

}

#endif