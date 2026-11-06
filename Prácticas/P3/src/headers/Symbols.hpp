#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/** 
 * 1. Definir en un comentario la gramática G'(N', T, P', S)
 *
 */

 /** 
 * Simbolo inicial: 
 * S = programa
 * N' = { programa, declaraciones, declaraciones', declaracion, tipo, lista_var, 
 *        lista_var', sentencias, sentencias', sentencia, expresion, expresion', 
 *        termino, termino', factor }
 * T = { int, float, ;, ,, identificador, =, if, (, ), else, while, +, -, *, /, numero }
 * P' = {
 *   1. programa → declaraciones sentencias
 *   2. declaraciones → declaracion declaraciones'
 *   3. declaraciones' → declaracion declaraciones' | ε
 *   4. declaracion → tipo lista_var ;
 *   5. tipo → int | float
 *   6. lista_var → identificador lista_var'
 *   7. lista_var' → , identificador lista_var' | ε
 *   8. sentencias → sentencia sentencias'
 *   9. sentencias' → sentencia sentencias' | ε
 *   10. sentencia → identificador = expresion ;
 *   11. sentencia → if ( expresion ) sentencias else sentencias
 *   12. sentencia → while ( expresion ) sentencias
 *   13. expresion → termino expresion'
 *   14. expresion' → + termino expresion' | - termino expresion' | ε
 *   15. termino → factor termino'
 *   16. termino' → * factor termino' | / factor termino' | ε
 *   17. factor → ( expresion ) | identificador | numero
 * }
 * 
 */


 

/**
 * 2. Determinar la enumeración para el conjunto T
 */
enum Token { t_eof, 
            int_token, 
            float_token, 
            pcoma_token, 
            coma_token, 
            id_token, 
            equal_token,                   
            if_token, pleft_token, pright_token, else_token, while_token,                                  
            sum_token, rest_token, mult_token, div_token, num_token   
};

/**
 * 3. Determinar la enumeración para el conjunto N
 */
enum NoTerm { strEmpty =100, // ε                                                    
      PROGRAMA, 
      DECLARACIONES, 
      DECLARACIONES_P, 
      DECLARACION, 
      TIPO,        
      LISTA_VAR, 
      LISTA_VAR_P, 
      SENTENCIAS, 
      SENTENCIAS_P, 
      SENTENCIA,    
      EXPRESION, 
      EXPRESION_P, 
      TERMINO, 
      TERMINO_P, 
      FACTOR              
};

#endif // !__SYMBOLS_HPP__
