#include <bits/stdc++.h>

using namespace std;

#define INF (1<<30)

struct object {
  int i, x1, x2, y; // x2 == -INF indicates a point
  bool operator<(const object& rhs) const { return y < rhs.y; }
};

struct sensor {
  int x1, x2, y;
};

vector<int> die;
vector<object> drops;

void processBarrier(const object& obj) {
  int my = INF;

  for (const auto& d : drops)
    if (obj.x1 <= d.x1 && d.x1 <= obj.x2)
      my = min(my, d.y);

  if (my == INF) return;

  for (int i = 0; i < drops.size(); ++i)
    if (obj.x1 <= drops[i].x1 && drops[i].x1 <= obj.x2 && drops[i].y == my) {
      die[drops[i].i] = obj.y;
      swap(drops[i], drops.back());
      drops.pop_back();
      --i;
    }
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<object> obj(n+m);
  die.assign(n, 0);

  for (int i = 0; i < n; ++i) {
    cin >> obj[i].x1 >> obj[i].y;
    obj[i].i = i;
    obj[i].x2 = -INF;
  }
  for (int i = n; i < n+m; ++i) {
    cin >> obj[i].x1 >> obj[i].x2 >> obj[i].y;
  }

  sort(obj.begin(), obj.end());

  // finally do the sweep
  for (int i = obj.size()-1; i >= 0; --i) {
    if (obj[i].x2 == -INF) drops.push_back(obj[i]);
    else processBarrier(obj[i]);
  }

  for (int y : die) cout << y << endl;

  return 0;
}
