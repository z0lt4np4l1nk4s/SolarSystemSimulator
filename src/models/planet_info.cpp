#include "models/planet_info.h"

PlanetInfo::PlanetInfo() {}

PlanetInfo::PlanetInfo(std::string name, float diameter, float distanceFromSun,
                       float distanceFromEarth, float orbitalPeriod, float rotationPeriod, float tiltAngle,
                       std::string funFact)
    : name(name), diameter(diameter), distanceFromSun(distanceFromSun),
      distanceFromEarth(distanceFromEarth), orbitalPeriod(orbitalPeriod),
      rotationPeriod(rotationPeriod), tiltAngle(tiltAngle), funFact(funFact) {}

std::map<std::string, PlanetInfo> PlanetInfo::createPlanets()
{
  std::map<std::string, PlanetInfo> planets;

  planets["Sun"] = PlanetInfo("Sun", 4.0f, 0.0f, 0.0f, 0.0f, 24.0f, 7.25f,
                              "The Sun is a star at the center of the Solar System.");
  planets["Mercury"] = PlanetInfo("Mercury", 0.8f, 1.0f, 77, 0.24f, 407.6f, 0.034f,
                                  "Mercury has no atmosphere to retain heat, making it extremely hot and cold.");
  planets["Venus"] = PlanetInfo("Venus", 1.8f, 1.45f, 41, 0.62f, -832.5f, 177.4f,
                                "Venus has a runaway greenhouse effect, making it hotter than Mercury!");
  planets["Earth"] = PlanetInfo("Earth", 2.0f, 2.3f, 0, 1.00f, 24.0f, 23.5f,
                                "Earth is the only planet known to support life.");
  planets["Mars"] = PlanetInfo("Mars", 1.2f, 3.25f, 78, 1.88f, 24.6f, 25.2f,
                               "Mars has the tallest volcano in the solar system: Olympus Mons.");
  planets["Jupiter"] = PlanetInfo("Jupiter", 4.2f, 4.45f, 628, 11.86f, 9.9f, 3.1f,
                                  "Jupiter has a giant storm called the Great Red Spot.");
  planets["Saturn"] = PlanetInfo("Saturn", 3.9f, 6.5f, 1270, 29.46f, 10.7f, 26.7f,
                                 "Saturn's rings are made mostly of ice and rock.");
  planets["Uranus"] = PlanetInfo("Uranus", 2.5f, 7.8f, 2720, 84.02f, -17.2f, 97.8f,
                                 "Uranus rotates on its side, making it unique in the solar system.");
  planets["Neptune"] = PlanetInfo("Neptune", 2.4f, 9.0f, 4350, 164.8f, 16.1f, 28.3f,
                                  "Neptune has the fastest winds in the solar system, reaching 2,100 km/h!");
  return planets;
}

PlanetInfo planets[] = {
    PlanetInfo("Sun", 1392700, 0.0f, 0.0f, 0.0f, 24.0f, 7.25f, "The Sun is a star at the center of the Solar System."),
    PlanetInfo("Mercury", 4879, 0.39f, 77, 0.24f, 1407.6f, 0.034f, "Mercury has no atmosphere to retain heat, making it extremely hot and cold."),
    PlanetInfo("Venus", 12104, 0.72f, 41, 0.62f, -5832.5f, 177.4f, "Venus has a runaway greenhouse effect, making it hotter than Mercury!"),
    PlanetInfo("Earth", 12742, 1.00f, 0, 1.00f, 24.0f, 23.5f, "Earth is the only planet known to support life."),
    PlanetInfo("Mars", 6779, 1.52f, 78, 1.88f, 24.6f, 25.2f, "Mars has the tallest volcano in the solar system: Olympus Mons."),
    PlanetInfo("Jupiter", 139820, 5.20f, 628, 11.86f, 9.9f, 3.1f, "Jupiter has a giant storm called the Great Red Spot."),
    PlanetInfo("Saturn", 116460, 9.58f, 1270, 29.46f, 10.7f, 26.7f, "Saturn's rings are made mostly of ice and rock."),
    PlanetInfo("Uranus", 50724, 19.22f, 2720, 84.02f, -17.2f, 97.8f, "Uranus rotates on its side, making it unique in the solar system."),
    PlanetInfo("Neptune", 49244, 30.05f, 4350, 164.8f, 16.1f, 28.3f, "Neptune has the fastest winds in the solar system, reaching 2,100 km/h!")};

PlanetInfo *PlanetInfo::getOriginalInfo()
{
  return planets;
}
