#ifndef SPHERE_H
#define SPHERE_H

#include <libraries/stb_image.h>
#include <libraries/shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Sphere
{
public:
    Sphere(float radius, const std::string &texturePath);
    ~Sphere();

    glm::vec3 getPosition() const { return position; }
    float getRadius() const { return radius; }

protected:
    float radius;
    unsigned int texture;
    unsigned int VAO, VBO, EBO;
    Shader shader;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 position;

    void bindBuffers();
    void generateSphere(float radius);
};

#endif