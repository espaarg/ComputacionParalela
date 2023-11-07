#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char **argv) {
    //declaracion de las variables a utilizar
    int rank, size, *arregloDesordenado, *arregloOrdenado, *subArreglo, *subArregloMaster;

    MPI_Init(&argc, &argv); //iniciamos MPI

    //Para que el usuario ingrese el tamaño del arreglo
    int tamanio_arreglo = atoi(argv[1]);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //obtener identificador
    MPI_Comm_size(MPI_COMM_WORLD, &size); //obtener la cantidad de procesos

    //para saber cuantos elementos tendrá cada sub arreglo (contando el master)
    int cantElementos = (int)(tamanio_arreglo/(size));
//    printf("%d \n", cantElementos);
//    printf("%d \n", size);


    //Verificar si el tamaño del arreglo ingresado es valido
    if (tamanio_arreglo % size != 0) {
        printf("La cantidad de elementos ingresada no es múltiplo de la cantida de nodos a utilizar");
        MPI_Abort(MPI_COMM_WORLD, 1); //abandonar la ejecución
    }

    //el master crea el arreglo y lo llena
    if (rank == 0) {
        // reservamos el espacio para el arreglo a ordenar
        arregloDesordenado = malloc(sizeof(int) * tamanio_arreglo);

        //llenar el arreglo a ordenar aleatoriamente
        srand(time(NULL)); //inicializar la semilla aleatoria
        int i;
        for (i= 0; i < tamanio_arreglo; i++) {
            arregloDesordenado[i] = rand() % 100; //GENERA NUMEROS ALEATORIOS DEL 0 AL 99 (colocar 1000 o mas para que los numeros aleatorios sean mayores)
        }
        //printf("Llegué a armar el arreglo \n");
    }

    //reservamos espacio para el arreglo de cada proceso (ACA NO ESTAMOS CONTANDO AL MASTER REVISAR)
    if (rank != 0){
        subArreglo = malloc(sizeof(int) * (cantElementos));
    }

    //repartimos el arreglo entre todos los procesos
    MPI_Scatter(arregloDesordenado, cantElementos, MPI_INT, subArreglo, cantElementos, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0){
        subArregloMaster = malloc(sizeof(int) * (tamanio_arreglo % (size-1)));
    }

   // MPI_Scatter(arregloDesordenado, cantElementos, MPI_INT, subArreglo, cantElementos, MPI_INT, 0, MPI_COMM_WORLD);


    //cada proceso ordena su arreglo    VER SI PONER ESTO COMO UNA FUNCION FUERA DEL MAIN
    int paso;
    while ( paso <= tamanio_arreglo/(size-1)) {
        if (subArreglo[paso] > subArreglo[paso + 1]) {
            subArreglo[paso + 1] = subArreglo[paso];
        }
    }

    //PARA HACER EL MERGE

    //imprimir los elementos del subArreglo (solo para pruebas)
    int k;
    for (k = 0;k<=cantElementos; k++){
        printf("%d", subArreglo[k]);
    };
    MPI_Finalize();
};
