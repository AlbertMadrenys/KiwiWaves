////////////////////////////////////////////////////////////////////
// Implementation of the Balance class
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include "Balance.h"

using namespace KiwiWaves;

void Balance::dsp()
{
    m_rmsSig.process();
    m_rmsComp.process();

    for (size_t i = 0; i < m_s.size(); i++)
    {
        switch (m_zeroHandling)
        {
        case addSmallNumber:
            m_s[i] = m_sigIn[i] * (m_rmsComp[i] / (m_rmsSig[i] > 0. ? m_rmsSig[i] : min_double));
            break;
        case equalToOne:
            m_s[i] = m_sigIn[i] * (m_rmsSig[i] > 0. ? m_rmsComp[i] / m_rmsSig[i] : 1.);
            break;
        default:
            // Default is addSmallNumber
            m_s[i] = m_sigIn[i] * (m_rmsComp[i] / (m_rmsSig[i] > 0. ? m_rmsSig[i] : min_double));
        }
    }
}
