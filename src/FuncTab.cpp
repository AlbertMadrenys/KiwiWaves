////////////////////////////////////////////////////////////////////
// Implementation of the FuncTab class
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include "FuncTab.h"

using namespace KiwiWaves;

const double& FuncTab::operator[](size_t idx) const
{
    return m_table[idx];
}

void FuncTab::normalize()
{
    size_t n;
    double max = 0.;
    for (n = 0; n < m_table.size(); n++)
        max = m_table[n] > max ? m_table[n] : max;

    if (max)
    {
        for (n = 0; n < m_table.size(); n++)
            m_table[n] /= max;
    }    
}