////////////////////////////////////////////////////////////////////
// Implementation of the Delay and Comb classes
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include "Delay.h"
#include "Comb.h"

using namespace KiwiWaves;

void Delay::dsp()
{
    double delSample;
    double a, b;
    double readPos;
    size_t readPosI;
    for (size_t i = 0; i < m_s.size(); i++)
    {
        delSample = (m_delVal[i] < 0. ? 0. : m_delVal[i] * m_sr);
        if (delSample > (double)m_delLine.size())
            delSample = (double)m_delLine.size();

        readPos = (double)m_writePos - delSample;
        if (readPos < 0.)
            readPos += (double)m_delLine.size();

        readPosI = (size_t)readPos < m_delLine.size()-1 ? (size_t)readPos : m_delLine.size()-1;

        if (m_interp)
        {
            a = m_delLine[readPosI];
            b = readPosI < m_delLine.size() - 1 ? m_delLine[readPosI + 1] : m_delLine[0];
            m_s[i] = a + (readPos - (double)readPosI) * (b - a); // linear interpolation
        }
        else
        {
            m_s[i] = m_delLine[readPosI]; // no interp
        }

        m_delLine[m_writePos] = m_sigIn[i] + getFb(i);
        m_writePos = m_writePos >= m_delLine.size() - 1 ? 0 : m_writePos + 1;
    }
}

double Delay::getFb(size_t pos)
{
    return m_s[pos] * m_fb[pos];
}

double Comb::getFb(size_t pos)
{
    if (m_currentRT60 != m_fb[pos] || m_currentDel != m_delVal[pos] || m_currentFb == -1.)
    {
        // in the Comb class, m_fb is used to store the RT60 values instead of the feedback
        m_currentRT60 = m_fb[pos]; 
        m_currentDel = m_delVal[pos];
        m_currentFb = pow(0.001, m_currentDel / m_currentRT60);
    }

    return m_s[pos] * m_currentFb;
}
