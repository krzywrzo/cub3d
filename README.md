# cub3D

A 3D raycasting game engine inspired by Wolfenstein 3D, developed as part of the 42 school curriculum.

## Description

cub3D is a minimalist 3D graphics project that implements a raycasting algorithm to render a pseudo-3D perspective view of a maze-like environment. Players can navigate through the map using keyboard controls and view textured walls with proper perspective rendering.

## Features

- Raycasting-based 3D rendering
- Textured walls with DDA (Digital Differential Analyzer) algorithm
- Keyboard-controlled player movement and rotation
- Map parsing and validation with flood-fill algorithm
- Linux-only build configuration

## Requirements

- Linux operating system
- GCC compiler
- Make
- X11 development libraries (`libxext-dev`, `libx11-dev`)
- MiniLibX graphics library (included in project)

## Installation

```bash
cd /path/to/cub3d
make
```

This will:
1. Compile the libft library
2. Compile the MiniLibX graphics library
3. Compile and link the cub3D executable

## Usage

```bash
./cub3D maps/valid_map.cub
```

Replace `map_file.cub` with a valid map file.

### Keyboard Controls

- **W** - Move forward
- **A** - Move left
- **S** - Move backward
- **D** - Move right
- **LEFT ARROW** - Rotate view left
- **RIGHT ARROW** - Rotate view right
- **ESC** - Close application

## Map Format

Map files must have a `.cub` extension and include:

- **R** - Screen resolution (e.g., `R 1920 1080`)
- **NO** - North texture path
- **SO** - South texture path
- **EA** - East texture path
- **WE** - West texture path
- **F** - Floor color (RGB format: `F 220,100,0`)
- **C** - Ceiling color (RGB format: `C 100,100,255`)
- **Map** - 2D map layout:
  - `0` - Walkable space
  - `1` - Wall
  - `N/S/E/W` - Player starting position and direction

### Example Map

```
R 1920 1080

NO textures/north.xpm
SO textures/south.xpm
EA textures/east.xpm
WE textures/west.xpm

F 220,100,0
C 100,100,255

1111111111111111111111111
1000000000000000000000001
10000N0000000000000000001
1000000000000000000000001
1111111111111111111111111
```

## Project Structure

```
cub3d/
├── src/              # Source code files
│   ├── main.c
│   ├── parsing.c
│   ├── game_init.c
│   ├── raycasting_*.c
│   └── ...
├── includes/         # Header files
│   ├── cub3d.h
│   └── parsing.h
├── libft/            # Custom C library
├── minilibx/         # Graphics library
├── textures/         # Texture files
├── maps/             # Map files
└── Makefile
```

## Compilation Details

- **Compiler Flags**: `-DLINUX=1` for Linux-specific features
- **Libraries Used**:
  - libft (custom C library functions)
  - MiniLibX (graphics rendering)
  - X11 (display server)
- **Optimization**: Compiled with `-g` for debugging support

## Code Standards

The project adheres to the **42 Norm**, which enforces:
- Maximum 80-character line length
- Maximum 25 lines per function
- Specific formatting and naming conventions
- Proper comment styling

## Validation

Map files are validated for:
- Proper file format and texture definitions
- Valid map characters
- Exactly one player starting position
- Enclosed map (surrounded by walls)
- No invalid character adjacency

## Errors

The program will exit with an error message if:
- Invalid or missing map file
- Malformed map or missing elements
- Player not properly placed
- Map not enclosed by walls

## License

School project - 42 network

## Author

- kwrzosek & szmadeja (42 students)
