#include "terrain_gen/mesh.hpp"
#include "shaders/shader.hpp"
#include "../libs/noise/FastNoiseLite.h"

Mesh::Mesh(NoiseData noiseData)
{
	GenerateMesh(noiseData);
}

void Mesh::GenerateMesh(NoiseData data)
{
	// cheating
	//width = 100;
	//height = 100;
	//data.subdivisions = 1024;
	//
	//float waveLegnth = width / data.frequency;
	
	vertices.clear();
	indices.clear();

	std::cout << data.seed << std::endl;
	FastNoiseLite noiseGenerator = FastNoiseLite(data.seed);
	noiseGenerator.SetNoiseType(static_cast<FastNoiseLite::NoiseType>(data.noiseType));
	//noiseGenerator.SetFrequency(0.01);
	
	noiseGenerator.SetFractalType(static_cast<FastNoiseLite::FractalType>(data.fractalType));
	noiseGenerator.SetFractalOctaves(data.fractalOctaves);
	//noiseGenerator.SetRotationType3D(FastNoiseLite::RotationType3D_None);
	//noiseGenerator.SetDomainWarpAmp(8);

	// verticies
	int columns = data.subdivisions + 1;
	for (size_t row = 0; row <= data.subdivisions; row++)
	{
		/*
		if (!(row % data.levelOfDetail == 0))
		{
			continue;
		}*/

		for (size_t col = 0; col <= data.subdivisions; col++)
		{
			/*
			if (!(col % data.levelOfDetail == 0))
			{
				continue;
			}*/

			Vertex v;
			v.UV.x = ((float)col / data.subdivisions);
			v.UV.y = ((float)row / data.subdivisions);
			v.position.x = -data.width / 2 + data.width * v.UV.x;
			v.position.z = data.width / 2 - data.width * v.UV.y;
			v.normal = glm::vec3(0, 1, 0);

			// height map setup
			float elevation = (1 * noiseGenerator.GetNoise(1 * (float)row * data.frequency, 1 * (float)col * data.frequency)
				+ (0.5 * noiseGenerator.GetNoise(2 * (float)row * data.frequency, 2 * (float)col * data.frequency))
				+ (0.25 * noiseGenerator.GetNoise(4 * (float)row * data.frequency, 4 * (float)col * data.frequency))) * data.amplitude;
				;
			elevation = elevation / (1 + 0.5 + 0.25);

			if (elevation < data.lowestPoint)
			{
				elevation = data.lowestPoint;
			}
			if (elevation > data.highestPoint)
			{
				elevation = data.highestPoint;
			}
			elevation += 10;
			elevation = pow(elevation, data.redistribution);
			elevation -= 10;
			v.position.y = elevation;
			vertices.push_back(v);
			//std::cout << v.position.x << " " << v.position.z << std::endl;
		}
	}
	std::cout << "# of vertexes: " << vertices.size() << std::endl;
	//INDICES
	for (size_t row = 0; row < data.subdivisions; row++)
	{
		for (size_t col = 0; col < data.subdivisions; col++)
		{
			int start = row * columns+ col;
			indices.push_back(start);
			indices.push_back(start + 1);
			indices.push_back(start + columns + 1);
			indices.push_back(start + columns + 1);
			indices.push_back(start + columns);
			indices.push_back(start);
		}
	}

	LoadMesh();
}

void Mesh::LoadMesh()
{
	if (!initialized) {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		//Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		//Normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(1);

		//UV attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, UV)));
		glEnableVertexAttribArray(2);

		initialized = true;
	}

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	if (vertices.size() > 0) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	}
	if (indices.size() > 0) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}
	numVertices = vertices.size();
	numIndices = indices.size();

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



}

void Mesh::Draw()
{
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	//std::cout << numVertices << std::endl;
	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);


}