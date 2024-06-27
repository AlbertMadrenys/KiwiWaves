////////////////////////////////////////////////////////////////////
// Implementation of the Reson, ResonR, and ResonZ classes
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include "Reson.h"

using namespace KiwiWaves;

void ResonR::update()
{
    double r, rsq, rr, costh;
    r = exp(-m_bw * pi / m_sr);
    rr = 2. * r;
    rsq = r * r;
    costh = (rr / (1. + rsq)) * cos(2 * pi * m_freq / m_sr);
    m_scal = (1 - rsq) * sin(acos(costh));
    m_b[0] = -rr * costh;
    m_b[1] = rsq;
    m_a[2] = -r;
    m_a[0] = 1.;
    m_a[1] = 0;
}

void Reson::dsp() {
    double y;
    for (size_t i = 0; i < m_s.size(); i++)
    {
        if (prepareUpdate(i)) update();

        y = m_sigIn[i] * m_scal - m_b[0] * m_del[0] - m_b[1] * m_del[1];
        m_del[1] = m_del[0];
        m_s[i] = m_del[0] = y;
    }
}

void ResonZ::update()
{
    ResonR::update();
    m_a[2] = -1.;
}
