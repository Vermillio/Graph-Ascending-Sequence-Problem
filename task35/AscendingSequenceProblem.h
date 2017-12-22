#pragma once

#include <map>
#include <vector>

using namespace std;

namespace asp
{
	struct edge
	{
		int to;
		int weight;
		edge(int _to) : to(_to), weight(1) {};
	};

	class AscSeqChecker
	{
	//	vector<int> order; // init -1

		void dfs(int v, vector<vector<edge>>&g, vector<int>&ans, bool *used);
		void check(int v, vector<vector<edge>>&g, bool *used, bool &b);
		void topologicalSort(vector<vector<edge>> &gr, vector<int> &ans, bool *used);

	public:
		bool run(const vector<string> &relations, vector<string> *ans = nullptr); // string examples: "A>B", "B<C", etc
		void demo();
		void input();
		void test();
	};
}