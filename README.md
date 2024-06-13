C++ Particle Simulator (particle-simulator)  
===========================
[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)  
This project is a particle simulator implemented in C++. It simulates the behavior of particles under various forces and constraints.  

Background   
===========================
This project serves as a learning platform for me, focusing on the intersection of object-oriented programming, data structures and algorithms, memory optimization, particle physics simulations, and various other concepts. It allows me to apply theoretical knowledge to a real-world problem, gaining practical experience in these areas. The project is intended to be a stepping stone for future projects that leverage these concepts, and also to be used directly as a particle simulator in other projects.    

It leverages several core concepts and technologies, including:

- Object-Oriented Programming: The simulator is designed using an object-oriented approach to model particles, forces, and interactions.

- Data Structures: The project employs quad trees for efficient collision detection, a fundamental data structure used in spatial partitioning.

- Algorithms: Verlet integration, a well-regarded algorithm for numerical simulation of motion, is used for accurate and stable particle movement.

- SFML Library: The SFML (Simple and Fast Multimedia Library) is used for the rendering of the particles.  

Intellectual Provenance:  
-------
This project draws inspiration from [VerletSFML](https://github.com/johnBuffer/VerletSFML/tree/3ba304d83cd8790732cd2de88802874fde8f606d), which also employs Verlet integration for particle simulation. However, this project takes a different approach to collision detection optimization, utilizing quad tree spatial partitioning for greater efficiency.

Features
=======
This particle simulator offers:  
- Customizable Particles: Simulate multiple particles with adjustable properties like position, velocity, radius, and color.

- Realistic Collisions.

- Accurate Physics: Simulate gravity, mass, and air resistance using Verlet integration for stable and realistic particle movement.

- Interactive Control: Add and remove particles, and modify simulation parameters.

Install  
=======
Make sure you have the following installed:  
- A C++ compiler (e.g., g++, clang)  
- [SFML](https://www.sfml-dev.org/) development library  

Run Project
===========================
Live:
-------
*coming soon :P*  

Locally:
------
Run the following commands in your terminal to build the program with CMake

- `mkdir build`

- `cd build`

- `cmake ..`

- `make`

- `./ParticleSimulator`

Future Development
=======
This project is still under development, and several enhancements are planned:  

1. Multithreading:  

- Goal: Implement multithreading to improve performance and enable the simulation of a larger number of particles.
- Rationale: Multithreading allows the simulation to take advantage of multiple CPU cores, significantly increasing the number of particles that can be handled simultaneously. This will lead to more complex and visually impressive simulations.  

2. Quad Tree Optimization:  

- Goal: Further optimize the quad tree data structure for collision detection, specifically focusing on techniques like cache optimization. This will enable the simulation of a larger number of particles.
- Rationale: While quad trees are efficient for collision detection, further optimization can improve performance. Cache optimization aims to reduce memory access times, leading to faster collision checks.  

Contributions
===========================
Contributions and suggestions are always welcome! Feel free to:

- Open an issue: Report bugs, request features, or discuss ideas.
- Submit a pull request: Contribute code improvements or new features.  

For any questions or feedback, you can reach me at kristan.nagassar@gmail.com. I'll do my best to respond as promptly as possible :D

License
======
UNLICENSED