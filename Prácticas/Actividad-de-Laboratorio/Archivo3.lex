%option noyywrap

%{

#include <stdio.h>

int numero = 0;
int suma = 0;
%}
    /*Estados para cacular la suma binaria a partir de la literal binaria*/
%x STATENUM STATEBIN

%%

<INITIAL>0 {BEGIN(STATENUM); }
<STATENUM>b {numero = 0; BEGIN(STATEBIN); }
<STATEBIN>0 {numero = numero * 2; }
    /*Cada nuevo bit se calcula como el valor = valor * 2 + bit*/
<STATEBIN>1 {numero = numero * 2 + 1; }
<STATEBIN>\n {suma += numero; numero = 0; BEGIN(INITIAL); }
<STATEBIN>[ \t]+ {suma += numero; numero = 0; BEGIN(INITIAL); }
<INITIAL>[ \t\n]+ {/* Ignorar espacios y saltos de línea */}
. {/* Ignorar cualquier otro carácter */}

%%

int main(int argc, char **argv){
    if(argc > 1){
        yyin = fopen(argv[1], "r");
    }

    yylex();
    printf("Numero: %d\n", suma);
}