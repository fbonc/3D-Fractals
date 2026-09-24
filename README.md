
# 3D Fractals

A real-time C++20 and OpenGL 3.3 raymarcher for the Mandelbulb, Menger sponge, Julia, Kleinian, and Mandelbox fractals. Use the Dear ImGui controls to switch fractals and adjust the camera, lighting, color, and distance-estimation settings while the scene renders.

<p align="middle">
<img width="400" alt="fractals" src="https://github.com/user-attachments/assets/690b1b4c-df3f-43cd-b777-707b9a525c74" />
</p>

## How it works

Each fragment shader casts a ray through a full-screen quad and samples the selected fractal's distance estimator. Over-relaxed sphere tracing advances the ray, while a hit threshold that grows with distance tracks roughly one pixel's width at the current depth. Nearby distance samples provide surface normals for lighting; background, coloring, and post-processing run in GLSL.

## Architecture

- **GLFW and glad** create the OpenGL context, load functions, and handle input. Eigen supports camera math.
- **AppController** runs the frame loop; **CameraController** and **UIManager** update the camera and ImGui controls.
- **GLSLManager** resolves `#include` directives across shader modules and hot-reloads changed files. **ShaderManager** compiles and links the resulting programs.
- **SceneRenderer** draws the full-screen quad and sends camera, fractal, and UI settings to the active shader.

The tracing method follows [*Enhanced Sphere Tracing* (Keinert et al., 2014)](https://diglib.eg.org/items/8ea5fa60-fe2f-4fef-8fd0-3783cb3200f0).

## Build and run

Requires CMake 3.20+, a C++20 compiler, an OpenGL 3.3-capable system, and internet access to fetch dependencies.

On macOS or Linux:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/fractals
```

On Windows with Visual Studio:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\fractals.exe
```
