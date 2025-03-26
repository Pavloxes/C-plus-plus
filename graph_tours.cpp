#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<long long>dist;

void dijkstra(int s)
{
    dist[s] = 0;

    static set<pair<int, int>> st;
    st.insert({ 0, s });


    while (!st.empty())
    {
        pair<int, int> cur_edge = *st.begin();
        long long cur_weight = cur_edge.first, v = cur_edge.second;
        st.erase(cur_edge);

        if (cur_weight > dist[v]) continue;

        for (auto& e : graph[v])
        {
            int u = e.first, w = e.second;
            if (dist[v] + w < dist[u]) 
            {
                dist[u] = dist[v] + w;
                st.insert({ dist[u], u });
            }
        }
    }
}
 
void bfs(int s)
{
    dist[s] = 0;
    queue<int> q;
    q.push(s);
 
    while (!q.empty()) 
    {
        int v = q.front();
        q.pop();
        for (auto& e : graph[v])
        {
            int u = e.first, w = e.second;
            if (dist[v] + w < dist[u]) 
            {
                dist[u] = dist[v] + w;
                q.push(u);
            }
        }
    }
}

void dfs(int v)
{
    tin[v] = t++;
    used[v] = 1;
    for (int u : graph[v])
    {
        if (!used[u])
        {
            dfs(u);
        }
    }
    tout[v] = t++;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    return 0;
}
