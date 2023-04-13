#pragma once
#include <array>
#include <math.h>
#define Tranpose

using namespace std;
// utilitários de calculos
class Math
{
public:
	static void Transposef(float (&matrix)[4][4])
	{
		
		//PrintMaxtrixf(matrix);
		for (int i = 0; i < 4; i++)
			for (int j = i; j < 4; j++)
				std::swap(matrix[i][j], matrix[j][i]);

				
		//PrintMaxtrixf(matrix);
	}

	static float Deg2Rad(float deg)
	{
		return (deg / 180) * PI;
	}

	
	static void PrintMaxtrixf(float(&matrix)[4][4])
	{
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++)
				std::cout << matrix[i][j] << "\t";
			std::cout << endl;

		}


	}

    

};