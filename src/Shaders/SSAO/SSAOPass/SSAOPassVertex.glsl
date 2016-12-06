#version 410 core

layout (location = 0) in vec3 position_modelSpace;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position_modelSpace, 1.0f);

    TexCoord = position_modelSpace.xy * 0.5 + vec2(0.5);
}