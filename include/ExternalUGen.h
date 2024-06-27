/////////////////////////////////////////////////////////////////////
// ExternalUgen class: Vector wrapper useful to make the data
// compatible with KiwiWaves features
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _EXTERNALUGEN_H_
#define _EXTERNALUGEN_H_
#include "UGen.h"

namespace KiwiWaves
{

/** Vector wrapper useful to make the data
	compatible with KiwiWaves features.
*/
class ExternalUGen : public UGen
{
public:
	/** ExternalUGen constructor. \n
		vsiz - number of frames in vector.\n
		sr - sampling rate.
	*/
	ExternalUGen(size_t vsiz = def_vsize, double sr = def_sr) : KiwiWaves::UGen(vsiz, sr) { };

	/** Set the data vector to a sig array.
	*/
	void setData(const double* data, size_t size)
	{
		std::copy(data, data + size, m_s.begin());
	}

	/** Set the data vector to a sig vector.
	*/
	void setData(std::vector<double>& data)
	{
		m_s = data;
	}

	/** Fill the entire audio vector with a value.
	*/
	void setData(double val)
	{
		std::fill(m_s.begin(), m_s.end(), val);
	}

	/** Set a the value of a single sample at
		position idx off the data vector.
	*/
	void setData(double val, size_t pos)
	{
		m_s[pos] = val;
	}
};

}

#endif