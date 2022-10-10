# GLFW-Engine

![Sample](docs/sample.png)
Wow, what an amazing image :)

Game Engine Testing in cpp with GLFW + GLEW and some other stuff OpenGL ig?

A Game Engine designed in C++ using the GLFW and GLEW libraries

- uses `OpenGL`
- includes:
  - `glm` math library
  - `stb` image loading header file
  - `glfw` header files
  - `gl` glew header files

## Features?

As of commit: `d9a69fad5977e4cfb47c4e6db7ac41d7b44651fc`, gameobjects have been implemented but none of it is completed nor finished so it hasn't been applied in the code yet.

The features:

- texture loading
- vertex array creation and handling (vertex buffers and index buffers)
- keyboard and mouse input
- window creation/deletion
- framebuffers
- shaders
- started component system

What can you do?:

- you can use `WASD` to move camera and `SHIFT` + `SPACE` to move camera up and down

## File Structure

- `engine`: the engine
  - `.`: the main files (the engine, input, time, utils...)
  - `mesh`: vertex buffer stuff
  - `graphics`: graphics objects (shaders, textures..)
  - `handler`: mesh + graphics handlers
  - `audio`: to be added (contains audio OpenAL stuff?)

## Compilation

You don't :)

Just kidding;

### Both use G++/Gcc/GNU? idk man just that thing

There are two files you can use for compilation:

1. `compile.bat`: compiles on windows
   - you can change it if you want
2. `macbuild.txt`: should contain the compilation command for mac build
   - help required!

## Debug

One file, not too sure how it works tho

1. `debug.bat`: the debug file for WINDOWS
   - uses gdb
   - when you call command, press `c + enter`
   - then enter `start + enter`
   - to continue, press `c` each time

Only runs on windows becuase I have no idea how to use on MAC
