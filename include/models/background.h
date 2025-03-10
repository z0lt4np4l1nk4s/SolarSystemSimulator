#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <libraries/shader.h>

class Background
{
public:
    Background();
    ~Background();

    void render();

private:
    void bindBuffers();
    unsigned int texture;
    unsigned int VAO, VBO, EBO;
    Shader shader;
};

#endif