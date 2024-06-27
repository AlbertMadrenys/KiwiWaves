////////////////////////////////////////////////////////////////////
// Implementation of the Rms class
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include "Rms.h"

using namespace KiwiWaves;

double Rms::rect(double x) { return x < 0.0 ? -x : x; }

void Rms::dsp()
{
    for (size_t i = 0; i < m_s.size(); i++)
    {
        if (m_freq != m_cutFreq[i])
        {
            m_freq = m_cutFreq[i];
            update();
        }

        m_del = m_a * rect(m_sigIn[i]) - m_b * m_del;
        m_s[i] = m_del;
    }
}