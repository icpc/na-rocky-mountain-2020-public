#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
const ll INF = (1ll<<62);

int main() {
  ll n, m, l;
  cin >> n >> m >> l;

  vector<pll> folds;
  folds.push_back({0, +1});
  for (ll i = 0, f; i < n; ++i) {
    cin >> f;
    ll loc = l+((i&1)?f:-f);
    folds.push_back({loc, (i&1)?+2:-2});
    l = 2*loc-l;
  }
  folds.push_back({l, (n&1)?+1:-1});
  sort(folds.begin(), folds.end());

  ll pre = 0;
  for (ll i = 0, c; i <= m; ++i) {
    if (i < m) cin >> c;
    else c = INF;

    ll cur = 0;
    for (const auto& f : folds) {
      if (f.first < c) cur += (c-f.first)*f.second;
      else break;
    }
    cout << cur-pre << (i==m?'\n':' ');
    pre = cur;
  }

  return 0;
}
