#include "NoiseGenerator.h"

double* NoiseGenerator::createData(float startX, float endX, float startY, float endY)
{
	// use perlin noise algorithm and find delta starts to ends
	module::Perlin perlinNoise;
	double* data = new double[CHUNK_LENGTH * CHUNK_WIDTH];

	perlinNoise.SetSeed(seed);
	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(perlinNoise);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(16, 16);
	heightMapBuilder.SetBounds(startX, endX, startY, endY);
	heightMapBuilder.Build();

	// fill the data using the perlin noise algorithm
	for (int i = 0; i < CHUNK_LENGTH * CHUNK_WIDTH; i++)
	{
		data[i] = heightMap.GetValue
		(
			i % 16,
			i / 16
		);

		//cout << (int)(data[i] * 1000) << endl;
	}

	return data;
}

NoiseGenerator::NoiseGenerator()
{
	srand(time(0));
	seed = rand() * 12;
	seedSet = false;
}