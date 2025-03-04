#include "terrain_gen/mesh.hpp"
#include "shaders/shader.hpp"
#include "../libs/noise/FastNoiseLite.h"

Mesh::Mesh(float width, float height, int subdivisions, NoiseData noiseData)
{
	GenerateMesh(width, height, subdivisions, noiseData);
}

void Mesh::GenerateMesh(float width, float height, int subdivisions, NoiseData data)
{
	// cheating
	width = 500;
	height = 500;
	subdivisions = 1024;
	//

	
	vertices.clear();
	indices.clear();

	
	FastNoiseLite noiseGenerator = FastNoiseLite(data.seed);
	noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	//noiseGenerator.SetFrequency(0.01);
	noiseGenerator.SetFractalOctaves(2);
	noiseGenerator.SetFractalType(FastNoiseLite::FractalType_Ridged);
	//noiseGenerator.SetDomainWarpAmp(8);

	// verticies
	int columns = subdivisions + 1;
	for (size_t row = 0; row <= subdivisions; row++)
	{
		for (size_t col = 0; col <= subdivisions; col++)
		{
			Vertex v;
			v.UV.x = ((float)col / subdivisions);
			v.UV.y = ((float)row / subdivisions);
			v.position.x = -width / 2 + width * v.UV.x;
			v.position.y = noiseGenerator.GetNoise((float)row, (float)col) * 2;
			v.position.z = height / 2 - height * v.UV.y;
			v.normal = glm::vec3(0, 1, 0);
			vertices.push_back(v);
			//std::cout << v.position.x << " " << v.position.z << std::endl;
		}
	}
	//INDICES
	for (size_t row = 0; row < subdivisions; row++)
	{
		for (size_t col = 0; col < subdivisions; col++)
		{
			int start = row * columns + col;
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