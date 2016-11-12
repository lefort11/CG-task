#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 Position;
out vec3 cameraPos;

uniform mat4 model;
uniform mat4 mvp;
uniform mat3 normalMat;
uniform mat4 view;

uniform vec3 cp;

void main()
{
    gl_Position = mvp * vec4(position, 1.0f);
    Normal = normalMat * normal;
    Position = vec3(model * vec4(position, 1.0f));

    mat4 viewInv = inverse(view);
    cameraPos = viewInv[3].xyz/viewInv[3].w; // Might have to divide by w if you can't assume w == 1
}