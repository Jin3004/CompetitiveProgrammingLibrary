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
	SegmentTree(Container arg, Function func) {

		f = func;
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

	//k�Ԗڂ̔z��̒l��val�ɕς���B
	void update(Int k, Int val) {
		//�؂̃C���f�b�N�X�ɕς���
		k += leaf_size - 1;
		data[k] = val;
		//�ċA�I�ɍX�V����
		while (k > 0) {
			k = (k - 1) / 2;
			data[k] = f(data[k * 2 + 1], data[k * 2 + 2]);
		}
		rep(i, tree_size) {
			debug(data[i]);
		}
	}

};