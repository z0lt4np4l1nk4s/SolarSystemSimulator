#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <libraries/shader.h>

class Light
{
private:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

public:
    Light(glm::vec3 position);

    void applyToShader(Shader &shader) const;

    glm::vec3 getPosition() const { return position; }
    glm::vec3 getAmbient() const { return ambient; }
    glm::vec3 getDiffuse() const { return diffuse; }
    glm::vec3 getSpecular() const { return specular; }
};

#endif