/////////////////////////////////////////////////////////////////////
// FourierTab class: Fourier series tables
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _FOURIERTAB_H_
#define _FOURIERTAB_H_
#include "FuncTab.h"
#include <vector>

namespace KiwiWaves
{

/** Function table based on Fourier series.
*/
class FourierTab : public FuncTab
{
public:
	/** FourierTab constructor. \n
		harmAmps - array of harmonic amplitudes. \n
		ph - normalized phase offset. \n
		tsiz - table size. \n
		norm - normalize option.
	*/
	FourierTab(std::vector<double> harmAmps, double ph = 0., size_t tsiz = def_tsize, bool norm = true) : FuncTab(tsiz)
	{
		fillTable(harmAmps, ph, norm);
	}

protected:
	/** Basic FourierTab constructor used by derived classes.
		The table won't be filled. \n
		tsiz - table size.
	*/
	FourierTab(size_t tsiz = def_tsize) : FuncTab(tsiz) { } // Basic constructor used by derived classes. The table won't be filled.

	/** Fills the table. \n
		harmAmps - array of harmonic amplitudes. \n
		ph - normalized phase offset. \n
		norm - normalize option.
   */
	void fillTable(const std::vector<double>& harmAmps, double ph = 0., bool norm = true);
};

/** Sawtooth wave function table based on Fourier series.
*/
class SawTab : public FourierTab
{
public:
	/** SawTab constructor. \n
		harm - number of harmonics. \n
		tsiz - table size.
	*/
	SawTab(unsigned int harms = 7, size_t tsiz = def_tsize) : FourierTab(tsiz)
	{
		std::vector<double> harmAmps(harms);
		for (size_t i = 0; i < harmAmps.size(); i++)
			harmAmps[i] = 1.f / (i + 1);

		fillTable(harmAmps, 0.);
	}
};

/** Triangle wave function table based on Fourier series.
*/
class TriangleTab : public FourierTab
{
public:
	/** TriangleTab constructor. \n
		harm - number of harmonics. \n
		tsiz - table size.
	*/
	TriangleTab(unsigned int harms = 7, size_t tsiz = def_tsize) : FourierTab(tsiz)
	{
		std::vector<double> harmAmps(harms, 0.);
		for (size_t i = 0; i < harmAmps.size(); i += 2)
			harmAmps[i] = 1.f / ((i + 1) * (i + 1));

		fillTable(harmAmps, 0.25);
	}
};

/** Square wave function table based on Fourier series.
*/
class SquareTab : public FourierTab
{
public:
	/** SquareTab constructor. \n
		harm - number of harmonics. \n
		tsiz - table size.
	*/
	SquareTab(unsigned int harms = 7, size_t tsiz = def_tsize) : FourierTab(tsiz)
	{
		std::vector<double> harmAmps(harms, 0.);
		for (size_t i = 0; i < harmAmps.size(); i += 2)
			harmAmps[i] = 1.f / (i + 1);

		fillTable(harmAmps, 0.);
	}
};

}

#endif