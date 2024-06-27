/////////////////////////////////////////////////////////////////////
// Osc class: oscillator with no interpolation
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _OSC_H_
#define _OSC_H_
#include "FuncTab.h"
#include "UGen.h"
#include "Phasor.h"
#include "TableRead.h"

namespace KiwiWaves
{

/** Truncating oscillator with no interpolation.
*/
class Osc : public UGen
{
public:
	/** Osc constructor. \n
		amp - amplitude. \n
		fr - frequency. \n
		tab - table to read. \n
		ph - normalized phase offset. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Osc(double amp, double fr, const FuncTab& tab,
		double ph = 0., double dco = 0., size_t vsiz = def_vsize, double sr = def_sr) :
		m_amp(amp), m_ph(fr, ph, vsiz, sr), m_tr(m_ph, tab, true, true, vsiz, sr), m_dcoff(dco),
		UGen(vsiz, sr) { };

	/** Osc constructor. \n
		amp - amplitude. \n
		fr - frequency. \n
		tab - table to read. \n
		ph - normalized phase offset. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Osc(double amp, UGen& fr, const FuncTab& tab,
		double ph = 0., double dco = 0., size_t vsiz = def_vsize, double sr = def_sr) :
		m_amp(amp), m_ph(fr, ph, vsiz, sr), m_tr(m_ph, tab, true, true, vsiz, sr), m_dcoff(dco),
		UGen(vsiz, sr) { };

	/** Osc constructor. \n
		amp - amplitude. \n
		fr - frequency. \n
		tab - table to read. \n
		ph - normalized phase offset. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Osc(UGen& amp, double fr, const FuncTab& tab,
		double ph = 0., double dco = 0., size_t vsiz = def_vsize, double sr = def_sr) :
		m_amp(amp), m_ph(fr, ph, vsiz, sr), m_tr(m_ph, tab, true, true, vsiz, sr), m_dcoff(dco),
		UGen(vsiz, sr) { };

	/** Osc constructor. \n
		amp - amplitude. \n
		fr - frequency. \n
		tab - table to read. \n
		ph - normalized phase offset. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Osc(UGen& amp, UGen& fr, const FuncTab& tab,
		double ph = 0., double dco = 0., size_t vsiz = def_vsize, double sr = def_sr) :
		m_amp(amp), m_ph(fr, ph, vsiz, sr), m_tr(m_ph, tab, true, true, vsiz, sr), m_dcoff(dco),
		UGen(vsiz, sr) { };

	void setFreq(double val) { m_ph.setFreq(val); }
	void setFreq(UGen& modulator) { m_ph.setFreq(modulator); }

	void setAmp(double val) { m_amp.set(val); }
	void setAmp(UGen& modulator) { m_amp.set(modulator); }

protected:
	/** Protected Osc constructor for setting different
		Phasors and TableReads in derived classes constructors. \n
		amp - amplitude. \n
		ph - phasor. \n
		tr - table read. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Osc(UGen& amp, Phasor ph, TableRead tr,
		double dco = 0., size_t vsiz = def_vsize, double sr = def_sr) :
		m_amp(amp), m_ph(ph), m_tr(tr), m_dcoff(dco),
		UGen(vsiz, sr) { };

	/** Protected Osc constructor for setting different
		Phasors and TableReads in derived classes constructors. \n
		amp - amplitude. \n
		ph - phasor. \n
		tr - table read. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Osc(double amp, Phasor ph, TableRead tr,
		double dco = 0., size_t vsiz = def_vsize, double sr = def_sr) :
		m_amp(amp), m_ph(ph), m_tr(tr), m_dcoff(dco),
		UGen(vsiz, sr) { };

	Phasor m_ph;

	void dsp() override;

private:
	UGenParam m_amp;
	TableRead m_tr;
	double m_dcoff;
};

/** Linear interpolation oscillator.
 */
class OscI : public Osc
{
public:
	/** OscI constructor. \n
		amp - amplitude. \n
		fr - frequency. \n
		tab - table to read. \n
		ph - normalized phase offset. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	OscI(double amp, double fr, const FuncTab& tab, double ph = 0., double dco = 0.,
		size_t vsiz = def_vsize, double sr = def_sr) :
		Osc(amp, Phasor(fr, ph, vsiz, sr), TableReadI(m_ph, tab, true, true, vsiz, sr), dco, vsiz, sr) {};

	/** OscI constructor. \n
		amp - amplitude. \n
		fr - frequency. \n
		tab - table to read. \n
		ph - normalized phase offset. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	OscI(double amp, UGen& fr, const FuncTab& tab, double ph = 0., double dco = 0.,
		size_t vsiz = def_vsize, double sr = def_sr) :
		Osc(amp, Phasor(fr, ph, vsiz, sr), TableReadI(m_ph, tab, true, true, vsiz, sr), dco, vsiz, sr) {};

	/** OscI constructor. \n
		amp - amplitude. \n
		fr - frequency. \n
		tab - table to read. \n
		ph - normalized phase offset. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	OscI(UGen& amp, double fr, const FuncTab& tab, double ph = 0., double dco = 0.,
		size_t vsiz = def_vsize, double sr = def_sr) :
		Osc(amp, Phasor(fr, ph, vsiz, sr), TableReadI(m_ph, tab, true, true, vsiz, sr), dco, vsiz, sr) {};

	/** OscI constructor. \n
		amp - amplitude. \n
		fr - frequency. \n
		tab - table to read. \n
		ph - normalized phase offset. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	OscI(UGen& amp, UGen& fr, const FuncTab& tab, double ph = 0., double dco = 0.,
		size_t vsiz = def_vsize, double sr = def_sr) :
		Osc(amp, Phasor(fr, ph, vsiz, sr), TableReadI(m_ph, tab, true, true, vsiz, sr), dco, vsiz, sr) {};
};

/** Cubic interpolation oscillator.
 */
class OscC : public Osc
{
public:
	/** OscC constructor. \n
		amp - amplitude. \n
		fr - frequency. \n
		tab - table to read. \n
		ph - normalized phase offset. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	OscC(double amp, double fr, const FuncTab& tab, double ph = 0., double dco = 0.,
		size_t vsiz = def_vsize, double sr = def_sr) :
		Osc(amp, Phasor(fr, ph, vsiz, sr), TableReadI(m_ph, tab, true, true, vsiz, sr), dco, vsiz, sr) {};

	/** OscC constructor. \n
		amp - amplitude. \n
		fr - frequency. \n
		tab - table to read. \n
		ph - normalized phase offset. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	OscC(double amp, UGen& fr, const FuncTab& tab, double ph = 0., double dco = 0.,
		size_t vsiz = def_vsize, double sr = def_sr) :
		Osc(amp, Phasor(fr, ph, vsiz, sr), TableReadI(m_ph, tab, true, true, vsiz, sr), dco, vsiz, sr) {};

	/** OscC constructor. \n
		amp - amplitude. \n
		fr - frequency. \n
		tab - table to read. \n
		ph - normalized phase offset. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	OscC(UGen& amp, double fr, const FuncTab& tab, double ph = 0., double dco = 0.,
		size_t vsiz = def_vsize, double sr = def_sr) :
		Osc(amp, Phasor(fr, ph, vsiz, sr), TableReadI(m_ph, tab, true, true, vsiz, sr), dco, vsiz, sr) {};

	/** OscC constructor. \n
		amp - amplitude. \n
		fr - frequency. \n
		tab - table to read. \n
		ph - normalized phase offset. \n
		dco - DC offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	OscC(UGen& amp, UGen& fr, const FuncTab& tab, double ph = 0., double dco = 0.,
		size_t vsiz = def_vsize, double sr = def_sr) :
		Osc(amp, Phasor(fr, ph, vsiz, sr), TableReadI(m_ph, tab, true, true, vsiz, sr), dco, vsiz, sr) {};
};

}
#endif
