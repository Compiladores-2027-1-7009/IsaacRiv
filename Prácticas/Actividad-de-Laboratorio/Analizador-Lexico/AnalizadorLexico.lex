%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *salida;
int linea = 1;
/*Construccion para los tokens*/
void token(char *clase, char *valor){fprintf(salida, "<%s, %s>\n", clase, valor);}

%}

%option noyywrap
    /*Estado para leer multiples comentarios*/
%x COMENTARIO

DIGITO  [0-9]
LETRA   [a-zA-Z]
ALNUM   [a-zA-Z0-9_]
IDENT   {LETRA}{ALNUM}*

%%

    /*Espacios en blanco*/

[ \t\r]+ {/* Ignorar espacios */}
\n {linea++;}

    /*Comentarios*/

"--".* {/* Comentario de una línea */}

    /* Comentarios multilínea */
    /*Realizamos mejor una transicion de estados para evitar erorres*/
"<*" {BEGIN(COMENTARIO);}
<COMENTARIO>"*>" {BEGIN(INITIAL);}
<COMENTARIO>\n {linea++;}
<COMENTARIO>. {/* Ignorar contenido */}

    /*Números*/
    /* Número real */
{DIGITO}+"."{DIGITO}+   { token("REAL", yytext);}

    /* Número entero */
{DIGITO}+   { token("ENTERO", yytext);}

    /* Cadenas*/
\"([^\"\n]|\\.)*\"  {token("CADENA", yytext);}


    /* Palabras reservadas*/

"if"    {token("IF", yytext);}
"then"  {token("THEN", yytext);}
"else"  {token("ELSE", yytext);}
"while" {token("WHILE", yytext);}
"do"    {token("DO", yytext);}
"case"  {token("CASE", yytext);}
"is"    {token("IS", yytext);}
"void"  {token("VOID", yytext);}
"true"  {token("TRUE", yytext);}
"false" {token("FALSE", yytext);}
"begin" {token("BEGIN", yytext);}
"end"   {token("END", yytext);}
"not"   {token("NOT", yytext);}

    /* Identificadores*/
{IDENT}     {token("IDENTIFICADOR", yytext);}

    /* Operadores aritméticos*/

"+" {token("SUMA", yytext);}
"-" {token("RESTA", yytext);}
"*" {token("MULTIPLICACION", yytext);}
"/" {token("DIVISION", yytext);}
"%" {token("MODULO", yytext);}

    /* Operadores relacionales*/

">"  {token("MAYOR", yytext);}
"<"  {token("MENOR", yytext);}
"<>" {token("DIFERENTE", yytext);}
"="  {token("IGUAL", yytext);}
":=" {token("ASIGNACION", yytext);}


    /* Símbolos */

"(" {token("PARENTESIS_IZQ", yytext);}
")" {token("PARENTESIS_DER", yytext);}
"{" {token("LLAVE_IZQ", yytext);}
"}" {token("LLAVE_DER", yytext);}
";" {token("PUNTO_COMA", yytext);}
"," {token("COMA", yytext);}


    /* Error léxico*/

. {fprintf(salida,"ERROR: caracter '%s' en linea %d\n", yytext, linea);}

%%

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Uso: %s archivo.art\n", argv[0]);
        return 1;
    }

    /* Comprobar extensión .art */
    char *extension = strrchr(argv[1], '.');

    if(extension == NULL || strcmp(extension, ".art") != 0){
        printf("Error: el archivo de entrada debe tener extension .art\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");

    if(yyin == NULL){
        perror("Error al abrir el archivo de entrada");
        return 1;
    }

    /* Crear nombre del archivo .tokens */
    char nombreSalida[256];

    strcpy(nombreSalida, argv[1]);
    extension = strrchr(nombreSalida, '.');
    strcpy(extension, ".tokens");
    salida = fopen(nombreSalida, "w");

    if(salida == NULL){
        perror("Error al crear el archivo de salida");
        fclose(yyin);
        return 1;
    }
    yylex();

    fclose(yyin);
    fclose(salida);
}
