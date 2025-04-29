#pragma once
#include <vector>
#include <glm.hpp>
#include <iostream>
#include <fstream>
#include <terrain_gen/perlin_generator.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 UV;
};


class Mesh
{
	bool initialized = false;
	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int ebo = 0;
	unsigned int numVertices = 0;
	unsigned int numIndices = 0;

	int subdivisions;

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh() {};
	Mesh(NoiseData noiseData);

	void GenerateMesh(NoiseData& data);
	void LoadMesh();

	glm::mat4 GetModelMatrix();

	void Draw();

	void SaveToObj(std::string filename)
	{
		std::ofstream output;
		output.open(filename);

		// verticies
		for (int i = 0; i < vertices.size(); i++)
		{
			output << "v " << vertices[i].position.x << " " << vertices[i].position.y << " " << vertices[i].position.z << std::endl;
		}

		// faces
		/*
		for (int i = 0; i < indices.size(); i += 3)
		{
			output << "f " << indices[i] << " " << indices[i]+1 << " " << indices[i+2] << std::endl;
		}
		*/
		
		
		int columns = subdivisions + 1;
		for (size_t row = 1; row < subdivisions; row++)
		{
			for (size_t col = 1; col < subdivisions; col++)
			{
				output << "f ";
				int start = row * columns + col;
				output << start << " ";
				output << start + 1 << " ";
				output << start + columns + 1 << std::endl << "f ";
				output << start + columns + 1 << " ";
				output << start + columns << " ";
				output << start << std::endl;
			}
		}
		

		output.close();
	}


};



struct Transform {
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);


	glm::mat4 translate(const glm::vec3& t)
	{
		return glm::mat4{
			1.0, 0.0, 0.0, 0.0,  //col 0
			0.0, 1.0, 0.0, 0.0,  //col 1 
			0.0, 0.0, 1.0, 0.0,  //col 2
			t.x, t.y, t.z, 1.0   //col 3
		};
	}

	glm::mat4 rotateX(float a)
	{
		return glm::mat4{
			1.0,  0.0, 0.0, 0.0,
			0.0, cos(a), sin(a), 0.0,
			0.0, -sin(a), cos(a), 0.0,
			0.0, 0.0, 0.0, 1.0
		};
	}

	glm::mat4 rotateY(float a)
	{
		return glm::mat4{
			cos(a),  0.0, sin(a), 0.0,
			0.0,         1.0, 0.0,       0.0,
			-sin(a), 0.0, cos(a), 0.0,
			0.0,         0.0, 0.0,       1.0
		};
	}

	glm::mat4 rotateZ(float a)
	{
		return glm::mat4{
			cos(a), sin(a), 0.0, 0.0,  //col 0
			-sin(a), cos(a),  0.0, 0.0,//col 1 
			0.0, 0.0,               1.0, 0.0, //col 2
			0.0, 0.0,               0.0, 1.0  //col 3
		};
	}

	glm::mat4 Scale(const glm::vec3& s)
	{
		return glm::mat4{
			s.x, 0.0, 0.0, 0.0, //col 0
			0.0, s.y, 0.0, 0.0,	//col 1 
			0.0, 0.0, s.z, 0.0,	//col 2
			0.0, 0.0, 0.0, 1.0	//col 3
		};
	}


	glm::mat4 getModelMatrix() {
		return translate(position) * rotateX(rotation.x) * rotateY(rotation.y) * rotateZ(rotation.z) * Scale(scale);
	}
	void reset() {
		position = glm::vec3(0);
		rotation = glm::vec3(0);
		scale = glm::vec3(1);
	}
};