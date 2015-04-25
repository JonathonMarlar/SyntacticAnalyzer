#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <cctype>
using namespace std;

// To save us the trouble of remembering the correct token IDs,
// let's use an enumeration to 'save' them in the program
enum TokenID
{
	PROGRAM = 1,
	VAR,
	BEGIN,
	END,
	ENDP,
	INTEGER,
	FOR,
	READ,
	WRITE,
	TO,
	DO,
	SEMICOLON,
	COLON,
	COMMA,
	EQUALS,
	PLUS,
	MINUS,
	TIMES,
	DIV,
	LEFTPAREN,
	RIGHTPAREN,
	IDENTIFIER,
	NUM
};

struct Symbol
{
	string name;
	int tokenCode;
};

int getToken(string line, string expr, int goalTokenID);
bool isDelimiter(char n);

