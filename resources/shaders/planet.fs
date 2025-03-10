#version 330 core

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D sphere;
uniform vec3 viewPosition;
uniform vec3 lightPosition;
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;
uniform bool isSun;

void main()
{
    vec4 texColor = texture(sphere, TexCoord);

    if (isSun)
    {
        FragColor = texColor;
    }
    else
    {
        // Normal lighting calculations for planets
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPosition - FragPos);
        
        // Ambient
        vec3 ambient = lightAmbient;
        
        // Diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightDiffuse;
        
        // Specular
        vec3 viewDir = normalize(viewPosition - FragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfwayDir), 0.0), 32);
        vec3 specular = lightSpecular * spec;

        vec3 result = (ambient + diffuse + specular) * texColor.rgb;
        FragColor = vec4(result, texColor.a);
    }
}
