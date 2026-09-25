%{
#include <iostream>
#include <string>
using namespace std;

#include "tokens.hpp"
#include "Lexer.hpp"
%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="C_1::Lexer"
%option case-insensitive


DIG [0-9]
    /*Reutilizamos las expresiones anteriores*/
letra [a-zA-Z]
palabra {letra}+
espacio [ \t\n]
identificador [a-zA-Z_][a-zA-Z0-9_]{0,31}
decimal (0|[1-9]{DIG}*)(\.{DIG}+)?([e][+-]?{DIG}+)?
 /*Colocamos las palabras reservadas, signos y operadores*/
mas "+"
meno "-"
multi "*"
div "\\"
asig "="
lr "("
rr ")"
coma ","
pycoma ";"
if "if"
int "int"
while "while"
else "else"
float "float"

%%

    /*retornamos el numero al que fue asociado el token*/
{espacio}
{lr} {return 6;}
{rr} {return 7;}
{coma} {return 8;}
{pycoma} {return 9;}
{if} {return 11;}
{int} {return 12;}
{while} {return 13;}
{else} {return 14;}
{float} {return 15;}
{identificador} {return 10;}
{decimal} {return 16;}
. { cout << "ERROR LEXICO" << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}