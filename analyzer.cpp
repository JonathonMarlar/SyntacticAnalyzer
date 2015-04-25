#include <iostream>
#include <vector>
#include "analyzer.h"
#include "scanner.h"
using namespace std;

/*
g_prog:
- Acts as the main grammar that detects whether the code is in the grammar
- Returns true if the code is in the grammar, otherwise returns false
*/
bool g_prog(vector<TokenLine>& v)
{
	// iterator
	int i = 0;
	
	// match PROGRAM
	if (v[i].token == PROGRAM)
		i++;
	else
	{
		cout << "Error: missing PROGRAM on line " << v[i].line << endl;
		return false;
	}
	
	// match <prog_name>
	if (g_prog_name(v,i))
		i++;
	else
	{
		cout << "Error: not an ID on line " << v[i].line << endl;
		return false;
	}
	
	// match VAR
	if (v[i].token == VAR)
		i++;
	else
	{
		cout << "Error: not a VAR for <prog> on line " << v[i].line << endl;
		return false;
	}
	
	// match <dec-list>
	if (g_dec_list(v,i))
		i++;
	else
	{
		cout << "Error: not a <dec-list> for <prog> on line " << v[i].line << endl;
		return false;
	}
	
	// match BEGIN
	if (v[i].token == BEGIN)
		i++;
	else
	{
		cout << "Error: missing BEGIN on line " << v[i].line << endl;
		return false;
	}
	
	// match <stmt-list>
	if (g_stmt_list(v,i))
		i++;
	else
	{
		cout << "Statement List Error on line " << v[i].line << endl;
		return false;
	}
	
	// now match the last token
	if (v[i].token == ENDP)
		return true;
	else
	{
		cout << "Error: missing END. on line " << v[i].line << endl;
		return false;
	}
}

bool g_prog_name(vector<TokenLine>& v, int& i)
{
	// code
	if (v[i].token == IDENTIFIER)
		return true;
	else
		return false;
}

bool g_dec_list(vector<TokenLine>& v, int& i)
{
	bool temp = false;
	
	if (g_dec(v,i))
	{
		temp = true;
		i++;
	}
	else
	{
		cout << "Error: not a <dec> on line " << v[i].line << endl;
		return false;
	}
	
	while (v[i].token == SEMICOLON)
	{
		if (g_dec(v,i))
		{
			temp = true;
			i++;
		}
		else
		{
			cout << "Error: not a <dec> on line " << v[i].line << endl;
			return false;
		}
	}
	i--;
		
	return temp;
}
bool g_dec(vector<TokenLine>& v, int& i)
{
	if (g_id_list(v,i))
		cout << "OKda" << endl;
	else
	{
		cout << "Error: not an id-list for <dec> on line " << v[i].line << endl;
		return false;
	}
	if (v[i].token == COLON)
		i++;
	else
	{
		cout << "Error: not a colon for <dec> on line " << v[i].line << endl;
		return false;
	}
	if (g_type(v,i))
		return true;
	else
	{
		cout << "Error: not a <type> for <dec> on line " << v[i].line << endl;
		return false;
	}
}

bool g_type(vector<TokenLine>& v, int& i)
{
	return v[i].token == INTEGER;
}

bool g_id_list(vector<TokenLine>& v, int& i)
{
	bool temp = false;
	
	// change temp to true only when there's at least one id
	if (v[i].token == IDENTIFIER)
	{
		temp = true;
		i++;
	}
	
	// there could be more ids, so let's check
	while (v[i].token != RIGHTPAREN && v[i].token != COLON)
	{
		// must be id THEN comma
		if (v[i].token == COMMA)
			i++;
		else
			temp = false;
		if (v[i].token == IDENTIFIER)
			i++;
		else
			temp = false;
	}
	
	return temp;
}

bool g_stmt_list(vector<TokenLine>& v, int& i)
{
	// code
}

bool g_stmt(vector<TokenLine>& v, int& i)
{
	if (g_assign(v,i) || g_read(v,i) || g_write(v,i) || g_for(v,i))
		return true;
	else
		return false;
}

bool g_assign(vector<TokenLine>& v, int& i)
{
	if (v[i].token == IDENTIFIER)
		i++;
	else
		return false;
	if (v[i].token == EQUALS)
		i++;
	else
		return false;
	if (g_exp(v,i))
		return true;
	else
		return false;
}

bool g_exp(vector<TokenLine>& v, int& i)
{
	// code
}

bool g_term(vector<TokenLine>& v, int& i)
{
	// code
}

bool g_factor(vector<TokenLine>& v, int& i)
{
	bool temp = false;
	
	if (v[i].token == IDENTIFIER || v[i].token == NUM)
		temp = true;
	else if (v[i].token == LEFTPAREN)
	{
		i++;
		if (g_exp(v,i))
		{
			if (v[i].token == RIGHTPAREN)
				temp = true;
		}
	}
	
	return temp;
}

bool g_read(vector<TokenLine>& v, int& i)
{
	// code
}

bool g_write(vector<TokenLine>& v, int& i)
{
	// code
}

bool g_for(vector<TokenLine>& v, int& i)
{
	// code
}

bool g_index_exp(vector<TokenLine>& v, int& i)
{
	// code
}

bool g_body(vector<TokenLine>& v, int& i)
{
	// code
}
