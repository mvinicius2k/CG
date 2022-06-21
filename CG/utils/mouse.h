#pragma once
#include <cmath>

using namespace  std;
class Mouse
{
public:
	inline static bool Enabled = true;
	inline static float Grid = 0.25;
	inline static float Pass = 0.25;

	static float Step(float value)
	{
		if (!Enabled)
			return value;

		auto mod = fmodf(value, Grid);
		if (mod == 0.f)
			return value;
		else
			return value + std::abs(mod) ;

		
	}

	static void IncreaseGrid()
	{
		Grid += Pass;
	}
	static void DecreaseGrid()
	{
		Grid -= Pass;
	}

private:

};
