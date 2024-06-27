////////////////////////////////////////////////////////////////////
// Implementation of the LowP, HighP, BandP and BandR classes
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include "Butterworth.h"

using namespace KiwiWaves;

bool LowP::prepareUpdate(const size_t& indx)
{
    if (m_freq != m_cutFreq[indx])
    {
        m_freq = m_cutFreq[indx];
        return true;
    }
    return false;
}

void LowP::update() {
    double l = 1 / tan(pi * m_freq / m_sr);
    double sqrt2l = sqrt(2.) * l;
    double lsq = l * l;
    m_a[0] = 1. / (1. + sqrt2l + lsq);
    m_a[1] = 2. * m_a[0];
    m_a[2] = m_a[0];
    m_b[0] = 2. * (1. - lsq) * m_a[0];
    m_b[1] = (1. - sqrt2l + lsq) * m_a[0];
}

void HighP::update() {
    double l = tan(pi * m_freq / m_sr);
    double sqrt2l = sqrt(2.) * l;
    double lsq = l * l;
    m_a[0] = 1. / (1. + sqrt2l + lsq);
    m_a[1] = -2. * m_a[0];
    m_a[2] = m_a[0];
    m_b[0] = 2. * (lsq - 1.) * m_a[0];
    m_b[1] = (1. - sqrt2l + lsq) * m_a[0];
}

bool BandP::prepareUpdate(const size_t& indx)
{
    if (m_freq != m_cutFreq[indx] || m_bw != m_band[indx])
    {
        m_freq = m_cutFreq[indx];
        m_bw = m_band[indx];
        return true;
    }
    return false;
}

void BandP::update() {
    double l = 1. / tan(pi * m_bw / m_sr);
    double cosl = 2. * cos(2 * pi * m_freq / m_sr);
    m_a[0] = 1. / (1. + l);
    m_a[1] = 0;
    m_a[2] = -m_a[0];
    m_b[0] = -l * cosl * m_a[0];
    m_b[1] = (l - 1.) * m_a[0];
}

void BandR::update() {
    double l = tan(pi * m_bw / m_sr);
    double cosl = 2. * cos(2 * pi * m_freq / m_sr);
    m_a[0] = 1. / (1. + l);
    m_a[1] = -cosl * m_a[0];
    m_a[2] = m_a[0];
    m_b[0] = m_a[1];
    m_b[1] = (1. - l) * m_a[0];
}