/**
 * @file
 * @brief contém a implementação das funções correspondentes às operações
 * sobre arrays
 */

#include <string.h>
#include "arrayOperations.h"
#include "blockOperations.h"
#include "logicOperations.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * \brief Procura pelo padrão fornecido na string dada, desalocando os argumentos
 *        fornecidos.
 * 
 *        Retorna o índice no qual o padrão inicia na string dada, ou -1 
 *        caso o padrão não exista na string.
 *
 * @param st  A string dada (sob a forma de #Value)
 *
 * @param pat O padrão a procurar na string dada (sob a forma de #Value)
 *
 * @return    O #Value com um inteiro correspondente ao índice da 
 *  1ª ocorrência na string, -1 se o padrão não for uma substring da string dada
 */
Value substrAndDispose(Value st, Value pat) {
    Value res = substr(st, pat);
    //Desaloca os valores
    disposeValue(st);
    disposeValue(pat);

    return res;
}

/**
 * \brief Procura pelo padrão fornecido na string dada. 
 * 
 *        Retorna o índice no qual o padrão inicia na string dada, ou -1 
 *        caso o padrão não exista na string.
 *
 * @param st  A string dada (sob a forma de #Value)
 *
 * @param pat O padrão a procurar na string dada (sob a forma de #Value)
 *
 * @return    O #Value com um inteiro correspondente ao índice da 
 *  1ª ocorrência na string, -1 se o padrão não for uma substring da string dada
 */
Value substr(Value st, Value pat) {
    //Obtém as strings através dos Values
    char *str = toString(st);
    char *pattern = toString(pat);
    long long res = -1;
    
    for(long long i = 0; str[i]; i++) {
        long long j;

        //Calcula até onde é que as strings coincidem
        for(j = 0; str[i + j] && str[i + j] == pattern[j]; j++);

        //Se chegamos ao fim do padrão então encontramos uma correspondência
        if(!pattern[j]) {
            res = i;
            break;
        }
    }

    free(str);
    free(pattern);

    return fromInteger(res);
}


/**
 * \brief Auxiliar da função separateBySubstr. Parte a string fornecida
 *        pelo padrão dado (na forma de strings (char*))
 *
 * @param str      A string a separar
 *
 * @param pattern  O padrão a usar para separar a string
 *
 * @return         A array (stack) de strings
 */
Stack separateBySubstrAux(char* str, char* pattern) {
    Stack st = empty();

    long long pat_length = strlen(pattern);
    char* current = pattern; //posicao atual no padrao
    char* accum = str; //último split (no início nao houve splits)

    //Enquanto não acabar o string
    for (; *str; str++) {
        current = (*str == *current) ? current + 1 : pattern;

        //Se tivermos encontrado uma ocorrência do padrão
        if (*current == '\0') {
            if (str - pat_length >= accum) {
                char temp = *(str - pat_length + 1); //Guarda o caracter a seguir ao split
                *(str - pat_length + 1) = '\0';      //e substitui por um null terminator
                push(st, fromString(accum));         //para poder chamar fromString.
                *(str - pat_length + 1) = temp;      //Depois é só substituir de volta.
            }
            current = pattern;
            accum = str + 1;
        }
    }

    if (*accum) //ultimo push se for preciso
        push(st, fromString(accum));

    return st;
}

/**
 * \brief Separa uma string pela substring dada, retornando uma array de strings
 *
 * @param s      A string a separar (sob a forma de #Value)
 *
 * @param pat    O padrão a usar para separar a string (sob a forma de #Value)
 *
 * @return       O #Value correspondendo a uma array (stack) de strings
 */
Value separateBySubstr(Value s, Value pat) {
    //Obtém as strings a partir dos Values
    char *str = toString(s);
    char* pattern = toString(pat);

    Stack r = separateBySubstrAux(str, pattern);

    //Libertar valores, pq não vão ser reutilizados
    disposeValue(s);
    disposeValue(pat);

    //Libertar strings
    free(str);
    free(pattern);

    return fromStack(r);
}

/**
 * \brief Separa a stack st pelo índice x a contar de cima
 * @param st      A stack a separar; são-lhe subtraídos x elementos
 * @param x       O índice pelo o qual se vai separar
 * @return        Retorna a stack de cima (com x elementos)
 */
Stack split(Stack st, long long x){
    Stack res = empty();

    for (long long i = length(st) - x; i < length(st); i++)
        push(res, st->values[i]);

    st->size -= x;
    return res;
}

/**
 * \brief Ordena o array dado de acordo com o bloco fornecido
 * @param array   O array a ordenar
 * @param x       O bloco que é usado para comparar elementos
 * @return        O array ordenado
 */
Value sort(State* s, Value array, Value block) {
    long long size = length(array.array);
    //Chama o merge sort
    //Esta função auxiliar é necessária pois é preciso saber de antemão
    //o tamanho da stack.
    return fromStack(mergeSort(s, array.array, block, size));
}

/**
 * \brief Função que inverte a stack
 * @param s Stack fornecida e que irá ser invertida
 */

void reverseStack(Stack s) {
    Stack st = empty();
    while(!isEmpty(s))
        push(st, pop(s));

    struct stack aux = *st;
    *st = *s;
    *s = aux;
    disposeStack(st);
}

/**
 * \brief Ordena o array dado de acordo com o bloco fornecido
 * @param s       O estado do programa
 * @param l       O primeiro array a juntar
 * @param r       O segundo array a juntar
 * @param block   O bloco que é usado para comparar elementos
 * @return        O array ordenado
 */
Stack mergeStacks(State* s, Stack l, Stack r, Value block) {
    Stack res = empty();
    //Enquanto nenhuma stack é vazia
    while(!isEmpty(l) && !isEmpty(r)) {
        Value v1 = executeValue(s, deepCopy(top(l)), block);
        Value v2 = executeValue(s, deepCopy(top(r)), block);

        //Se a condição executada retorna verdadeiro, então l < r
        //Inserimos só o menor elemento
        push(res, pop(isTrue(isLess(v1, v2)) ? l : r));
    }
    
    //Reverte as stacks para poder fazer merge sem trocar a ordem
    //dado os elementos estão invertidos nas stacks originais
    reverseStack(l);
    reverseStack(r);
    //Insere na stack res todos os elementos das duas stacks que ainda não foram
    //inseridos (apenas tem efeito para uma das stacks)
    res = merge(res, l);
    res = merge(res, r);

    return res;
}

/**
 * \brief Ordena o array dado de acordo com o bloco fornecido
 * @param s       O estado do programa
 * @param array   O array a ordenar
 * @param x       O bloco que é usado para comparar elementos
 * @return        O array ordenado
 */
Stack mergeSort(State* s, Stack st, Value block, long long n) {
    //Caso base: a stack já está ordenada
    if(n <= 1)
        return st;
    //Parte a stack em duas
    Stack secondHalf = split(st, n / 2);

    //Ordena as duas metades
    st = mergeSort(s, st, block, (n + 1) / 2);
    secondHalf = mergeSort(s, secondHalf, block, n / 2);

    //Inverter as stacks, de forma a que os elementos maiores estejam no início
    reverseStack(st);
    reverseStack(secondHalf);
    //Junta as metades ordenadas para uma nova stack ordenada
    return mergeStacks(s, st, secondHalf, block);
}