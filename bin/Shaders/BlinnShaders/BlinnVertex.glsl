#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 vertexColor;


uniform vec4 lightPosition;

uniform mat4 mvp;
uniform mat4 model;
uniform mat3 normalMat;

//uniform mat4 lightViewMat;

out vec3 modelPosition3;
out vec3 lightDirection;
out vec3 normal3;

out vec4 fragmentColor;

void main()
{
  // vec4 vertexPosition_worldSpace = lightViewMat * model * vec4(vertexPosition_modelspace, 1);
   vec4 vertexPosition_worldSpace = model * vec4(vertexPosition_modelspace, 1);
   modelPosition3 = vertexPosition_worldSpace.xyz / vertexPosition_worldSpace.w;


   vec3 lightPosition3 = lightPosition.xyz / lightPosition.w;

   normal3 = normalize(normalMat * normal);
   lightDirection = normalize(lightPosition3 - modelPosition3);
 //  lightDirection = normalize(lightPosition3);

   gl_Position = mvp * vec4(vertexPosition_modelspace,1);

   fragmentColor = vec4(vertexColor,1);
  //fragmentColor = vec4(1);
}