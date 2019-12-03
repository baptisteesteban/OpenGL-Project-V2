# OpenGL Project V2

## Introduction

This project is a class project. It is the V2 because the first version of this prject was ill-designed and difficult to maintained.

The objective of this project is to simulate a shoal of fish in the sea. To do this, we use a geometry shader to design the fishes and a compute shader to compute the current position of the fishes.

## Command

### Camera

* up: move the camera to the up
* down: move the camera to the down
* left: move the camera to the left
* right: move the camera to the right
* z: move the camera to the front
* s: move the camera behind

## Build
```
cd path/to/the/project
mkdir build
cd build
cmake ..
make
```

This will generate the binary `fish_in_the_sea` and copy the shaders code source in the build directory such that the binary can be use in the build directory.