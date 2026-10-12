%{
#include <iostream>
#include <string>
using namespace std;

#include "headers/Symbols.hpp"
#include "headers/Lexer.hpp"

int line=1;
%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="Lexer"

    /* Signos de puntuacion */

MULT "*"
SUM "+"
REST "-"
DIV "/"
EQUAL "="
COMA ","
PCOMA ";"
PLEFT "("
PRIGHT ")"

    /* Palabras reservadas */

IF "if"
ELSE "else"
WHILE "while"
INT "int"
FLOAT "float"

    /* Identificadores */

LETRA [A-Za-z_]
DIGITO [0-9]
ID {LETRA}({LETRA}|{DIGITO})*

    /* Numeros */

NUM {DIGITO}+(\.{DIGITO}+)?

%%

   /* Palabras reservadas */

{IF}    { return if_token; }
{ELSE}  { return else_token; }
{WHILE} { return while_token; }
{INT}   { return int_token; }
{FLOAT} { return float_token; }

    /* Signos de puntuación y operadores */

{MULT}  { return mult_token; }
{SUM}   { return sum_token; }
{REST}  { return rest_token; }
{DIV}   { return div_token; }
{EQUAL} { return equal_token; }
{COMA}  { return coma_token; }
{PCOMA} { return pcoma_token; }
{PLEFT} { return pleft_token; }
{PRIGHT} { return pright_token; }

    /* Números e identificadores */

{NUM} { return num_token; }
{ID}  { return id_token; }

<<EOF>>  { return t_eof;}

[ \t\r]+ {}
"\n" 	 {line++;}
.    	 { cout << "ERROR LEXICO " << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}

int Lexer::getLine()
{
    return line;
}