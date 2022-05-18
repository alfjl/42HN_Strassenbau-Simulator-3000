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
* [Example](#example)
* [Resources](#resources)
* [Notes](#notes)


## Introduction
###### <p align="right">Next: [Approach](#approach)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
### Allowed functions
xxx

Aditionally all functions of the [MinilibX](https://github.com/42Paris/minilibx-linux) can be used.

### Description
This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.

### General rules
* xxx [config-file](#config-file)

### Config-file
* xxx

## Approach
###### <p align="right">Next: [Prerequisites](#prerequisites)&emsp;Previous: [Introduction](#introduction)&emsp;&emsp;[[Contents](#table-of-contents)]</p>

xxx

## Prerequisites
###### <p align="right">Next: [How to launch](#how-to-launch)&emsp;Previous: [Approach](#approach)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
###Linux (tested on Ubuntu 20.04.3 LTS)
* gcc (```sudo apt-get install gcc```)
* make (```sudo apt-get install make```)
* X11 include files (```sudo apt-get install xorg```)
* XShm extension must be present (```sudo apt-get install libxext-dev```)
* Utility functions from BSD systems - development files (```sudo apt-get install libbsd-dev```)

###MacOS (tested on macOS Catalina 10.15.7)
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

## Example
###### <p align="right">Next: [Resources](#resources)&emsp;Previous: [How to play](#how-to-play)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
_Sample of a game on the map "example.cub"_

xxx

## Resources
###### <p align="right">Next: [Notes](#notes)&emsp;Previous: [Example](#example)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
[MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) made by [hsmits](https://github.com/harm-smits) and @jvan-sni.

Images used from https://opengameart.org/ and https://www.seekpng.com/.

## Notes
###### <p align="right">Previous: [Resources](#resources)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
xxx
