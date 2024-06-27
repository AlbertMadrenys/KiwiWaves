////////////////////////////////////////////////////////////////////
// Implementation of the Iir class
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
#include "Iir.h"

using namespace KiwiWaves;

void Iir::dsp() {
    double w;
    m_sigIn.process();

    for (size_t i = 0; i < m_s.size(); i++)
    {
        if (prepareUpdate(i)) update();

        // Direct Form II implementation
        w = m_scal * m_sigIn[i] - m_b[0] * m_del[0] - m_b[1] * m_del[1];
        m_s[i] = w * m_a[0] + m_a[1] * m_del[0] + m_a[2] * m_del[1];
        m_del[1] = m_del[0];
        m_del[0] = w;
    }
}