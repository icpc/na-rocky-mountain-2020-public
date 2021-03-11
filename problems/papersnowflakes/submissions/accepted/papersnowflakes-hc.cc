#include <bits/stdc++.h>

using namespace std;

// Cheap hack to convert everything to 64-bit integers
#define int int64_t

// entries are (x, layer), where layer = +1/+2 if we increase layers by 1 or 2,
// -1/-2 if we decrease layers by 1 or 2, and 0 at a cut point
typedef pair<int,int> pii;
const int64_t MAX_L = 1e18;

#undef int
int main()
#define int int64_t
{
  int N, M, L;
  cin >> N >> M >> L;

  vector<pii> events;
  events.reserve(N+M+2);
  events.emplace_back(0, 1);

  int loose = L;
  
  for (int i = 0; i < N; i++) {
    int f;
    cin >> f;

    if (i % 2 == 0) {
      // fold left
      int x = loose - f;
      events.emplace_back(x, -2);
      loose = x - f;
    } else {
      // fold right
      int x = loose + f;
      events.emplace_back(x, 2);
      loose = x + f;
    }
  }

  events.emplace_back(loose, (N % 2 == 0) ? -1 : 1);

  vector<int> cut(M);
  for (int i = 0; i < M; i++) {
    cin >> cut[i];
    events.emplace_back(cut[i], 0);
  }
  sort(begin(events), end(events));

  int layers = 0;
  int ans = 0;
  int prev_x = -2*MAX_L;
  for (auto [x, l] : events) {
    ans += layers * (x - prev_x);
    if (l == 0) {
      cout << ans << ' ';
      ans = 0;
    }
    layers += l;
    prev_x = x;
  }

  cout << ans << endl;

  return 0;
}
