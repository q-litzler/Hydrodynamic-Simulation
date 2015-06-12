#MOD1

MOD1 is an hydrodynamic simulation written in C++ and using OpenGL. It parses a .mod1 map file to interpolate a relief on which water will flow in different scenarios. This project was written within the context of undergraduate studies in computer science over the course of three weeks, by a team of two.

#Source tree

`incs/`
Contains header files related to libraries (GL, GLM, GLFW) and source files.

`lib/`
Contains GLEW and GLFW3 static libraries.

`srcs/`
Contains the C++ source code.

`maps/`
Contains a set of maps used by the programm.

#Configuration

*OpenGL 3.3* or greater is required for this project to run. It is currently set up to use OpenGL 4.1, but you can always change it to match your hardware by editing the following lines:

*incs/Define.hpp*

```
# define GL_MAJOR					4
# define GL_MINOR					1
```

This programm was tested solely on `OSX` machines, but should be compatible with `UNIX` operating systems. You can always contact us for support, but keep in mind that this piece of software was not designed with cross-platform compatiblity as a requirement.

Depending on your graphical hardware, you might experience slowdowns when using the "rain" scenario. Decrease or increase the numbers of instances editing this line:

*incs/Define.hpp*

```
# define MAX_INSTANCES				17000
```

Recent graphical hardwares can handle up to millions of instances.

#Usage

**Makefile commands**

`make` or `make all`

Compiles and link the sources.

`make clean`

Clean object files.

`make fclean`

Calls *make clean* and delete binary files.

`make re`

Calls *make fclean* and *make all*.

**Start the programm**

`./mod1 scenario maps`

**Available scenarios:**

`flood`: Waters flood the scene from all four borders.

`waves`: A gentle wave comes from one border of the scene and progressively covers the terrain.

`rain`: Strong precipitations.

`drain`: Withdrawal of waters from all four borders.

`tsunami`: A giant wave crashes the scene.


**Maps**

Specify a path to a map file. Map file should end with .mod1 extension and should have the following format:

#Create map file

*Resolution*

`width:<100:2560> height:<100:1440>`

*Grid*

`col:<20:3000> row:<20:3000>`

*Height Map*

`x:<0:col> y:<0:> z:<0:row>`

You can add as many height points as you like. As we work in a three dimensional space, the y coordinate indicates the actual height.

Feel free to create your own map and to share it on this github repository.

#Licence:

The MIT License (MIT)

Copyright (c) [2015] [Paride BROGGI & Quentin LITZLER]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


