#pragma once
#include "../libs/noise/FastNoiseLite.h"

struct NoiseData
{
	int seed = 0;
	int width = 250;
	int subdivisions = 1024;
	float amplitude = 1.5;
	float frequency = 1.15;
	float redistribution = 1.5;
	float lowestPoint = -0.5;
	int noiseType = FastNoiseLite::NoiseType::NoiseType_OpenSimplex2;
	int fractalType = FastNoiseLite::FractalType::FractalType_None;
	int fractalOctaves = 1;
	int levelOfDetail = 1;



};


