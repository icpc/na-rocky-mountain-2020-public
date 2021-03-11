#include <bits/stdc++.h>

using namespace std;
const int MAX_N = 500000;
typedef vector<int> vi;

int main()
{
  int N;
  cin >> N;
  
  vector<int> left(N), right(N), v(N);
  vector<bool> present(N, true);
  
  for (int i = 0; i < N; i++) {
    cin >> v[i];
    left[i] = i-1;
    right[i] = i+1;
  }
  right[N-1] = -1;

  vi cand;
  cand.reserve(MAX_N);
  for (int i = 0; i < N; i++) {
    if ((i > 0 && v[i] < v[i-1]) ||
	(i < N-1 && v[i] < v[i+1])) {
      cand.push_back(i);
    }
  }

  vector<vi> remove;
  while (cand.size() > 0) {
    vi step;
    step.reserve(cand.size());
    for (auto i : cand) {
      step.push_back(v[i]);
      present[i] = false;
    }
    remove.push_back(step);

    vi cand2;
    cand2.reserve(MAX_N);
    for (auto i : cand) {
      int l = left[i];
      if (l >= 0 && !present[l]) continue;
      int r = right[i];
      while (r >= 0 && !present[r]) {
	r = right[r];
      }

      if (l >= 0) {
	right[l] = r;
      }
      if (r >= 0) {
	left[r] = l;
      }
      if (l >= 0 && r >= 0) {
	if (v[l] < v[r]) cand2.push_back(l);
	else if (v[l] > v[r]) cand2.push_back(r);
      }
    }
    sort(begin(cand2), end(cand2));
    cand2.resize(unique(begin(cand2), end(cand2)) - begin(cand2));
    cand.swap(cand2);
  }

  cout << remove.size() << endl;
  for (auto v : remove) {
    for (auto x : v) {
      cout << x << ' ';
    }
    cout << endl;
  }

  for (int i = 0; i < N; i++) {
    if (present[i]) {
      cout << v[i] << ' ';
    }
  }
  cout << endl;
  
  return 0;
}
