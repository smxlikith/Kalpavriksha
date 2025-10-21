# Sonar Image Processing (Matrix Rotation & Smoothing Filter)

This is a command-line program in **C** that simulates sonar image processing used for whale movement tracking. The program performs the following operations on a randomly generated **N×N matrix** of sonar intensity values:

1. **Matrix Generation**: Generates a random matrix of intensity values between 0 and 255.
2. **90° Matrix Rotation (In-Place)**: Rotates the matrix 90° clockwise using pointer manipulation.
3. **3×3 Smoothing Filter (In-Place)**: Applies a 3×3 smoothing filter in-place on the rotated matrix.

## Features

- **Matrix Generation**: Create a random N×N matrix with sonar intensity values between 0 and 255.
- **Matrix Rotation**: Rotate the matrix 90° clockwise in-place using pointer arithmetic (no additional memory).
- **3×3 Smoothing Filter**: Smooth the rotated matrix by replacing each cell's value with the average of itself and its valid neighbors.

## Usage

### Compile

To compile the program, run the following command in the terminal:

```bash
gcc sonarImageProcessing.c -o sonarImageProcessing
```

### Run

After compilation, you can run the program using:

```bash
./sonarImageProcessing
```
