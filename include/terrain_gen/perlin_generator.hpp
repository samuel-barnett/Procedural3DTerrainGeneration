#pragma once
#include "../libs/noise/FastNoiseLite.h"

struct NoiseData
{
	int seed = 0;
	int width = 250;
	int subdivisions = 150;
	float amplitude = 1.5;
	float frequency = 1.15;
	float redistribution = 1.5;
	float lowestPoint = -0.5;
	float highestPoint = 20;
	float domainWarp = 8;
	int noiseType = FastNoiseLite::NoiseType::NoiseType_OpenSimplex2;
	int fractalType = FastNoiseLite::FractalType::FractalType_None;
	int fractalOctaves = 1;
	int levelOfDetail = 1;

	float lowestCurr = 1000000, highestCurr = -1000000;

	bool Compare(NoiseData other)
	{
		if (seed != other.seed)
		{
			return false;
		}
		if (width != other.width)
		{
			return false;
		}
		if (subdivisions != other.subdivisions)
		{
			return false;
		}
		if (amplitude != other.amplitude)
		{
			return false;
		}
		if (frequency != other.frequency)
		{
			return false;
		}
		if (redistribution != other.redistribution)
		{
			return false;
		}
		if (lowestPoint != other.lowestPoint)
		{
			return false;
		}
		if (highestPoint != other.highestPoint)
		{
			return false;
		}
		if (noiseType != other.noiseType)
		{
			return false;
		}
		if (fractalType != other.fractalType)
		{
			return false;
		}
		if (fractalOctaves != other.fractalOctaves)
		{
			return false;
		}
		if (levelOfDetail != other.levelOfDetail)
		{
			return false;
		}
		return true;
	};

	void Copy(NoiseData other)
	{
		seed = other.seed;
		width = other.width;
		subdivisions = other.subdivisions;
		amplitude = other.amplitude;
		frequency = other.frequency;
		redistribution = other.redistribution;
		lowestPoint = other.lowestPoint;
		highestPoint = other.highestPoint;
		noiseType = other.noiseType;
		fractalType = other.fractalType;
		fractalOctaves = other.fractalOctaves;
		levelOfDetail = other.levelOfDetail;
	};

};


