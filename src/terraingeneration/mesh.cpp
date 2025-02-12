#include "terrain_gen/mesh.hpp"
#include "shaders/shader.hpp"

void Mesh::Draw()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



}