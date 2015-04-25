/*
Lexical Analyzer (Scanner)
Jonathon Cole Marlar
CS 421 - Automata Theory and Compiler Construction
20 March 2015
*/
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <cctype>
#include <unordered_map>
#include <vector>
#include "scanner.h"
#include "analyzer.h"
using namespace std;

// a hash table to handle our numbers and identifiers
unordered_map <string, Symbol> idTable;

// a vector array of tokens
vector<TokenLine> tokenArray;

void PreProcessBuffer(string filename);
void ProcessBuffer(string filename);
void printTable();

// DFA functions may go into another file entirely.

int main(int argc, char** argv)
{
	// Small little interface to ask for code file
	string fname;
	cout << "Enter the filename of the code you want to run: ";
	cin >> fname;
	
	// Call the pre-processing buffer here
	PreProcessBuffer(fname);

	// Call the processing buffer here
	ProcessBuffer("clean.txt");
	
	// now we show off the table
	printTable();
	
	if (g_prog(tokenArray))
		cout << "In the language!" << endl;

	// system("PAUSE");
	return 0;
}

/*
PreProcessBuffer:
	- Takes in a file to be scanned
	- Takes out any comment lines (i.e. (* ... *)
	- Condenses any extraneous whitespace to a single space (' ')
	- This new format will be saved to a new file
	cleanedFile << line << endl;
*/
void PreProcessBuffer(string filename)
{
	string line;
	ifstream codeFile(filename);
	ofstream cleanedFile("clean.txt");
	bool inComment = false;

	if (codeFile.is_open() && cleanedFile.is_open())
	{
		while (getline(codeFile, line))
		{
			// we don't want to do anything until we hit a non-whitespace character
			char* it = &line[0];
			while (*it != NULL)
			{
				if (inComment == false)
				{
					if (isspace(*it))
					{
						if (*it != line[0] && !isspace(*(it - 1)))
							cleanedFile << *it;
					}
					else if (*it == '(' && *(it + 1) == '*')
					{
						inComment = true;
					}
					else
					{
						cleanedFile << (char) toupper(*it);
					}
				}
				else
				{
					if (*it == '*' && *(it + 1) == ')')
					{
						inComment = false;
						it++;
					}
				}
				it++;
			}
			cleanedFile << endl;
		}
		cleanedFile.close();
		codeFile.close();
	}
}

/*
ProcessBuffer:
- For each line, reads letters one by one
- Recognizes tokens using a regular expression (or dfa)
- Stores data into hash table
*/
void ProcessBuffer(string filename)
{
	// open the cleaned file
	string line;
	ifstream cleanCode(filename);
	
	if (cleanCode.is_open())
	{
		int lineNum = 1;
		int errorCount = 0;
		
		while (getline(cleanCode, line))
		{
			// print the line number
			cout << lineNum << " " << line << endl;
			lineNum++;
			
			// now we have to scan in, char by char, to find tokens
			char* start = &line[0];
			
			// until we hit end of line, keep finding tokens!
			while (*start != NULL)
			{
				char* lookahead = start;
				string temp = "";
				
				while (!isDelimiter(*lookahead) && temp.length() != 16 && *lookahead != NULL && *lookahead != ' ')
				{
					// if we haven't hit a delimiter, add text to temp
					temp = temp + *lookahead;
					lookahead++;
					
					if (isdigit(*start) && isalpha(*lookahead))
						break;
				}
				
				// we need to keep up with what token it is
				int token;
				
				// now we need to choose our 'dfa' by looking at the start pointer
				switch (*start)
				{
					case 'P':
						{
							token = getToken(temp, "PROGRAM", PROGRAM);
							break;
						}
						
					case 'V':
						{
							token = getToken(temp, "VAR", VAR);
							break;
						}
					case 'B':
						{
							token = getToken(temp, "BEGIN", BEGIN);
							break;
						}
					case 'E':
						{
							if (*(lookahead-1) == '.')
							{
								token = getToken(temp, "END.", ENDP);
							}
							else
							{
								token = getToken(temp, "END", END);
							}
							break;
						}
					case 'I':
						{
							token = getToken(temp, "INTEGER", INTEGER);
							break;
						}
					case 'F':
						{
							token = getToken(temp, "FOR", FOR);
							break;
						}
					case 'R':
						{
							token = getToken(temp, "READ", READ);
							break;
						}
					case 'W':
						{
							token = getToken(temp, "WRITE", BEGIN);
							break;
						}
					case 'T':
						{
							token =  getToken(temp, "TO", TO);
							break;
						}
					case 'D':
						{
							if (*(lookahead-1) == 'V')
								token = getToken(temp, "DIV", DIV);
							else
								token = getToken(temp, "DO", DO);
							break;
						}
					// Delimiters are usually left on their own, so we don't need a regex for them
					case ';':
						{
							token = SEMICOLON;
							temp = temp + *start;
							lookahead++;
							break;
						}
					case ':':
						{
							if (*(lookahead+1) == '=')
							{
								token = EQUALS;
								temp = temp + *start + *(start+1);
								lookahead++;
							}
							else
							{
								token = COLON;
								temp = temp + *start;
							}
							lookahead++;
							break;
						}
					case ',':
						{
							token = COMMA;
							temp = temp + *start;
							lookahead++;
							break;
						}
					case '+':
						{
							token = PLUS;
							break;
						}
					case '-':
						{
							token = MINUS;
							break;
						}
					case '*':
						{
							token = TIMES;
							break;
						}
					case '(':
						{
							token = LEFTPAREN;
							temp = temp + *start;
							lookahead++;
							break;
						}
					case ')':
						{
							token = RIGHTPAREN;
							temp = temp + *start;
							lookahead++;
							break;
						}
					// our regex function checks for legit integers and ids, so we need to use it
					case '0': case '1': case '2': case '3': case '4': case '5': 
					case '6': case '7': case '8': case '9': 
						{
							token = getToken(temp, "", NUM);
							break;	
						}
					default:
						{
							if (isalpha(*start))
								token = getToken(temp, "", IDENTIFIER);
							else
							{
								cout << "Error: unrecognized token" << endl;
								token = -1;
							}
							break;	
						}
				}
				
				// after the token has been found, print it, add it to the token list & put it in the symbol table if needed
				cout << "\t" << token << "  " << temp << endl;
				TokenLine tl;
				tl.line = lineNum - 1;
				tl.token = token;
				tokenArray.push_back(tl);
				if (token == IDENTIFIER || token == NUM)
				{
					Symbol s;
					s.name = temp;
					s.tokenCode = token;
					idTable[temp] = s;
				}
				
				if (token == -1)
					errorCount++;
				
				// need to make sure the pointer ahead isn't null (i.e. end of line)
				// parentheses are a special case since they are delimiters with no spacing between them
				if (*lookahead != NULL && !isDelimiter(*lookahead) && *(lookahead-1) != '(' && !isalpha(*lookahead))
					start = lookahead + 1;
				else
					start = lookahead;
			}
		}
		cleanCode.close();
		// now print out the final tally of lines and errors found.
		cout << endl << lineNum-1 << " Lines, " << errorCount << " Errors" << endl;
	}
}

/*
printTable:
	- Prints out the symbol table
	- No need for parameters, idTable is global here
*/
void printTable()
{
	cout << "\n-- Symbol Table --\n" << endl;
	for (auto itr = idTable.begin(); itr != idTable.end(); itr++)
	{
		cout << (*itr).first << " : ";
		Symbol s = (*itr).second;
		cout << s.name << " " << s.tokenCode << endl;
	}
}


