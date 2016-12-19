#version 410 core

layout (location = 0) in vec3 position_modelSpace;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 view;

out vec3 position_cameraSpace;

void main()
{
    gl_Position = mvp * vec4(position_modelSpace, 1.0);

    position_cameraSpace = (view * model * vec4(position_modelSpace, 1.0)).xyz;
}