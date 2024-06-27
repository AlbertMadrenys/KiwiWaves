////////////////////////////////////////////////////////////////////
// Implementation of the Osc class
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include "Osc.h"

using namespace KiwiWaves;

void Osc::dsp()
{
	// An oscillator is reading a table with the index dictated by a phasor,
	// multiplied by an amplitude and adding the DC offset.

	m_ph.process();
	m_tr.process();

	for (size_t i = 0; i < m_s.size(); i++) {
		m_s[i] = m_tr[i] * m_amp[i] + m_dcoff;
	}
}