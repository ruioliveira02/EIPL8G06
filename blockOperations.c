/**
* @file contém a implementação das funções correspondentes
* às operações relacionadas com blocos
*/
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "logicOperations.h"
#include "stackOperations.h"
#include "arrayOperations.h"

/**
 * \brief Executa um bloco dentro de uma stack
 * @param s O estado do programa
 * @param block bloco fornecido
 * @return Value que é resultado da operação do bloco dentro da stack
 */

Value execute (State* s, Stack st, Value block) {
    Stack temp = s->stack;
    s->stack = st;
    processInput (&block.block, s);
    s->stack = temp;
    return st->value;
}


/**
 * \brief Executa um bloco dentro de uma stack enquanto houver um valor verdadeiro no topo da stack
 * @param st a stack fornecida
 * @param block bloco fornecido
 */

void executeWhileTrue (State* s, Value block) {
    while (!isEmpty(s->stack) && isTrue(s->stack->value))
        execute (s, s->stack, block);
}

/**
 * \brief Mofica cada valor da array para a respetiva imagem pela função block.
 * @param s     o estado do programa
 * @param block bloco fornecido
 */
void map (State* s, char* block){
    /*Stack st = empty();
    while(!isEmpty(s->stack)) {
        Value v = execute(s, s->stack, block);
        push(st, v);
        disposeValue(pop(s->stack));
    }
    //printStackLine(st);
    *s->stack = *st;*/
    //disposeStack(st);
    int len = strlen(block);
    if(isEmpty(s->stack)==0){
        Stack st = s->stack;
        s->stack = s->stack->previous;
        map(s, block);
        s->stack = st;
        execute(s, s->stack, fromBlock(block, len));
    }
}

/**
 * \brief Retira da stack os elementos que não satisfazem a condição do block
 * @param s     o estado do programa
 * @param block bloco fornecido
 */
void filter (State* s, Value block){

    if(isEmpty(s->stack)==0){
        Stack st = s->stack;
        s->stack = s->stack->previous;
        filter(s, block);
        Stack a=convertToStack(deepCopy(st->value)).array;
        s->stack = a;
        if(isTrue(execute(s, s->stack, block))==0)
            eraseTop(st);
        
        s->stack = st;
        disposeStack(a);
    }
}

/**
 * \brief Aplica a função do block enquanto que o tamanho da stack seja no mínimo 2
 * @param s     o estado do programa
 * @param st    o array sobre o qual fazer fold
 * @param block bloco fornecido
 */
Value fold (State* s, Stack st, Value block){
    if (isEmpty(st) || isEmpty(st->previous))
        return st->value;

    Value top = pop(st);
    fold(s, st, block);
    push(st, top);
    execute(s, st, block);
    return st-> value;


    /*reverseStack(st);


    while (!isEmpty(st->previous)) {
        rotateTop(st, 2);
        execute(s, &st, block);
    }

    Value ans = pop(st);
    disposeStack(st);
    return ans;*/
}