#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <sstream>
using namespace std;
unsigned long long square_and_multiply(unsigned long long a, unsigned long long b, unsigned long long n)
{
	long h;
	unsigned long long c = a;
	int bin[32];
	int i = 0;

	/* Converts b in Binary */
	while (b > 0) {

		if (b % 2 == 0) {
			bin[i] = 0;
		}
		else {
			bin[i] = 1;
		}

		b /= 2;
		i++;

	}

	i--;

	while (i > 0) {

		c = (c * c) % n;

		if (bin[--i] == 1) {
			c = (c * a) % n;
		}

	}

	return c;
}
bool isrp(int a, int b)
{
	if (a == 1 || b == 1)    
		return true;
	while (1)
	{         
		int t = a%b;
		if (t == 0)
		{
			break;
		}
		else
		{
			a = b;
			b = t;
		}
	}
	if (b>1)	return false;
	else return true;
}
vector<string> split(string str) {
	istringstream in(str);
	string tmp_str;
	vector<string> vec;

	while (getline(in, tmp_str, ' ')) {
		vec.push_back(tmp_str);
	}
	return vec;
}
int main()
{
	cout << "初始化請輸入init,加密請輸入e {plaintext} {n} {e},解密請輸入d {ciphertext} {n} {d}:" << endl;
	int prime[21] = { 11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97 };
	string input;
	while (getline(cin,input))
	{
		int p, q, n, fn, e, d;
		vector<int> coprime;
		vector<string> v;
		int pos = input.find_first_of(" ");
		if (input.substr(0, pos) == "init")
		{
			srand(time(NULL));
			p = prime[(rand() % 21)];
			do {
				q = prime[(rand() % 21)];
			} while (q == p);
			n = p*q;
			fn = (p - 1)*(q - 1);
			for (int i = 1; i < fn; i++)
			{
				if (isrp(i, fn))
					coprime.push_back(i);
			}
			e = coprime[rand() % coprime.size()];
			int x = 1;
			while (1)
			{
				int fnt = fn*x+1;
				if (fnt%e == 0)
				{
					d = fnt / e;
					break;
				}
				x += 1;
			}
			cout << (e*d) % fn <<endl;
			cout << "p = " << p << "\n" << "q = " << q << "\n" << "n = " << n << "\n" << "e = " << e << "\n" << "d = " << d << "\n";
			coprime.clear();
		}
		else if (input.substr(0, pos) == "e")
		{
			v = split(input);
			int text = 0;
			int j = input.size() - 2 - v[v.size() - 1].size() - v[v.size() - 2].size();
			for (int i = 2; i < j; i++)
			{
				cout << square_and_multiply(((unsigned long long)input[i] - 33), (unsigned long long)stoi(v[v.size() - 1]), (unsigned long long)stoi(v[v.size() - 2]));

				if (i != j - 1) cout << " ";
			}
			cout << endl;
			v.clear();
		}
		else if (input.substr(0, pos) == "d")
		{
			v = split(input);
			int text = 0;
			for (int i = 1; i < v.size()-2; i++)
			{

				cout << (char)(square_and_multiply((unsigned long long)stoi(v[i]), (unsigned long long)stoi(v[v.size() - 1]), (unsigned long long)stoi(v[v.size() - 2]))+33);
			}
			cout << endl;
			v.clear();
		}
	}
}