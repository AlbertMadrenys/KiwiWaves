////////////////////////////////////////////////////////////////////
// Implementation of the SegmentEnv class
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include "SegmentEnv.h"
#include <cmath>

using namespace KiwiWaves;

void SegmentEnv::dsp()
{
	if (!m_validVectorSizes)
		return;

	for (size_t i = 0; i < m_s.size(); i++) {
		m_s[i] = m_val + m_offset;

		if (m_count < m_times[m_ind] * m_sr) {
			if (m_curves[m_ind] == linear) m_val += m_incr;
			else if (m_curves[m_ind] == exponential) m_val *= m_incr;
			m_count++;
		}
		else
		{
			m_val = m_levels[m_ind + 1];
			// Start the next segment only if there's more, except when the last segment is release.
			// In that case, hold the end of the last two segments
			if ((int)m_ind < ((int)m_times.size() - 2) || (!m_releaseSeg && m_ind < (m_times.size() - 1)))
			{
				startSegment(m_ind + 1);
			}
		}
	}
}

void SegmentEnv::retrig()
{
	m_val = m_levels[0];
	startSegment(0);
}

void SegmentEnv::release()
{
	if (m_releaseSeg)
	{
		startSegment((unsigned int)m_times.size()-1);
	}
}

void SegmentEnv::startSegment(unsigned int newSeg = 0)
{
	m_ind = newSeg;
	m_count = 0;

	if (m_curves[m_ind] == exponential)
	{
		solveZeros();
		m_incr = pow((m_levels[m_ind + 1] / m_levels[m_ind]), 1 / (m_times[m_ind] * sr()));
	}	
	else if (m_curves[m_ind] == linear)
	{
		m_incr = (m_levels[m_ind + 1] - m_levels[m_ind]) / (m_times[m_ind] * sr());
	}
}

void SegmentEnv::solveZeros()
{
	if (m_levels[m_ind] == 0. && m_levels[m_ind + 1] >= 0.) m_levels[m_ind] = imperceptible_db;
	else if (m_levels[m_ind] == 0.) m_levels[m_ind] = -imperceptible_db;
	if (m_levels[m_ind + 1] == 0. && m_levels[m_ind] >= 0.) m_levels[m_ind + 1] = imperceptible_db;
	else if (m_levels[m_ind + 1] == 0.) m_levels[m_ind + 1] = -imperceptible_db;
}

bool SegmentEnv::checkVectorSizes()
{
	m_validVectorSizes = true;

	m_validVectorSizes &= (m_times.size() != m_curves.size());
	m_validVectorSizes &= (m_times.size() >= 1);
	m_validVectorSizes &= (m_levels.size() >= 2);
	m_validVectorSizes &= (m_levels.size() - m_times.size() == 1);
	m_validVectorSizes &= (m_times.size() >= 2 && m_releaseSeg);
	m_validVectorSizes &= (m_levels.size() >= 1 && m_releaseSeg);
	m_validVectorSizes &= (m_curves.size() >= 1 && m_releaseSeg);

	return m_validVectorSizes;
}
