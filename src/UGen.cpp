////////////////////////////////////////////////////////////////////
// Implementation of the UGen class
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#include "UGen.h"

using namespace KiwiWaves;

const double* UGen::process()
{
	dsp();
	return m_s.data();
}

const double* UGen::data()
{
	return m_s.data();
}

const double& UGen::operator [](const size_t& idx) const
{
	return m_s[idx];
}

const UGen& UGen::operator+=(const UGen& other)
{
	for (size_t i = 0; i < m_s.size(); i++)
		m_s[i] += other.m_s[i];

	return *this;
}

const UGen UGen::operator+(const UGen& other) const
{
	UGen n(*this);
	n += other;
	return n;
}

const UGen& UGen::operator+=(const double& val)
{
	for (size_t i = 0; i < m_s.size(); i++)
		m_s[i] += val;

	return *this;
}

const UGen UGen::operator+(const double& val) const
{
	UGen n(*this);
	n += val;
	return n;
}

const UGen& UGen::operator-=(const UGen& other)
{
	for (size_t i = 0; i < m_s.size(); i++)
		m_s[i] -= other.m_s[i];

	return *this;
}

const UGen UGen::operator-(const UGen& other) const
{
	UGen n(*this);
	n -= other;
	return n;
}

const UGen& UGen::operator-=(const double& val)
{
	for (size_t i = 0; i < m_s.size(); i++)
		m_s[i] -= val;

	return *this;
}

const UGen UGen::operator-(const double& val) const
{
	UGen n(*this);
	n -= val;
	return n;
}

const UGen& UGen::operator*=(const UGen& other)
{
	for (size_t i = 0; i < m_s.size(); i++)
		m_s[i] *= other.m_s[i];

	return *this;
}

const UGen UGen::operator*(const UGen& other) const
{
	UGen n(*this);
	n *= other;
	return n;
}

const UGen& UGen::operator*=(const double& scalar)
{
	for (size_t i = 0; i < m_s.size(); i++)
		m_s[i] *= scalar;

	return *this;
}

const UGen UGen::operator*(const double& scalar) const
{
	UGen n(*this);
	n *= scalar;
	return n;
}

const UGen& UGen::operator/=(const UGen& other)
{
	for (size_t i = 0; i < m_s.size(); i++)
		m_s[i] /= other.m_s[i];

	return *this;
}

const UGen UGen::operator/(const UGen& other) const
{
	UGen n(*this);
	n /= other;
	return n;
}

const UGen& UGen::operator/=(const double& scalar)
{
	for (size_t i = 0; i < m_s.size(); i++)
		m_s[i] /= scalar;

	return *this;
}

const UGen UGen::operator/(const double& scalar) const
{
	UGen n(*this);
	n /= scalar;
	return n;
}

void KiwiWaves::UGen::fillDataToZero()
{
	std::fill(m_s.begin(), m_s.end(), 0.);
}

void KiwiWaves::UGen::fillDataToOne()
{
	std::fill(m_s.begin(), m_s.end(), 1.);
}
