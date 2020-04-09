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
using Grid = vector<vector<T>>; // �񎟌��z��B[y][x]
template<typename T, typename U>
using Umap = unordered_map<T, U>;
template<typename T>
using Uset = unordered_set<T>;
template<typename T>
using P = pair<T, T>;

///a��b�̍ő���񐔂����߂�֐��B�v�Z�ʂ�O(log min(a, b))
Int Gcd(Int a, Int b) {
	if (a % b == 0)return b;
	else return Gcd(b, a % b);
}

//a��b�̍ŏ����{�������߂�֐��B�v�Z�ʂ�O(log min(a, b)) ���Gcd�ƃZ�b�g�ŃR�s�y���Ă�
Int Lcm(Int a, Int b) {
	return a * b / Gcd(a, b);
}

///�f��������������֐��B�v�Z�ʂ�O(��n)
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

///n�̖񐔂�񋓂���֐��B�v�Z�ʂ�O(��n)
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

//�x���@���烉�W�A���ɕϊ�����֐��B�v�Z�ʂ�O(1)
constexpr double toRadian(double angle) {
	constexpr double pi = 3.141592;
	return angle * pi / 180;
}

//���W�A������x���@�ɕϊ�����֐��B�v�Z�ʂ�O(1)
constexpr double toAngle(double rad) {
	constexpr double pi = 3.141592;
	return rad * 180 / pi;
}

//a, a + 1, a + 2, ... , b - 1, b�̑��a�����߂�֐�(a <= b)�B�v�Z�ʂ�O(1)
Int Sum(Int a, Int b) {
	if (b < a)return 0;
	if ((b - a + 1) % 2 == 0)return (a + b) * (b - a + 1) / 2;
	else return (a + b) * ((b - a + 1) / 2) + (a + b) / 2;
}

// n���ڂ̃t�B�{�i�b�`������v�Z����֐��B�v�Z�ʂ�O(n)
Int Fibonacci(Int n) {
	switch (n) {
	case 0: return 0;
	case 1: return 1;
	default: return Fibonacci(n - 1) + Fibonacci(n - 2);
	}
}

//n�̌�����Ԃ��֐��BO(1) n == 0�̂��Ƃ͑z�肳��Ă��Ȃ��Bn == 0�̂Ƃ��G���[�N���邩��
Int Digit(Int n) {
	Int res = 0;
	while (n) {
		n /= 10;
		res++;
	}
	return res;
}

//l����r�܂ł͈̔͂̒���func�𖞂����ő�̒l��Ԃ�
template<typename Func>//bool�^�̊֐�(Func�^�̃I�u�W�F�N�g)�������Ɏ��B
Int BinarySearch(Int l, Int r, Func func) {

	Int left = l, right = r + 1;//[left, right)
	while (right - left > 1) {
		Int mid = (left + right) / 2;
		if (func(mid))left = mid; else right = mid;
	}

	return left;

}

//[l, r]�̂����A�֐��I�u�W�F�N�gf�𖞂����ŏ��̒l��Ԃ��B
Int BinarySearch(Int l, Int r) {

	auto f = []() {return true; };//�����͓K�X�ς��Ă�������

	Int left = l - 1, right = r + 1;
	while (right - left > 1) {
		Int mid = left + (right - left) / 2;
		if (f())right = mid; else left = mid;
	}
	return right;
}

//a��b������؂��܂Ŋ���(���񕪐��ɂȂ�܂�)�B�v�Z�ʂ�O(��n + n)
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

	Int ans = 1;// ����ׂ���

	for (auto itr = res_a.begin(); itr != res_a.end(); ++itr) {
		auto tmp = res_b.find(itr->first);
		if (tmp != res_b.end()) {//����b�ɂ����l�̈�������������
			ans *= (pow(itr->first, min(res_b[itr->first], itr->second)));
		}
	}

	return make_pair(a / ans, b / ans);

}

//�f������B�v�Z�ʂ�O(��n)�B
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

	//�v�Z�ʂ�O(n)�B*n�͔z��̒���
	SegmentTree(Container arg, Function func)
		: f(func) {
		arr_size = arg.size();
		Int n = 1;
		tree_size = 1;

		while (n < arr_size) {//���S�񕪖؂ɂ��邽��2^n > len�ƂȂ�ŏ���2^n�����߂�
			n *= 2;
			tree_size += n;
			depth++;
		}
		leaf_size = n;
		data.resize(tree_size);//�؂̔z��̃T�C�Y��������

		for (Int i = 0; i < n; ++i) {//�t�̒l��������
			if (i <= arr_size - 1)data[n + i - 1] = arg[i];
			else data[n + i - 1] = invalid_value;
		}
		//goes well till here.

		Int tmp_size = leaf_size;
		for (Int i = 0; i < depth - 1; ++i) {
			for (Int j = 0; j < tmp_size / 2; ++j) {//�m�[�h��(j * 2, j * 2 + 1)
				data[(tmp_size + j * 2 - 2) / 2] = f(data[tmp_size + j * 2 - 1], data[tmp_size + j * 2]);
			}
			tmp_size /= 2;
		}

	}

	//k�Ԗڂ̔z��̒l��val�ɕς���B�v�Z�ʂ�O(log n)
	void update(Int k, Int val) {
		//�؂̃C���f�b�N�X�ɕς���
		k += leaf_size - 1;
		data[k] = val;
		//�ċA�I�ɍX�V����
		while (k > 0) {
			k = (k - 1) / 2;
			data[k] = f(data[k * 2 + 1], data[k * 2 + 2]);
		}
	}

	//[a, b)�̃N�G����Ԃ��B�g���Ƃ���query(a, b, 0, 0, n)�ŌĂяo���ĂˁB�v�Z�ʂ�O(log n)
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

//�����̐擪�̐���Ԃ��BO(log10(n))
Int head(Int n) {
	Int tmp = n;
	while (n > 0) {
		tmp = n;
		n /= 10;
	}
	return tmp;
}

//�����̖����̐���Ԃ��BO(1)
Int tail(Int n) {
	if (n < 10)return n;
	Int tmp = n;
	n /= 10;
	return tmp - n * 10;
}

//num�̊e����Ԃ��B ��: digit(702) == {7, 0, 2} �v�Z��O(log10(n))
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