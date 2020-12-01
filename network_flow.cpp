#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h> 
#include<math.h> 
#include<string> 
#include<string.h> 
#include<iostream>
#include<vector> 
#include<set> 
#include<algorithm>
#include<time.h> 
#include<queue>  
#include<map> 
#include<stack>
#include<limits.h> 
#include<fstream>
using namespace std;

//fast types
#define vi vector<int>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef double dd;

/*primes in range 1 - n
1 - 100(1e2) -> 25 primes
1 - 1000(1e3) -> 168 primes
1 - 10000(1e4) -> 1229 primes
1 - 100000(1e5) -> 9592 primes
1 - 1000000(1e6) -> 78498 primes
1 - 10000000(1e7) -> 664579 primes
large primes ->
104729 1299709 15485863 179424673 2147483647 32416190071
*/

//defines
#define read(f)    freopen(f, "r", stdin)
#define write(f)   freopen(f, "w", stdout)
#define fast  std :: ios :: sync_with_stdio ( false ) 
#define mp make_pair 

//constants
#define pi 3.141592653589793238462643383279 
#define rad 57.2957795130823208767981548141
#define eps 1e-5
#define mod ((int)1e9+7)

struct edge {
	int otk, ku, cap, flow,obr;
	edge(int otk, int ku,int obr, int cap = 0, int flow = 0) :otk(otk), ku(ku),obr(obr), cap(cap), flow(flow) {}
};
vector<edge>E;
vector<int>G[150];
int s=1, t;
int d[150],ptr[150];
int bfs() {
	for (int i = 1; i <= t; i++) {
		d[i] = -1;
		ptr[i] = 0;
	}
	d[s] = 0;
	queue<int>que;
	que.push(1);
	int from;
	bool k = false;;
	while (!que.empty()) {
		from = que.front();
		que.pop();
		for (auto c : G[from]) {
			if (d[E[c].ku] == -1 && E[c].flow!=E[c].cap) {
				que.push(E[c].ku);
				d[E[c].ku] = d[from] + 1;
			}
		}
	}
	return d[t] != -1;
}

int dfs(int v, int f = 1000000000) {
	if (f <= 0)
		return 0;
	if (v == t)
		return f;
	for (;ptr[v]<G[v].size(); ptr[v]++) {
		int i = ptr[v];
		int ind = G[v][i], to = E[ind].ku;
		if (d[v] + 1 == d[to]) {
			int p = dfs(to, min(f, E[ind].cap - E[ind].flow));
			if (p == 0)continue;
			E[ind].flow += p;
			E[ind ^ 1].flow -= p;
			return p;
		}
	}
	return 0;
}
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
#else
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	int n,m,_1,_2,_3;
	cin >> n >> m;
	t = n;
	for (int i = 0; i < m; i++) {
		cin >> _1 >> _2 >> _3;
		E.push_back(edge(_1, _2, 0, _3));
		E.push_back(edge(_2, _1, 0));
		G[_1].push_back(i*4);
		G[_2].push_back(i * 4 + 1);
		E.push_back(edge(_2, _1, 1, _3));
		E.push_back(edge(_1, _2, 1));
		G[_2].push_back(i * 4 + 2);
		G[_1].push_back(i * 4 + 3);
	}
	int ans=0;
	while (bfs()) {
		while (1) {
			int d = dfs(s);
			if (d == 0)break;
			ans += d;
		}
	}
	cout << ans << endl;
	bool k;
	for (int i = 0; i < m; i++) {
		k = false;
		if (E[i * 4].flow > 0) {
			if (E[i * 4].obr)
				cout << "-";
			cout << E[i * 4].flow << endl;
			k = true;
		}
		if (E[i * 4 + 2].flow > 0) {
			if (E[i * 4 + 2].obr)
				cout << "-";
			cout << E[i * 4 + 2].flow << endl;
			k = true;
		}
		if (!k) {
			cout << 0 << endl;
		}
	}
	return 0;
}
