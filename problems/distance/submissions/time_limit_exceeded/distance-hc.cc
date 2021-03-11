#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  int n;
  cin >> n;

  vector<int> s(n), a(n);
  for (int i = 0; i < n; i++) {
    cin >> s[i] >> a[i];
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      ans += abs(s[j]-s[i]) + abs(a[j]-a[i]);
    }
  }
  cout << ans << endl;
  
  return 0;
}
