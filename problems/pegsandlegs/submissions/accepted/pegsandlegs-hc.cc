#include <bits/stdc++.h>

using namespace std;

struct Value
{
  double val, pstuck;
};

const int MAX_LP = 100000;
Value ans[MAX_LP*2];

bool drop[MAX_LP*2];

int main()
{
  int L, P;
  cin >> L >> P;
  fill(drop, drop+L+P, true);

  for (int i = 0; i < L; i++) {
    cin >> ans[i].val;
    ans[i].pstuck = 0.0;
  }
  
  for (int i = L; i < L+P; i++) {
    double pl, pr;
    int left, right;
    cin >> pl >> pr >> left >> right;
    left--; right--;
    ans[i].val = pl * ans[left].val + pr * ans[right].val;
    ans[i].pstuck = pl * ans[left].pstuck + pr * ans[right].pstuck +
      (1-pl-pr);
    drop[left] = drop[right] = false;
  }

  double V = 0.0;
  for (int i = 0; i < L+P; i++) {
    if (drop[i]) {
      // you can assume that you always drop from the same spot, because
      // it is true for the optimal one
      double val = ans[i].val / (1 - ans[i].pstuck);
      V = max(val, V);
    }
  }

  cout << fixed << setprecision(10) << V << endl;
  
  return 0;
}
