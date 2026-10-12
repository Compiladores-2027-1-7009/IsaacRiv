#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "Lexer.hpp"
#include "Symbols.hpp"
using namespace std;

namespace C_1
{
  class Parser
  {

  private:
    Lexer *lexer;
    int token;
    
  public:
    Parser();
    Parser(Lexer *lexer);
    ~Parser();
    
    void programa(); //función del símbolo incial                                                            
    void declaraciones();                                       
    void declaraciones_p();                                       
    void declaracion();                                       
    void tipo();                                       
    void lista_var();                                       
    void lista_var_p();                                       
    void sentencias();                                       
    void sentencias_p();                                       
    void sentencia();                                       
    void expresion();                                       
    void expresion_p();                                       
    void e_termino();                                       
    void e_termino_p();                                         
    void e_factor();
    
    Token eat();
    void error(string msg);
    void parse();
  };    
    
}


#endif
