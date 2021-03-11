// Does not use a priority queue, just an unordered set
// and scans for the minimum each time.

#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

int main() {
  int n, m;
  cin >> n >> m;

  vector<vi> g(n);
  while (m--) {
    int u, v;
    cin >> u >> v;
    g[--u].push_back(--v);
    g[v].push_back(u);
  }

  vi army(n);
  for (int& x : army) cin >> x;

  unordered_set<int> open;
  vector<bool> seen(n, false);

  int tot = 0;
  open.insert(0);
  seen[0] = true;

  while (open.size()) {
    int mu = *open.begin();
    for (int x : open) if (army[x] < army[mu]) mu = x;
    open.erase(mu);

    if (mu != 0 && army[mu] >= tot) break;
    tot += army[mu];
    for (int w : g[mu])
      if (!seen[w]) {
        seen[w] = true;
        open.insert(w);
      }
  }

  cout << tot << endl;

  return 0;
}
