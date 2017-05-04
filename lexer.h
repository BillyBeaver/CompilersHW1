#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include "and_expr.h"
#include "or_expr.h"
#include "bool_expr.h"
#include "not_expr.h"
#include "xor_expr.h"
#include "int_expr.h"
#include "gt_expr.h"
#include "gte_expr.h"
#include "lt_expr.h"
#include "lte_expr.h"
#include "if_else_expr.h"
#include "eql_expr.h"
#include "neq_expr.h"
#include "add_expr.h"
#include "sub_expr.h"
#include "mul_expr.h"
#include "div_expr.h"
#include "mod_expr.h"
#include "neg_expr.h"
#include "symbol_table.h"
#include <ctype.h>

enum Token_Kind {
	EOF_TOKEN,
	ADD_TOKEN,
	AND_TOKEN,
	BOOL_TOKEN,
	DIV_TOKEN,
	EQL_TOKEN,
	GT_TOKEN,
	GTE_TOKEN,
	COND_TOKEN,
	INT_TOKEN,
	LT_TOKEN,
	LTE_TOKEN,
	MOD_TOKEN,
	MUL_TOKEN,
	NEG_TOKEN,
	NEQ_TOKEN,
	NOT_TOKEN,
	OR_TOKEN,
	SUB_TOKEN,
	XOR_TOKEN,
	LPAR_TOKEN,
	RPAR_TOKEN,
	COL_TOKEN,
	OCTO_TOKEN,
	VAR_TOKEN,
	ASGN_TOKEN
};

class Token {
private:
	Token_Kind name;
	int value;

public:
	Token() { }
	Token(Token_Kind n) {
		name = n;
		value = 0;
	}
	Token(Token_Kind n, int val) {
		name = n;
		value = val;
	}
	~Token() { }
	Token_Kind getName() {
		return name;
	}
	int getValue() {
		return value;
	}

	std::string print() {
		std::string str = std::to_string(long long (value));
		switch(name) {
		case EOF_TOKEN:
			return "EOF_TOKEN";
			break;
		case ADD_TOKEN:
			return "ADD_TOKEN";
			break;
		case AND_TOKEN:
			return "AND_TOKEN";
			break;
		case BOOL_TOKEN:
			str = (value ? "true" : "false");
			return "BOOL_TOKEN: " + str;
			break;
		case DIV_TOKEN:
			return "DIV_TOKEN";
			break;
		case EQL_TOKEN:
			return "EQL_TOKEN";
			break;
		case GT_TOKEN:
			return "GT_TOKEN";
			break;
		case GTE_TOKEN:
			return "GTE_TOKEN";
			break;
		case COND_TOKEN:
			return "COND_TOKEN";
			break;
		case INT_TOKEN:
			return "INT_TOKEN: " + str;
			break;
		case LT_TOKEN:
			return "LT_TOKEN";
			break;
		case LTE_TOKEN:
			return "LTE_TOKEN";
			break;
		case MOD_TOKEN:
			return "MOD_TOKEN";
			break;
		case MUL_TOKEN:
			return "MUL_TOKEN";
			break;
		case NEG_TOKEN:
			return "NEG_TOKEN";
			break;
		case NEQ_TOKEN:
			return "NEQ_TOKEN";
			break;
		case NOT_TOKEN:
			return "NOT_TOKEN";
			break;
		case OR_TOKEN:
			return "OR_TOKEN";
			break;
		case SUB_TOKEN:
			return "SUB_TOKEN";
			break;
		case XOR_TOKEN:
			return "XOR_TOKEN";
			break;
		case LPAR_TOKEN:
			return "LPAR_TOKEN";
			break;
		case RPAR_TOKEN:
			return "RPAR_TOKEN";
			break;
		case COL_TOKEN:
			return "COL_TOKEN";
			break;
		case OCTO_TOKEN:
			return "OCTO_TOKEN";
			break;
		case VAR_TOKEN:
			return "VAR_TOKEN";
			break;
		case ASGN_TOKEN:
			return "ASGN_TOKEN";
			break;
		}
	}
};

class Punc_Token : public Token {
public:
	Punc_Token() { }
	Punc_Token(Token_Kind n) : Token(n) { }
	~Punc_Token() { }
};

class Int_Token : public Token {
public:
	Int_Token() { }
	Int_Token(Token_Kind n, int val) : Token(n, val) { }
	~Int_Token() { }
};

class Bool_Token : public Token {
public:
	Bool_Token() { }
	Bool_Token(Token_Kind n, bool val) : Token(n, val) { }
	~Bool_Token() { }
};

class Var_Token : public Token {
private:
	std::string name;
public:
	Var_Token() { }
	Var_Token(Token_Kind n, std::string val) : Token(n) { 
		name = val;
	}
	~Var_Token() { }
};

class Lexer {
private:
	const char* first;
	const char* last;
	const char* stream;

public:
	Lexer() { }
	Lexer(const char* stream) {
		this->stream = stream;
		last = &stream[strlen(stream)];
		first = &stream[0];
	}
	~Lexer() { }

	bool Eof() {
		return first == last;
	}

	char lookahead() {
		if(Eof())
			return 0;
		else
			return *first;
	}

	void consume() {
		++first;
	}

	Token* next() {
		const char * iter;
		std::string str;
		int n;
		while(!Eof()) {
			switch(lookahead()) {
			case '<':
				consume();
				if(lookahead() == '=') {
					consume();
					return new Punc_Token(LTE_TOKEN);
				}
				else {
					return new Punc_Token(LT_TOKEN);
				}
				break;
			case '>':
				consume();
				if(lookahead() == '=') {
					consume();
					return new Punc_Token(GTE_TOKEN);
				}
				else {
					return new Punc_Token(GT_TOKEN);
				}
				break;
			case '=':
				consume();
				if(lookahead() == '=') {
					consume();
					return new Punc_Token(EQL_TOKEN);
				}
				else {
					return new Punc_Token(ASGN_TOKEN);
					//assert(false && "Syntax Error, Double Equal Sign (Expected Single)");
				}
				break;
			case '!':
				consume();
				if(lookahead() == '=') {
					consume();
					return new Punc_Token(NEQ_TOKEN);
				}
				else {
					return new Punc_Token(NEG_TOKEN);
				}
				break;

			case '?':
				consume();
				return new Punc_Token(COND_TOKEN);
				break;
			case ':':
				consume();
				return new Punc_Token(COL_TOKEN);
				break;

			case '&':
				consume();
				if(lookahead() == '&') {
					consume();
					return new Punc_Token(AND_TOKEN);
				}
				else {
					assert(false && "Syntax Error, Single Ampersand (Expected Double)");
				}
				break;
			case '|':
				consume();
				if(lookahead() == '|') {
					consume();
					return new Punc_Token(OR_TOKEN);
				}
				else {
					assert(false && "Syntax Error, Single Pipe (Expected Double)");
				}
				break;
			
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z':
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
			case '_':
				iter = first;
				while(!Eof() && (isdigit(lookahead()) || isalpha(lookahead()))) {
					consume();
				}
				str = std::string(iter, first);
				//sm.addSymbol(str, 0);
				//return new Int_Token(INT_TOKEN, n);
				if(str == "false")
					return new Bool_Token(BOOL_TOKEN, false);
				else if(str == "true")
					return new Bool_Token(BOOL_TOKEN, true);
				else
					return new Var_Token(VAR_TOKEN, str);
				break;
			/*
			case 't':
				consume();
				if(lookahead() == 'r') {
					consume();
					if(lookahead() == 'u') {
						consume();
						if(lookahead() == 'e') {
							consume();
							return new Bool_Token(BOOL_TOKEN, true);
						}
						else {
							assert(false && "Syntax Error, 'true' expected");
						}
					}
					else {
						assert(false && "Syntax Error, 'true' expected");
					}
				}
				else {
					assert(false && "Syntax Error, 'true' expected");
				}
				break;
				*/
			/*case 'f':
				consume();
				if(lookahead() == 'a') {
					consume();
					if(lookahead() == 'l') {
						consume();
						if(lookahead() == 's') {
							consume();
							if(lookahead() == 'e') {
								consume();
								return new Bool_Token(BOOL_TOKEN, false);
							}
							else {
								assert(false && "Syntax Error, 'false' expected");
							}
						}
						else {
							assert(false && "Syntax Error, 'false' expected");
						}
					}
					else {
						assert(false && "Syntax Error, 'false' expected");
					}
				}
				else {
					assert(false && "Syntax Error, 'false' expected");
				}
				break;
				*/
			case '+':
				consume();
				return new Punc_Token(ADD_TOKEN);
				break;
			case '-':
				consume();
				//if(isdigit(lookahead())) {
				//	return new Punc_Token(NEG_TOKEN);
				//}
				//else {
					return new Punc_Token(SUB_TOKEN);
				//}
				break;
			case '*':
				consume();
				return new Punc_Token(MUL_TOKEN);
				break;
			case '/':
				consume();
				return new Punc_Token(DIV_TOKEN);
				break;
			case '%':
				consume();
				return new Punc_Token(MOD_TOKEN);
				break;

			case '(':
				consume();
				return new Punc_Token(LPAR_TOKEN);
				break;
			case ')':
				consume();
				return new Punc_Token(RPAR_TOKEN);
				break;

			case '#':
				consume();
				while(!Eof()) {
					consume();
				}
				return new Punc_Token(OCTO_TOKEN);
				break;

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				iter = first;
				while(!Eof() && isdigit(lookahead())) {
					consume();
				}
				str = std::string(iter, first);
				n = std::atoi(str.c_str());
				return new Int_Token(INT_TOKEN, n);
				break;
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				consume();
				continue;
			}
		}
		return new Punc_Token(EOF_TOKEN);
	}
};

#endif
