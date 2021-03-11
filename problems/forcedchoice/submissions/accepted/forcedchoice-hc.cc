#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200;

int main()
{
  int n, p, s;
  cin >> n >> p >> s;

  for (int i = 0; i < s; i++) {
    int m, c;
    cin >> m;

    bool keep = false;
    for (int j = 0; j < m; j++) {
      cin >> c;
      keep |= c == p;
    }
    cout << (keep ? "KEEP" : "REMOVE") << endl;
  }

  return 0;
}
