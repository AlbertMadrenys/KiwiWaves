////////////////////////////////////////////////////////////////////
// Implementation of the TableRead class
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include <cmath>
#include <algorithm>
#include "TableRead.h"

using namespace KiwiWaves;

double TableRead::getRawIndex(const size_t& indx)
{
	double tabPos = m_ind[indx] * (m_norm ? m_table.size() : 1); // normalization to table size scale
	if (m_wrap) tabPos = fmod(tabPos, m_table.size()); // wrap
	else tabPos = std::max(0., std::min(tabPos, (double)m_table.size())); // clamp
	return tabPos;
}

void TableRead::dsp()
{
	for (size_t i = 0; i < m_s.size(); i++)
		m_s[i] = m_table[(int)getRawIndex(i)]; // truncation
}

void TableReadI::dsp()
{
	double raw, a, b;
	size_t posi, s = m_s.size();
	for (size_t i = 0; i < s ; i++)
	{
		raw = getRawIndex(i);
		posi = (unsigned int)raw;
		a = m_table[posi];
		b = posi < s - 1 ? m_table[posi + 1] : m_table[0];
		m_s[i] = a + (raw - (double)posi) * (b - a); // linear interpolation
	}
}

void TableReadC::dsp()
{
	double frac, raw;
	double a, b, c, d;
	double tmp, fracsq, fracb;
	size_t posi, s = m_s.size();
	for (size_t i = 0; i < s; i++)
	{
		raw = getRawIndex(i);
		posi = (int)raw;
		frac = raw - posi;
		a = posi > 0 ? m_table[posi - 1] : m_table[s - 1];
		b = m_table[posi];
		c = posi + 1 < s ? m_table[posi + 1] : m_table[0];
		d = posi + 2 < s ? m_table[posi + 2] : m_table[posi + 2 - s];
		tmp = d + 3.f * b;
		fracsq = frac * frac;
		fracb = frac * fracsq;
		m_s[i] = fracb * (-a - 3.f * c + tmp) / 6.f +
			fracsq * ((a + c) / 2.f - b) +
			frac * (c + (-2.f * a - tmp) / 6.f) + b; // cubic interpolation
	}
}