#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <glm/glm.hpp>
#include <string>
#include <libraries/shader.h>
#include "camera.h"
#include <libraries/stb_truetype.h>

class TextRenderer
{
private:
    Shader shader;
    GLuint VAO, VBO;
    GLuint regularTexture;
    GLuint boldTexture;
    unsigned char *fontData;
    unsigned char regularTextureAtlas[512 * 512];
    unsigned char boldTextureAtlas[512 * 512];
    stbtt_bakedchar cdata[96];

    void setupTextRendering();
    void loadFont(const char *fontPath, unsigned char *textureAtlas);
    void createTextTextures();

public:
    TextRenderer();
    ~TextRenderer();
    void renderText(Camera &camera, const std::string &text, float x, float y, float fontSize, glm::vec3 color, bool bold);
};

#endif
