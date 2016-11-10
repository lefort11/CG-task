#version 330 core

in vec3 fragmentColor;

out vec3 color;

void main()
{
    //color = vec3(1.0f,0.0f,0.0f);
    color = fragmentColor;
}
