# 2D Cloth Simulation in C++ with SDL

A real-time 2D cloth physics simulation using Verlet integration, implemented in C++ with SDL2 for cross-platform graphics.

## Tutorial

Read the tutorial, where the code and all the underlying theory is explained in great depth at https://pikuma.com/blog/verlet-integration-2d-cloth-physics-simulation

## Building and Running

### Ubuntu/Linux

#### Prerequisites
```bash
# Install SDL2 development libraries
sudo apt update
sudo apt install libsdl2-dev

# Ensure you have a C++ compiler
sudo apt install build-essential
```

#### Build
```bash
# Clone/download the repository
git clone <repository-url>
cd cloth-simulation-2d

# Compile the project
make

# Run the simulation
make run
# or
./bin/cloth-simulation
```

#### Clean Build
```bash
make clean
```

### Other Platforms

For Windows or other platforms, you'll need to:
1. Install SDL2 development libraries for your platform
2. Create appropriate build configuration (CMake, Visual Studio, etc.)
3. Link against SDL2 libraries

## Controls

- **Mouse**: Click and drag to interact with the cloth
- **Close Window**: Exit the simulation

## Project Structure

```
cloth-simulation-2d/
├── source/           # Source code files
│   ├── Main.cpp      # Entry point
│   ├── Application.* # Main application class
│   ├── Cloth.*       # Cloth physics simulation
│   ├── Point.*       # Individual cloth points
│   ├── Stick.*       # Constraints between points
│   ├── Mouse.*       # Mouse interaction
│   ├── Renderer.*    # SDL2 rendering
│   └── Vec2.h        # 2D vector math
├── obj/              # Build artifacts (created during build)
├── bin/              # Compiled executable (created during build)
└── Makefile          # Build configuration
```

## Features

- Real-time cloth physics simulation using Verlet integration
- Interactive mouse controls to manipulate the cloth
- Optimized for Linux/Ubuntu development
- Efficient constraint-based physics system
