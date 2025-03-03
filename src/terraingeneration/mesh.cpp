#include "terrain_gen/mesh.hpp"
#include "shaders/shader.hpp"

Mesh::Mesh(float width, float height, int subdivisions)
{
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
			v.position.z = 0;
			v.position.y = height / 2 - height * v.UV.y;
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
	//glDrawArrays(GL_TRIANGLES, 0, numVertices);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);


}