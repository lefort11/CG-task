#version 410 core



uniform sampler2DShadow shadowMap;

uniform vec4 MaterialSpecular;
uniform vec4 MaterialAmbient;
uniform vec4 MaterialDiffuse;
uniform float Shininess;

uniform vec4 LightDiffuse = vec4(1.0,1.0,1.0,1.0);
//uniform vec4 LightAmbient = vec4(0.2,0.2,0.2,1.0);

uniform bool SoftShadows;

uniform sampler2D gAOMap;

uniform vec2 ScreenSize;


vec4 GetAmbientReflection(
	vec4 surfaceColor,
    vec4 lightColor)
{
	return lightColor * surfaceColor;
}

vec4 GetDiffuseReflection(
	vec4 surfaceColor,
	vec3 surfaceNormal,
    vec4 lightColor,
	vec3 lightDirection)
{
	float diffuseFactor =
		clamp(
			dot(lightDirection, surfaceNormal),0.0,1.0);
	return lightColor * surfaceColor * diffuseFactor;
}

vec4 GetSpecularReflection(
	vec4 surfaceColor,
    float  surfaceShininess,
    vec3 surfaceNormal,
    vec4 lightColor,
    vec3 halfAngle)
{
	float specularFactor =
	   pow(clamp(dot(halfAngle, surfaceNormal),0.0,1.0), surfaceShininess);
	if(surfaceShininess == 0)
	{
	    return vec4(0);
	}

	return lightColor * surfaceColor * specularFactor;
}

vec4 GetBlinnReflection(
//	vec4 ambientSurfaceColor,
  //  vec4 ambientLightColor,
    vec4 diffuseSurfaceColor,
    vec4 specularSurfaceColor,
    float  surfaceShininess,
    vec3 surfaceNormal,
    vec3 halfAngle,
    vec3 lightDirection,
    vec4 lightColor) {

//	vec4 ambient = GetAmbientReflection(ambientSurfaceColor, ambientLightColor);

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

//	return diffuse + specular + ambient;
    return diffuse + specular;
}

vec2 poissonDisk[16] = vec2[](
   vec2( -0.94201624, -0.39906216 ),
   vec2( 0.94558609, -0.76890725 ),
   vec2( -0.094184101, -0.92938870 ),
   vec2( 0.34495938, 0.29387760 ),
   vec2( -0.91588581, 0.45771432 ),
   vec2( -0.81544232, -0.87912464 ),
   vec2( -0.38277543, 0.27676845 ),
   vec2( 0.97484398, 0.75648379 ),
   vec2( 0.44323325, -0.97511554 ),
   vec2( 0.53742981, -0.47373420 ),
   vec2( -0.26496911, -0.41893023 ),
   vec2( 0.79197514, 0.19090188 ),
   vec2( -0.24188840, 0.99706507 ),
   vec2( -0.81409955, 0.91437590 ),
   vec2( 0.19984126, 0.78641367 ),
   vec2( 0.14383161, -0.14100790 )
);

float random(vec3 seed, int i)
{
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

vec2 CalcScreenTexCoord()
{
    return gl_FragCoord.xy / ScreenSize;
}

in vec4 fragmentColor;
//in vec3 vertexPosition_worldSpace;
in vec3 normal_worldSpace;
in vec3 eyeDirection_worldSpace;
//in vec3 lightDirection_cameraSpace;
in vec4 ShadowCoord;
in vec3 lightDirection_worldSpace;


out vec4 color;

void main()
{
    float visibility=1.0;

    vec3 n = normalize(normal_worldSpace);

    vec3 l = normalize(lightDirection_worldSpace);

    vec3 v = normalize(eyeDirection_worldSpace);

    vec3 halfAngle = normalize(l + v);

 /*   vec3 E = normalize(eyeDirection_worldSpace);

   	vec3 R = reflect(-l,n);

    float cosTheta = clamp( dot( n,l ), 0,1 );

    float cosAlpha = clamp( dot( E,R ), 0,1 ); */

    float bias = 0;

    if(SoftShadows)
    {
        for(int i = 0; i < 4; ++i)
        {
            visibility -= 0.2*
            (1.0-texture( shadowMap, vec3(ShadowCoord.xy + poissonDisk[i]/650.0,  (ShadowCoord.z-bias)/ShadowCoord.w) ));
        }
    }
    else
    {
        visibility = texture(shadowMap, vec3(ShadowCoord.xy, (ShadowCoord.z-bias) / ShadowCoord.w));
    }

    vec4 AOColor = vec4(1.5) * texture(gAOMap, CalcScreenTexCoord()).r;


    color = (visibility *
    GetBlinnReflection( MaterialDiffuse,
                        MaterialSpecular,
                        Shininess,
                        n,
                        halfAngle,
                        l,
                        LightDiffuse) + MaterialAmbient * AOColor);



}