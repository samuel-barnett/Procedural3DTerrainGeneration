#pragma once
#include "../libs/noise/FastNoiseLite.h"

struct NoiseData
{
	int seed = 0;
	int width = 500, height = 500;
	int subdivisions = 1024;
	float amplitude = 5;
	float frequency = 2;
	float redistribution = 1.25;
	float lowestPoint = 0;
	int noiseType = FastNoiseLite::NoiseType::NoiseType_OpenSimplex2;
	int fractalType = FastNoiseLite::FractalType::FractalType_None;
	int fractalOctaves = 1;



};


