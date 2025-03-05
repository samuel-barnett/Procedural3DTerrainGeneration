#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTextCoord;

uniform mat4 model;
uniform mat4 viewProjection;

//out vec3 fragPosition;

out Surface
{
	vec3 WorldPos;
	vec3 WorldNormal;
	vec2 TexCoord;
	//mat3 TBN;
}vs_out;

void main()
{
	vs_out.WorldPos = vec3(model * vec4(aPos, 1.0));
	vs_out.WorldNormal = transpose(inverse(mat3(model))) * aNormal;
	vs_out.TexCoord = aTextCoord;

    //fragPosition = aPos;

    vec4 WorldPos = model * vec4(aPos, 1.0);

    gl_Position = viewProjection * WorldPos;
};