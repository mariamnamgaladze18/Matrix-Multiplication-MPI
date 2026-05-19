#include <stdio.h>
#include <mpi.h>

#define N 500
#define TAG 0

int main(int argc, char *argv[]) {

    int rank, size;
    int A[N][N], B[N][N], C[N][N];
    int rowA[N], rowC[N];
    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (N % size != 0) {
        if (rank == 0)
            printf("Number of processors must divide N\n");
        MPI_Finalize();
        return 0;
    }

    int rows = N / size;

    if (rank == 0) {

        printf("Parallel Matrix Multiplication using %d processors\n", size);
        printf("Matrix size: %d x %d\n\n", N, N);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i + j + 1;
                B[i][j] = i == j ? 1 : 0;
                C[i][j] = 0;
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    if (rank == 0) {

        for (int p = 1; p < size; p++) {

            MPI_Send(B, N*N, MPI_INT, p, TAG, MPI_COMM_WORLD);

            for (int r = 0; r < rows; r++) {
                int rowIndex = p * rows + r;
                MPI_Send(A[rowIndex], N, MPI_INT, p, TAG, MPI_COMM_WORLD);
            }
        }

        for (int r = 0; r < rows; r++) {

            int rowIndex = r;

            for (int j = 0; j < N; j++) {
                C[rowIndex][j] = 0;
                for (int k = 0; k < N; k++)
                    C[rowIndex][j] += A[rowIndex][k] * B[k][j];
            }
        }

        for (int p = 1; p < size; p++) {
            for (int r = 0; r < rows; r++) {
                int rowIndex = p * rows + r;
                MPI_Recv(C[rowIndex], N, MPI_INT, p, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
    }
    else {

        MPI_Recv(B, N*N, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int r = 0; r < rows; r++) {

            MPI_Recv(rowA, N, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int j = 0; j < N; j++) {
                rowC[j] = 0;
                for (int k = 0; k < N; k++)
                    rowC[j] += rowA[k] * B[k][j];
            }

            MPI_Send(rowC, N, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    if (rank == 0) {
        printf("Execution Time: %f seconds\n", end - start);
        printf("Result check: C[0][0] = %d, C[N-1][N-1] = %d\n",
               C[0][0], C[N-1][N-1]);
    }

    MPI_Finalize();
    return 0;
}



