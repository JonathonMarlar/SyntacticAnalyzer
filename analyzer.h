#pragma once

#include <iostream>
#include <vector>
using namespace std;

struct TokenLine
{
	int token;
	int line;
};

bool g_prog(vector<TokenLine>& v);
bool g_prog_name(vector<TokenLine>&, int& i);
bool g_dec_list(vector<TokenLine>& v, int& i);
bool g_dec(vector<TokenLine>& v, int& i);
bool g_type(vector<TokenLine>& v, int& i);
bool g_id_list(vector<TokenLine>& v, int& i);
bool g_stmt_list(vector<TokenLine>& v, int& i);
bool g_stmt(vector<TokenLine>& v, int& i);
bool g_assign(vector<TokenLine>& v, int& i);
bool g_exp(vector<TokenLine>& v, int& i);
bool g_term(vector<TokenLine>& v, int& i);
bool g_factor(vector<TokenLine>& v, int& i);
bool g_read(vector<TokenLine>& v, int& i);
bool g_write(vector<TokenLine>& v, int& i);
bool g_for(vector<TokenLine>& v, int& i);
bool g_index_exp(vector<TokenLine>& v, int& i);
bool g_body(vector<TokenLine>& v, int& i);

