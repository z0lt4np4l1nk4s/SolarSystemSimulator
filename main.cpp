#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include "opengl.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include "camera.h"
#include "settings.h"
#include "text_renderer.h"
#include "models/background.h"
#include "models/planet.h"
#include "models/datetime.h"
#include "models/moon.h"
#include "models/light.h"
#include "util/string_util.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 20.0f), 60.0f, 0.1f, 400.0f);

DateTime referenceDate(2000, 1, 1);
DateTime activeDate;
float lastTime = 0.0f;
const float updateInterval = 0.08f;
bool isAutoMoving = false;
float lastSpacePress = 0.0f;
bool isF1Pressed = false;
const glm::vec3 fontColor = glm::vec3(1.0f, 1.0f, 1.0f);

int main()
{
    GLFWwindow *window = initOpenGL();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwMaximizeWindow(window);

    activeDate = DateTime::today();

    TextRenderer textRenderer;
    Light light(glm::vec3(0.0f, 0.0f, 0.0f));

    std::map<std::string, PlanetInfo> planetsData = PlanetInfo::createPlanets();
    PlanetInfo *originalPlanetsData = PlanetInfo::getOriginalInfo();

    Background background;
    Planet planets[] = {
        Planet(RESOURCE_SUN, planetsData[SUN]),
        Planet(RESOURCE_MERCURY, planetsData[MERCURY]),
        Planet(RESOURCE_VENUS, planetsData[VENUS]),
        Planet(RESOURCE_EARTH, planetsData[EARTH]),
        Planet(RESOURCE_MARS, planetsData[MARS]),
        Planet(RESOURCE_JUPITER, planetsData[JUPITER]),
        Planet(RESOURCE_SATURN, planetsData[SATURN]),
        Planet(RESOURCE_URANUS, planetsData[URANUS]),
        Planet(RESOURCE_NEPTUNE, planetsData[NEPTUNE])};

    Moon moons[] = {
        Moon(0.4f, RESOURCE_MOON, 1.8f, 1.0f, 5.14f, 1.5f, 27.3f, &planets[3])};

    const int planetCount = 9;
    const int moonCount = 1;

    std::pair<glm::vec3, float> planetPositions[planetCount];
    for (int i = 0; i < planetCount; ++i)
    {
        planetPositions[i] = {planets[i].getPosition(), planets[i].getRadius()};
    }

    glm::mat4 matrix = camera.matrix();
    float time;
    float elapsedTime;
    float fontSize = 40.0f;
    PlanetInfo selectedPlanet;
    float textY = 400.0f;

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        camera.inputs(window, planetPositions);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        matrix = camera.matrix();
        time = glfwGetTime();
        elapsedTime = activeDate.yearsSince(referenceDate);

        // std::cout << "Time: " << time << std::endl;
        background.render();
        for (int i = 0; i < planetCount; ++i)
        {
            if (camera.getMode() == CAMERA_MODE_SOLAR_SYSTEM)
            {
                planets[i].updateOrbit(elapsedTime);
            }

            planets[i].render(camera, light, time);
            planetPositions[i] = {planets[i].getPosition(), planets[i].getRadius()};
        }

        for (int i = 0; i < moonCount; ++i)
        {
            moons[i].render(camera, light, time);
        }

        textY = 10.0f;

        if (isF1Pressed)
        {
            textRenderer.renderText(camera, "Left Arrow - Decrease the date", 0.0f, textY, fontSize, fontColor, true);
            textY += 40.0f;
            textRenderer.renderText(camera, "Right Arrow - Increase the date", 0.0f, textY, fontSize, fontColor, true);
            textY += 40.0f;
            textRenderer.renderText(camera, "Space - Toggle auto date increase", 0.0f, textY, fontSize, fontColor, true);
            textY += 40.0f;
            textRenderer.renderText(camera, "Scroll - Zoom in/out", 0.0f, textY, fontSize, fontColor, true);
            textY += 40.0f;
            textRenderer.renderText(camera, "0 Key - Reset camera", 0.0f, textY, fontSize, fontColor, true);
            textY += 40.0f;
            textRenderer.renderText(camera, "1 - 9 Keys - Planet POV", 0.0f, textY, fontSize, fontColor, true);
        }
        else
        {
            textRenderer.renderText(camera, "F1 - HELP", 0.0f, textY, fontSize, fontColor, true);
        }

        textY = camera.getHeight() - 6 * 40.0f;

        if (camera.getMode() == CAMERA_MODE_PLANET)
        {
            selectedPlanet = originalPlanetsData[camera.getPlanetIndex()];
            isAutoMoving = false;
            textRenderer.renderText(camera, "INFO:", 0.0f, textY, fontSize, fontColor, true);
            textY += 40.0f;
            textRenderer.renderText(camera, "Name: " + selectedPlanet.name, 0.0f, textY, fontSize, fontColor, true);
            textY += 40.0f;
            textRenderer.renderText(camera, "Diameter: " + toStringWithPrecision(selectedPlanet.diameter) + " km", 0.0f, textY, fontSize, fontColor, true);
            textY += 40.0f;
            textRenderer.renderText(camera, "Orbital period: " + toStringWithPrecision(selectedPlanet.orbitalPeriod) + " years", 0.0f, textY, fontSize, fontColor, true);
            textY += 40.0f;
            textRenderer.renderText(camera, "Rotation period: " + toStringWithPrecision(selectedPlanet.rotationPeriod) + " hours", 0.0f, textY, fontSize, fontColor, true);
            textY += 40.0f;
            textRenderer.renderText(camera, "Fun fact: " + selectedPlanet.funFact, 0.0f, textY, fontSize, fontColor, true);
        }

        textRenderer.renderText(camera, activeDate.toString(), camera.getWidth() - 175.0f, 20.0f, 48.0f, fontColor, true);

        glfwSwapBuffers(window);
        glfwPollEvents();

        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            std::cerr << "OpenGL Error: " << err << std::endl;
            return -1;
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    float currentTime = glfwGetTime();

    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
    {
        isF1Pressed = true;
    }

    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_RELEASE)
    {
        isF1Pressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && currentTime - lastSpacePress >= 0.5)
    {
        isAutoMoving = !isAutoMoving;

        lastSpacePress = currentTime;
    }

    if (camera.getMode() == CAMERA_MODE_SOLAR_SYSTEM && currentTime - lastTime >= updateInterval)
    {
        if (isAutoMoving)
        {
            activeDate.addDays(1);
            lastTime = currentTime;
        }
        else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            activeDate.addDays(1);
            lastTime = currentTime;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            activeDate.addDays(-1);
            lastTime = currentTime;
        }
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    camera.setViewport(width, height);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.zoom((float)yoffset);
}
