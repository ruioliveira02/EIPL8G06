#include "logicOperations.h"
#include <string.h>

/**
 * \brief Avalia o valor lógico do value
 * @param a   o elemento do tipo #Value
 * @return Um inteiro que simboliza o valor lógico (1 caso seja verdadeiro e 0 caso seja falso)
 */

bool isTrue(Value a)
{
	switch (a.type) {
		case Double:	return a.decimal != 0;
		case Int: 		return a.integer != 0;
		case Char: 		return a.character != '\0';
		case String:	return *a.string != '\0';
		default:		return false;
	}
}

/**
 * \brief Executa as operações pedidas
 * @param str A string correspondente aos operadores
 * @param x   o elemento do tipo #Value
 * @param y   o elemento do tipo #Value
 * @return    x ou y, dependendo do resultado da operação que for efetuada
 */

Value shortcutSelect(char* str, Value x, Value y)
{
	switch (*str)
	{
		case '&':	return isTrue(x) ? y : x;
		case '|':	return isTrue(x) ? x : y;
		//case '<':	return isTrue(menor(x, y)) ? x : y;
		//case '>':	return isTrue(maior(x, y)) ? x : y;
		default: 	return isTrue(x) ? x : y;
	}
}


/**
 * \brief Operação if then else
 * @param x   o elemento do tipo #Value que atua como condição
 * @param y   o elemento do tipo #Value que é o resultado caso a condição seja verdadeira
 * @param z   o elemento do tipo #Value que é o resultado caso a condição seja falsa
 * @return    y se for verdade, z se for falso
 */

Value conditional(Value x, Value y, Value z){

	return isTrue(x) ? y : z;
}

/**
 * \brief Operação de comparação de valores
 * @param x   o elemento do tipo #Value 
 * @param y   o elemento do tipo #Value 
 * @return    1 se for verdade, 0 se for falso
 */

Value isEqual (Value x, Value y){

	if(x.type==String){
		return fromInteger (strcmp (x.string,y.string)==0);
	}else{//se forem tipos diferentes automaticamente não são iguais
	   NumericOperationAux(&x,&y);
		switch(x.type){
			case Double:
			return fromInteger(x.decimal==y.decimal);//testar tolerâncias
			case Int:
			return fromInteger(x.integer==y.integer);
			case Char:
			return fromInteger(x.character==y.character);
		}
	}
}

/**
 * \brief Verifica se o primeiro argumento é menor que o segundo
 * @param x   o elemento do tipo #Value 
 * @param y   o elemento do tipo #Value 
 * @return    1 se for verdade, 0 se for falso
 */

Value isLess (Value x, Value y){

	if(x.type==String){
		return fromInteger (strcmp (x.string,y.string)<0);
	}else{//se forem tipos diferentes automaticamente não são iguais
	   NumericOperationAux(&x,&y);
		switch(x.type){
			case Double:
			return fromInteger(x.decimal<y.decimal);//testar tolerâncias
			case Int:
			return fromInteger(x.integer<y.integer);
			case Char:
			return fromInteger(x.character<y.character);
		}
	}
}

/**
 * \brief Verifica se o primeiro argumento é maior que o segundo
 * @param x   o elemento do tipo #Value 
 * @param y   o elemento do tipo #Value 
 * @return    1 se for verdade, 0 se for falso
 */

Value isGreater (Value x, Value y){

	if(x.type==String){
		return fromInteger (strcmp (x.string,y.string)>0);
	}else{//se forem tipos diferentes automaticamente não são iguais
	   NumericOperationAux(&x,&y);
		switch(x.type){
			case Double:
			return fromInteger(x.decimal>y.decimal);//testar tolerâncias
			case Int:
			return fromInteger(x.integer>y.integer);
			case Char:
			return fromInteger(x.character>y.character);
		}
	}
}

/**
 * \brief Devolve 1 se for 0 e devolve 0 caso contrário
 * @param x   o elemento do tipo #Value 
 * @return    1 se for 0 e 0 se for 1
 */

Value logicNot (Value x){

	switch(x.type){
		case Double:
		return fromInteger(x.decimal==0.0);//testar tolerâncias
		case Int:
		return fromInteger(x.integer==0);
		case Char:
		return fromInteger(x.character==0);
	}
}
/**
 * \brief Muda o valor da variável para ser o x
 * @param var variável dada (letra de A a Z)
 * @param x   o elemento do tipo #Value
 * @param s   o state do programa
 */
Value setVariable(char var, Value x, State s){
	s.variables[var-'A']=x;
	return x;
}

/**
 * \brief Define o valor inicial das variáveis
 * @param s   o state do programa
 */
void initializeVariables(State *s){
	int i;

	for(i=0;i<=5;i++){
		setVariable('A'+i,fromInteger(10+i),*s);
	}
	for(i=0;i<=2;i++){
		setVariable('X'+i,fromInteger(i),*s);
	}
	setVariable('N',fromCharacter('\n'),*s);
	setVariable('S',fromCharacter(' '),*s);
}