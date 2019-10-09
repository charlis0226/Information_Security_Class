#include <iostream>
#include <string>
#include <vector>

using namespace std;

string stringTranes(string, const int);
string caser(string, int);
string vernam(string, string);
string rail_fence(string, int);
string row(string, string);
string playfair(string, string);

int main()
{
	string select;
	string str_key;
	string plainText;
	string cipherTrxt;
	int    int_key;

	cin >> select;

	select = stringTranes(select, 1);


	if (select == "caeser")
	{
		cin >> int_key >> plainText;
		cout << caser(plainText, int_key);

	}
	else if (select == "playfair")
	{
		cin >> str_key >> plainText;
		cout << playfair(plainText, str_key);
	}
	else if (select == "vernam")
	{
		cin >> str_key >> plainText;
		cout << vernam(plainText, str_key);
	}
	else if (select == "row")
	{
		cin >> str_key >> plainText;
		cout << row(plainText, str_key);
	}
	else if (select == "rail_fence")
	{
		cin >> int_key >> plainText;
		cout << rail_fence(plainText, int_key);
	}
}

string stringTranes(string String, const int cst)
{
	if (cst)
	{
		for (int i = 0; i < String.length(); i++)
		{
			if (String[i] <= 'Z')
			{
				String[i] += 32;
			}
		}
	}
	else
	{
		for (int i = 0; i < String.length(); i++)
		{
			if (String[i] >= 'a')
			{
				String[i] -= 32;
			}
		}
	}

	return String;
}

string playfair(string plainText, string key)
{
	string newKey = "";
	string tText = "";
	char cipher[5][5];
	newKey += key[0];
	for (int i = 1; i < key.length(); i++)
	{
		for (int j = 0; j < newKey.length(); j++)
		{
			if (key[i] == newKey[j])
			{
				break;
			}
			if (j == newKey.length() - 1)
			{
				int flag = 0;
				if (key[i] == 'j'||key[i]=='i')
				{
					for (int k = 0; k < newKey.length(); k++)
					{
						if (newKey[k] == 'i' || newKey[k] == 'j')
						{
							flag = 1;
							break;
						}
					}
				}
				if (flag == 0)
				{
					newKey += key[i];
				}
			}
		}
	}
	for (int i = 0; i < 26; i++)
	{
		char temp = i + 'a';
		for (int j = 0; j < newKey.length(); j++)
		{
			if (newKey[j] == temp)
			{
				break;
			}
			if ((newKey[j] == 'i' && temp == 'j') || (newKey[j] == 'j' && temp == 'i'))
			{
				break;
			}
			if (j == newKey.length() - 1)
			{
				newKey += temp;
			}
		}
	}
	int counter = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cipher[i][j] = newKey[counter];
			counter++;
			cout << cipher[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < plainText.length(); i += 2)
	{
		int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (cipher[j][k] == plainText[i] || (cipher[j][k] == 'j' && plainText[i] == 'i') || (cipher[j][k] == 'i' && plainText[i] == 'j'))
				{
					x1 = j;
					y1 = k;
				}
				if (cipher[j][k] == plainText[i + 1] || (cipher[j][k] == 'j' && plainText[i + 1] == 'i') || (cipher[j][k] == 'i' && plainText[i + 1] == 'j'))
				{
					x2 = j;
					y2 = k;
				
				}
			}
		}
		cout << x1 << " " << y1 << endl;
		cout << x2 << " " << y2 << endl;
		if (x1 == x2)
		{
			if (y1 == 4)y1 = -1;
			if (y2 == 4)y2 = -1;
			tText += cipher[x1][y1+1];
			tText += cipher[x2][y2+1];
		}
		else if (y1 == y2)
		{
			if (x1 == 4)x1 = -1;
			if (x2 == 4)x2 = -1;
			tText += cipher[x1+1][y1];
			tText += cipher[x2+1][y2];
		}
		else {
			tText += cipher[x1][y2];
			tText += cipher[x2][y1];
		}

		cout << x1 << " " << y1 << endl;
		cout << x2 << " " << y2 << endl;
	}

	return tText;
}


string caser(string plainText, int key)
{
	while (key >= 26)
	{
		key -= 26;
	}
	for (int i = 0; i < plainText.length(); i++)
	{
		if (plainText[i] >= ('z' - key))
		{
			plainText[i] -= 26;
		}
		plainText[i] += key;
		if (plainText[i] > 'z')
		{
			plainText[i] -= 26;
		}
	}
	return stringTranes(plainText, 0);
}


string vernam(string plainText, string key)
{
	if (plainText.length() != key.length())return plainText;
	for (int i = 0; i < plainText.length(); i++)
	{
		int a, b, c;

		a = plainText[i] - 'a';
		b = key[i] - 'a';

		c = a ^ b;

		plainText[i] = c + 'a';
	}
	return stringTranes(plainText, 0);
}

string rail_fence(string plainText, int key)
{
	vector<string> arys;
	int flag = 0;
	int counter = 0;
	for (int i = 0; i < key; i++)
	{
		arys.push_back("");
	}
	for (int i = 0; i < plainText.length(); i++)
	{
		arys[counter] += plainText[i];

		if (flag == 0)
		{
			counter++;
		}
		else if (flag == 1)
		{
			counter--;
		}
		if (counter == 0)
		{
			flag = 0;
		}
		else if (counter == key - 1)
		{
			flag = 1;
		}
	}
	plainText = "";
	for (int i = 0; i < key; i++)
	{
		plainText += arys[i];
	}
	return stringTranes(plainText, 0);
}

string row(string plainText, string key)
{
	vector<string> arys;
	string temp = "";
	int nums = key.length();
	if (nums == 1)
	{
		return stringTranes(plainText, 0);
	}

	for (int i = 0; i < plainText.length(); i++)
	{
		temp += plainText[i];
		if ((i + 1) % nums == 0 && i != 0)
		{
			arys.push_back(temp);
			temp = "";
		}
	}
	arys.push_back(temp);
	plainText = "";
	for (int i = 1; i < key.length() + 1; i++)
	{
		for (int j = 0; j < key.length(); j++)
		{
			if (i == key[j] - '0')
			{
				for (int k = 0; k < arys.size(); k++)
				{
					if (arys[k].length() > j)
					{
						plainText += arys[k][j];
					}
				}
				break;
			}
		}
	}

	return stringTranes(plainText, 0);
}