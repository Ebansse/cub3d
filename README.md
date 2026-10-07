*This project has been created as part of the 42 curriculum by ebansse and cguinot.*

# cub3D

A first-person 3D maze renderer in C, inspired by *Wolfenstein 3D*. It uses **raycasting** with the MiniLibX library to turn a 2D grid into a textured 3D view you can walk around in real time.

## Controls

| Key | Action |
|---|---|
| `W` / `S` | move forward / backward |
| `A` / `D` | strafe left / right |
| `←` / `→` | turn the camera |
| `Esc` or the close button | quit |

Keys can be held down for smooth movement, and the player can't walk through walls.

## Scene file (`.cub`)

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 23,23,32
C 200,200,200

111111
100101
1000N1
111111
```

- `NO` / `SO` / `WE` / `EA`: the wall texture for each direction (XPM files)
- `F` / `C`: floor and ceiling colours (R,G,B from 0 to 255)
- Map: `1` = wall, `0` = empty space, `N` `S` `E` `W` = player start and facing direction, and spaces are allowed outside the map

The parser rejects the file with `Error` and an explanation when, for example: the extension isn't `.cub`, a texture is missing or can't be opened, an identifier appears twice, a colour is out of range, the map isn't closed, there are zero or several players, or the map contains an unknown character.

## How it works

The camera has a 60° field of view. For each of the 2000 columns of the window, a ray leaves the player's position at a slightly different angle and moves forward in small fixed steps until it enters a wall cell. The distance travelled, multiplied by the cosine of the angle between the ray and the view direction to remove the fish-eye effect, sets the height of the wall slice to draw. The direction the ray came from picks the N/S/E/W texture, and the exact hit position picks the texture column. The floor and ceiling are filled with the colours from the scene file.

## Build & run

Requires Linux with X11 (`libx11-dev`, `libxext-dev`, `libbsd-dev`). MiniLibX is bundled in `mlx/`.

```bash
make
./cub3D working.cub
```

## Project structure

| Path | Role |
|---|---|
| `main.c` | entry point, file and map checks |
| `parser/` | `.cub` parsing: textures, colours, map, closure checks |
| `raycasting/` | ray casting, distance correction and frame rendering |
| `player/` | texture loading, player setup and movement |
| `free.c` | cleanup |
| `textures/` | XPM wall textures |
| `mlx/` | MiniLibX |
