#pragma once

#include <stdlib.h>

namespace nu
{
	inline int RandInt()
	{
		return rand();
	}

	/// <summary>
	/// Get random integer value [0, max)
	/// </summary>
	/// <param name="max">Exclusive max</param>
	/// <returns>Random number between 0 and max</returns>
	inline int RandInt(int max)
	{
		return RandInt() % max;
	}

	/// <summary>
	/// Get random integer value [min, max]
	/// </summary>
	/// <param name="min">Inclusive min</param>
	/// <param name="max">Inclusive max</param>
	/// <returns>Random number between min and max</returns>
	inline int RandInt(int min, int max)
	{
		return min + RandInt((max - min) + 1);
	}

	inline float RandFloat()
	{
		return rand() / (float)RAND_MAX;
	}

	inline float RandFloat(float max)
	{
		return RandFloat() * max;
	}

	inline float RandFloat(float min, float max)
	{
		return min + RandFloat() * (max - min);
	}
}