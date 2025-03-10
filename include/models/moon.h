#ifndef MOON_H
#define MOON_H

#include "models/sphere.h"
#include "camera.h"
#include "models/light.h"

class Moon : public Sphere
{
public:
    Moon(float radius, const std::string &texturePath, float orbitRadius, float orbitPeriod, float orbitInclination, float tiltAngle, float rotationPeriod, Sphere *planet);
    ~Moon();

    void render(Camera &camera, const Light &light, float deltaTime);

private:
    float orbitRadius;      // Distance from the planet
    float orbitPeriod;      // Speed of rotation around the planet (in radians)
    float orbitInclination; // Inclination of the orbit
    Sphere *planet;         // The planet the moon is orbiting
    float angle;            // Angle in radians to determine position in orbit
    float tiltAngle;        // Axial tilt of the moon
    float rotationPeriod;   // Rotation period of the moon
};

#endif
