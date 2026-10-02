%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
    /*. Le permite al compilador de C reconocer funciones de manipulación de cadenas 
    (strcmp, strdup, strlen) cuando se realizan acciones en las expresiones regulares.*/
#include <string.h>
%}

%%
    /*Comprobamos que la expresion regular con cualquier numero y espacios cumple con la terminacion A*/
([0-9]+[ \t]+)*[0-9]+[ \t]*A {char *p = yytext; int suma = 0; 
    while (*p != 'A') {
        if(*p >= '0' && *p <= '9'){
            /* Con strtol se puede convertir una cadena de caracteres en un valor entero de tipo long int */
            suma += strtol(p, &p, 10);
        }else{
            p++;
        }
    }
    printf("%d\n", suma);
}

    /*De no ser asi, solo se imprime la cadena*/
([0-9]+[ \t]+)*[0-9]+[ \t]*B    {printf("%s", yytext); printf("\n"); }
\n  {/* ignorar */}

%%

int main(int argc, char **argv){
    if(argc > 1){
        yyin = fopen(argv[1], "r");
    }

    yylex();
}
