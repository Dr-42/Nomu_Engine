# Nomu_Engine

This is a basic Game Engine using OpenGL. Most of it learned from https://learnopengl.com.

## Features
---------------------------------------------------------------------------

This Engine compiles and works on both Windows and Linux. This is made possible by my own build tool CppBuild. I never got the hang of Cmake and I don't know why my Makefiles werent very satisfying. So this is the result.

## Usage
---------------------------------------------------------------------------

### Dependencies
---------------------------------------------------------------------------
1. GLEW
2. GLFW
3. Freetype2
4. STB Image
5. GLM

### Environment Setup
---------------------------------------------------------------------------
### Windows
---------------------------------------------------------------------------

I am using the MSYS2 mingw 64-bit g++ compiler for installation of libraries and such.


To install libraries in msys2

```
pacman -S mingw-w64-ucrt-x86_64-glew mingw-w64-ucrt-x86_64-glfw mingw-w64-ucrt-x86_64-stb mingw-w64-ucrt-x86_64-freetype mingw-w64-ucrt-x86_64-glm
```

For environment variables, locations to add to path

```
C:\msys64\ucrt64\bin
```

### Linux
---------------------------------------------------------------------------

I have tested this both on WSL and a physical laptop.

In an Arch based distro run the following command to install libraries

```
sudo pacman -S glew glfw-x11 glm stb freetype2 pkg-config
```

On debian based 
```
apt install libglfw3-dev libglew-dev libstb-dev libglm-dev libfreetype-dev pkg-config
```

On a wayland system install the glfw-wayland library instead of the x11 one.

Other distros should have these libraries available too though I have not tested on them.

### Build
---------------------------------------------------------------------------
Install build tool
```
cargo install builder_cpp
```

The binaries will be placed in the bin directory

To compile the Engine 
```
$ builder_cpp -b
```

To run the Application
```
$ builder_cpp -r
```
It is important to be in the root directory because of how the engine library is linked. This is not an issue in Windows. If you want to change this, edit the parameters in the build script.

To get help on the build script run

```
$ builder_cpp -h
```
