# Parallel Matrix Multiplication using MPI

## Project Overview
This project implements parallel matrix multiplication using MPI (Message Passing Interface) in C. The workload is distributed among multiple processors to improve execution time and demonstrate the advantages of parallel computing.

## Technologies Used
- C Programming
- MPI (Message Passing Interface)
- Linux
- Parallel Computing

## Features
- Sequential matrix multiplication
- Parallel matrix multiplication using MPI
- Distributed row-wise computation
- Performance analysis using multiple processors
- Execution time comparison

## Experimental Setup
The program was tested using:
- 1 processor
- 2 processors
- 4 processors
- 5 processors
- 10 processors

Matrix size:
- N = 500 × 500

## Performance Results

| Processors | Execution Time (seconds) |
|---|---|
| 1 | 1.73 |
| 2 | 1.57 |
| 4 | 1.54 |
| 5 | 1.45 |
| 10 | 1.39 |

The results demonstrate that execution time decreases as the number of processors increases.

## MPI Concepts Used
- MPI_Send
- MPI_Recv
- MPI_Barrier
- MPI_Wtime
- Distributed computation

## Files Included
- MPI source code
- PDF project report
- PowerPoint presentation
- Execution screenshots

## Author
Mariam Namgaladze
CSC 429
