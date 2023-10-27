#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Combinar dos arreglos (parteBAJA y parteALTA) en el espacio del arreglo original
void combinarArreglos(int arregloRecibido[], int baseArray, int valorMedio, int techoArray) {

    // Crear parteBAJA ← A[baseArray..valorMedio] y parteALTA ← A[valorMedio+1..techoArray]

    int tamanioParteBAJA = valorMedio - baseArray + 1; // SE CALCULA EL TAMAÑO DE LA PARTE BAJA DEL ARREGLO RECIBIDO
    int tamanioParteAltaArreglo = techoArray - valorMedio; // SE CALCULA EL TAMAÑO DE LA PARTE ALTA DEL ARREGLO RECIBIDO

    int parteBAJA[tamanioParteBAJA], parteALTA[tamanioParteAltaArreglo]; // SE ASIGNA A CADA PARTE SU CORRESPONDIENTE TAMAÑO

    for (int i = 0; i < tamanioParteBAJA; i++)
        parteBAJA[i] = arregloRecibido[baseArray + i];
    for (int j = 0; j < tamanioParteAltaArreglo; j++)
        parteALTA[j] = arregloRecibido[valorMedio + 1 + j];


    int i, j, posicionAsignacion;

    i = 0; //ELEMENTO USADO PARA EL BUCLE
    j = 0; //ELEMENTO USADO PARA EL BUCLE
    posicionAsignacion = baseArray; // SE COMIENZA ASIGNANDO EN EL ARRAY POR EL VALOR QUE RECIBIMOS DE BASE

    while (i < tamanioParteBAJA && j < tamanioParteAltaArreglo) { //COMPARAMOS QUE LA REPETECIÓN DEL BUCLE SEA MENOR AL TAMAÑO DE LAS DOS PARTES

        if (parteBAJA[i] <= parteALTA[j]) { // SI EL VALOR EN LA PARTE BAJA ES MENOR O IGUAL AL DE LA ALTA, SE ASIGNA ESTE AL ARREGLO QUE ESTAMOS UNIENDO, Y SE INCREMENTA EL CONTADOR DE i (PARTE BAJA)
            arregloRecibido[posicionAsignacion] = parteBAJA[i];
            i++;
        } else { // SI EL VALOR EN LA PARTE ALTA ES MENOR AL DE LA BAJA, SE ASIGNA ESTE AL ARREGLO QUE ESTAMOS UNIENDO, Y SE INCREMENTA EL CONTADOR DE j (PARTE ALTA)
            arregloRecibido[posicionAsignacion] = parteALTA[j];
            j++;
        }
        posicionAsignacion++; // SE INCREMENTA EL VALOR DEL ARRAY QUE ESTAMOS UNIENDO PARA USAR LA SIGUIENTE POSICION
    }

    while (i < tamanioParteBAJA) {
        arregloRecibido[posicionAsignacion] = parteBAJA[i]; // CUANDO SE LLEGA AL LIMITE DE TAMAÑO DE LA PARTE ALTA, LOS VALORES DE LA BAJA SE ASIGNAN DIRECTAMENTE AL ARREGLO
        i++;
        posicionAsignacion++;
    }

    while (j < tamanioParteAltaArreglo) {
        arregloRecibido[posicionAsignacion] = parteALTA[j]; // CUANDO SE LLEGA AL LIMITE DE TAMAÑO DE LA PARTE BAJA, LOS VALORES DE LA BAJA SE ASIGNAN DIRECTAMENTE AL ARREGLO
        j++;
        posicionAsignacion++;
    }
}

// DIVIDE EL ARREGLO EN DOS SUBARREGLOS
void dividirArreglo(int arregloRecibido[], int baseArreglo, int techoArreglo) {
    if (baseArreglo < techoArreglo) {

        // valorMedioArreglo ES EL EL PUNTO DONDE SE DIVIDE EN DOS EL ARREGLO
        int valorMedioArreglo = baseArreglo + (techoArreglo - baseArreglo) / 2;

        // SE HACE UNA LLAMADA RECURSIVA PASANDO LAS DOS MITADES DEL ARREGLO PARA QUE SE VUELVA A DIVIDIR
        dividirArreglo(arregloRecibido, baseArreglo, valorMedioArreglo);
        dividirArreglo(arregloRecibido, valorMedioArreglo + 1, techoArreglo);

        // UNE LOS ARREGLOS
        combinarArreglos(arregloRecibido, baseArreglo, valorMedioArreglo, techoArreglo);
    }
}

// imprimir el arreglo ordenado
void imprimirArregloOrdenado(int arr[], int tamanioArray) {
    for (int i = 0; i < tamanioArray; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// imprimir el arreglo original
void imprimirArregloOriginal(int arr[], int tamanioArray) {
    for (int i = 0; i < tamanioArray; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// COMIENZA EL PROGRAMA PRINCIPAL
int main(int argc, char **argv) {

    int tamanio_arreglo;
    int *arreglo;

    // SOLICITA AL USUARIO QUE INGRESE EL TAMAÑO DEL ARREGLO
    printf("Ingrese la cantidad de elementos en el arreglo: ");
    scanf("%d", &tamanio_arreglo);

    // SE CREA EL ARREGLO DINAMICO DEL TAMAÑO INGRESADO
    arreglo = (int *)malloc( sizeof(int) * tamanio_arreglo);
    //int arreglo[tamanio_arreglo];

    printf("%d", tamanio_arreglo);
    // SE RELLENA EL ARREGLO CON NUMEROS ALEATORIOS

    srand(time(NULL)); //inicializar la semilla aleatoria
    for (int i = 0; i < tamanio_arreglo; i++){
        arreglo[i] = rand() % 100; //GENERA NUMEROS ALEATORIOS DEL 0 AL 99
    }

    printf("Arreglo original: \n");
    imprimirArregloOriginal(arreglo, tamanio_arreglo); //IMPRIME EL ARREGLO GENERADO ALEATORIAMENTE, QUE SE ENCUENTRA DESORDENADO

    //LLAMA A LA FUNCION QUE SE ENCARGA DE DIVIDIR EL ARREGLO
    dividirArreglo(arreglo, 0, tamanio_arreglo - 1); /**/

    printf("Arreglo ordenado: \n");
    imprimirArregloOrdenado(arreglo, tamanio_arreglo); //IMPRIME EL ARREGLO ORDENADO

    free(arreglo);

    return 0;
}}