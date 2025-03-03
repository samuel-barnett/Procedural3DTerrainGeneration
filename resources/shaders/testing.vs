#version 330 core
layout (location = 0) in vec3 aPos;

uniform Mat4 _Model
uniform Mat4 _ViewProjection

out vec3 fragPosition;

void main()
{
    fragPosition = aPos;

    vec4 WorldPos = _Model * vec4(aPos, 1.0)

    gl_Position = _ViewProjection * WorldPos;
};