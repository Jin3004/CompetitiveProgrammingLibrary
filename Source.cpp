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

//numの各桁を返す。 例: digit(702) == {7, 0, 2} 計算量O(log10(n))
auto digit(Int num) {
	vector<Int> res = { num % 10 };
	Int tmp = num / 10;
	while (tmp) {
		res.push_back(tmp % 10);
		tmp /= 10;
	}

	return res;
}


void calc() {

	/*
	Int N, M; cin >> N >> M;
	vector<Int> s(M), c(M);
	rep(i, M)cin >> s[i] >> c[i];

	for (Int num = 0; num <= 999; ++num) {
		rep(i, M) {

		}
	}*/

	auto res = digit(702);
	for (const auto elem : res) {
		cout << elem << endl;
	}


}


int main() {

	calc();

	return 0;
}