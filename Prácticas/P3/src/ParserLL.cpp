#include "headers/ParserLL.hpp"


ParserLL::ParserLL(Lexer *lexer)
{
    this->lexer = lexer;
}

ParserLL::~ParserLL()
{
}


void ParserLL::loadSyms()
{
  /*********************************************
   * 4. Agregar todos los símbolos (N'∪T) de G'*
   *********************************************/
   // Indicar la cantidad de terminales (18) y no terminales (15) en la gramática
    grammar.setNum(18, 15);
    grammar.start = PROGRAMA;
    // Cargar No Terminales (N')
    grammar.addSymbol(t_eof, Symbol(t_eof));
    grammar.addSymbol(int_token, Symbol(int_token));
    grammar.addSymbol(float_token, Symbol(float_token));
    grammar.addSymbol(pcoma_token, Symbol(pcoma_token));
    grammar.addSymbol(coma_token, Symbol(coma_token));
    grammar.addSymbol(id_token, Symbol(id_token));
    grammar.addSymbol(equal_token, Symbol(equal_token));
    grammar.addSymbol(if_token, Symbol(if_token));
    grammar.addSymbol(pleft_token, Symbol(pleft_token));
    grammar.addSymbol(pright_token, Symbol(pright_token));
    grammar.addSymbol(else_token, Symbol(else_token));
    grammar.addSymbol(while_token, Symbol(while_token));
    grammar.addSymbol(sum_token, Symbol(sum_token));
    grammar.addSymbol(rest_token, Symbol(rest_token));
    grammar.addSymbol(mult_token, Symbol(mult_token));
    grammar.addSymbol(div_token, Symbol(div_token));
    grammar.addSymbol(num_token, Symbol(num_token));
    // Cargar Terminales (Σ)
    grammar.addSymbol(strEmpty, Symbol(strEmpty));
    grammar.addSymbol(PROGRAMA, Symbol(PROGRAMA));
    grammar.addSymbol(DECLARACIONES, Symbol(DECLARACIONES));
    grammar.addSymbol(DECLARACIONES_P, Symbol(DECLARACIONES_P));
    grammar.addSymbol(DECLARACION, Symbol(DECLARACION));
    grammar.addSymbol(TIPO, Symbol(TIPO));
    grammar.addSymbol(LISTA_VAR, Symbol(LISTA_VAR));
    grammar.addSymbol(LISTA_VAR_P, Symbol(LISTA_VAR_P));
    grammar.addSymbol(SENTENCIAS, Symbol(SENTENCIAS));
    grammar.addSymbol(SENTENCIAS_P, Symbol(SENTENCIAS_P));
    grammar.addSymbol(SENTENCIA, Symbol(SENTENCIA));
    grammar.addSymbol(EXPRESION, Symbol(EXPRESION));
    grammar.addSymbol(EXPRESION_P, Symbol(EXPRESION_P));
    grammar.addSymbol(TERMINO, Symbol(TERMINO));
    grammar.addSymbol(TERMINO_P, Symbol(TERMINO_P));
    grammar.addSymbol(FACTOR, Symbol(FACTOR));
}

void ParserLL::loadProds()
{
  /************************************************
   * 5. Agregar todas las producciones (P') de G' *
   ************************************************/
   //programa -> declaraciones sentencias  
    grammar.addProd(0,  Production(PROGRAMA, {DECLARACIONES, SENTENCIAS}));
    //declaraciones -> declaracion declaraciones_p
    grammar.addProd(1,  Production(DECLARACIONES, {DECLARACION, DECLARACIONES_P}));
    // declaraciones_p -> declaracion declaraciones_p
    grammar.addProd(2,  Production(DECLARACIONES_P, {DECLARACION, DECLARACIONES_P}));
    //declaraciones_p -> epsilon
    grammar.addProd(3,  Production(DECLARACIONES_P, {strEmpty}));
    // declaracion -> tipo lista_var ;
    grammar.addProd(4,  Production(DECLARACION, {TIPO, LISTA_VAR, pcoma_token}));
    // tipo -> int ...
    grammar.addProd(5,  Production(TIPO, {int_token}));
    grammar.addProd(6,  Production(TIPO, {float_token}));
    grammar.addProd(7,  Production(LISTA_VAR, {id_token, LISTA_VAR_P}));
    grammar.addProd(8,  Production(LISTA_VAR_P, {coma_token, id_token, LISTA_VAR_P}));
    grammar.addProd(9,  Production(LISTA_VAR_P, {strEmpty}));
    grammar.addProd(10, Production(SENTENCIAS, {SENTENCIA, SENTENCIAS_P}));
    grammar.addProd(11, Production(SENTENCIAS_P, {SENTENCIA, SENTENCIAS_P}));
    grammar.addProd(12, Production(SENTENCIAS_P, {strEmpty}));
    grammar.addProd(13, Production(SENTENCIA, {id_token, equal_token, EXPRESION, pcoma_token}));
    grammar.addProd(14, Production(SENTENCIA, {if_token, pleft_token, EXPRESION, pright_token, SENTENCIAS, else_token, SENTENCIAS}));
    grammar.addProd(15, Production(SENTENCIA, {while_token, pleft_token, EXPRESION, pright_token, SENTENCIAS}));
    grammar.addProd(16, Production(EXPRESION, {TERMINO, EXPRESION_P}));
    grammar.addProd(17, Production(EXPRESION_P, {sum_token, TERMINO, EXPRESION_P}));
    grammar.addProd(18, Production(EXPRESION_P, {rest_token, TERMINO, EXPRESION_P}));
    grammar.addProd(19, Production(EXPRESION_P, {strEmpty}));
    grammar.addProd(20, Production(TERMINO, {FACTOR, TERMINO_P}));
    grammar.addProd(21, Production(TERMINO_P, {mult_token, FACTOR, TERMINO_P}));
    grammar.addProd(22, Production(TERMINO_P, {div_token, FACTOR, TERMINO_P}));
    grammar.addProd(23, Production(TERMINO_P, {strEmpty}));
    grammar.addProd(24, Production(FACTOR, {pleft_token, EXPRESION, pright_token}));
    //factor -> identificador
    grammar.addProd(25, Production(FACTOR, {id_token}));
    //factor -> numero
    grammar.addProd(26, Production(FACTOR, {num_token}));
    
}

void ParserLL::loadTable()
{

  /*************************************************
   **     6.Cargar la tabla de AS predictivo      **
   *************************************************/
    //0: programa -> declaraciones sentencias
    table[PROGRAMA][int_token] = 0;
    table[PROGRAMA][float_token] = 0;

    //1: declaraciones -> declaracion declaraciones_p
    table[DECLARACIONES][int_token] = 1;
    table[DECLARACIONES][float_token] = 1;

    //2: declaraciones_p -> declaracion declaraciones_p
    //3: declaraciones_p -> epsilon
    table[DECLARACIONES_P][int_token] = 2;
    table[DECLARACIONES_P][float_token] = 2;
    table[DECLARACIONES_P][id_token] = 3;
    table[DECLARACIONES_P][if_token] = 3;
    table[DECLARACIONES_P][while_token] = 3;

    //4: declaracion -> tipo lista_var ;
    table[DECLARACION][int_token] = 4;
    table[DECLARACION][float_token] = 4;

    //5: tipo -> int
    //6: tipo -> float
    table[TIPO][int_token] = 5;
    table[TIPO][float_token] = 6;

    //7: lista_var -> identificador lista_var_p
    table[LISTA_VAR][id_token] = 7;

    //8: lista_var_p -> , identificador lista_var_p
    //9: lista_var_p -> epsilon
    table[LISTA_VAR_P][coma_token] = 8;
    table[LISTA_VAR_P][pcoma_token] = 9;

    //10: sentencias -> sentencia sentencias_p
    table[SENTENCIAS][id_token] = 10;
    table[SENTENCIAS][if_token] = 10;
    table[SENTENCIAS][while_token] = 10;

    //11: sentencias_p -> sentencia sentencias_p
    //12: sentencias_p -> epsilon
    table[SENTENCIAS_P][id_token] = 11;
    table[SENTENCIAS_P][if_token] = 11;
    table[SENTENCIAS_P][while_token] = 11;
    table[SENTENCIAS_P][else_token] = 12;
    table[SENTENCIAS_P][t_eof] = 12;

    //13: sentencia -> identificador = expresion ;
    //14: sentencia -> if ( expresion ) sentencias else sentencias
    //15: sentencia -> while ( expresion ) sentencias
    table[SENTENCIA][id_token] = 13;
    table[SENTENCIA][if_token] = 14;
    table[SENTENCIA][while_token] = 15;

    //16: expresion -> termino expresion_p
    table[EXPRESION][id_token] = 16;
    table[EXPRESION][pleft_token] = 16;
    table[EXPRESION][num_token] = 16;

    //17: expresion_p -> + termino expresion_p
    //18: expresion_p -> - termino expresion_p
    //19: expresion_p -> epsilon
    table[EXPRESION_P][sum_token] = 17;
    table[EXPRESION_P][rest_token] = 18;
    table[EXPRESION_P][pcoma_token] = 19;
    table[EXPRESION_P][pright_token] = 19;

    //20: termino -> factor termino_p
    table[TERMINO][id_token] = 20;
    table[TERMINO][pleft_token] = 20;
    table[TERMINO][num_token] = 20;

    //21: termino_p -> * factor termino_p
    //22: termino_p -> / factor termino_p
    //23: termino_p -> epsilon
    table[TERMINO_P][mult_token] = 21;
    table[TERMINO_P][div_token] = 22;
    table[TERMINO_P][sum_token] = 23;
    table[TERMINO_P][rest_token] = 23;
    table[TERMINO_P][pcoma_token] = 23;
    table[TERMINO_P][pright_token] = 23;

    //24: factor -> ( expresion )
    //25: factor -> identificador
    //26: factor -> numero
    table[FACTOR][pleft_token] = 24;
    table[FACTOR][id_token] = 25;
    table[FACTOR][num_token] = 26;
}

int ParserLL::parse()
{
  /**************************************************
   ** 7. Implementar el algoritmo de AS predictivo **
   **************************************************/

  //Auxiliares
  //stack<Symbol> pila;    
  //map<Token, int>::iterator accion;    
  //vector<int> body;    
  //Symbol X;
    stack<int> pila;
    pila.push(t_eof);
    pila.push(PROGRAMA);

    token = eat();

    while (!pila.empty())
    {
      int topIndex = pila.top();
      pila.pop();

      Symbol X = grammar.getSym(topIndex);

      if (X.getType() == terminal)
      {
        if (X.getToken() == token)
        {
          if (token == t_eof)
          {
            aceptar("Programa válido :)");
            return 0; // Accept
          }
          token = eat();
        }
        else
        {
          error("Error sintáctico: se esperaba un token específico");
          return -1;
        }
      }
      else
      {
        NoTerm currentNoTerm = X.getNoTerm();
        if (table[currentNoTerm].find(token) != table[currentNoTerm].end())
        {
          int prodId = table[currentNoTerm][token];
          Production p = grammar.getProd(prodId);
          vector<int> body = p.getBody();

          if (body.size() > 0 && body[0] != strEmpty)
          {
            for (int i = body.size() - 1; i >= 0; i--)
            {
              pila.push(body[i]);
            }
          }
        }
        else
        {
          error("Error sintáctico: no hay producción en la tabla predictiva");
          return -1;
        }
      }
    }
    return -1;

  
}

void ParserLL::error(string msg)
{
    cout<<msg<<endl;
    exit(EXIT_FAILURE);
}

Token ParserLL::eat()
{
    return (Token) lexer->yylex();    
}

void ParserLL::aceptar(string msg)
{
    cout<<msg<<endl;
}
