#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char **argv) {

    //declaracion de las variables a utilizar
    int rank, size, *arregloDesordenado, *arregloOrdenado, *subArreglo, *subArregloMaster;

    int tamanio_arreglo = atoi(argv[1]);

    // para guardar la cantidad de elementos en cada subarreglo

    MPI_Init(&argc, &argv); //iniciamos MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //obtener identificador
    MPI_Comm_size(MPI_COMM_WORLD, &size); //obtener la cantidad de procesos

    int cantElementos = (int)(tamanio_arreglo/(size-1));
    printf("%d", cantElementos);
    printf("%d", size);

    if (rank == 0) {
        //CREACION DEL ARREGLO
        // reservamos el espacio para el arreglo a ordenar
        arregloDesordenado = malloc(sizeof(int) * tamanio_arreglo);

        //llenar el arreglo a ordenar aleatoriamente
        srand(time(NULL)); //inicializar la semilla aleatoria
        int i;
        for (i= 0; i < tamanio_arreglo; i++) {
            arregloDesordenado[i] = rand() % 100; //GENERA NUMEROS ALEATORIOS DEL 0 AL 99
        }
    }

    if (rank != 0){
        //reservamos espacio para el arreglo de cada proceso
        subArreglo = malloc(sizeof(int) * (cantElementos));
    }

    if (tamanio_arreglo % (size - 1) != 0) {
        //repartimos el arreglo entre todos los procesos
        //MPI_Scatter(arregloDesordenado, cantElementos, MPI_INT, subArreglo, cantElementos, MPI_INT, 0, MPI_COMM_WORLD);
        if (rank == 0){
            subArregloMaster = (int *)malloc(sizeof(int) * (tamanio_arreglo % (size-1)));
        }
    } else {
        //MPI_Scatter(arregloDesordenado, cantElementos, MPI_INT, subArreglo, cantElementos, MPI_INT, 0, MPI_COMM_WORLD);
    }

    //cada proceso ordena su arreglo
    int j;
    while ( j <= tamanio_arreglo/(size-1)) {
        if (subArreglo[j] > subArreglo[j + 1]) {
            subArreglo[j + 1] = subArreglo[j];
        }
    };
    int k;
    for (k = 0;k<=cantElementos; k++){
        printf("%d", subArreglo[k]);
    };
    MPI_Finalize();
};