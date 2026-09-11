#include <stdio.h>

/* Utilizamos #pragma message */
#pragma message("Iniciando program2.c...")
/*Definimos limite y modo inicila */
#define MAX 1000
#define INICIAL 1

/* Utilizamos #undef para desahacer el modo inicial */
#undef INICIAL
#define ACCESO 2

/* Definimos un error en caso de que el sobrepase el limite #error */
#if MAX < 10
    #error "El limite maximo configurado es invalido."
#endif

/* #if / #else / #endif */
#if ACCESO == 2
    #define USUARIO "Administrador"
#else
    #define USUARIO "Usuario"
#endif

int main(void){
    printf("Acceso concedido como: %s\n", USUARIO);
    printf("Limite de recursos: %d\n", MAX);
    return 0;
}