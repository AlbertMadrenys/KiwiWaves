/////////////////////////////////////////////////////////////////////
// TableRead class: function table reader
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _TABLEREAD_H_
#define _TABLEREAD_H_
#include "FuncTab.h"
#include "UGen.h"

namespace KiwiWaves
{

/** Table reader with truncated lookup.
*/
class TableRead : public UGen
{
public:
	/** TableRead constructor. \n
		index - index of the position to read. \n
		tab - table to read. \n
		norm - option to read the index as normalized. \n
		wrap - wrap the table once finished. \n
		vsiz - number of frames in vector.\n
		sr - sampling rate.
	*/
	TableRead(double index, const FuncTab& tab, bool norm = true, bool wrap = true,
		size_t vsiz = def_vsize, double sr = def_sr) :
		m_ind(index), m_table(tab),
		m_norm(norm), m_wrap(wrap), UGen(vsiz, sr) { };

	/** TableRead constructor. \n
		index - index of the position to read. \n
		tab - table to read. \n
		norm - option to read the index as normalized. \n
		wrap - wrap the table once finished. \n
		vsiz - number of frames in vector.\n
		sr - sampling rate.
	*/
	TableRead(UGen& index, const FuncTab& tab, bool norm = true, bool wrap = true,
		size_t vsiz = def_vsize, double sr = def_sr) :
		m_ind(index), m_table(tab),
		m_norm(norm), m_wrap(wrap), UGen(vsiz, sr) { };

	void setIndex(double val) { m_ind.set(val); }
	void setIndex(UGen& modulator) { m_ind.set(modulator); }

	const bool& norm() const { return m_norm; }
	const bool& wrap() const { return m_wrap; }

protected:
	FuncTab m_table;
	UGenParam m_ind;
	bool m_norm;
	bool m_wrap;

	void dsp() override;

	/** Get the correct table position taking into
		consideration normalization, wrapping and clamping.
	*/
	double getRawIndex(const size_t& indx);
};

/** Table reader with linear interpolation.
 */
class TableReadI : public TableRead
{
public:
	/** TableReadI constructor. \n
		index - index of the position to read. \n
		tab - table to read. \n
		norm - option to read the index as normalized. \n
		wrap - wrap the table once finished. \n
		vsiz - number of frames in vector.\n
		sr - sampling rate.
	*/
	TableReadI(double index, const FuncTab& tab, bool norm = true, bool wrap = true,
		size_t vsiz = def_vsize, double sr = def_sr) :
		TableRead(index, tab, norm, wrap, vsiz, sr) { };

	/** TableReadI constructor. \n
		index - index of the position to read. \n
		tab - table to read. \n
		norm - option to read the index as normalized. \n
		wrap - wrap the table once finished. \n
		vsiz - number of frames in vector.\n
		sr - sampling rate.
	*/
	TableReadI(UGen& index, const FuncTab& tab, bool norm = true, bool wrap = true,
		size_t vsiz = def_vsize, double sr = def_sr) :
		TableRead(index, tab, norm, wrap, vsiz, sr) { };

protected:
	void dsp() override;
};

/** Table reader with cubic interpolation.
 */
class TableReadC : public TableRead
{
public:
	/** TableReadC constructor. \n
		index - index of the position to read. \n
		tab - table to read. \n
		norm - option to read the index as normalized. \n
		wrap - wrap the table once finished. \n
		vsiz - number of frames in vector.\n
		sr - sampling rate.
	*/
	TableReadC(double& index, const FuncTab& tab, bool norm = true, bool wrap = true,
		size_t vsiz = def_vsize, double sr = def_sr) :
		TableRead(index, tab, norm, wrap, vsiz, sr) { };

	/** TableReadC constructor. \n
		index - index of the position to read. \n
		tab - table to read. \n
		norm - option to read the index as normalized. \n
		wrap - wrap the table once finished. \n
		vsiz - number of frames in vector.\n
		sr - sampling rate.
	*/
	TableReadC(UGen& index, const FuncTab& tab, bool norm = true, bool wrap = true,
		size_t vsiz = def_vsize, double sr = def_sr) :
		TableRead(index, tab, norm, wrap, vsiz, sr) { };

protected:
	void dsp() override;
};

}
#endif