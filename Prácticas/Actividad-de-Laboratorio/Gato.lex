%option noyywrap

%{
#include <stdio.h>
    /*Utilizamos una cadena de 9 caracteres que simula la matriz para gato*/
char tablero[10];
int posicion = 0;
    /*Posibles combinaciones para ganar*/
int gana(char jugador){return
        (tablero[0] == jugador && tablero[1] == jugador && tablero[2] == jugador) ||
        (tablero[3] == jugador && tablero[4] == jugador && tablero[5] == jugador) ||
        (tablero[6] == jugador && tablero[7] == jugador && tablero[8] == jugador) ||

        (tablero[0] == jugador && tablero[3] == jugador && tablero[6] == jugador) ||
        (tablero[1] == jugador && tablero[4] == jugador && tablero[7] == jugador) ||
        (tablero[2] == jugador && tablero[5] == jugador && tablero[8] == jugador) ||

        (tablero[0] == jugador && tablero[4] == jugador && tablero[8] == jugador) ||
        (tablero[2] == jugador && tablero[4] == jugador && tablero[6] == jugador); }
%}

%%
    /*poscicion del tablero*/
[XO_]       {tablero[posicion] = yytext[0];posicion++;}
    /*Saltos de linea*/
\n      {/* ignorar */}
[ \t]+  {/* ignorar */}
.       {/* ignorar */}

%%

int main(int argc, char **argv){
    if(argc > 1){
        yyin = fopen(argv[1], "r");
    }
    yylex();

    if(gana('X')){
        printf("-> gana X\n");
    }else if(gana('O')){
        printf("-> gana O\n");
    }else if(posicion == 9){
        int verificador = 1;
        for(int i = 0; i < 9; i++){
            if(tablero[i] == '_'){
                verificador = 0;
            }
        }
        if(verificador){
            printf("-> empate\n");
        }else{
            printf("-> sin ganador\n");
        }
    }else{
        printf("-> sin ganador\n");
    }
}
