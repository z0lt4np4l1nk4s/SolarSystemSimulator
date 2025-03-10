#include "camera.h"
#include "iostream"

Camera::Camera(int width, int height, glm::vec3 position, float fov, float minDistance, float maxDistance)
{
    this->width = width;
    this->height = height;
    this->position = position;
    this->fov = fov;
    this->minDistance = minDistance;
    this->maxDistance = maxDistance;
}

glm::mat4 Camera::matrix()
{
    // Convert rotation angles into spherical coordinates
    float camX = center.x + radius * cos(glm::radians(rotationAngleX)) * sin(glm::radians(rotationAngleY));
    float camY = center.y + radius * sin(glm::radians(rotationAngleX));
    float camZ = center.z + radius * cos(glm::radians(rotationAngleX)) * cos(glm::radians(rotationAngleY));

    glm::vec3 cameraPos = glm::vec3(camX, camY, camZ);

    glm::mat4 view = glm::lookAt(cameraPos, center, upDirection);

    // Perspective projection
    glm::mat4 projection = getProjection();

    return projection * view;
}

glm::mat4 Camera::getProjection()
{
    return glm::perspective(glm::radians(fov), (float)width / height, minDistance, maxDistance);
}

void Camera::inputs(GLFWwindow *window, const std::pair<glm::vec3, float> *planetPositions)
{
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        resetCamera();
    }

    for (int i = 0; i < 9; i++)
    {
        if (glfwGetKey(window, GLFW_KEY_1 + i) == GLFW_PRESS)
        {
            planetIndex = i;
            std::pair<glm::vec3, float> planet = planetPositions[i];

            float aspectRatio = (float)width / height;

            // Convert FOV to radians
            float fovRad = glm::radians(60.0f);

            float theta = atan(tan(fovRad / 2.0f) * std::max(1.0f, aspectRatio));

            float optimalDistance = (2.0f * planet.second) / (2.0f * tan(fovRad / 2.0f));

            if (planet.second >= 3.0f)
            {
                optimalDistance *= 7.5f;
            }
            else if (planet.second >= 1.8f)
            {
                optimalDistance *= 4.35f;
            }
            else if (planet.second >= 1.0f)
            {
                optimalDistance *= 2.5f;
            }
            else if (planet.second >= 0.5)
            {
                optimalDistance *= 2.0f;
            }

            setPlanetPOV(planet.first, optimalDistance);
        }
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick)
        {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

        // Update rotation angles (limit X-axis rotation to avoid flipping)
        rotationAngleX += rotX;
        rotationAngleY += rotY;

        if (rotationAngleX > 89.0f)
            rotationAngleX = 89.0f;
        if (rotationAngleX < -89.0f)
            rotationAngleX = -89.0f;

        glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}

void Camera::resetCamera()
{
    mode = CAMERA_MODE_SOLAR_SYSTEM;
    center = glm::vec3(0.0f, 0.0f, 0.0f);
    radius = 100.0f;
    rotationAngleX = 6.28f;
    rotationAngleY = 0.0f;
    planetIndex = -1;
}

void Camera::zoom(float offset)
{
    if (mode != CAMERA_MODE_SOLAR_SYSTEM)
    {
        return;
    }

    radius -= offset * 0.75f;
    if (radius < minRadius)
        radius = minRadius;
    if (radius > maxRadius)
        radius = maxRadius;
}

void Camera::setPlanetPOV(glm::vec3 planetPos, float distance)
{
    radius = distance;
    mode = CAMERA_MODE_PLANET;
    center = planetPos;
    position = glm::vec3(planetPos.x, planetPos.y, planetPos.z + distance);
}