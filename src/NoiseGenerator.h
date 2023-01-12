#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>

#include <noise.h>
#include "noiseUtils.h"

#define CHUNK_WIDTH 16
#define CHUNK_LENGTH 16

using namespace std;

class NoiseGenerator
{
public:
	NoiseGenerator();
	bool seedSet;
	unsigned int seed;
	double* createData(float bottomX, float topX, float bottomY, float topY);
};