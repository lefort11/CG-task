#version 330 core
in vec3 Normal;
in vec3 Position;
out vec4 color;

in vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    //vec3 R = refract(I, normalize(Normal), 1.0/1.3);
    color = texture(skybox, R);
}