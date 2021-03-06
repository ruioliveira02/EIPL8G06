/**
 * 
 * @file
 * @brief contém as definições das funções usadas para processar o input e 
 * preencher a stack fornecida.
 * 
 */

#ifndef PARSER_H
/*! Include guard */
#define PARSER_H


#include "stack.h"
#include "operations.h"
#include "stackOperations.h"
#include "typeOperations.h"
#include "logicOperations.h"
#include "blockOperations.h"
#include "arrayOperations.h"

//! Seleciona os argumentos das funções sobre a stack
#define POP_0S st->stack
//! Seleciona o argumento das funções com um arguemnto
#define POP_1 pop(st->stack)
//! Seleciona o argumento das funções com um argumento sobre a stack
#define POP_1S st, pop(st->stack)
//! Seleciona o argumento das funções com um argumento e sub operações
#define POP_0SO *(str + 1), st
//! Seleciona o argumento das funções com dois argumentos
#define POP_2 pop(st->stack), pop(st->stack)
//! Seleciona o argumento das funções com dois argumentos sobre a stack
#define POP_2S st, pop(st->stack), pop(st->stack)
//! Seleciona o argumento das funções com dois argumentos e sub operações
#define POP_2O str + 1, pop(st->stack), pop(st->stack)
//! Seleciona o argumento das funções com três argumentos
#define POP_3 pop(st->stack), pop(st->stack), pop(st->stack)

//! Não efetua push do resultado da operação.
#define PUSH_0(x,y) y
//! Efetua push do resultado da operação.
#define PUSH_1(x,y) push(x,y)

//! Contém o registo de todos os operadores e respetivos argumentos, de forma a facilitar a adição de novos operadores.
/*!  
 *  Cada entrada da tabela é uma ENTRY, que compreende toda a informação
 *  necessária para a chamada da função respetiva.
 *
 */
#define JUMP_TABLE \
        ENTRY('l', 1, readLine, 0S, 0) \
        ENTRY('_', 1, duplicate, 0S, 0) \
        ENTRY(';', 1, eraseTop, 0S, 0) \
        ENTRY('\\', 1, swap, 0S, 0) \
        ENTRY('@', 1, rotate, 0S, 0) \
        ENTRY('t', 1, readAllLines, 0S, 0) \
        ENTRY('p', 1, printTop, 0S, 0) \
        \
        \
        ENTRY('f', 1, convertAndDisposeToDouble, 1, 1) \
        ENTRY('i', 1, convertAndDisposeToInt, 1, 1) \
        ENTRY('c', 1, convertAndDisposeToChar, 1, 1) \
        ENTRY('s', 1, convertAndDisposeToString, 1, 1) \
        ENTRY('!', 1, logicNot,1, 1) \
        ENTRY('S', 2, splitByWhitespace, 1, 1) \
        ENTRY('N', 2, splitByLinebreak, 1, 1) \
        \
        ENTRY('~', 1, negate, 1S, 0) \
        ENTRY('$', 1, copyElement, 1S, 1) \
        ENTRY('(', 1, decrement, 1S, 1) \
        ENTRY(')', 1, increment, 1S, 1) \
        ENTRY(',', 1, comma, 1S, 1) \
        ENTRY('w', 1, executeWhileTrue, 1S, 0) \
        \
        ENTRY(':', 2, setVariable, 0SO, 0) \
        \
        \
        ENTRY('+', 1, sum, 2, 1) \
        ENTRY('-', 1, subtract, 2, 1) \
        ENTRY('*', 1, multiply, 2S, 1) \
        ENTRY('/', 1, divide, 2, 1) \
        ENTRY('%', 1, module, 2S, 1) \
        ENTRY('#', 1, exponentiate, 2, 1) \
        ENTRY('&', 1, and, 2, 1) \
        ENTRY('|', 1, or, 2, 1) \
        ENTRY('^', 1, xor, 2, 1) \
        ENTRY('=', 1, isEqual, 2, 1) \
        ENTRY('<', 1, isLess, 2, 1) \
        ENTRY('>', 1, isGreater, 2, 1) \
        \
        ENTRY('e', 1, shortcutSelect, 2O, 1) \
        \
        \
        ENTRY('?', 1, conditional, 3, 1)


//! Expansão da JumpTable para Switch.
/*!
 *  a é o primeiro caracter do operador

 *  b é o tamanho mínimo do operador

 *  c é a função chamada para executar a operação

 *  d é um código que representa o número e tipo de argumentos que a função c recebe

 *  e é 1 se o valor de retorno deve ser empurrado para a stack e 0 se não
 */
#define ENTRY(a, b, c, d, e) case a: if (length >= b) { PUSH_##e(st->stack, c(POP_##d)); return true; } break;

bool operation(char* str, long long length, State* st);

Value readValue(char* str, long long length, State* st);

char getControlChar(char c);

Value readString(char** str);

void readBlock(char** str);

void resolveWord(char* str, long long length, State* st);

void processInput(char** str, State* st);

#endif
