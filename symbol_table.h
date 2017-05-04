#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>

class Symbol_table {
private:
	std::map<std::string, int> symbols;

public:
	Symbol_table() {
		symbols = std::map<std::string, int>();
	}

	~Symbol_table() { }

	void addSymbol(std::string s, int val) {
		std::pair<std::map<std::string, int>::iterator, bool> r;
		r = symbols.insert(std::pair<std::string, int>(s, val));
		assert(r.second && "Variable already exists . . .");
	}

	int getVal(std::string s) {
		return symbols[s];
	}
};

#endif
