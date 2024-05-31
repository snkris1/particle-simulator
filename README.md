C++ Particle Simulator
===========================
This project is a particle simulator implemented in C++ using the SFML library. It visually simulates the behavior of particles under various forces and constraints.

Features: 
===========================
Particle System: The simulator supports a system of multiple particles, each with customizable properties such as: Position, Velocity, Radius, Color

Collision Detection: Particles can collide with each other and with the boundaries of the simulation area. Efficient collision detection is achieved using a quad tree for spatial partitioning.

Realistic Physics: The simulator can simulate Gravity, Mass and Air resistance. Verlet integration is used to integrate Newton's equations of motion for accurate and stable particle movement.

Interactive Controls: Users can interact with the simulation through: Adding or removing particles and Changing particle properties

How to Run:
===========================
Dependencies: Make sure you have the following installed: A C++ compiler (e.g., g++, clang) and SFML development library

Compilation: (run the following commands in your terminal (without the arrows) to build the program with CMake)

-> mkdir build

-> cd build

-> cmake ..

-> make

About:
===========================
This project was developed to further my understanding of C++.

Contributions:
===========================
Contributions and suggestions are welcome! Feel free to open an issue or submit a pull request.