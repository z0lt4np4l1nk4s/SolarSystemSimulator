# Solar System Simulator

This is a **Solar System Simulator** app created using **OpenGL** as part of my college project for the **3D Computer Graphics** subject. The app simulates the positions of planets in the solar system and allows users to interact by changing the date using the left and right arrow keys.

---

## Features

- Displays the positions of planets in the solar system, updating according to the current date.
- Allows users to change the date using the left and right arrow keys.
- Planetary motion is simulated assuming that planets move in perfect circular orbits around the Sun.
- The sizes of the planets and their distances are not to scale, but have been adjusted to custom sizes for better visual clarity.
- Provides the ability to focus on the point of view (POV) of each planet by pressing keys 1-9

---

## 🗺️ Table of Contents

- [Project Purpose](#project-purpose)
- [Quick Start](#quick-start)
- [Controls](#controls)
- [Directory Layout](#directory-layout)
- [Architecture & Methodology](#architecture--methodology)
- [Results](#results)
- [Known Limitations](#known-limitations)
- [Screenshots and Demo](#screenshots-and-demo)

## Project Purpose

I built this simulator for the **3D Computer Graphics** course at **MATHOS Osijek** to demonstrate how a small, well‑structured OpenGL project can visualise complex motion while staying performant on entry‑level hardware.

## Quick Start

1. Download `` from the [latest release](https://github.com/z0lt4np4l1nk4s/SolarSystemSimulator/releases).
2. Extract and double‑click ``.
3. Use `` inside the app for the full keymap.

```bash
git clone https://github.com/z0lt4np4l1nk4s/SolarSystemSimulator.git
cd SolarSystemSimulator
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/SolarSystemSimulator      # add .exe on Windows
```

*Requires ****CMake ≥ 3.20****, a C++17 compiler and an OpenGL 3.3+ GPU.*

> **Windows shortcut:** run `` in the repo root to produce `out.exe`.

---

## Controls

- **Left Arrow Key**: Decrease the current date and move backward in time.
- **Right Arrow Key**: Increase the current date and move forward in time.
- **Auto-Move** feature: Press the **Spacebar** to start the planets moving automatically. Press **Spacebar** again to stop the auto-movement.
- **Scroll**: Zoom in/out
- **0 Key**: Reset the camera
- **1-9 Keys**: Switch to the point of view of the corresponding planet:
  - **1**: Focus on the Sun
  - **2**: Focus on Mercury
  - **3**: Focus on Venus
  - **4**: Focus on Earth
  - **5**: Focus on Mars
  - **6**: Focus on Jupiter
  - **7**: Focus on Saturn
  - **8**: Focus on Uranus
  - **9**: Focus on Neptune

*(The help overlay is rendered with a custom bitmap‑font text engine implemented in **`src/text_renderer.cpp`**.)*

---

## Directory Layout

```
.
├─ include/           # Public headers (GLAD, GLFW, GLM, stb_image, engine headers)
├─ src/               # Application source (.cpp)
│  ├─ models/         # Planet, moon, light & sphere primitives
│  └─ …
├─ resources/
│  ├─ shaders/        # GLSL sources (background, planet, text)
│  ├─ textures/       # 2K JPEG planet textures + skybox
│  └─ fonts/          # BigShouldersInline‑*.ttf (OFL‑1.1)
├─ screenshots/       # GIFs & PNGs used in this README
├─ compile.bat        # One‑click Windows build helper
├─ CMakeLists.txt     # Cross‑platform build script
└─ LICENSE            # MIT Licence
```

Key third‑party libraries are **GLFW, GLAD, GLM** and **stb\_image** — all bundled under permissive licenses so the project builds out‑of‑the‑box without system‑wide installs.

---

## Architecture & Methodology

### Data Sources

- Orbital periods & radii: NASA Planetary Fact Sheet *(retrieved 2025‑05‑01).*
- Textures: [Solar System Scope](https://www.solarsystemscope.com/textures/) *(CC‑BY‑4.0).*
- Skybox: Milky Way by **SpaceEngine**.

### Core Components

| Module         | Responsibility                           | Key APIs                     |
| -------------- | ---------------------------------------- | ---------------------------- |
| `Simulation`   | Julian‑day clock, circular‑orbit math    | `<chrono>`, GLM              |
| `Renderer`     | VBO/VAO setup, shader management, skybox | OpenGL 3.3, GLAD             |
| `Input`        | GLFW callbacks → app commands            | GLFW                         |
| `TextRenderer` | Bitmap‑font rendering (HUD & help)       | FreeType (via stb\_truetype) |
| `Assets`       | Texture & shader loading                 | stb\_image, `<filesystem>`   |

---

## Known Limitations

- Circular, coplanar orbits — no eccentricity/inclination.
- Planet sizes & distances vastly compressed for visibility.
- Single light source; no shadows or atmospheric scattering.
- No asteroid belt, dwarf planets or moons *(planned — see roadmap)*.

---

## Limitations

- The orbits of the planets are simplified to perfect circles, which is not completely accurate in real life.
- Planet sizes are not scaled to their actual dimensions, instead using custom sizes to make the simulation visually more appealing.

## Screenshots and Demo

### App Screenshot
Here’s a screenshot of the app:

![Simulator Image](screenshots/screenshot.png)

### Demo GIF
Check out a short demo showing the app in action:

![Simulator Animation](screenshots/simulation.gif)
