#include <bits/stdc++.h>

using namespace std;


// RMQ:
//   call constructRMQ to get data structure M                   O(n)
//   call getmax to get the maximum from [a..b] inclusive        O(log n)
//     returns a pair of the form (maximum value,index of maximum value)
//   call update to change a value in the array                  O(log n)
typedef int Type;             // Change this as needed
const Type oo = INT_MIN;      // Change to INT_MAX for min.
const int MAX_N = 100000*3;
typedef pair<Type,int> pti;
const pti p_oo = make_pair(oo,-1);

int sizeM;
Type A[MAX_N];
pti M[4*MAX_N];

void constructRMQ(Type A[MAX_N], pti M[4*MAX_N], int n) {
  sizeM = 1; while(sizeM < n) sizeM <<= 1;
  for (int i=0; i < sizeM; i++) M[sizeM-1+i] = (i < n ? make_pair(A[i],i) : p_oo);
  for (int i=sizeM-2; i>=0; i--) M[i] = max(M[2*i+1],M[2*i+2]);
}

pti getmax(pti M[4*MAX_N], int a, int b, int st=0,int en=sizeM,int ind=0) {
  if (a > b || a >= en || b < st)         return p_oo;
  if ((a <= st && en <= b) || st+1 >= en) return M[ind];
  int mid = (st+en)/2;
  return max(getmax(M,a,b,st,mid,2*ind+1), getmax(M,a,b,mid,en,2*ind+2));
}

void update(Type A[MAX_N], pti M[4*MAX_N], int i, Type val){
  A[i] = val; M[i += sizeM-1] = make_pair(val,i);
  while((i = (i-1)/2)) M[i] = max(M[2*i+1],M[2*i+2]);
}

set<int> xcoord;
map<int,int> xmap;

vector<int> ans;
vector<stack<pair<int,int>>> drops;

struct Event
{
  int y;

  // this is antigravity too!!!  makes it easier to work with my library
  // code
  Event(int yy) : y{-yy} {}
  virtual void precompress() const = 0;
  virtual void compress() = 0;
  virtual void process() = 0;
  virtual void print() const = 0;

  bool operator<(const Event &e) const
  {
    return y < e.y;
  }
};


struct Drop : Event
{
  int x;
  int index;

  Drop(int xx, int yy, int i) : Event{yy}, x{xx}, index{i} {}

  void precompress() const
  {
    xcoord.insert(x);
  }

  void compress()
  {
    x = xmap[x];
  }

  void process()
  {
    drops[x].emplace(y, index);
    update(A, M, x, y);
  }

  void print() const
  {
    cout << "Drop " << index << " (" << x << ", " << y << ")" << endl;
  }
};

struct Sensor : Event
{
  int x1, x2;

  Sensor(int xx1, int xx2, int yy) : Event{yy}, x1{xx1}, x2{xx2} {}

  void precompress() const
  {
    xcoord.insert(x1);
    xcoord.insert(x2);
  }

  void compress()
  {
    x1 = xmap[x1];
    x2 = xmap[x2];
  }

  void process_drop(int x, int y)
  {
    assert(!drops[x].empty());
    auto d = drops[x].top();
    ans[d.second] = -y;
    drops[x].pop();
    if (!drops[x].empty()) {
      d = drops[x].top();
      update(A, M, x, d.first);
    } else {
      update(A, M, x, oo);
    }
  }

  void process()
  {
    auto ans = getmax(M, x1, x2);
    int yy = ans.first, xx = ans.second;
    if (yy == INT_MIN) return;     // no rain drop

    process_drop(xx, y);

    // get rid of all drops hitting at the same time
    while (true) {
      ans = getmax(M, x1, x2);
      if (ans.first != yy) break;
      xx = ans.second;
      assert(xx >= 0);
      process_drop(xx, y);
    }
  }

  void print() const
  {
    cout << "Sensor " << " (" << x1 << ", " << x2 << ", " << y << ")" << endl;
  }
};

vector<Event *> event;
int D, S;

void read_input()
{
  cin >> D >> S;

  ans.resize(D, 0);

  for (int i = 0; i < D; i++) {
    int x, y;
    cin >> x >> y;
    event.push_back(new Drop(x, y, i));
  }
  for (int i = 0; i < S; i++) {
    int x1, x2, y;
    cin >> x1 >> x2 >> y;
    event.push_back(new Sensor(x1, x2, y));
  }

  for (auto p : event) {
    p->precompress();
  }
  int v = 0;
  for (auto x : xcoord) {
    xmap[x] = v++;
  }
  for (auto p : event) {
    p->compress();
  }
  drops.resize(v);
}

bool cmp(const Event *e1, const Event *e2)
{
  return *e1 < *e2;
}

int main()
{
  read_input();

  fill(A, A+drops.size(), oo);
  constructRMQ(A, M, drops.size());

  sort(begin(event), end(event), cmp);
  /*
  for (auto p : event) {
    p->print();
  }
  */
  for (auto p : event) {
    p->process();
  }

  for (int i = 0; i < D; i++) {
    cout << ans[i] << endl;
  }


  return 0;
}
