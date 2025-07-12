# Solar System Simulator

This is a **Solar System Simulator** app created using **OpenGL** as part of my college project for the **3D Computer Graphics** subject. The app simulates the positions of planets in the solar system and allows users to interact by changing the date using the left and right arrow keys.

---

## Table of Contents

1. [Project Purpose](#project-purpose)
2. [Build instructions](#build-instructions)
3. [Features](#features)
4. [Controls](#controls)
5. [Directory Layout](#directory-layout)
6. [Architecture & Methodology](#architecture--methodology)
7. [Known Limitations](#known-limitations)
8. [Screenshots and Demo](#screenshots-and-demo)

---

## Project Purpose

This project was created to demonstrate how a structured OpenGL application can visualize complex 3D motion while remaining performant on modest hardware. The focus was on readability, modularity, and blending mathematical simulation with visual clarity.

---

## Build instructions

Windows

1. Clone the repository

```bash
git clone https://github.com/z0lt4np4l1nk4s/SolarSystemSimulator && cd SolarSystemSimulator
```

2. Build using one of the following options:

**Option A: Using MSYS2 with mingw32-make**

Install MSYS2 and required packages:

```bash
pacman -Syu
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw make
```

_Make sure you added mingw32-make to PATH_

Build with:

```bash
mingw32-make
```

**Option B: Using GnuWin32 with make**

Download and install make from [GnuWin32](https://gnuwin32.sourceforge.net/packages/make.htm)

Then build with:

```bash
make
```

3. Run the simulation

```bash
./SolarSystemSimulator.exe
```

_Requires a C++17 compiler_

Linux:

1. Clone the repository

```bash
git clone https://github.com/z0lt4np4l1nk4s/SolarSystemSimulator && cd SolarSystemSimulator
```

2. Install the dependencies

Install make if not already

```bash
sudo apt install make
```

Install the project dependencies

```bash
make install-deps
```

Or install manually:

```bash
sudo apt install make build-essential pkg-config libglfw3-dev libglm-dev libgles-dev mesa-common-dev
```

3. Build using make

```bash
make
```

3. Run the simulation

```bash
./SolarSystemSimulator
```

---

## Features

- Displays the positions of planets in the solar system, updating according to the current date
- Allows users to change the date using the left and right arrow keys
- Planetary motion is simulated assuming that planets move in perfect circular orbits around the Sun
- The sizes of the planets and their distances are not to scale, but have been adjusted to custom sizes for better visual clarity
- Provides the ability to focus on the point of view (POV) of each planet by pressing keys 1-9

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

_(The help overlay is rendered with a custom bitmap‑font text engine implemented in **`src/text_renderer.cpp`**.)_

---

## Directory Layout

```
.
├─ include/           # Public C++ headers for external and internal components (GLFW, GLAD, GLM, stb_image)
├─ lib/               # Precompiled third-party libraries and static dependencies
├─ resources/         # Non-code assets used at runtime
│  ├─ shaders/        # GLSL shader programs (planet rendering, text overlay, skybox)
│  ├─ textures/       # High-resolution JPEG planet textures and starfield skybox
│  └─ fonts/          # TrueType fonts for HUD (e.g. BigShouldersInline‑*.ttf)
├─ screenshots/       # Visual assets (GIFs, PNGs) used in README or presentation
├─ src/               # Application source files (main logic, rendering, input, simulation)
│  ├─ models/         # Scene primitives: planets, moons, lighting, mesh generators
│  └─ …               # Other modules like renderer, input manager, orbit simulation
├─ compile.bat        # One‑click build script for Windows users (calls CMake + MSVC)
├─ main.cpp           # Entry point of the application (initialises window, engine, loop)
```

Key third‑party libraries are **GLFW, GLAD, GLM** and **stb_image** — all bundled under permissive licenses so the project builds out‑of‑the‑box without system‑wide installs.

---

## Architecture & Methodology

### Data Sources

- Orbital periods & radii: NASA Planetary Fact Sheet
- Textures: [Solar System Scope](https://www.solarsystemscope.com/textures/) _(CC‑BY‑4.0)_

### Core Components

| Module         | Responsibility                           | Key APIs                    |
| -------------- | ---------------------------------------- | --------------------------- |
| `Simulation`   | Julian‑day clock, circular‑orbit math    | `<chrono>`, GLM             |
| `Renderer`     | VBO/VAO setup, shader management, skybox | OpenGL 3.3, GLAD            |
| `Input`        | GLFW callbacks → app commands            | GLFW                        |
| `TextRenderer` | Bitmap‑font rendering (HUD & help)       | FreeType (via stb_truetype) |
| `Assets`       | Texture & shader loading                 | stb_image, `<filesystem>`   |

---

## Known Limitations

- **Idealised orbits** – planets follow perfect circles in a single plane; eccentricity, inclination and axial tilt are ignored
- **Not‑to‑scale sizing** – planetary diameters and inter‑planet distances are intentionally exaggerated/compressed to keep everything visible in one view
- **Only one moon** – currently _only Earth’s Moon_ is rendered; no other natural satellites, dwarf planets or asteroid belt
- **Single light source** – simple Phong lighting without shadows, eclipses or atmospheric scattering
- **Preset trajectories** – planets do not exert gravity on each other; they move along predefined paths

## Screenshots and Demo

### App Screenshot

Here’s a screenshot of the app:

![Simulator Image](screenshots/screenshot.png)

### Demo GIF

Check out a short demo showing the app in action:

![Simulator Animation](screenshots/simulation.gif)
