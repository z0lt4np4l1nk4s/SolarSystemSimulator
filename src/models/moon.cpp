#include "models/moon.h"

Moon::Moon(float radius, const std::string &texturePath, float orbitRadius, float orbitPeriod, float orbitInclination, float tiltAngle, float rotationPeriod, Sphere *planet)
    : Sphere(radius, texturePath), orbitRadius(orbitRadius), orbitPeriod(orbitPeriod), orbitInclination(orbitInclination), planet(planet), angle(0.0f), tiltAngle(tiltAngle), rotationPeriod(rotationPeriod)
{
}

Moon::~Moon() {}

void Moon::render(Camera &camera, const Light &light, float elapsedTime)
{
    shader.use();

    light.applyToShader(shader);
    shader.setVec3("viewPosition", camera.getPosition());

    // Calculate mean anomaly (angle of orbit progress)
    float orbitSpeed = 360.0f / (orbitPeriod); // Degrees per year

    // Compute current angle based on elapsed time
    float angle = glm::radians(elapsedTime * orbitSpeed); // Convert to radians

    // If the angle exceeds 360 degrees, reset it to 0
    if (angle > glm::two_pi<float>())
        angle -= glm::two_pi<float>();

    // Define the orbit inclination in degrees and convert to radians
    float inclinationRadians = glm::radians(orbitInclination);

    // Compute the moon's position in the **local orbital plane**
    float x = orbitRadius * cos(angle);
    float y = orbitRadius * sin(angle) * sin(inclinationRadians); // Apply inclination
    float z = orbitRadius * sin(angle) * cos(inclinationRadians); // Apply inclination

    // Transform the position into world space by adding the planet's position
    position = planet->getPosition() + glm::vec3(x, y, z);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

    // Apply axial tilt (if the moon has an axial tilt, which can be added as an attribute)
    float tiltRadians = glm::radians(tiltAngle);
    model = glm::rotate(model, tiltRadians, glm::vec3(1.0f, 0.0f, 0.0f)); // Tilt around X-axis

    // Handle moon's rotation (if any)
    if (rotationPeriod != 0.0f)
    {
        float rotationSpeed = (360.0f / abs(rotationPeriod)); // Degrees per hour
        float rotationAngle = glm::radians(elapsedTime * rotationSpeed);

        // If retrograde (negative period), reverse rotation direction
        if (rotationPeriod < 0.0f)
            rotationAngle = -rotationAngle;

        model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y-axis
    }

    // Scale the moon based on its radius
    model = glm::scale(model, glm::vec3(getRadius()));

    glm::mat4 matrix = camera.matrix();

    // Set transformation matrices for the shader
    shader.setMat4("matrix", matrix);
    shader.setMat4("model", model);

    // Bind the moon's texture
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
