////////////////////////////////////////////////////////////////////
// Implementation of the FourierTab class
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include "FourierTab.h"
#include <cmath>

using namespace KiwiWaves;

void FourierTab::fillTable(const std::vector<double>& harmAmps, double ph, bool norm)
{
	double sample;
	ph *= twopi;
	for (size_t i = 0; i < m_table.size(); i++)
	{
		sample = 0;
		for (size_t j = 0; j < harmAmps.size(); j++)
		{
			sample += harmAmps[j] * sin((i * twopi * (j + 1) / m_table.size()) + ph);
		}
		m_table[i] = sample;
	}

	if (norm) normalize();
}