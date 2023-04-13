#pragma once
#include <cmath>

using namespace  std;
// Basicamente implementa a sensação de grade no mundo ao transladar, rotacionar e escalar
class Mouse
{
public:
	inline static bool Enabled = true;
	inline static float Grid = 0.25;
	inline static float Pass = 0.25;
	inline static float RotationGrid = 15;
	inline static float RotationPass = 15;
	
	


	static float Step(float value, float stepSize = Grid)
	{
		if (!Enabled)
			return value;

		auto mod = fmodf(value, stepSize);
		if (mod == 0.f)
			return value;
		
		return value >= 0 ? value - abs(mod) : value + abs(mod);

		
	}

	static float RotateStep(float value, float stepSize = RotationGrid)
	{
		return Step(value, stepSize);
	}

	static void IncreaseGrid()
	{
		Grid += Pass;
	}
	static void DecreaseGrid()
	{
		Grid -= Pass;
	}
	static void IncreaseRotationGrid()
	{
		RotationGrid += RotationPass;
	}
	static void DecreaseRotationGrid()
	{
		RotationGrid -= RotationPass;
	}

private:

};
