#Intro

In this file, we will discuss algorithmic and architecural choices we made for this hydrodynamic simulation.
We will assume a general knowledge of OOP, C/C++ language and OpenGL of our readers.
We will not discuss every aspect of the source code, but rather focus on what's interesting in our eyes.

#Architecture

This programm revolves around a simply Model / View couple.
The Model class is in charge of building every elements needed by the View class in order to display the simulation.
To keep our files clean and of reasonable length, we chose to divide our Model into multiple classes, each one
being a component of the scene we are trying to render.

The division occurs following this logic:
To draw an independant OpenGL object, we need to create several buffers:
- Vertices buffer
- Elements buffer
- Colors buffer
- Normals buffer
- Positions buffer (for instances only)

Each of the following classes needs its own buffers, hence the separation: 

- Terrain
- Borders
- Water
- WaterBorders
- Drop

Diving the Model into smaller entities makes sense on many level, but causes one problem we still have to solve:
The model class stores a numbers of private attributes, initialized by the parser class or precomputed.
These attributes needs to be accessed by all the sub-divided classes, preferably without getters as it would be
too cumbersome.

Our solution:

```
class Model
{
	friend class Terrain;
	friend class Drop;
	friend class Water;
	friend class Borders;
	friend class WaterBorders;
	...
}
```

Using friend class has to be justified

