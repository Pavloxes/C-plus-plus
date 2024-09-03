#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>

using namespace std;

vector<int> p_function(string s)
{
	int n = (int)s.length();
	vector<int>p(n, 0);
	for (int i = 1; i < n; ++i)
	{
		int j = p[i - 1];
		while (j > 0 && s[i] != s[j])
		{
			j = p[j - 1];
		}
		if (s[i] == s[j]) ++j;
		p[i] = j;
	}
	return p;
}

vector<int> z_function(string s)
{
	int n = (int)s.length();
	vector<int> z(n);
	z[0] = n;
	for (int i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	return z;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	string s;
	cin >> s;
	
	vector<int>p = p_function(s), z = z_function(s);

	for (int i = 0; i < (int)s.size(); i++)
	{
		cout << p[i] << ' ';
	}

	cout << '\n';

	for (int i = 0; i < (int)s.size(); i++)
	{
		cout << z[i] << ' ';
	}

	return 0;
}
