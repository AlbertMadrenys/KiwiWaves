/////////////////////////////////////////////////////////////////////
// SegmentEnv class: multi-segment envelope generator
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _SEGMENTENV_H_
#define _SEGMENTENV_H_
#include "UGen.h"
#include <vector>

namespace KiwiWaves
{

/** Multi-segment envelope generator.
*/
class SegmentEnv : public UGen
{
public:
	/** SegmentEnv constructor. \n
		levels - vector of the levels of each segment. \n
		times - vector of the times between segments. \n
		curves - transition curves between segments.\n
		offset - offset to add. \n
		lastSegIsRelease - wait for release call to start the last segment. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	SegmentEnv(std::vector<double> levels, std::vector<double> times, std::vector<Curve> curves,
		double offset = 0., bool lastSegIsRelease = false, size_t vsiz = def_vsize, double sr = def_sr) :
		m_levels(levels), m_times(times), m_curves(curves),
		m_offset(offset), m_releaseSeg(lastSegIsRelease), m_validVectorSizes(true),
		UGen(vsiz, sr)
	{
		if (!checkVectorSizes()) fillDataToZero();
		solveZeros();
		retrig();
	};

	/** SegmentEnv constructor. \n
		levels - vector of the levels of each segment. \n
		times - vector of the times between segments. \n
		curve - transition curve between segments.\n
		offset - offset to add. \n
		lastSegIsRelease - wait for release call to start the last segment. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	SegmentEnv(std::vector<double> levels, std::vector<double> times, Curve curve = linear,
		double offset = 0., bool lastSegIsRelease = false, size_t vsiz = def_vsize, double sr = def_sr) :
		m_levels(levels), m_times(times), m_curves(std::vector<Curve>(times.size(), curve)),
		m_offset(offset), m_releaseSeg(lastSegIsRelease), m_validVectorSizes(true), 
		UGen(vsiz, sr)
	{
		if (!checkVectorSizes()) fillDataToZero();
		retrig();
	};

	/** SegmentEnv constructor. \n
		start - start level of a single segment. \n
		end - end level of a single segment. \n
		time - time of the segment. \n
		curve - transition curve.\n
		offset - offset to add. \n
		lastSegIsRelease - wait for release call to start the segment. \n
		vsiz - number of frames in vector. \n
		sr - sampling rate.
	*/
	SegmentEnv(double start, double end, double time, Curve curve = linear,
		double offset = 0., bool lastSegIsRelease = false, size_t vsiz = def_vsize, double sr = def_sr) :
		m_levels{start, end}, m_times{time}, m_curves{curve},
		m_offset(offset), m_releaseSeg(lastSegIsRelease), m_validVectorSizes(true), 
		UGen(vsiz, sr)
	{
		if (!checkVectorSizes()) fillDataToZero();
		retrig();
	};

	/** Start the envelope from the beggining.
	*/
	virtual void retrig();

	/** Start the last segment of release if any.
	*/
	void release();

protected:
	void dsp() override;

private:
	std::vector<double> m_levels, m_times;
	std::vector<Curve> m_curves;
	unsigned int m_count, m_ind;
	double m_offset, m_val, m_incr;
	bool m_releaseSeg, m_validVectorSizes;

	/** Start new segment.
	*/
	void startSegment(unsigned int newSegment);

	/** True if the vector m_levels, m_times and m_curves are correct.
	*/
	bool checkVectorSizes();

	/** Solve zero level values in exponential curves.
	*/
	void solveZeros();
};

}
#endif