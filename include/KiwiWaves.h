/////////////////////////////////////////////////////////////////////
// KiwiWaves.h: library-wide definitions
// 
// Copyright (C) 2024 Albert Madrenys
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _KIWIWAVES_H_
#define _KIWIWAVES_H_
#include <cstdint>
#include <cmath>

/** Types of curves for control signals.
 */
enum Curve : uint8_t { linear, exponential };

/** How to handle divisions by zero.
 */
enum ZeroHandlingMode : uint8_t { addSmallNumber, equalToOne };

/** Time unit modes.
 */
enum TimeUnit : uint8_t { seconds, samples };

/** Default signal vector size.
 */
const size_t def_vsize = 64;

/** Default function table length.
 */
const size_t def_tsize = 16384;

/** default sample rate.
 */
const double def_sr = 44100.;

/** Default control rate.
 */
const double def_kr = def_sr / def_vsize;

/** The pi definition.
 */
const double pi = 4 * atan(1.);

/** The two pi definition.
 */
const double twopi = 8 * atan(1.);

/** Small dBFs value that in most cases will be imperceptible.
 */
const double imperceptible_db = 0.00001;

/** Default near-zero exponential curve offset.
 */
const double def_exp_curve_offset = 0.1;

/** Smallest positive value for double.
 */
const double min_double = std::numeric_limits<double>::min();

#endif