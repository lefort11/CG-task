#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 2) in vec3 vertexColor;

// Values that stay constant for the whole mesh.
uniform mat4 mvp;

out vec3 fragmentColor;

void main(){
    
    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  mvp * vec4(vertexPosition_modelspace,1);

    fragmentColor = vertexColor;
    
}
