# EM-Sim
A simple electromagnetic field simulator that solves Maxwell's curl equations using the finite difference time domain (FDTD) method and the Yee Grid. Written in C++ and OpenGL.

The images below show a hard-sourced plane wave oscillating in the x component of the electric field. 

![image](/screenshots/001.png)

![image](/screenshots/002.png)

![image](/screenshots/003.png)

# Issues to Address
Absorbing Boundary Conditions - Currently, waves are reflected off the boundary of the grid, causing nonphysical reflections. Adding an ABC like a Perfectly Matched Layer (PML) should fix this issue. 

Subcell Models - The parabolic antennas shown in the image above distort the wave due to the coarseness of the grid.  A subcell model for the antenna may remedy this issue. 

# Build Instructions
(Windows)

Required: g++ and mingw

Run ````mingw32-make```` in cmd in the root directory. 

# References
Computational Electrodynamics, Taflove et al., 2005

Finite Difference Method, Yee Algorithm, Purdue ECE604 Lecture 37, Weng Cho Chew, 2020
