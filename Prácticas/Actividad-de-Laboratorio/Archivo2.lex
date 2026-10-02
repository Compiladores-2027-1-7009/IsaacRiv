%option noyywrap

%{

#include <stdio.h>
int linea = 0;
int words = 0;
int bytes = 0;
%}

%%
\n              {linea++; bytes++;}
[ \t]+          {bytes += yyleng;}
[^ \t\n]+       {words++; bytes += yyleng;}
%%

int main(int argc, char **argv){
    /*saltos de línea tiene, el número de words y el número de bytes.*/
    if(argc > 1){
        yyin = fopen(argv[1], "r");
    }

    yylex();

    printf("Lineas: %d\n", linea);
    printf("Palabras: %d\n", words);
    printf("Bytes: %d\n", bytes);
}