# ICG_A1
Intermediate Computer Graphics Assignment 1

The movement of the camera is as follows: 

  W - Forward
  A - Left
  S - Backward
  D - Right
  Q - Up
  E - Down

Pausing the spinning can be done by pressing the space key. Just a warning, it's a little janky sometimes, but it generally works. 

Changing the view modes of the assets are done with the following keys:

  1 - No lighting
  2 - ambient lighting only
  3 - specular lighting only 
  4 - specular and rim lighting
  5 - ambient, specular, and rim lighting
  6 - toggle diffuse warp
  7 - toggle specular warp
  8 - toggle colour grading warm
  9 - toggle colour grading cool
  0 - toggle colour grading custom (greyscale)

For some points regarding these toggles: the specular highlights are minimal due to the texturing, but they function properly; the math for the rim lighting appears correct, with the issue more likely lying in the objects and their meshes; functions 6 through 0 don't produce the results, however the framework for it to be implemented is there, with the key presses still being toggles, just toggling nothing. 
Also, while the colour grading post-processing isn't implemented, we included look-up tables in the event that we could get it to be functional on time, located in /Assets/LUTs/, with all three being there with all the files provided when exported from Photoshop. 

On that note, everything needed to run the solution should be included without needing to install the engine, with the libraries being included in the Git repository. If any issues arise and you're feeling charitable, let us know and we'll do our best to fix the issue and have it running. 

----

All assets shown were created for our project "Primordial" by Carter Menary, and were allowed for use by the team. 