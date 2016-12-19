#version 410 core

in vec3 position_cameraSpace;

layout(location = 0) out vec3 PositionOut;

void main()
{
    PositionOut = position_cameraSpace;
}