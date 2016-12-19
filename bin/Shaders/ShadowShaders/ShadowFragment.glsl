#version 330

in vec4 ShadowCoord;
//in vec2 TexCoordOut;
uniform sampler2DShadow gShadowMap;

out vec4 FragColor;

void main()
{
    //float Depth = texture(gShadowMap, TexCoordOut).x;
   // Depth = 1.0 - (1.0 - Depth) * 25.0;
   // FragColor = vec4(Depth);
    float visibility = texture(gShadowMap, vec3(ShadowCoord.xy, (ShadowCoord.z)/ShadowCoord.w) );
    FragColor = visibility * vec4(1);
}