# Final Project Proposal: TUI Drawing Program

## The Problem

I would like to create a drawing program that works in the terminal. 

Users will be able to:

- Draw various shapes on a canvas using their mouse, or by entering in coordinates.
- Specify the color of each shape.
- Undo shapes.
- Make multiple drawings and open/edit old drawings.
- Access the same drawings even after the program restarts.

## The Implementation

A **linked list** will act as the drawing itself (also the undo buffer). This linked list is implemented as a **stack** because users can only undo from, or add to, one end of the linked list. The linked list contains information about each shape in the drawing, in the order it was drawn. There will be a class for each type of shape (a.k.a. triangle, line, circle, etc) and its color and dimensions. Given one of these linked lists, the program should be able to recreate a drawing.

Each drawing stack will be converted into a parse-able text format and saved to a text file, so a function can read from the file and parse each drawing back into a linked list of shapes. If needed, I will try to find other ways of saving to and loading from files to make this process easier.

A **sorted list** contains the filenames of each drawing, sorted by timestamp. The user will be able to select a drawing from the sorted list within the TUI, or select a drawing by name (a search algorithm will be used for this). Every time the program starts, the sorted list is populated using one of the sorting algorithms we covered in class.

I will use the fxtui library to implement the TUI.
