#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MASTER 0
#define TAM 3000

int main(int argc, char** argv) {

    int *vet;
    int *recebido;

    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    //printf("Hello from rank %d out of %d on %s\n", rank, size, hostname);

    int chunk = TAM / size;

    if (rank == MASTER) {
        vet = malloc(sizeof(int) * TAM);
        for (int i = 0; i < TAM; i++) {
            vet[i] = 1;
        }
    } 
    
    recebido = malloc(sizeof(int) * chunk);
    

    MPI_Scatter(vet, chunk, MPI_INT, recebido, chunk, MPI_INT, MASTER, MPI_COMM_WORLD);

    int soma = 0;

    // Corrigido: Somar os valores do vetor recebido
    for (int i = 0; i < chunk; i++) {
        soma += recebido[i];
    }

    if (rank == MASTER) {
        int soma_total = soma;
        int recebido;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&recebido, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            soma_total += recebido; // Soma os valores recebidos dos outros processos
        }
        printf("Soma total: %d\n", soma_total);
    } 
    else {
        MPI_Send(&soma, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
        // Envia a soma parcial para o processo MASTER
    }

    MPI_Finalize();
    return 0;
}

