# Student Performance Analyzer

This is a console-based program in **C** that accepts student details and evaluates their academic performance based on marks obtained in three subjects.
It calculates total marks, average marks, assigns a grade, and displays a performance pattern using stars (`*`) based on the grade.

## Features

- Store student details using a `struct`: Roll Number, Name, Marks in 3 subjects.
- Calculate **Total Marks** and **Average Marks** using arithmetic operators.
- Assign **Grade** based on average marks:

| Average | Grade |
| ------- | ----- |
| ≥ 85    | A     |
| ≥ 70    | B     |
| ≥ 50    | C     |
| ≥ 35    | D     |
| < 35    | F     |

- Display a **Performance Pattern** of stars based on the grade (A: 5, B: 4, C: 3, D: 2).
- Skip printing the star pattern if average is below 35 using `continue`.
- Supports **multiple students** input using loops.
- Demonstrates **functions** for calculations, **recursion** to print roll numbers, and variable scope.

## Usage

### Compile

```bash
gcc Assignment-3/3.c -o student_perf
```

### Run

```bash
./student_perf
```
