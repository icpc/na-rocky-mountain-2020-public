#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll dist(const vector<int> &s)
{
  ll ans = 0;
  ll S = 0;   // S = sum(s[i]-s[j], j=0..i-1)
  for (int i = 1; i < (int)s.size(); i++) {
    S += i*(s[i]-s[i-1]);
    ans += S;
  }
  return ans;
}

int main()
{
  int n;
  cin >> n;

  vector<int> s(n), a(n);
  for (int i = 0; i < n; i++) {
    cin >> s[i] >> a[i];
  }
  sort(begin(s), end(s));
  sort(begin(a), end(a));

  cout << dist(s) + dist(a) << endl;
  
  return 0;
}
