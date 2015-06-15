#Hydrodynamic Simulation

![](screenshots/crater%20flood.png)

HDS is an hydrodynamic simulator written in C++ and using OpenGL. It parses a `.hds` map file to interpolate a landscape on which water will flow in different scenarios. This project was written within the context of undergraduate studies in computer science over the course of three weeks, by a team of two.

#Configuration

`OpenGL 3.3` or greater is required for this project to run. It is currently set up to use `OpenGL 4.1`, but you can always change it to match your hardware by editing the following lines:

*incs/Define.hpp*

```
# define GL_MAJOR					4
# define GL_MINOR					1
```

This programm was tested solely on `OSX` machines, but should be compatible with `UNIX` operating systems. You can always contact us for support, but keep in mind that this piece of software was not designed with cross-platform compatiblity as a requirement.

Depending on your graphical hardware, you might experience slowdowns when using the `rain` scenario. Decrease or increase the numbers of instances editing this line:

*incs/Define.hpp*

```
# define MAX_INSTANCES				17000
```

Recent graphical hardwares can handle up to millions of instances.

#Commands

During the simulation, if the scenario is not `rain`, you can press the following keys:

`arrow keys`: change the angle of the camera

`+`: zoom in

`-` zoom out

`v`: start draining the water out of the scene

`f`: restart the simulation as a 'flood' scenario

`w`: trigger a wave

#Usage

**Makefile commands**

`make` or `make all`

Compile and link the sources.

`make clean`

Clean object files.

`make fclean`

Call *make clean* and delete binary files.

`make re`

Call *make fclean* and *make all*.

**Start the programm**

`./hds scenario maps`

**Available scenarios:**

`flood`: Waters flood the scene from all four borders.

`waves`: A gentle wave comes from one border of the scene and progressively covers the terrain.

`rain`: Strong precipitations.

`drain`: Withdrawal of waters from all four borders.

`tsunami`: A giant wave crashes the scene.
**Maps**

Specify a path to a map file.

#Create map file

Map file should end with *.hds* extension and should have the following format:

*Resolution*

`width:<100:2560> height:<100:1440>`

*Grid*

`col:<20:3000> row:<20:3000>`

*Height Map*

`x:<0:col> y:<0:> z:<0:row>`

You can add as many height points as you like. As we work in a three dimensional space, the y coordinate indicates the actual height.

Feel free to create your own map and to share it on this github repository.

#Source tree

`incs/`
Contains header files related to libraries (GL, GLM, GLFW) and source files.

`lib/`
Contains GLEW and GLFW3 static libraries.

`srcs/`
Contains the C++ source code.

`maps/`
Contains a set of maps used by the programm.

#Licence:

[The MIT License (MIT)](http://opensource.org/licenses/MIT){:target="_blank"}
