/**
 Empty Juice Voxel: Complete minecraft rewrite by the Empty Juice Box Group.
 */

EJB aims to rewrite the popular voxel-based game minecraft using efficient
methods and the C++ language. In essence, to rid the world of dependencies
on Notch-code.

Collaborators:
* StructInf (A.K.A. xdot)
* Manearrior 
* Ckef       
* Barry

Structure of EJV
================

EJV consists of three basic parts:
1. Core library. The core holds the state of the simulation, provides a minimal API and is responsible for loading modules during runtime.
2. Modules. A module is a shared library that is loaded during runtime and enhances the simulation.
3. Launcher. The launcher is responsible for the initialization of the core and the game.

There are 4 module types:
1. Loader. A loader is responsible for correctly loading chunks from a file.
2. Generator. A generator is responsible for generating chunks based on certain properties.
3. UI. A UI module acts as an interface between the core and an external program, like a graphics backend or a remote instance of EJV.
4. Rule. A Rule module defines the interactions and the rules that govern the simulation.

Each rule module can register new objects of the following three primitve object types:
1. Block. A block is an axis-aligned box model.
2. Entity. An entity is a freeform model that possesses an orientation.
3. Item. An item is an abstract object that can be carried.

// TODO: Provide further insight into the structure of EJV
