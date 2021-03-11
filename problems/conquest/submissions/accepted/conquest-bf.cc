#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

vector<ll> A;
vector<vector<int>> V;
vector<bool> seen;

struct CustomCompare{
  bool operator()(const int &i, const int &j){
    if(A[i] == A[j])
      return i < j;
    return A[i] > A[j];
  }
};

int main(){
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;
  V.resize(n);
  A.resize(n);
  seen.resize(n, false);
  
  for(int i = 0; i < m; i++){
    int u,v; cin >> u >> v;
    V[u-1].push_back(v-1);
    V[v-1].push_back(u-1);
  }
  for(auto &x:A)
    cin >> x;
  ll s = 0,c;
  c = A[s];
  priority_queue<int, vector<int>, CustomCompare> PQ;
  seen[s] = true;
  for(auto x:V[s]){
    PQ.push(x);
    seen[x] = true;
  }
  while(!PQ.empty() and A[PQ.top()] < c){
    int top = PQ.top(); PQ.pop();
    c += A[top];
    for(auto x:V[top]){
      if(!seen[x]){
	seen[x] = true;
	PQ.push(x);
      }
    }
  }
  int cnt = 0;
  for(auto x:seen)
    cnt += x;
  //  cout << cnt - PQ.size() - 1 << endl << c << endl;
  cout << c << endl;
  
  
  return 0;
}
