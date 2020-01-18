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

using Int = int32_t;
using namespace std;

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