%{
  /*directivas de procesamiento
    direcciones memotecnicas */
  #include <iostream>
%}

%option c++
%option noyywrap


digito [0-9]
letra [a-zA-Z]
palabra {letra}+
espacio [ \t\n]
  /*Se agrega hexadecimal*/
hexadecimal 0[xX][0-9a-fA-F]+
  /*Se agregan palabras reservadas*/
reservada while|for|if|int|string
  /*Se agrega el identificador*/
identificador [a-zA-Z_][a-zA-Z0-9_]{0,31}
  /*El ejecicio iv esta completado en la palabra reservada 'espacio'*/

%%

{espacio} {/* La acción léxica puede ir vacía si queremos que el escáner ignore la regla*/}
{digito}+ { std::cout << "Encontré un número: " << yytext << std::endl;}
{hexadecimal} {std::cout << "Encontré un hexadecimal: " << yytext << std::endl;}
  /*palabras reservadas*/
{reservada} {std::cout << "Encontré la palabra reservada: " << yytext << std::endl;}
  /*identificador*/
{identificador} {std::cout << "Encontré un identificador: " << yytext << std::endl;}
{palabra} { std::cout << "Encontré una palabra: " << yytext << std::endl;}
  /*Se agrega hexadecimal*/
%%


int main() {
  FlexLexer* lexer = new yyFlexLexer;
  lexer->yylex();
}