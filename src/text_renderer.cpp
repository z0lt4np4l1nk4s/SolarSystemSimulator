#include "text_renderer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

TextRenderer::TextRenderer()
    : shader("resources/shaders/text.vs", "resources/shaders/text.fs")
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    loadFont("resources/fonts/BigShouldersInline-Regular.ttf", regularTextureAtlas);
    loadFont("resources/fonts/BigShouldersInline-Bold.ttf", boldTextureAtlas);

    setupTextRendering();
    createTextTextures();
}

TextRenderer::~TextRenderer()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteTextures(1, &regularTexture);
    glDeleteTextures(1, &boldTexture);
    free(fontData);
}

void TextRenderer::setupTextRendering()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::loadFont(const char *fontPath, unsigned char *textureAtlas)
{
    FILE *fontFile = fopen(fontPath, "rb");
    if (!fontFile)
    {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    fseek(fontFile, 0, SEEK_END);
    size_t fontSize = ftell(fontFile);
    fseek(fontFile, 0, SEEK_SET);

    fontData = (unsigned char *)malloc(fontSize);
    fread(fontData, 1, fontSize, fontFile);
    fclose(fontFile);

    stbtt_BakeFontBitmap(fontData, 0, 48.0f, textureAtlas, 512, 512, 32, 96, cdata);
}

void TextRenderer::createTextTextures()
{
    // Load regular font texture
    glGenTextures(1, &regularTexture);
    glBindTexture(GL_TEXTURE_2D, regularTexture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, regularTextureAtlas);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Load bold font texture (you would need a separate bold font texture)
    glGenTextures(1, &boldTexture);
    glBindTexture(GL_TEXTURE_2D, boldTexture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, boldTextureAtlas);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::renderText(Camera &camera, const std::string &text, float x, float y, float fontSize, glm::vec3 color, bool bold)
{
    glDisable(GL_DEPTH_TEST);

    shader.use();
    shader.setInt("textTexture", 0);
    shader.setVec3("textColor", color);

    glm::mat4 projection = glm::ortho(0.0f, (float)camera.getWidth(), 0.0f, (float)camera.getHeight());
    shader.setMat4("projection", projection);

    glActiveTexture(GL_TEXTURE0);

    if (bold)
    {
        glBindTexture(GL_TEXTURE_2D, boldTexture);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, regularTexture);
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Calculate the scale based on fontSize
    float scale = fontSize / 48.0f;
    float xPos, yPos;
    float width, height;

    for (char c : text)
    {
        if (c < 32 || c > 126)
            continue; // Ignore non-printable ASCII characters

        stbtt_bakedchar &ch = cdata[c - 32];

        // Position adjustment to start from bottom-left
        xPos = x + 5 + ch.xoff * scale;
        yPos = camera.getHeight() - y - (ch.yoff + ch.y1 - ch.y0) * scale - fontSize + 15.0f;

        width = (ch.x1 - ch.x0) * scale;
        height = (ch.y1 - ch.y0) * scale;

        float vertices[] = {
            xPos, yPos + height, ch.x0 / 512.0f, ch.y0 / 512.0f,
            xPos, yPos, ch.x0 / 512.0f, ch.y1 / 512.0f,
            xPos + width, yPos, ch.x1 / 512.0f, ch.y1 / 512.0f,

            xPos, yPos + height, ch.x0 / 512.0f, ch.y0 / 512.0f,
            xPos + width, yPos, ch.x1 / 512.0f, ch.y1 / 512.0f,
            xPos + width, yPos + height, ch.x1 / 512.0f, ch.y0 / 512.0f};

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += ch.xadvance * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);
}
