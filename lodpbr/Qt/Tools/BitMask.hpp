/*
 * BitMask.hpp
 *
 *  Created on: Nov 5, 2009
 *      Author: fmc
 */

/*
 * bitmask.h
 *
 * This wrapper provides a checked, typesafe mechanism for
 * storing bitmasks. Each bit's value is defined in an enum
 * separately, and the enum is provided to the template.
 * The storage size of the bitmask can be explicitly set as
 * well using template parameters.
 *
 * Note that this object has literally no overhead versus
 * simply writing the bitfield ops by hand in raw code: the
 * storage of each instance is minimal and controlled by the
 * templated storage type; there are no virtual members and
 * therefore no vtabl for the objects; and all operations
 * are inlined by the compiler so there is no function call
 * overhead for manipulating or checking the bitmask.
 */

#pragma once


template<typename Holder, typename FlagEnum>
class Bitmask
{
public:
	Bitmask(Holder defval = 0) : Bitfield(defval) { }

	// Sets all bitmask bits which are set in "flags"
	inline void Set(Holder flags)
	{ Bitfield |= flags; }

	// Clears all bitmask bits which are set in "flags"
	inline void Clear(FlagEnum flags)
	{ Bitfield &= (~flags); }

	// Return true if ANY of the bits set in "flags" are
	// also set for the bitmask
	inline bool Test(FlagEnum flags) const
	{ return ((Bitfield & flags) != 0); }

	// Return true only if ALL bits set in "flags" are
	// also set for the bitmask
	inline bool TestAllFlags(Holder flags) const
	{ return ((Bitfield & flags) == flags); }

protected:
	Holder Bitfield;
};


/*
 *
#include "bitmask.h"

enum WindowAppearanceFlags : unsigned
{
   WA_FullScreen = 0x001,
   WA_ScrollBarX = 0x002,
   WA_ScrollBarY = 0x004,
   WA_NoResize = 0x008,
   WA_NoMinimize = 0x010
};

typedef Bitmask<unsigned, WindowAppearanceFlags> WindowAppearanceBitmask;

void Foo()
{
   WindowAppearanceBitmask foomask;
   foomask.Set(WA_FullScreen | WA_NoResize);

   // Do stuff

   if(foomask.Test(WA_NoMinimize))
   {
       // etc.
   }
}
 *
 */

