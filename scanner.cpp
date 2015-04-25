#include <iostream>
#include <string>
#include <regex>
#include <cctype>
#include "scanner.h"
using namespace std;

/*
getToken:
- Takes in a string, a regex, and a goal token ID
- Checks against regular expression (or DFA) and changes tokens accordingly
- Returns the token ID
*/
int getToken(string line, string expr, int goalTokenID)
{
	int tokenID = IDENTIFIER;
	regex r(expr);

	if (regex_match(line, r))
		tokenID = goalTokenID;

	// if it's still an identifier, we need to check if it's legit
	else if (tokenID == IDENTIFIER && goalTokenID != NUM)
	{
		for (int i = 0; i < line.length(); i++)
		{
			if (!(isalnum(line[i]) || line[i] == '_'))
			{
				tokenID = -1;
				cout << "Error: Invalid identifier" << endl;
				break;
			}
		}
	}
	
	// or it could be a number
	else if (tokenID == IDENTIFIER && goalTokenID == NUM)
	{
		for (int i = 0; i < line.length(); i++)
		{
			if (!isdigit(line[i]))
			{
				tokenID = -1;
				cout << "Error: Invalid identifier" << endl;
				break;
			}
			else
				tokenID = goalTokenID;		
		}
	}

	return tokenID;
}

/*
isDelimiter:
- Takes in a scharacter
- Checks against a list of potential delimiters
- Returns true if the character matched anything in the list
*/
bool isDelimiter(char n)
{
	string delimiters = ";:,()";

	for (int i = 0; i < delimiters.length(); i++)
	{
		if (n == delimiters[i])
			return true;
	}

	return false;
}

