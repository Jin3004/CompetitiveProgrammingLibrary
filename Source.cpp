/*
このコード、と～おれ!
Be accepted!
∧＿∧　
（｡･ω･｡)つ━☆・*。
⊂　　 ノ 　　　・゜+.
　しーＪ　　　°。+ *´¨)
 　　　　　　　　　.· ´¸.·*´¨) ¸.·*¨)
			　　　　　　　　　　(¸.·´ (¸.·'* ☆
					*/

#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <climits>
#include <tuple>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <memory>
#include <iomanip>

#define rep(i, n) for(Int (i) = 0; (i) < (n); ++(i))
#define debug(var) cout << #var << ": " << var << endl
using namespace std;
using Int = int64_t;
using Uint = uint64_t;
constexpr Uint mod = 1e9 + 7;
constexpr Int INF = INT_MAX;
template<typename T>
using Grid = vector<vector<T>>; // 二次元配列。[y][x]
template<typename T, typename U>
using Umap = unordered_map<T, U>;
template<typename T>
using Uset = unordered_set<T>;
template<typename T>
using P = pair<T, T>;
using Graph = vector<vector<bool>>;

class UnionFind {
public:
	vector<Int> d;
	UnionFind(Int n) : d(n, -1) {}

	Int root(Int x) {
		if (d[x] < 0)return x;
		return d[x] = root(d[x]);
	}

	bool unite(Int x, Int y) {
		x = root(x); y = root(y);
		if (x == y)return false;
		if (d[x] > d[y])swap(x, y);
		d[x] += d[y];
		d[y] = x;
		return true;
	}

	bool same(Int x, Int y) { return root(x) == root(y); }
	Int size(Int x) { return -d[root(x)]; }

};

void calc() {

	Int N, M, K; cin >> N >> M >> K;
	UnionFind uf(N);
	rep(i, M) {
		Int a, b; cin >> a >> b; a--; b--;
		uf.unite(a, b);
	}

}


int main() {

	calc();

	return 0;
}