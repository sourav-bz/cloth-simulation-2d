# 2D Cloth Simulation in C++ with OpenGL

An OpenGL version of the real-time 2D cloth physics simulation using Verlet integration. This version uses OpenGL/GLFW/GLEW for modern graphics rendering while maintaining the same physics engine as the SDL version.

## Features

- **Same Physics Engine**: Uses identical Verlet integration and cloth physics as the SDL version
- **Modern OpenGL Rendering**: Hardware-accelerated rendering with OpenGL 3.3 Core Profile
- **Cross-Platform**: Works on Linux, Windows, and macOS with GLFW
- **Shader-Based Rendering**: Custom vertex and fragment shaders for efficient line rendering
- **Interactive Controls**: Same mouse interaction system as the original

## Project Structure

```
cloth-simulation-2d/
├── source/              # Original SDL version
├── source-opengl/       # OpenGL version
│   ├── MainGL.cpp       # Entry point for OpenGL version
│   ├── ApplicationGL.*  # OpenGL application class
│   ├── RendererGL.*     # OpenGL renderer implementation
│   ├── IRenderer.h      # Abstract renderer interface
│   ├── Cloth.*          # Cloth physics (adapted for IRenderer)
│   ├── Point.*          # Individual cloth points (shared)
│   ├── Stick.*          # Constraints between points (adapted for IRenderer)
│   ├── Mouse.*          # Mouse interaction (shared)
│   └── Vec2.h           # 2D vector math (shared)
├── Makefile             # SDL version build
├── Makefile-OpenGL      # OpenGL version build
└── README-OpenGL.md     # This file
```

## Building and Running

### Prerequisites

#### Ubuntu/Linux
```bash
# Install OpenGL development libraries
sudo apt update
sudo apt install libgl1-mesa-dev libglew-dev libglfw3-dev

# Ensure you have a C++ compiler
sudo apt install build-essential
```

#### Other Platforms
- **Windows**: Install GLFW, GLEW, and OpenGL libraries through vcpkg or manually
- **macOS**: Install dependencies via Homebrew: `brew install glfw glew`

### Build

```bash
# Clone/download the repository
git clone <repository-url>
cd cloth-simulation-2d

# Install dependencies (Ubuntu/Linux)
make -f Makefile-OpenGL install-deps

# Compile the OpenGL version
make -f Makefile-OpenGL

# Run the simulation
make -f Makefile-OpenGL run
# or directly
./bin/cloth-simulation-opengl
```

### Clean Build
```bash
make -f Makefile-OpenGL clean
```

## Controls

- **Mouse**: Click and drag to interact with the cloth
- **Mouse Wheel**: Adjust interaction radius
- **Right Click**: Break cloth constraints
- **Escape Key**: Exit the simulation
- **Close Window**: Exit the simulation

## Technical Details

### Renderer Architecture
- **IRenderer Interface**: Abstract base class allowing both SDL and OpenGL implementations
- **Shader-Based**: Uses modern OpenGL with vertex and fragment shaders
- **Orthographic Projection**: 2D coordinate system matching the original SDL version
- **Dynamic Drawing**: Efficient line and point rendering with dynamic vertex buffers

### Shared Components
The following components are shared between SDL and OpenGL versions:
- **Physics Engine**: Complete cloth simulation logic
- **Vector Math**: 2D vector operations
- **Mouse Input**: Interaction logic (adapted for GLFW)
- **Point System**: Individual particle physics

### OpenGL-Specific Components
- **RendererGL**: OpenGL 3.3 Core Profile renderer
- **ApplicationGL**: GLFW-based application management
- **Shader Management**: Vertex and fragment shader compilation and linking

## Performance

The OpenGL version offers several advantages:
- **Hardware Acceleration**: GPU-accelerated rendering
- **Scalability**: Better performance with larger cloth meshes
- **Modern Graphics**: Uses contemporary graphics APIs
- **Cross-Platform**: Consistent behavior across platforms

## Comparison with SDL Version

| Feature | SDL Version | OpenGL Version |
|---------|-------------|----------------|
| Rendering | Software-based | Hardware-accelerated |
| Performance | Good for small meshes | Excellent for all sizes |
| Dependencies | SDL2 | GLFW + GLEW + OpenGL |
| Platform Support | Excellent | Excellent |
| Code Complexity | Simpler | More complex (shaders) |

## Development Notes

- Both versions share the same physics engine for consistency
- The IRenderer interface allows easy switching between rendering backends
- GLFW provides more modern input handling compared to SDL events
- Shaders are embedded in the source code for simplicity

## Troubleshooting

### Common Issues
1. **OpenGL Context Creation Failed**: Ensure graphics drivers are up to date
2. **GLEW Initialization Failed**: Check OpenGL version compatibility
3. **Shader Compilation Errors**: Verify OpenGL 3.3+ support

### System Requirements
- OpenGL 3.3 or higher
- Modern graphics drivers
- C++17 compatible compiler
