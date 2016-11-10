#version 330 core


uniform vec4 materialSpecular = vec4(0.9,0.9,0.9,1.0);
uniform vec4 materialAmbient = vec4(0.2,0.2,0.2,1.0);
uniform vec4 materialDiffuse = vec4(0.7,0.7,0.7,1.0);
uniform float shininess = 10.0;

uniform vec4 lightDiffuse = vec4(1.0,1.0,1.0,1.0);
uniform vec4 lightAmbient = vec4(0.2,0.2,0.2,1.0);

uniform sampler2DShadow gShadowMap;


vec4 GetAmbientReflection(vec4 materialColor, vec4 lightColor)
{
    return lightColor * materialColor;
}

vec4 GetSpecularReflection(vec4 materialColor, float materialShininess, vec3 surfaceNormal, vec4 lightColor, vec3 halfAngle)
{
    float specularFactor =
    	   pow(clamp(dot(halfAngle, surfaceNormal),0.0,1.0), materialShininess);

    	return lightColor * materialColor * specularFactor;
}

vec4 GetDiffuseReflection(
	vec4 surfaceColor,
	vec3 surfaceNormal,
    vec4 lightColor,
	vec3 lightDirection)
{
	float diffuseFactor =
		clamp(dot(lightDirection, surfaceNormal),0.0,1.0);
	return lightColor * surfaceColor * diffuseFactor;
}


vec4 GetBlinnReflection(vec4 ambientSurfaceColor,
                        vec4 ambientLightColor,
                        vec4 diffuseSurfaceColor,
                        vec4 specularSurfaceColor,
                        float surfaceShininess,
                        vec3 surfaceNormal,
                        vec3 halfAngle,
                        vec3 lightDirection,
                        vec4 lightColor)
{

    vec4 ambient = GetAmbientReflection(ambientSurfaceColor, ambientLightColor);

    vec4 diffuse = GetDiffuseReflection(
        diffuseSurfaceColor,
        surfaceNormal,
        lightColor,
        lightDirection);

    vec4 specular = GetSpecularReflection(
        specularSurfaceColor,
        surfaceShininess,
        surfaceNormal,
        lightColor,
        halfAngle);

    if (dot(lightDirection, surfaceNormal) <= 0.0)
    {
        specular = vec4(0.0, 0.0, 0.0, 0.0);
    }

    return diffuse + specular + ambient;
}


in vec4 fragmentColor;

in vec3 modelPosition3;
in vec3 lightDirection;
in vec3 normal3;

in vec4 ShadowCoord;

out vec4 color;


void main()
{
    vec3 normalizedLightDirection = normalize(lightDirection);
    vec3 viewerDirection = normalize(-modelPosition3);
    vec3 halfAngle = normalize(normalize(viewerDirection) + normalizedLightDirection);

    float visibility = texture(gShadowMap, vec3(ShadowCoord.xy, (ShadowCoord.z)/ShadowCoord.w) );

    color = visibility * GetBlinnReflection(
    		materialDiffuse,
    		lightAmbient,
    		materialDiffuse,
    		materialSpecular,
    		shininess,
    		normal3,
    		halfAngle,
    		normalizedLightDirection,
    		lightDiffuse) * fragmentColor;
}