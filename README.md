# Magshimim Movie Maker

Desktop application in C for creating and playing frame-by-frame animations. You load images, set how long each one displays, reorder them, and hit play. Have options to save and load projects from a file.

The frames are stored in a custom linked list. Each node holds the frame name, image path, and duration in milliseconds. Rendering is handled by Raylib which opens a window and draws each frame as a texture. Project files are plain text, one frame per line, comma-separated, parsed with strtok.



This project was built as a final project in Magshimim, an Israeli non-profit tech education program that teaches programming to high school students. It was made to practice real programming skills like dynamic memory, data structures, file I/O, and working with an external library.

This repo is a backup uploaded to GitHub after finishing the project, to save it and have it as a portfolio piece.
