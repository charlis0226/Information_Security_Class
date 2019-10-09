#include <iostream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;
string Decrypt(string Cipher, string Key, string CipherText)
{
	string Plaintext;
	if (Cipher == "caesar")
	{
		int temp;
		if (stoi(Key) > 25) Key = to_string(stoi(Key) % 26);
		for (int i = 0; i < CipherText.size(); i++)
		{
			temp = CipherText[i] + 32 - stoi(Key);
			if (temp < 97) temp += 26;
			CipherText[i] = temp;
		}
		Plaintext = CipherText;
	}
	if (Cipher == "row")
	{
		vector<string> temp;
		vector<string> temp1;
		int x = CipherText.size() / Key.size();//一次至少取x個
		int y = CipherText.size() % Key.size(); //row沒填滿多出來的文字個數
		int column = Key.size();
		int index = 0;
		string mKey="";
		for (int i = 0; i < Key.size(); i++)
			for (int j = 0; j < Key.size(); j++)
			{
				if (Key[j] - 48 == i + 1)
					mKey += (j + 1+48);
			}
		Key = mKey;
		for (int i = 0; i < Key.size(); i++)
		{
			if (Key[i]-48 <= y)
			{
				temp.push_back(CipherText.substr(index, x + 1));
				index+=(x+1);
			}
			else
			{
				temp.push_back(CipherText.substr(index, x));
				index += x;
			}
		}
		for (int i = 0; i < Key.size(); i++)
			for (int j = 0; j < Key.size(); j++)
			{
				if (Key[j]-48 == i + 1)
					temp1.push_back(temp[j]);
			}
		index = 0;
		for (int i = 0; i < CipherText.size(); i++)
		{
			Plaintext += (temp1[index][0]+32);
			temp1[index].erase(0, 1);
			index += 1;
			if (index == temp1.size()) index = 0;
		}
	}
	if (Cipher == "rail_fence")
	{
		vector<string> vec;
		int index = 0;
		int key = stoi(Key);
		for (int i = 0; i < stoi(Key); i++)
		{
			if (i < CipherText.size() % key)
			{
				vec.push_back(CipherText.substr(index, CipherText.size() / key + 1));
				index += 1;
			}
			else
				vec.push_back(CipherText.substr(index, CipherText.size() / key));
			index +=( CipherText.size() / key);
		}
		for (int i = 0; i < CipherText.size(); i++)
		{
			Plaintext += (vec[i%key][0]+32);
			vec[i%key].erase(0, 1);
		}
	}
	if (Cipher == "vernam")
	{
		string temp;
		for (int i = 0; i < CipherText.size(); i++)
		{
			char a, b;
			if (CipherText[i] >= 65) a = CipherText[i]-65; else a = CipherText[i];
			if (Key[i] >= 65) b = Key[i]-65; else b = Key[i];
			char x = (a) ^ (b);
			if (x <= 25) temp += (x + 65);
			else temp += x;
			Key += temp[i];
			Plaintext += (temp[i] + 32);
		}
	}
	if (Cipher == "playfair")
	{
		string newKey;
		char Engtable[26] = {0};
		for (int i= 0; i < Key.size(); i++)
		{
			if (Engtable[Key[i] - 65] == 0)
			{
				Engtable[Key[i] - 65] = 1;
				newKey += Key[i];
			}
		}

		string matrix=newKey;
		for (char i = 65; i <= 90; i += 1)
		{
			if (Engtable[8] == 1 && Engtable[9] == 1 && Engtable[16] == 0 && i == 81)//i j同時
				goto tag;
			else if (Engtable[8] == 1 && Engtable[9] == 0 && i == 74)
				goto tag;
			else if (Engtable[8] == 0 && Engtable[9] == 1 && i == 73)
				goto tag;
			else if (Engtable[8] == 0 && Engtable[9] == 0 && i == 74)
				goto tag;
			for (int j = 0; j < newKey.size(); j++)
			{
				if (newKey[j] == i)
					break;
				else if (newKey[j] != i&&j == newKey.size() - 1)
					matrix += i;
			}
		tag:;
		}
		int i = 0;
		while (i < CipherText.size())
		{
			int index[2];
			for (int j = 0; j < 2; j++)
				for (int z = 0; z < 25; z++)
				{
					if (!(Engtable[8] == 1 && Engtable[9] == 1))
					{
						if ((matrix[z] == 'I' || matrix[z] == 'J') && (CipherText[i + j] == 'I' || CipherText[i + j] == 'J'))
						{
							index[j] = z;
							break;
						}
					}
					if (matrix[z] == CipherText[i + j])
					{
						index[j] = z;
						break;
					}
				}
			if (abs(index[0] - index[1]) % 5 == 0) //同行
			{
				for (int j = 0; j < 2; j++)
				{
					if (index[j] < 5)
						Plaintext += matrix[index[j] + 20];
					else
						Plaintext += matrix[index[j] -5];
				}
			}
			else if ((abs(index[0] - index[1]) <= 4) && ((index[0]/5)==(index[1]/5)))//同列
			{
				for (int j = 0; j < 2; j++)
				{
					if (index[j] % 5 == 0)
						Plaintext += matrix[index[j] + 4];
					else
						Plaintext += matrix[index[j] - 1];
				}
			}
			else if (abs(index[0] - index[1]) % 5 != 0 && ((index[0] / 5) != (index[1] / 5)))//不同行不同列
			{
				int x0, x1,temp;
				x0 = index[0] % 5;
				x1 = index[1] % 5;
				temp = (index[0] / 5);
				index[0] = temp * 5 + x1;
				temp = (index[1] / 5);
				index[1] = temp * 5 + x0;
				Plaintext += matrix[index[0]];
				Plaintext += matrix[index[1]];
			}
			i += 2;
		}
	}
	
	return Plaintext;

}
int main(int argc, char *argv[])
{
	
	//string a, b, c;
	//cin >> a >> b >> c;
	cout << Decrypt(argv[1], argv[2], argv[3]);
	//cout << Decrypt(a, b, c);
	//system("PAUSE");
}
