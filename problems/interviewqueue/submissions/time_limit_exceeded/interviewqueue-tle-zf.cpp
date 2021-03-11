#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> q(n);
  for (int& x : q) cin >> x;

  vector<vector<int>> vo;

  while (true) {
    vector<int> out, in;
    for (int i = 0; i < q.size(); ++i)
      if ((i > 0 && q[i] < q[i-1]) || (i+1 < q.size() && q[i] < q[i+1])) out.push_back(q[i]);
      else in.push_back(q[i]);
    if (out.size() == 0) {
      vo.push_back(in);
      break;
    }
    vo.push_back(out);
    q = in;
  }

  cout << vo.size()-1 << endl;
  for (auto& v : vo) {
    for (int x : v) cout << x << ' ';
    cout << endl;
  }

  return 0;
}
