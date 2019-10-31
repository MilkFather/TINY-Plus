#ifndef __TINY_LEXICAL_STATE_MACHINE_H__
#define __TINY_LEXICAL_STATE_MACHINE_H__

#include "lex/lexical.h"

extern int (*StateMachine[51]) (Lex &sender);
extern int TerminatingStates[21];

#endif