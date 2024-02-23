# Evolution Game Engine

A simple and lightweight handcrafted game engine in C++ with python bindings. 
Mostly a personal sandbox to experiment with 3-D rendering.

### Source Structure
```
dep/ - many project dependencies
example/ - an example c++ project that uses Evolution Game Engine
lib/ - the actual game engine library
python/ - the python bindings for the game engine
```

### Dependencies
Most dependencies are packaged with this repository.
Only Boost and glew must be installed to build.
Evolution Game Engine depends on other C++ libraries:
 - imgui: for example frontent. Packaged in `dep/`.
 - eigen: packaged in `dep/`.
 - [color-console](https://github.com/aafulei/color-console) for colored console output, included in `dep/`.
 - stb_image: for png loading, packaged in `dep/`.
 - glfw: for window creation. Packaged as a submodule in `dep/`.
 - assimp: for asset loading. Packaged as a submodule in `dep/`.
 - boost: for filesystem, unit testing, and python module creation. Must be built and installed on the target system.
 - glew: for opengl extention wrangling. Must be installed on the target system.

### Build instructions
Once all dependencies are installed, use CMake to create projects. Currently only windows projects are supported. Plans
to support Linux will come in the future.
```
$ git clone git@github.com:bndkr/evolution.git
$ cd evolution
$ mkdir _bld
$ cmake -B _bld
$ cmake --build _bld --target all_build --config release
```

Please create an issue for support. Thanks!
