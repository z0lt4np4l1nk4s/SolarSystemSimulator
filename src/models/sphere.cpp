#include "models/sphere.h"
#include "settings.h"

Sphere::Sphere(float radius, const std::string &texturePath)
    : shader("resources/shaders/planet.vs", "resources/shaders/planet.fs"),
      radius(radius)
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *
        data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    generateSphere(radius);
    bindBuffers();
}

Sphere::~Sphere()
{
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Sphere::generateSphere(float radius)
{
    // Clear previous data
    vertices.clear();
    indices.clear();

    // Generate vertices
    for (int i = 0; i <= SPHERE_STACKS; ++i)
    {
        float stackAngle = glm::pi<float>() / 2 - (float)i / SPHERE_STACKS * glm::pi<float>();
        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);

        for (int j = 0; j <= SPHERE_SECTORS; ++j)
        {
            float sectorAngle = (float)j / SPHERE_SECTORS * 2 * glm::pi<float>();
            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            glm::vec3 normal = glm::normalize(glm::vec3(x, y, z));

            // Vertex position
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // Texture coordinates (UV mapping)
            float s = (float)j / SPHERE_SECTORS;
            float t = (float)i / SPHERE_STACKS;
            vertices.push_back(s);
            vertices.push_back(t);

            // Normal vector
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);
        }
    }

    for (int i = 0; i < SPHERE_STACKS; ++i)
    {
        for (int j = 0; j < SPHERE_SECTORS; ++j)
        {
            int first = (i * (SPHERE_SECTORS + 1)) + j;
            int second = first + SPHERE_SECTORS + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
}

void Sphere::bindBuffers()
{
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Normal vector attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
}