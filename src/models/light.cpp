#include "models/light.h"

Light::Light(glm::vec3 position)
    : position(position)
{
    // Soft ambient light
    ambient = glm::vec3(0.2f, 0.2f, 0.2f);

    // Yellowish diffuse light to simulate the Sun
    diffuse = glm::vec3(1.0f, 1.0f, 0.8f);

    // White specular light for reflections
    specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Light::applyToShader(Shader &shader) const
{
    shader.setVec3("lightPosition", position);
    shader.setVec3("lightAmbient", ambient);
    shader.setVec3("lightDiffuse", diffuse);
    shader.setVec3("lightSpecular", specular);
}
