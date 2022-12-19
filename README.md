# Final Project: Cubist Drawing Program

![image](https://user-images.githubusercontent.com/10780322/208482624-f1b9bec0-1a7a-441b-8cdb-1e48ca785710.png)


[Report](https://docs.google.com/document/d/1vcBDju4i5s_2xp2D4whaMZfoYne_WN_bA0_87-YG19k/edit?usp=sharing)

## Instructions for Professor

First time build:
```
mkdir build
cd build
cmake ..
```

To run the program:
```
make
./drawing
```

**Warning:** The buttons on the TUI are very sensitive and may accidentally click multiple times when you only mean to click them once.

I've prepopulated the `drawings` directory with example files. You can view them by selecting them in the menu and clicking "Load", or by typing in the name of a file in the Filename field and clicking "Load".

To draw a square, enter the coordinates in the "Point [number] [axis]" fields, select a color, then click "Draw".

To undo or redo, click "Undo" or "Redo".

The "Filled"/"Empty" toggle renders the squares as either solid or empty blocks.

To save a new drawing, type in a name and click "Save". Alternatively, you may save on top of an existing file by selecting it in the menu, or by typing its name, and clicking "Save".
