#pragma once
#include <iostream>
#include <vector>
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
#define rep(i, n) for(Int (i) = 0; (i) < (n); (i)++)
#define debug(var) cout << #var << ": " << var << endl
using namespace std;
using Int = int64_t;
using Uint = uint64_t;
constexpr Uint mod = 1e9 + 7;
constexpr Int INF = INT_MAX;
using Container = vector<Int>;
template<typename T>
using Grid = vector<vector<T>>; // 二次元配列。[y][x]
template<typename T, typename U>
using Umap = unordered_map<T, U>;
template<typename T>
using Uset = unordered_set<T>;
template<typename T>
using P = pair<T, T>;

///aとbの最大公約数を求める関数。計算量はO(log min(a, b))
Int Gcd(Int a, Int b) {
	if (a % b == 0)return b;
	else return Gcd(b, a % b);
}

//aとbの最小公倍数を求める関数。計算量はO(log min(a, b)) 上のGcdとセットでコピペしてね
Int Lcm(Int a, Int b) {
	return a * b / Gcd(a, b);
}

///素因数分解をする関数。計算量はO(√n)
unordered_map<Int, Int> Factorize(Int n) {

	unordered_map<Int, Int> res;
	for (Int i = 2; i * i <= n; ++i) {
		if (n % i != 0)continue;
		res[i] = 0;
		while (n % i == 0) {
			n /= i;
			res[i]++;
		}
	}
	if (n != 1)res[n] = 1;
	return res;

}

///nの約数を列挙する関数。計算量はO(√n)
vector<Int> Divisor(Int n) {
	vector<Int> res;
	for (Int i = 0; i * i <= n; ++i) {
		if (n % i == 0) {
			res.push_back(i);
			if (i * i != n)res.push_back(n / i);
		}
	}
	sort(begin(res), end(res));
	return res;
}

//度数法からラジアンに変換する関数。計算量はO(1)
constexpr double toRadian(double angle) {
	constexpr double pi = 3.141592;
	return angle * pi / 180;
}

//ラジアンから度数法に変換する関数。計算量はO(1)
constexpr double toAngle(double rad) {
	constexpr double pi = 3.141592;
	return rad * 180 / pi;
}

//a, a + 1, a + 2, ... , b - 1, bの総和を求める関数(a <= b)。計算量はO(1)
Int Sum(Int a, Int b) {
	if (b < a)return 0;
	if ((b - a + 1) % 2 == 0)return (a + b) * (b - a + 1) / 2;
	else return (a + b) * ((b - a + 1) / 2) + (a + b) / 2;
}

// n項目のフィボナッチ数列を計算する関数。計算量はO(n)
Int Fibonacci(Int n) {
	switch (n) {
	case 0: return 0;
	case 1: return 1;
	default: return Fibonacci(n - 1) + Fibonacci(n - 2);
	}
}

//nの桁数を返す関数。O(1) n == 0のことは想定されていない。n == 0のときエラー起きるかも
Int Digit(Int n) {
	Int res = 0;
	while (n) {
		n /= 10;
		res++;
	}
	return res;
}

//lからrまでの範囲の中でfuncを満たす最大の値を返す
template<typename Func>//bool型の関数(Func型のオブジェクト)を引数に取る。
Int BinarySearch(Int l, Int r, Func func) {

	Int left = l, right = r + 1;//[left, right)
	while (right - left > 1) {
		Int mid = (left + right) / 2;
		if (func(mid))left = mid; else right = mid;
	}

	return left;

}

//[l, r]のうち、関数オブジェクトfを満たす最小の値を返す。
Int BinarySearch(Int l, Int r) {

	auto f = []() {return true; };//ここは適宜変えてください

	Int left = l - 1, right = r + 1;
	while (right - left > 1) {
		Int mid = left + (right - left) / 2;
		if (f())right = mid; else left = mid;
	}
	return right;
}

//aとbが割り切れるまで割る(既約分数になるまで)。計算量はO(√n + n)
std::pair<Int, Int> Reduce(Int a, Int b) {

	const auto f = [](Int n) -> unordered_map<Int, Int> {
		unordered_map<Int, Int> res;
		for (Int i = 2; i * i <= n; ++i) {
			if (n % i != 0)continue;
			res[i] = 0;
			while (n % i == 0) {
				n /= i;
				res[i]++;
			}
		}
		if (n != 1)res[n] = 1;
		return res;
	};

	auto res_a = f(a), res_b = f(b);

	Int ans = 1;// 割るべき数

	for (auto itr = res_a.begin(); itr != res_a.end(); ++itr) {
		auto tmp = res_b.find(itr->first);
		if (tmp != res_b.end()) {//もしbにも同様の因数があったら
			ans *= (pow(itr->first, min(res_b[itr->first], itr->second)));
		}
	}

	return make_pair(a / ans, b / ans);

}

//素数判定。計算量はO(√n)。
bool IsPrime(Int n) {

	if (n < 2)return false;
	else if (n == 2)return true;
	else if (n % 2 == 0)return false;

	for (Int i = 3; i * i <= n; ++i) {
		if (n % i == 0)return false;
	}

	return true;

}

struct Point {
	Int x, y;
	Point(Int x, Int y) :x(x), y(y) {}

	Point operator+(Point arg) {
		return Point(x + arg.x, y + arg.y);
	}

	Point operator+(Point arg) {
		return Point(x - arg.x, y - arg.y);
	}
};

bool inrange(Int l, Int r, Int val) {
	return l <= val && val <= r;
}

//This sample is RMQ. Change a little difference by yourself.
template<typename Function>
class SegmentTree {
public:
	Int invalid_value = Int_max;
	Int depth = 1;
	Int leaf_size, tree_size, arr_size;
	Function f;
	Container data;

	//計算量はO(n)。*nは配列の長さ
	SegmentTree(Container arg, Function func)
		: f(func) {
		arr_size = arg.size();
		Int n = 1;
		tree_size = 1;

		while (n < arr_size) {//完全二分木にするため2^n > lenとなる最小の2^nを求める
			n *= 2;
			tree_size += n;
			depth++;
		}
		leaf_size = n;
		data.resize(tree_size);//木の配列のサイズを初期化

		for (Int i = 0; i < n; ++i) {//葉の値を初期化
			if (i <= arr_size - 1)data[n + i - 1] = arg[i];
			else data[n + i - 1] = invalid_value;
		}
		//goes well till here.

		Int tmp_size = leaf_size;
		for (Int i = 0; i < depth - 1; ++i) {
			for (Int j = 0; j < tmp_size / 2; ++j) {//ノードは(j * 2, j * 2 + 1)
				data[(tmp_size + j * 2 - 2) / 2] = f(data[tmp_size + j * 2 - 1], data[tmp_size + j * 2]);
			}
			tmp_size /= 2;
		}

	}

	//k番目の配列の値をvalに変える。計算量はO(log n)
	void update(Int k, Int val) {
		//木のインデックスに変える
		k += leaf_size - 1;
		data[k] = val;
		//再帰的に更新する
		while (k > 0) {
			k = (k - 1) / 2;
			data[k] = f(data[k * 2 + 1], data[k * 2 + 2]);
		}
	}

	//[a, b)のクエリを返す。使うときはquery(a, b, 0, 0, n)で呼び出してね。計算量はO(log n)
	Int query(Int a, Int b, Int k = 0, Int l = 0, Int r = -1) {
		if (r < 0)r = leaf_size;
		if (r <= a || b <= l)return invalid_value;
		if (a <= l && r <= b)return data[k];
		Int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
		Int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
		return f(vl, vr);
	}
};

template<typename Function>
SegmentTree<Function> make_SegmentTree(Container arg, Function func) {
	SegmentTree<Function> seg(arg, func);
	return seg;
}

//数字の先頭の数を返す。O(log10(n))
Int head(Int n) {
	Int tmp = n;
	while (n > 0) {
		tmp = n;
		n /= 10;
	}
	return tmp;
}

//数字の末尾の数を返す。O(1)
Int tail(Int n) {
	if (n < 10)return n;
	Int tmp = n;
	n /= 10;
	return tmp - n * 10;
}

//numの各桁を返す。 例: digit(702) == {7, 0, 2} 計算量O(log10(n))
auto digit(Int num) {
	vector<Int> res = { num % 10 };
	Int tmp = num / 10;
	while (tmp) {
		res.push_back(tmp % 10);
		tmp /= 10;
	}
	reverse(res.begin(), res.end());

	return res;
}

struct mint {
	Int x;
	mint(Int x = 0) :x((x% mod + mod) % mod) {}
	mint operator-() const { return mint(-x); }
	mint& operator+=(const mint a) {
		if ((x += a.x) >= mod) x -= mod;
		return *this;
	}
	mint& operator-=(const mint a) {
		if ((x += mod - a.x) >= mod) x -= mod;
		return *this;
	}
	mint& operator*=(const mint a) {
		(x *= a.x) %= mod;
		return *this;
	}
	mint operator+(const mint a) const {
		mint res(*this);
		return res += a;
	}
	mint operator-(const mint a) const {
		mint res(*this);
		return res -= a;
	}
	mint operator*(const mint a) const {
		mint res(*this);
		return res *= a;
	}
	mint operator%(const mint a)const {
		mint res(*this);
		res -= (res / a) * a;
		return res;
	}
	mint pow(Int t) const {
		if (t == 0) return 1;
		mint a = pow(t >> 1);
		a *= a;
		if (t & 1) a *= *this;
		return a;
	}

	// for prime mod
	mint inv() const {
		return pow(mod - 2);
	}
	mint& operator/=(const mint a) {
		return (*this) *= a.inv();
	}
	mint operator/(const mint a) const {
		mint res(*this);
		return res /= a;
	}

	friend ostream& operator<<(ostream& os, const mint& p) {
		return os << p.x;
	}
	friend istream& operator>>(istream& is, mint& p) {
		Int tmp;
		is >> tmp;
		p = tmp;
		return is;
	}

};

template<typename T>
void debug_table(Grid<T>& cont) {
	cout << "   ";
	rep(i, cont[0].size()) {
		cout << i << " ";
	}
	cout << endl;
	rep(i, cont.size()) {
		cout << i << ": ";
		rep(j, cont[i].size()) {
			cout << cont[i][j] << " ";
		}
		cout << endl;
	}
}

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