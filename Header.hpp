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

using Int = int32_t;
using namespace std;

///a��b�̍ő���񐔂����߂�֐��B�v�Z�ʂ�O(log min(a, b))
Int Gcd(Int a, Int b) {
	if (b == 0)return a;
	else return Gcd(a, a % b);
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