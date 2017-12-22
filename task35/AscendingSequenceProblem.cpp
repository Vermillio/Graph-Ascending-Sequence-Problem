#include "AscendingSequenceProblem.h"
#include <iostream>
#include <string>
#include <queue>

using namespace std;

bool asp::AscSeqChecker::run(const vector<string> &relations, vector<string> *ans)
{
	vector<vector<edge>> gr;

	int begin = 0;
	vector<string> names;
	for (auto v : relations)
	{
		//	bool valid = true;
		int i = 0;
		while (v[i] != '<' && v[i] != '>')
		{
			if (i == v.size() - 1)
				break;
			++i;
		}
		if (i == v.size() - 1)
		{
			cout << "Invalid expression ignored : " << i << endl;
			continue;
		}
		string from, to;
		if (v[i] == '<')
		{		
			from = string(v.begin(), v.begin() + i);
			to = string(v.begin() + i + 1, v.end());
		}
		else {
			to = string(v.begin(), v.begin() + i);
			from = string(v.begin() + i + 1, v.end());
		}
		if (from == to)
		{
			cout << "Invalid expression is ignored : " << i << endl;
			continue;
		}
		int from_it = -1, to_it = -1;
		for (int i = 0; i < gr.size(); ++i)
		{
			if (names[i] == from)
			{
				from_it = i;
				if (to_it != -1)
					break;
			} else 
				if (names[i] == to)
			{
				to_it = i;
				if (from_it != -1)
					break;
			}
		}
		if (to_it == begin)
			begin = from_it;
		if (from_it == -1)
		{
			gr.push_back({});
			names.push_back(from);
			from_it = gr.size() - 1;
		}
		if (to_it == -1)
		{
			gr.push_back({});
			names.push_back(to);
			to_it = gr.size() - 1;
		}
		gr[from_it].push_back(edge(to_it));
	}

	bool *used = new bool[gr.size()];
	for (int i = 0; i < gr.size(); i++) 
		used[i] = false;
	bool valid = true;
	check(0, gr, used, valid);
	if (!valid) 
		return false;
	else
	{
		for (int i = 0; i < gr.size(); i++) 
			used[i] = false;
		vector<int> sorting;
		topologicalSort(gr, sorting, used);
		valid = true;
		for (int i = 0; i < gr.size(); i++)
		{
			if (!used[i])
				valid = false;
		}

		if (!valid) 
			return false;
		else
		{
			if (ans)
			{
				ans->resize(sorting.size());
				for (int i = 0; i < gr.size(); i++)
					(*ans)[i] = names[sorting[i]];
			}
			return true;
		}
	}

	delete[] used;
}

void asp::AscSeqChecker::check(int v, vector<vector<edge>>&g, bool *used, bool &b)
{
	used[v] = true;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i].to;
		if (used[to]) 
			b = false;
		else
			check(to, g, used, b);
	}
	used[v] = false;
}
void asp::AscSeqChecker::topologicalSort(vector<vector<edge>>& gr, vector<int>& ans, bool * used)
{
	for (int i = 0; i<gr.size(); ++i)
		used[i] = false;
	ans.clear();
	for (int i = 0; i<gr.size(); ++i)
		if (!used[i])
			dfs(i, gr, ans, used);
	reverse(ans.begin(), ans.end());
}
void asp::AscSeqChecker::dfs(int v, vector<vector<edge>>&g, vector<int>&ans, bool *used)
{
	used[v] = true;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i].to;
		if (!used[to])
			dfs(to, g, ans, used);
	}
	ans.push_back(v);
}

void asp::AscSeqChecker::demo()
{
	

	bool choise;
	cout << "1 - INPUT, 0 - TEST : ";
	cin >> choise;
	if (choise)
		input();
	else test();
}

void asp::AscSeqChecker::input()
{
	vector<string> input;
	int i = 0;
	string s;
	cout << "ENTER RELATIONS : " << endl;
	getline(cin, s);
	while (s != "")
	{
		input.push_back(s);
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, s);
		++i;
	}
	vector<string> ans;
	bool isAscSeq = run(input, &ans);
	cout << "ASCENDING SEQUENCE CAN" << (isAscSeq ? " " : " NOT") << " BE FORMED." << endl;
	for (int i = 0; i < ans.size() - 1; ++i)
		cout << ans[i] << " < ";
	cout << ans[ans.size() - 1] << endl;
}

void asp::AscSeqChecker::test()
{
	int sz = 4;
	vector<vector<string>> TEST = {
		{ "A>B", "A>D", "B>C", "D>C" },
		{ "B>D", "A>D", "A>B", "D>C", "B>C", "A>C" },
		{ "A>B", "A>C", "A>D", "A>E", "B<C", "C<D"},
		{"A>B", "C>A", "B>C"}
	};
	vector<bool> ANS = { true, true, true, false };
	int count = 0;

	for (int i = 0; i < sz; ++i)
		if (run(TEST[i]) != ANS[i])
		{
			if (!count)
				cout << "Tests crashed : ";
			cout << i << " " << endl;
			++count;
		}


	
	cout << "Num of tests crashed : " << count << endl;
}
