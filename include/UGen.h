/////////////////////////////////////////////////////////////////////
// UGen class: KiwiWaves's digital signal processing base class
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _UGEN_H_
#define _UGEN_H_
#include <vector>
#include "KiwiWaves.h"

namespace KiwiWaves
{

/** KiwiWaves's digital signal processing base class.
*/
class UGen
{

protected:
	/** Protected UGen constructor. \n
		vsiz - number of frames in vector.\n
		sr - sampling rate.
	*/
	UGen(size_t vsiz = def_vsize, double sr = def_sr) : m_s(vsiz), m_sr(sr) { };

public:
	/** Process one vector of audio.
	*/
	const double* process();

	/** Get the processed data.
	*/
	const double* data();

	/** Get the sampling rate.
    */
	const double& sr() const { return m_sr; }

	/** Get the vector size.
    */
	const size_t vsize() const { return m_s.size(); }

	/** Get a reference of a single sample at
		sample position idx off the data vector.
	*/
	virtual const double& operator [](const size_t& idx) const;

	virtual const UGen& operator+=(const UGen& other);
	virtual const UGen operator+(const UGen& other) const;
	virtual const UGen& operator+=(const double& val);
	virtual const UGen operator+(const double& val) const;

	virtual const UGen& operator-=(const UGen& other);
	virtual const UGen operator-(const UGen& other) const;
	virtual const UGen& operator-=(const double& val);
	virtual const UGen operator-(const double& val) const;

	virtual const UGen& operator*=(const UGen& other);
	virtual const UGen operator*(const UGen& other) const;
	virtual const UGen& operator*=(const double& scalar);
	virtual const UGen operator*(const double& scalar) const;

	virtual const UGen& operator/=(const UGen& other);
	virtual const UGen operator/(const UGen& other) const;
	virtual const UGen& operator/=(const double& scalar);
	virtual const UGen operator/(const double& scalar) const;

	/** Virtual destructor.
	*/
	virtual ~UGen() {};

protected:
	double m_sr;
	std::vector<double> m_s;

	/** Kernel dsp method that each UGen will override.
	*/
	virtual void dsp() {};

	/** Set the entire audio vector to zero.
	*/
	void fillDataToZero();

	/** Set the entire audio vector to one.
	*/
	void fillDataToOne();

protected:

	/** Auxiliar class for UGen parameters that can be modulated.
	*/
	class UGenParam
	{
	public:

		/** UGenParam constructor.  \n
			val - fixed parameter value.
		*/
		UGenParam(double val) : m_FixedValue(val), m_Modulator(nullptr) { }
		
		/** UGenParam constructor.  \n
			val - parameter value for modulation.
		*/
		UGenParam(UGen& modulator) : m_FixedValue(0.), m_Modulator(&modulator) { }

		/** Set the parameter to a fixed value.
		*/
		inline void set(double val) { m_FixedValue = val; m_Modulator = nullptr; }

		/** Set the parameter to a UGen reference for modulation.
		*/
		inline void set(UGen& modulator) { m_FixedValue = 0.; m_Modulator = &modulator; }

		/** Get the control rate value of the parameter,
			will be the first value of the vector in case of modulation.
		*/
		inline const double& kr() const { return m_Modulator != nullptr ? (*m_Modulator)[0] : m_FixedValue; }

		/** Get a reference of the parameter value at position idx
			(the position does not matter if no modulation).
		*/
		inline const double& operator [](const size_t& idx) const { return m_Modulator ? (*m_Modulator)[idx] : m_FixedValue; }

	private:
		double m_FixedValue;
		UGen* m_Modulator;
	};
};

}
#endif