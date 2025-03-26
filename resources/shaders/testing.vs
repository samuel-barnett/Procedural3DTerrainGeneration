#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTextCoord;

uniform mat4 model;
uniform mat4 viewProjection;

out vec3 fragPosition;


void main()
{
    fragPosition = aPos;

    vec4 WorldPos = model * vec4(aPos, 1.0);

    gl_Position = viewProjection * WorldPos;
};