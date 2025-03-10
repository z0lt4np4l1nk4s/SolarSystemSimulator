#include "models/background.h"

#include <iostream>
#include <vector>
#include <libraries/stb_image.h>

Background::Background()
    : shader("resources/shaders/background.vs", "resources/shaders/background.fs")
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // Flip the loaded texture on the y-axis
    unsigned char *data = stbi_load("resources/textures/milky_way.jpg", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture background texture." << std::endl;
    }
    stbi_image_free(data);

    bindBuffers();
}

void Background::bindBuffers()
{
    // Bind background buffers
    float quadVertices[] = {
        // Positions      // Texture Coords
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Top-left
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom-left
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // Bottom-right
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f    // Top-right
    };

    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Background::render()
{
    glDisable(GL_DEPTH_TEST); // Disable depth test for 2D rendering

    shader.use(); // Use the background shader

    // Bind the background texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Bind the VAO for the quad and draw the elements
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw the quad with 6 indices

    glEnable(GL_DEPTH_TEST);
}

Background::~Background()
{
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}