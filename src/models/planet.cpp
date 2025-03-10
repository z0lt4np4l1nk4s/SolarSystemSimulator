#include "models/planet.h"
#include "settings.h"

Planet::Planet(const std::string &texturePath, const PlanetInfo &info)
    : Sphere(info.diameter / 2.0f, texturePath),
      info(info)
{
    position = (info.distanceFromSun == 0.0f)
                   ? glm::vec3(0.0f, 0.0f, 0.0f) // Sun at the center
                   : glm::vec3(info.distanceFromSun, 0.0f, 0.0f);
}

void Planet::render(Camera &camera, const Light &light, float elapsedTime)
{
    shader.use();

    light.applyToShader(shader);
    shader.setVec3("viewPosition", camera.getPosition());
    shader.setBool("isSun", info.name == SUN);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

    // Apply axial tilt first (if applicable)
    if (info.tiltAngle != 0.0f)
    {
        float tiltRadians = glm::radians(info.tiltAngle);
        model = glm::rotate(model, tiltRadians, glm::vec3(1.0f, 0.0f, 0.0f)); // Tilt around X-axis
    }

    // Handle planetary rotation around its own axis
    if (info.rotationPeriod != 0.0f)
    {
        float rotationSpeed = (360.0f / abs(info.rotationPeriod)); // Degrees per hour
        float rotationAngle = glm::radians(elapsedTime * rotationSpeed);

        // If retrograde (negative period), reverse rotation direction
        if (info.rotationPeriod < 0.0f)
            rotationAngle = -rotationAngle;

        model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y-axis (planet's own axis)
    }

    // Apply orbital rotation after the axial tilt and planetary rotation
    model = glm::scale(model, glm::vec3(getRadius()));

    shader.setMat4("matrix", camera.matrix());
    shader.setMat4("model", model);

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Planet::updateOrbit(float elapsedTime)
{
    if (info.orbitalPeriod == 0.0f)
        return; // The Sun remains stationary

    // Calculate mean anomaly (angle of orbit progress)
    float orbitSpeed = 360.0f / (info.orbitalPeriod); // Degrees per year

    // Compute current angle based on elapsed time
    float angle = glm::radians(elapsedTime * orbitSpeed); // Convert to radians

    // Scale distance to fit scene proportions (adjust multiplier as needed)
    float scaledDistance = info.distanceFromSun * 10.0f;

    // Compute orbital position assuming a circular orbit
    position = glm::vec3(scaledDistance * cos(angle), 0.0f, scaledDistance * sin(angle));
}