#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/** 
 * 1. Definir en un comentario la gramática G(N, T, P, S)
 * 
 */

/**
 * 2. Determinar la enumeración para el conjunto T
 */
enum Token { primero, t_eof,
            /* Identificadores y números */
            id_token,
            num_token,
            /* Signos de puntuación y operadores */
            mult_token,
            sum_token,
            rest_token,
            div_token,
            equal_token,
            coma_token,
            pcoma_token,
            pleft_token,
            pright_token,
            /* Palabras reservadas */
            if_token,
            else_token,
            while_token,
            int_token,
            float_token };

/**
 * 3. Determinar la enumeración para el conjunto N
 */
enum NoTerm { strEmpty, 
        nt_programa,                                                            
        nt_declaraciones,                                                       
        nt_declaraciones_p,                                                     
        nt_declaracion,                                                         
        nt_tipo,                                                                
        nt_lista_var,                                                           
        nt_lista_var_p,                                                         
        nt_sentencias,                                                          
        nt_sentencias_p,                                                        
        nt_sentencia,                                                           
        nt_expresion,                                                           
        nt_expresion_p,                                                         
        nt_e_term,                                                              
        nt_e_term_p_p,                                                            
        nt_e_fact};

#endif // !__SYMBOLS_HPP__
