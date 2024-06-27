/////////////////////////////////////////////////////////////////////
// Envelopes: commonly used envelopes
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _ENVELOPES_H_
#define _ENVELOPES_H_
#include "SegmentEnv.h"
#include <vector>

namespace KiwiWaves 
{

/** Trace a straight line between two specified levels.
*/
class Line : public SegmentEnv
{
public:
	/** Line constructor. \n
		start - start level. \n
		end - end level. \n
		time - duration. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	Line(double start, double end, double time, size_t vsiz = def_vsize, double sr = def_sr) :
		SegmentEnv(start, end, time, linear, 0., false, vsiz, sr) { };
};

/** Trace an exponential curve between two specified levels.
*/
class ExpCurve : public SegmentEnv
{
public:
	/** ExpCurve constructor. \n
		start - start level. \n
		end - end level. \n
		time - duration. \n
		offset - offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ExpCurve(double start, double end, double time, double offset = 0., size_t vsiz = def_vsize, double sr = def_sr) :
		SegmentEnv(start, end, time, exponential, offset, false, vsiz, sr) { };
};

/** Trace a series of line segments between specified levels.
*/
class LineSeg : public SegmentEnv
{
public:
	/** LineSeg constructor. \n
		levels - vector of the levels of each segment. \n
		times - vector of the times between segments. \n
		lastSegIsRelease - wait for release call to start the last segment. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	LineSeg(std::vector<double> levels, std::vector<double> times,
		bool lastSegIsRelease = false, size_t vsiz = def_vsize, double sr = def_sr) :
		SegmentEnv(levels, times, linear, 0., lastSegIsRelease, vsiz, sr) { };
};

/** Trace a series of exponential curves between specified levels.
*/
class ExpSeg : public SegmentEnv
{
public:
	/** ExpSeg constructor. \n
		levels - vector of the levels of each segment. \n
		times - vector of the times between segments. \n
		lastSegIsRelease - wait for release call to start the last segment. \n
		offset - offset to add. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ExpSeg(std::vector<double> levels, std::vector<double> times,
		bool lastSegIsRelease = false, double offset = 0., size_t vsiz = def_vsize, double sr = def_sr) :
		SegmentEnv(levels, times, exponential, offset, lastSegIsRelease, vsiz, sr) { };
};

/** Trace a straight line rise and decay pattern envelope.
*/
class LineEnv : public SegmentEnv
{
public:
	/** LineEnv constructor. \n
		timeAttack - duration of the attack. \n
		ampSustain - level of the sustain segment. \n
		totalTime - total duration. \n
		timeDecay - duration of the attack. \n
		lastSegIsRelease - wait for release call to start decaying. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	LineEnv(double timeAttack, double ampSustain, double totalTime, double timeDecay,
		bool lastSegIsRelease = false, size_t vsiz = def_vsize, double sr = def_sr) :
		SegmentEnv({ 0., ampSustain, ampSustain, 0. }, { timeAttack, totalTime - timeAttack - timeDecay, timeDecay },
			linear, 0., lastSegIsRelease, vsiz, sr) { };
};

/** Trace an exponential curve rise and decay pattern envelope.
*/
class ExpEnv : public SegmentEnv
{
public:
	/** ExpEnv constructor. \n
		timeAttack - duration of the attack. \n
		ampSustain - level of the sustain segment. \n
		totalTime - total duration. \n
		timeDecay - duration of the attack. \n
		lastSegIsRelease - wait for release call to start decaying. \n
		attFactor - near-zero value for starting and ending the envelope.
		Will impact the steepness of the curve. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ExpEnv(double timeAttack, double ampSustain, double totalTime, double timeDecay,
		bool lastSegIsRelease = false, double attFactor = def_exp_curve_offset,
		size_t vsiz = def_vsize, double sr = def_sr) :
		SegmentEnv({ attFactor, ampSustain+ attFactor, ampSustain+attFactor, attFactor }, { timeAttack, totalTime - timeAttack - timeDecay, timeDecay },
			exponential, -attFactor, lastSegIsRelease, vsiz, sr) { };
};

/** Trace the classical ADSR envelope using linear segments.
*/
class LineAdsr : public SegmentEnv
{
public:
	/** LineAdsr constructor. \n
		timeAttack - duration of the attack. \n
		ampAttack - end level of the attack segment. \n
		timeDecay - duration of the attack. \n
		ampSustain - level of the sustain segment. \n
		timeRelease - duration of the release. \n
		lastSegIsRelease - wait for release call to start releasing. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	LineAdsr(double timeAttack, double ampAttack, double timeDecay, double ampSustain, double timeRelease,
		bool lastSegIsRelease = true, size_t vsiz = def_vsize, double sr = def_sr) :
		SegmentEnv({ 0., ampAttack, ampSustain, 0. }, { timeAttack, timeDecay, timeRelease },
			linear, 0., lastSegIsRelease, vsiz, sr) { };
};

/** Trace the classical ADSR envelope using exponential curves.
*/
class ExpAdsr : public SegmentEnv
{
public:
	/** ExpAdsr constructor. \n
		timeAttack - duration of the attack. \n
		ampAttack - end level of the attack segment. \n
		timeDecay - duration of the attack. \n
		ampSustain - level of the sustain segment. \n
		timeRelease - duration of the release. \n
		lastSegIsRelease - wait for release call to start releasing. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	ExpAdsr(double timeAttack, double ampAttack, double timeDecay, double ampSustain, double timeRelease,
		bool lastSegIsRelease = true, size_t vsiz = def_vsize, double sr = def_sr) :
		SegmentEnv({ def_exp_curve_offset, ampAttack + def_exp_curve_offset, ampSustain + def_exp_curve_offset, def_exp_curve_offset },
			{ timeAttack, timeDecay, timeRelease }, exponential, -def_exp_curve_offset, lastSegIsRelease, vsiz, sr) { };
};


}
#endif