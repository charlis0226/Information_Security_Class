#include<iostream>
#include<math.h>
#include<string>

using namespace std;

//計算最大公因數
int gcd(int, int);

int main(int argc, char* argv[])
{
	double p, q, n, temp, phn, e, d;
	string message, messageEncrypt, messageDecrypt;

	//讀取p q 和 明文
	p = stoi(argv[1]);
	q = stoi(argv[2]);
	n = p * q;
	phn = (p - 1) * (q - 1);
	e = 2;
	message = argv[3];
	messageEncrypt = "";
	messageDecrypt = "";

	//計算e值
	while (e < phn)
	{
		double temp = gcd(e, phn);
		if (temp == 1)break;
		else e++;
	}

	//key
	d = fmod(1 / e, phn);

	//確認是否會溢位
	int temp1 = (int)p % 10;
	int temp2 = (int)q % 10;
	int carry = 0;
	if (temp1 * temp2 < 10)carry = 1;


	//逐字加解密
	for (int i = 0; i < message.length(); i++)
	{
		double temp = message[i];
		double encryptChr = pow(temp, e);
		double decryptChr = pow(encryptChr, d);

		//用key加密
		encryptChr = fmod(encryptChr, n);

		//用key解密
		decryptChr = fmod(decryptChr, n);

		//結果存到密文
		messageEncrypt += (int)encryptChr + carry;

		//結果存到明文
		messageDecrypt += (int)decryptChr + carry;

	}

	//輸出

	cout << "Encrypt Message: " << messageEncrypt << endl;
	cout << "Decrypt Message: " << messageDecrypt << endl;
	return 0;
}

int gcd(int a, int b)
{
	int temp;
	while (1)
	{
		temp = a % b;
		if (temp == 0)
			return b;
		a = b;
		b = temp;
	}
}