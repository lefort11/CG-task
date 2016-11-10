#version 330

layout (location = 0) in vec3 Position;

uniform mat4 mvp;
uniform mat4 lightBiasMVP;

out vec4 ShadowCoord;

void main()
{
        gl_Position = mvp * vec4(Position, 1.0);
        ShadowCoord = lightBiasMVP * vec4(Position, 1.0);

}