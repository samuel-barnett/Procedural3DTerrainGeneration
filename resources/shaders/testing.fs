#version 330 core
out vec4 FragColor;

in Surface
{
    vec3 WorldPos;
    vec3 WorldNormal;
    vec2 TexCoord;
}fs_in;

in vec3 fragPosition;

void main()
{
    float heightColor = (cos(fragPosition.y * 0.5) * 0.5); // + 0.25;
    //FragColor = vec4((sin(fs_in.WorldPos.x * 50.0) / 2.0) + 0.5, 0.55, 0.5, 1.0);
    FragColor = vec4(0, heightColor, 1.6, 1.0);
};