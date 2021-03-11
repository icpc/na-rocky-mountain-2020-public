#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

int main()
{
  int n, m;
  cin >> n >> m;
  
  vector<vector<int>> G(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    G[u-1].push_back(v-1);
    G[v-1].push_back(u-1);
  }

  vector<int> s(n);
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }

  int src = 0;
  //  cin >> src;
  //  src--;
  
  //  int ans = 0;
  int army = s[src];

  vector<bool> visited(n, false);
  priority_queue<pii, vector<pii>, greater<pii>> pq;

  visited[src] = true;
  for (auto v : G[src]) {
    pq.emplace(s[v], v);
    visited[v] = true;
  }

  while (!pq.empty()) {
    auto next = pq.top();
    pq.pop();
    if (army <= next.first) {
      break;
    }
    army += next.first;
    int u = next.second;
    for (auto v : G[u]) {
      if (!visited[v]) {
	pq.emplace(s[v], v);
	visited[v] = true;
      }
    }
    //    ans++;
  }
  
  //  cout << ans << endl;
  cout << army << endl;

  return 0;
}
