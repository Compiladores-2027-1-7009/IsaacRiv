%option noyywrap

%{
#include <stdio.h>
    /*Define funciones para clasificar y transformar caracteres (como isdigit, isalpha, tolower o toupper)*/
#include <ctype.h>
%}

%%
    /*Hacemos uso de toupper para moverlo a mayusculas*/
[a-z]+  { for (int i = 0; i < yyleng; i++) { printf("%c", toupper(yytext[i]));} }
[ \t\n]+    {printf("%s", yytext);}

%%

int main(int argc, char **argv){
    if(argc > 1){
        yyin = fopen(argv[1], "r");
    }
    yylex();
}
