# cub3D
This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way (May 2022).

## Table of contents
* [Introduction](#introduction)
  * [Allowed functions](#allowed-functions)
  * [Description](#description)
  * [General rules](#general-rules)
  * [Config-file](#config-file)
* [Approach](#approach)
* [Prerequisites](#prerequisites)
* [How to launch](#how-to-launch)
* [How to play](#how-to-play)
* [Examples](#examples)
* [Resources](#resources)
* [Notes](#notes)


## Introduction
###### <p align="right">Next: [Approach](#approach)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
### Allowed functions
open, close, read, write, printf, malloc, free, perror, strerror, exit

All functions of the math library.

Aditionally all functions of the [MinilibX](https://github.com/42Paris/minilibx-linux) can be used.

### Description
This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.

### General rules
* As a first argument, the program takes a [config-file](#config-file).
* The management of the window (changing to another window, minimizing, etc.) must remain smooth.
* Depending on which geographic direction a wall is facing (N, S, E, W), it must display a diffeen wall texture.
* The program must be able to set the colour of the floor and the ceiling to two different colours.
* Pressing ESC or clicking on the red cross on the window's frame must close the window and quit the program cleanly.

### Config-file
* The config file depicts a scene description for the game and must end with the ```.cub``` extension.
* The map must be composed of only 6 possible characters: ```0``` for an empty space, ```1``` for a wall, and ```N```,```S```,```E``` or ```W``` for the player’s start position and spawning orientation.
* The map must be surrounded by walls.
* Except for the map content, each type of element can be separated by one or more empty line(s).
* Except for the map content, which always has to be the last, each type of element can be set in any order in the file.
* Except for the map, each type of information from an element can be separated by one or more space(s).
* The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle. You must be able to parse any kind of map, as long as it respects the rules of the map.
* The elements to configure your game are:
  * ```NO``` = NORTH texture
  * ```SO``` = SOUTH texture
  * ```WE``` = WEST testure
  * ```EA``` = EAST texture
  * ```F``` = FLOOR colour (RGB values)
  * ```C``` = CEILING colour (RGB values)
* Each elements (except the map) first information is the type identifier (composed by one or two character(s)), followed by all specific informations for each object in a strict order such as:
  * ```NO ./path_to_the_north_texture```
  * ```F 220,100,0```

## Approach
###### <p align="right">Next: [Prerequisites](#prerequisites)&emsp;Previous: [Introduction](#introduction)&emsp;&emsp;[[Contents](#table-of-contents)]</p>

xxx

## Prerequisites
###### <p align="right">Next: [How to launch](#how-to-launch)&emsp;Previous: [Approach](#approach)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
### Linux (tested on Ubuntu 20.04.3 LTS)
* gcc (```sudo apt-get install gcc```)
* make (```sudo apt-get install make```)
* X11 include files (```sudo apt-get install xorg```)
* XShm extension must be present (```sudo apt-get install libxext-dev```)
* Utility functions from BSD systems - development files (```sudo apt-get install libbsd-dev```)

### MacOS (tested on macOS Catalina 10.15.7)
* gcc (```sudo apt-get install gcc```)
* make (```sudo apt-get install make```)

## How to launch
###### <p align="right">Next: [How to play](#how-to-play)&emsp;Previous: [Prerequisites](#prerequisites)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
Compile the program via the Makefile by using ```$ make``` in the root directory of the repository.

Run it by giving it the path to the config-file as argument (in this case the file "example.cub" within the directory "maps"):

```
$ ./cub3D maps/example.cub
```

For the required config-file format see: [Config-file](#config-file)

## How to play
###### <p align="right">Next: [Example](#example)&emsp;Previous: [How to launch](#how-to-launch)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
xxx. You can create your own map, by creating a [config-file](#config-file).

### Keyboard
```W``` - Move forwards

```A``` - Move left

```S``` - Move backwards

```D``` - Move right

```ARROW-LEFT``` - Turn left

```ARROW-RIGHT``` - Turn right

```SPACEBAR``` - Jump

```CONTROL``` - Toggle crouch

```SHIFT``` - Sprint

```E``` - Build wall

```Q``` - Destroy wall

```ESC``` - Exit game

### Mouse
```LEFT``` - Destroy wall

```RIGHT``` - Build wall

## Examples
###### <p align="right">Next: [Resources](#resources)&emsp;Previous: [How to play](#how-to-play)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
_Screenshot_
![screenshot](https://user-images.githubusercontent.com/80413516/171029396-45dc5b35-ee36-4ccf-a399-0f3a0195d7a1.JPG)

_Sample_
![cub3D](https://user-images.githubusercontent.com/80413516/171029219-92c13978-71cd-4cff-9a73-c07e66f62c53.gif)

## Resources
###### <p align="right">Next: [Notes](#notes)&emsp;Previous: [Example](#example)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
[MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) made by [hsmits](https://github.com/harm-smits) and @jvan-sni.

Images used from https://opengameart.org/ and https://www.seekpng.com/.

## Notes
###### <p align="right">Previous: [Resources](#resources)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
xxx
