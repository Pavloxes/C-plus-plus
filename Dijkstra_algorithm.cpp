#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

vector<int>st;
vector<bool>used(502);
map<string, vector<string>>gr;
int fl = 0;
string ans = "NO";
void dfs(string v, string to, map<string, int>used)
{
	used[v] = 1;
	for (auto child : gr[v]) {
		if (v == to)
		{
			ans = "YES";
		}
		if (!used[child])
		{
			dfs(child, to, used);
		}
	}
}

int main()
{
	cin.tie(0); cout.tie(0);
	ios_base::sync_with_stdio(false);

	int n, a, b;
	string s, s1, s2;
	cin >> n >> a >> b;

	for (int i = 0; i < n; i++)
	{
		cin >> s;
	}
	for (int i = 0; i < a; i++)
	{
		cin >> s1 >> s2;
		gr[s1].push_back(s2);
		gr[s2].push_back(s1);
	}

	for (int i = 0; i < b; i++)
	{
		ans = "NO";
		map<string, int>used;
		cin >> s1 >> s2;
		dfs(s1, s2, used);
		cout << ans << '\n';
	}


}
