#version 330 core
out vec4 FragColor;

in Surface
{
    vec3 WorldPos;
    vec3 WorldNormal;
    vec2 TexCoord;
}fs_in;

in vec3 fragPosition;

uniform float lowest;
uniform float highest;

void main()
{
    float heightColor = sin(fragPosition.y); // + 0.25;


    //float mixValue = (fragPosition.y - 15.0) / 20.0;

    float mixValue = (fragPosition.y - lowest)/(highest - lowest);
    //FragColor = vec4((sin(fs_in.WorldPos.x * 50.0) / 2.0) + 0.5, 0.55, 0.5, 1.0);
    FragColor = mix(vec4(0, 0, 1, 1.0), vec4(0, 1, 1, 1.0), mixValue);
};