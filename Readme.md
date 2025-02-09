# cub3D - 3D Maze Game Using Raycasting

## Overview
cub3D is a first-person 3D maze game inspired by the iconic Wolfenstein 3D. This project implements raycasting techniques to create a 3D graphical representation of a maze from a first-person perspective.

![Project Preview](preview.png)

## Features

### Core Features
- First-person perspective navigation
- Textured walls with different textures for each direction (North, South, East, West)
- Customizable floor and ceiling colors
- Smooth window management
- Map parsing from configuration files

### Controls
- `W` - Move forward
- `S` - Move backward
- `A` - Strafe left
- `D` - Strafe right
- `←` - Look left
- `→` - Look right
- `ESC` - Exit game

## Installation

### Prerequisites
- GCC compiler
- Make
- MinilibX library
- Math library

### Building
1. Clone the repository:
```bash
git clone https://github.com/yourusername/cub3D.git
cd cub3D
```

2. Compile the project:
```bash
make
```

3. Clean object files (optional):
```bash
make clean
```

4. Full clean (objects and executable):
```bash
make fclean
```

5. Rebuild:
```bash
make re
```

## Usage

Run the program with a map file:
```bash
./cub3D maps/example.cub
```

### Map Configuration File (.cub)
The map file must include:

1. Texture paths:
```
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture
```

2. Colors:
```
F R,G,B    # Floor color
C R,G,B    # Ceiling color
```

3. Map layout:
```
111111111
100000001
100N00001
100000001
111111111
```

Map symbols:
- `0` - Empty space
- `1` - Wall
- `N/S/E/W` - Player spawn position and orientation

### Map Rules
- Must be enclosed by walls
- Only valid characters: 0, 1, N, S, E, W
- One player spawn position only
- Map must be the last element in the configuration file

## Error Handling
The program includes comprehensive error checking for:
- Invalid map configurations
- Missing textures
- Invalid colors
- Map validation
- Memory management
- File operations

## Project Structure

```
cub3D/
├── src/
│   ├── main.c
│   ├── parser/
│   ├── raycasting/
│   └── utils/
├── includes/
├── textures/
├── maps/
├── Makefile
└── README.md
```

## Technical Details

### Libraries Used
- MinilibX for graphics rendering
- Math library for raycasting calculations
- LibFT (custom library) for utility functions

### Implementation Details
- Raycasting algorithm for 3D perspective
- DDA (Digital Differential Analysis) for ray calculations
- Event handling for smooth user interaction
- Texture mapping for wall rendering

## Contributing
1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a new Pull Request

## License
This project is part of the 42 School curriculum and is for educational purposes.

## Acknowledgments
- Inspired by Wolfenstein 3D
- 42 School for the project requirements
- MinilibX documentation and community