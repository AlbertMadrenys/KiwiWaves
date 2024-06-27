////////////////////////////////////////////////////////////////////
// Implementation of the ToneLP and ToneHP classes
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include "Tone.h"
#include <cmath>

using namespace KiwiWaves;

void ToneLP::dsp()
{
    for (size_t i = 0; i < m_s.size(); i++)
    {
        if (m_freq != m_cutFreq[i])
        {
            m_freq = m_cutFreq[i];
            update();
        }

        m_del = m_a * m_sigIn[i] - m_b * m_del;
        m_s[i] = m_del;
    }
}

void ToneLP::update()
{
    double costh = 2. - cos(2. * pi * m_freq / m_sr);
    m_b = sqrt(costh * costh - 1.) - costh;
    m_a = (1. + m_b);
}

void ToneHP::update()
{
    double costh = 2. + cos(2. * pi * m_freq / m_sr);
    m_b = costh - sqrt(costh * costh - 1.);
    m_a = (1. + m_b);
}
