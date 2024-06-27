/////////////////////////////////////////////////////////////////////
// FuncTab class: function tables
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _FUNCTAB_H_
#define _FUNCTAB_H_
#include <vector>
#include "KiwiWaves.h"

namespace KiwiWaves
{

/** Function table base class.
*/
class FuncTab
{
public:
	/** FuncTab constructor from vector. \n
		in - source vector. \n
		tsiz - table size.
	*/
	FuncTab(const double* in, size_t tsiz = def_tsize) : m_table(in, in + tsiz) { }

	/** FuncTab constructor. \n
		tsiz - table size.
	*/
	FuncTab(size_t tsiz = def_tsize) : m_table(tsiz) { }

	/** FuncTab constructor from vector. \n
		in - source vector. \n
	*/
	FuncTab(std::vector<double>& in) : m_table(in) { };

	/** Virtual destructor.
	*/
	virtual ~FuncTab() {};

	/** Get a reference of a single value at
		position idx off the table.
	*/
	virtual const double& operator [](size_t idx) const;

	/** Get the table size.
	*/
	const size_t size() const { return m_table.size(); }

protected:
	/** Normalise the table.
	*/
	void normalize();

	std::vector<double> m_table;
};

/** Sine wave function table.
*/
class SinTab : public FuncTab
{
public:
	/** SinTab constructor. \n
		tsiz - table size. \n
		amplitude - table size. \n
		ph - normalized phase offset.
	*/
	SinTab(size_t tsiz = def_tsize, double amp = 1., double ph = 0.) : FuncTab(tsiz) {
		ph *= twopi;
		for (size_t i = 0; i < m_table.size(); i++)
			m_table[i] = amp * sin((i * twopi / m_table.size()) + ph);
	}
};

}

#endif