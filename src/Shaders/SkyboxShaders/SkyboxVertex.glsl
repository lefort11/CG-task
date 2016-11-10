#version 330 core

layout(location = 0) in vec3 vertexPosition_modelSpace;
out vec3 texCoords;

uniform mat4 mvp;

void main()
{
    vec4 pos = mvp * vec4(vertexPosition_modelSpace,1.0);
    gl_Position = pos.xyww;
    texCoords = vertexPosition_modelSpace;
}