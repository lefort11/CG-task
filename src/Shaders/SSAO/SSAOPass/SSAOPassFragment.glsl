#version 410 core

in vec2 TexCoord;

uniform sampler2D gPositionMap;
uniform float gSampleRad = 0.5f;
uniform mat4 proj;

const int MAX_KERNEL_SIZE = 128;
uniform vec3 gKernel[MAX_KERNEL_SIZE];

out vec4 color;

void main()
{

    vec3 Position = texture(gPositionMap, TexCoord).xyz;

    float AO = 0.0;

    for (int i = 0 ; i < MAX_KERNEL_SIZE ; ++i)
    {
        vec3 samplePos = Position + gKernel[i];   // генерируем случайные точки
        vec4 offset = vec4(samplePos, 1.0);  // преобразуем в 4-вектор
        offset = proj * offset;        // проецируем на ближнюю плоскость клиппера
        offset.xyz /= offset.w;      // производим деление перспективы
        offset.xyz = offset.xyz * 0.5 + vec3(0.5);    // переносим на отрезок (0,1)

        float sampleDepth = texture(gPositionMap, offset.xy).z;

        /*if (abs(Position.z - sampleDepth) < gSampleRad)
        {
            AO += step(sampleDepth, samplePos.z);
        } */

        float rangeCheck = smoothstep(0.0, 1.0, gSampleRad / abs(Position.z - sampleDepth));
        AO += (sampleDepth >= samplePos.z ? 1.0 : 0.0) * rangeCheck;

    }

    AO = 1.0 - AO/MAX_KERNEL_SIZE;
    color = vec4(pow(AO, 2.0));
    color = vec4(AO);
}