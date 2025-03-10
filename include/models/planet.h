#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "models/planet_info.h"
#include "models/sphere.h"
#include "models/light.h"

class Planet : public Sphere
{
public:
    Planet(const std::string &texturePath, const PlanetInfo &info);

    void render(Camera &camera, const Light &light, float elapsedTime);
    void updateOrbit(float time);

private:
    PlanetInfo info;
};

#endif