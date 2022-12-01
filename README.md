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

### Environment Setup
---------------------------------------------------------------------------
### Windows
---------------------------------------------------------------------------

I am using the MSYS2 mingw 64-bit g++ compiler for installation of libraries and such.


To install libraries in msys2

```
pacman -S mingw-w64-x86_64-glew mingw-w64-x86_64-glfw mingw-w64-x86_64-stb mingw-w64-x86_64-freetype
```

For environment variables, locations to add to path

```
C:\msys64\mingw64\bin

C:\msys64\usr\bin
```

### Linux
---------------------------------------------------------------------------

I have tested this both on WSL and a physical laptop.

In an Arch based distro run the following command to install libraries

```
sudo pacman -S glew glfw stb freetype2
```

Other distros should have these libraries available too though I have not tested on them.

### Build
---------------------------------------------------------------------------
The binaries will be placed in the bin directory

To compile the Engine
```
cd Engine
python builder.py
```
To compile the Application
```
cd Game
python builder.py
```

To run the Application
```
cd Game
python builder.py -r
```
It is important to be in the Game directory because of how the engine library is linked. This is not an issue in Windows. If you want to change this, edit the parameters in the build script.

To get help on the build script run

```
python builder.py -h
```
or
```
python builder.py --help
```