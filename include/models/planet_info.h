#ifndef PLANETINFO_H
#define PLANETINFO_H

#include <string>
#include <map>

class PlanetInfo
{
public:
    std::string name;
    float diameter;          // in km
    float distanceFromSun;   // in AU
    float distanceFromEarth; // in million km (approx)
    float orbitalPeriod;     // in Earth years
    float rotationPeriod;    // in Earth hours
    float tiltAngle;         // in degrees
    std::string funFact;

    PlanetInfo();

    PlanetInfo(std::string name, float diameter, float distanceFromSun,
               float distanceFromEarth, float orbitalPeriod, float rotationPeriod, float tiltAngle,
               std::string funFact);

    static std::map<std::string, PlanetInfo> createPlanets();
    static PlanetInfo *getOriginalInfo();
};

#endif
