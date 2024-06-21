# cub3D

<p align="center">
  <img src="https://github.com/mcombeau/mcombeau/blob/main/42_badges/cub3de.png" alt="Cub3D 42 project badge"/>
</p>

Cub3D is a 42 school team project to create a dynamic view inside a 3D maze. Using the [MiniLibX library](https://github.com/42Paris/minilibx-linux), we must implement raycasting in the style of the famous [Wolfenstein 3D](http://users.atw.hu/wolf3d/) game, the first true FPS in videogame history.

## Prerequisites

Before compiling and running Cub3D, ensure you have the following installed:
- **Homebrew**: Install from brew if not already installed.
- **glfw framework**: Install using Homebrew:
```bash
  brew install glfw
```
## Installation

1. **Clone the repository**:
 ```bash
 git clone https://github.com/hael-mou/Cub3d.git
 cd Cub3d
```
2. Compile the project:
 ```bash
make
 ```

## Usage
 ```bash
./cub3D <map_file.cub>
```
`<map_file>` with the name of your map file (must have .cub extension).
