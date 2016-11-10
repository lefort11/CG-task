#version 330 core

// Ouput data
layout(location = 0) out float fragdepth;

void main()
{
    // Not really needed, OpenGL does it anyway
    fragdepth = gl_FragCoord.z;
}