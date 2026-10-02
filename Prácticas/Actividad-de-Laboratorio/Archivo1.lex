    /*Usamos %option noyywrap, 
    asi el escáner asume que no hay más archivos y se detiene inmediatamente 
    al encontrar el primer fin de archivo.*/
%option noyywrap

%{

#include <stdio.h>
int linea = 1;
%}

%%
\n      {printf("\n%4d  ", ++linea);}
.       {printf("%s", yytext);}
%%

int main(int argc, char **argv){
    if(argc > 1){
        yyin = fopen(argv[1], "r");
    }
    printf("%4d  ", linea);
    yylex();
}