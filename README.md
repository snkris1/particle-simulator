C++ Particle Simulator (particle-simulator)  
===========================
[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)  
This project is a particle simulator implemented in C++ using the SFML library. It simulates the behavior of particles under various forces and constraints.  

Background   
===========================
This project serves as a learning platform for me, focusing on the intersection of object-oriented programming, data structures and algorithms, memory optimization, particle physics simulations, and various other concepts. It allows me to apply theoretical knowledge to a real-world problem, gaining practical experience in these areas. The project is intended to be a stepping stone for future projects that leverage these concepts, and also to be used directly as a particle simulator in other projects.    

It leverages several core concepts and technologies, including:

- Object-Oriented Programming: The simulator is designed using an object-oriented approach to model particles, forces, and interactions.

- Data Structures: The project employs quad trees for efficient collision detection, a fundamental data structure used in spatial partitioning.

- Algorithms: Verlet integration, a well-regarded algorithm for numerical simulation of motion, is used for accurate and stable particle movement.

- SFML Library: The SFML (Simple and Fast Multimedia Library) is used for the rendering of the particles.  

Intellectual Provenance  
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

How to Run Locally:
===========================
Compilation: (run the following commands in your terminal (without the arrows) to build the program with CMake)

-> `mkdir build`

-> cd build

-> cmake ..

-> make

-> ./ParticleSimulator

Contributions:
===========================
Contributions and suggestions are welcome! Feel free to open an issue or submit a pull request.