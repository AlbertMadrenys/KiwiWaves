	KiwiWaves is an experimental C++ (ISO C++11) class library for audio DSP. It is
	mainly inspired by [AuLib](http://github.com/AuLib/AuLib), and also draws
	significant influence from the structures of languages like [Csound]
	(https://csound.com/) and [SuperCollider] (https://supercollider.github.io/).

	KiwiWaves provides developers with simple, classic, and easy-to-use modules
	for working with DSP audio. The foundation of the library includes function
	tables, oscillators, filters, and envelopes. These modules, or UGens, can be
	used to create more complex operations by chaining them together, as many of
	the modules allow their parameters to be either fixed values or modulated by
	other modules.

	This design creates a simple, yet very powerful and user-friendly way to design
	DSP programs.

Build
===========================================

	The library is built with CMake. External dependencies are not needed.

	The code can be used within any audio processing context and it can
	be incorporated in plugins and other programs with their own IO.

``` 
mkdir build
cd build
cmake ..
cmake --build .
cmake --install . --config Debug
```

Using
=====================================

	The most basic class provided by KiwiWaves is the `UGen` class, from which
	almost all other classes inherit. The parameters of the DSP module are
	initialized in the`UGen` constructor, though they can be changed later.
	When a new audio buffer is needed, the `Process()` method
	of the `UGen` can be called.

	If a parameter of a `UGen` is another `UGen` (for modulation purposes),
	make sure to process the modulating one first, followed by the main one.
 
Extending
============================
	
	The library classes can be easily extended. The most straightforward way to do
	this is to create a subclass of UGen or FuncTab. For UGen, you can create a
	new constructor to initialize the object and override the dsp() method to
	define the behavior of the object when processing audio. This method will
	typically update the values of the audio vector called m_s.

	Inheriting from UGen allows for easy integration with existing objects and
	provides access to the basic audio processing facilities available in the library.
 
License
=====================

	Copyright (C) 2024 Albert Madrenys Planas

	This software is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This software is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this software; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
	/
