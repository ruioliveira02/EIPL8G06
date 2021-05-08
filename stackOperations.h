/**
 * @file contém a declaração das funções correspondentes
 * às operações de manipulação da stack
 */

//! Include guard
#ifndef STACK_OPERATIONS_H
//! Include guard
#define STACK_OPERATIONS_H

#include "stack.h"

/**
 * \brief Roda os dois primeiros elementos da stack
 * @param st Stack dada
 */
#define swap(st) rotateTop(st, 2)

/**
 *  \brief Roda os três primeiros elementos da stack
 *  @param st Stack dada
 */
#define rotate(st) rotateTop(st, 3)

void rotateTop(Stack, int);

void printTop(Stack st);

Value copyElement(State*, Value);

void readLine(Stack);

void duplicate(Stack);

Stack range(long long);

Stack repeat(Stack, int);

Value comma(State* s, Value a);

#endif