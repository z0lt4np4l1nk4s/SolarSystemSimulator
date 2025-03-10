#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "settings.h"
#include <utility>

class Camera
{
public:
    Camera(int width, int height, glm::vec3 position, float fov, float minDistance, float maxDistance);

    glm::mat4 matrix();

    void inputs(GLFWwindow *window, const std::pair<glm::vec3, float> *planetPositions);
    void zoom(float offset);

    unsigned int getMode() { return mode; }
    int getPlanetIndex() { return planetIndex; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    glm::vec3 getPosition() { return position; }
    glm::mat4 getProjection();

    void setPlanetPOV(glm::vec3 planetPos, float distance);
    void setFov(float fov) { this->fov = fov; }
    void setMinDistance(float minDistance) { this->minDistance = minDistance; }
    void setMaxDistance(float maxDistance) { this->maxDistance = maxDistance; }
    void setViewport(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    void resetCamera();

private:
    unsigned int mode = CAMERA_MODE_SOLAR_SYSTEM;
    int planetIndex = -1;

    float fov = 60.0f;
    float minDistance = 0.1f;
    float maxDistance = 400.0f;

    glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);

    // Camera orbit radius
    float radius = 100.0f; // Default distance

    // Min and Max zoom limits
    float minRadius = 10.0f;  // Prevents zooming too close
    float maxRadius = 200.0f; // Prevents zooming too far

    // Stores the main vectors of the camera
    glm::vec3 position;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

    // Prevents the camera from jumping around when first clicking left click
    bool firstClick = true;

    // Stores the width and height of the window
    int width;
    int height;

    // Adjust the speed of the camera and it's sensitivity when looking around
    float speed = 0.1f;
    float sensitivity = 30.0f;

    float rotationAngleX = 6.28f; // Angle around the X-axis (vertical)
    float rotationAngleY = 0.0f;  // Angle around the Y-axis (horizontal)

    glm::mat4 rotationMatrix = glm::mat4(1.0f);
};
#endif