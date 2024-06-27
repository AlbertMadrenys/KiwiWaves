////////////////////////////////////////////////////////////////////
// Implementation of the Phasor class
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
#include "Phasor.h"

using namespace KiwiWaves;

void Phasor::dsp()
{
	for (size_t i = 0; i < m_s.size(); i++)
	{
		m_s[i] = m_ph;
		m_ph += m_fr[i] / m_sr;
		m_ph = m_ph - floor(m_ph); // mod1
	}
}