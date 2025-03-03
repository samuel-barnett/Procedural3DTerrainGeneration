#pragma once
#include <vector>
#include <glm.hpp>


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


public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh() {};
	Mesh(float width, float height, int subdivisions);

	glm::mat4 GetModelMatrix();

	void Draw();


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