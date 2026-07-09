#pragma once

namespace nu
{
	constexpr float Pi = 3.141592653589f;
	constexpr float TwoPi = Pi * 2.0f;
	constexpr float HalfPi = Pi / 2.0f;

	template<typename T>
	T Min(T a, T b) {
		if (a < b) { return a; }
		return b;
	}

	template<typename T>
	T Max(T a, T b) {
		if (a > b) { return a; }
		return b;
	}

	template<typename T>
	T Wrap(T min, T max, T value)
	{
		if (value > max) value = min;
		if (value < min) value = max;

		return value;
	}

	template<typename T>
	T Clamp(T min, T max, T value) {
		if (value < min) value = min;
		if (value > max) value = max;

		return value;
	}

}