#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  bool run = false;
  int prev = 0;
  int total = 0;

  for (int i = 0; i < N; i++) {
    int t;
    cin >> t;
    if (run) {
      total += t - prev;
    }
    run = !run;
    prev = t;
  }

  if (run) {
    cout << "still running" << endl;
  } else {
    cout << total << endl;
  }
  
  return 0;
}
