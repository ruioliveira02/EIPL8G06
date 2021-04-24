//!Include guard
#ifndef LOGIC_OPERATIONS_H
//!Include guard
#define LOGIC_OPERATIONS_H

#include "stack.h"
#include "parser.h"

bool isTrue(Value a);

Value shortcutSelect(char*, Value, Value);

Value conditional(Value x, Value y, Value z);

Value isEqual (Value x, Value y);

Value isLess (Value x, Value y);

Value isGreater (Value x, Value y);

Value logicNot (Value x);

Value setVariable(char var, State* s, Value x);

void initializeVariables(State *s);

#endif 