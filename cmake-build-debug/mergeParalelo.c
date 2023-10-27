#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <algorithm>
//#include <vector>
#include <mpi.h>
//#include <iostream>

int main(int argc, char **argv) {

    //declaracion de las variables a utilizar
    int rank, size, tamanio_arreglo, *arregloDesordenado, *arregloOrdenado, *subArreglo;

    MPI_Init(&argc, &argv); //iniciamos MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //obtener identificador
    MPI_Comm_size(MPI_COMM_WORLD, &size); //obtener la cantidad de procesos

    // SOLICITA AL USUARIO QUE INGRESE EL TAMAÑO DEL ARREGLO
    printf("Ingrese la cantidad de elementos en el arreglo: ");
    scanf("%d", &tamanio_arreglo);


    //CREACION DEL ARREGLO
    // reservamos el espacio para el arreglo a ordenar
    arregloDesordenado = (int *)malloc( sizeof(int) * tamanio_arreglo);

    //llenar el arreglo a ordenar aleatoriamente
    srand(time(NULL)); //inicializar la semilla aleatoria
    for (int i = 0; i < tamanio_arreglo; i++){
        arregloDesordenado[i] = rand() % 100; //GENERA NUMEROS ALEATORIOS DEL 0 AL 99
    }

    //reservamos espacio para el arreglo de cada proceso
    subArreglo = (int *)malloc( sizeof(int) * (tamanio_arreglo/(size-1)));

    if (tamanio_arreglo % (size-1) != 0){

    }

    MPI_Finalize();



}