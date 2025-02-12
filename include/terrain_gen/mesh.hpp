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
public:
	std::vector<Vertex> verticies;
	std::vector<unsigned int> indicies;

	void Draw();


};