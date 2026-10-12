#include "headers/Parser.hpp"
#include <iostream>

namespace C_1
{
  Parser::Parser(/* args */)
  {
  }

  Parser::Parser(Lexer *lexer)
  {
    this->lexer = lexer;
  }
    
  Parser::~Parser()
  {
  }
  // Función del símbolo inicial de la gramatica (programa → declaraciones sentencias)
  void Parser::programa(){
    declaraciones();
    sentencias();
  }

    // declaraciones -> declaracion declaraciones_p
  void Parser::declaraciones(){
    if(token == int_token || token == float_token){
        declaracion();
        declaraciones_p();
    }else{
        error("Se esperaba al menos una declaracion ('int' o 'float') al inicio del programa");
    }
  }

  // declaraciones_p -> declaracion declaraciones_p | epsilon
  void Parser::declaraciones_p(){
      if(token == int_token || token == float_token){
        declaracion();
        declaraciones_p();
    }
      // epsilon
  }

  // declaracion -> tipo lista_var ;
  void Parser::declaracion(){
      tipo();
      lista_var();
      if(token == pcoma_token){
          token = eat();
      }else{
          error("Se esperaba ';' al final de la declaracion");
      }
  }

  // tipo -> int | float
  void Parser::tipo(){
      if(token == int_token || token == float_token){
          token = eat();
      }else{
          error("Se esperaba un tipo de dato ('int' o 'float')");
      }
  }

  // lista_var -> id_token lista_var_p
  void Parser::lista_var(){
      if(token == id_token){
          token = eat();
          lista_var_p();
      }else{
          error("Se esperaba un identificador en la lista de variables");
      }
  }

  // lista_var_p -> , id_token lista_var_p | epsilon
  void Parser::lista_var_p(){
      if(token == coma_token){
          token = eat();
          if(token == id_token){
              token = eat();
              lista_var_p();
          }else{
              error("Se esperaba un identificador despues de ','");
          }
      }
      // epsilon
  }

  // sentencias -> sentencia sentencias_p
  void Parser::sentencias(){
      sentencia();
      sentencias_p();
  }

  // sentencias_p -> sentencia sentencias_p | epsilon
  void Parser::sentencias_p() {
      if(token == id_token || token == if_token || token == while_token){
          sentencia();
          sentencias_p();
      }
      // epsilon
  }

  // sentencia -> id = expresion ; | if ( expresion ) sentencias else sentencias | while ( expresion ) sentencias
  void Parser::sentencia(){
      if(token == id_token){
          token = eat();
          if(token == equal_token){
              token = eat();
              expresion();
              if(token == pcoma_token){
                  token = eat();
              }else{
                  error("Se esperaba ';' al final de la asignacion");
              }
          }else{
              error("Se esperaba '=' en la asignacion");
          }
      }else if(token == if_token){
          token = eat();
          if(token == pleft_token){
              token = eat();
              expresion();
              if(token == pright_token){
                  token = eat();
                  sentencias();
                  if(token == else_token){
                      token = eat();
                      sentencias();
                  }else{
                      error("Se esperaba 'else' en la estructura condicional");
                  }
              }else{
                  error("Se esperaba ')' tras la condicion del 'if'");
              }
          }else{
              error("Se esperaba '(' tras la palabra reservada 'if'");
          }
      }else if(token == while_token){
          token = eat();
          if(token == pleft_token){
              token = eat();
              expresion();
              if(token == pright_token){
                  token = eat();
                  sentencias();
              }else{
                  error("Se esperaba ')' tras la condicion del 'while'");
              }
          }else{
              error("Se esperaba '(' tras la palabra reservada 'while'");
          }
      }else{
          error("Instruccion o sentencia no valida");
      }
  }

  // expresion -> termino expresion_p
  void Parser::expresion(){
      e_termino();
      expresion_p();
  }

  // expresion_p -> + termino expresion_p | - termino expresion_p | epsilon
  void Parser::expresion_p(){
      if(token == sum_token || token == rest_token){
          token = eat();
          e_termino();
          expresion_p();
      }
      // epsilon
  }

  // termino -> factor termino_p
  void Parser::e_termino(){
      e_factor();
      e_termino_p();
  }

  // termino_p -> * factor termino_p | / factor termino_p | epsilon
  void Parser::e_termino_p(){
      if(token == mult_token || token == div_token){
          token = eat();
          e_factor();
          e_termino_p();
      }
      // epsilon
  }

  // factor -> ( expresion ) | id_token | num_token
  void Parser::e_factor(){
      if(token == pleft_token){
          token = eat();
          expresion();
          if(token == pright_token){
              token = eat();
          }else{
              error("Se esperaba ')' al cerrar la expresion");
          }
      }else if(token == id_token || token == num_token){
          token = eat();
      }else{
          error("Se esperaba '(', identificador o numero");
      }
  }

  // Solicita el siguiente token al lexer.
  Token Parser::eat(){
    return (Token) lexer->yylex();
  }

  void Parser::error(string msg){
    cout << "ERROR DE SINTAXIS " << msg << " en la línea "<< lexer->getLine() <<endl;
    // Agregamos exit(EXIT_FAILURE); dentro de la función error() para que 
    // el análisis sintáctico se aborte inmediatamente al detectar el primer error, asi
    // detienemos la ejecución del programa de inmediato 
    // (esto para las pruebas invalidas: "prueba_invalida1, prueba_invalida2")
    exit(EXIT_FAILURE); 
  }   

  /**
    Inicia el análisis sintáctico completo del archivo de entrada.
    Lee el primer token y llama al símbolo inicial (programa).
    Reporta si la cadena es aceptada o rechazada por la gramática.
  */
  void Parser::parse(){
    token = eat();
    programa();
    if(token == t_eof)
      cout << "La cadena es aceptada" << endl;
    else 
      cout << "La cadena no pertenece al lenguaje generado por la gramática" << endl;
  }

}
