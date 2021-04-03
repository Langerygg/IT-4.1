// ТИ№4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

int n;
void getN(string code);
string getCode();
bool CorrectCode(string code);
string Coding(string code);
bool CheckBitValue(string block, int index);
string Decoding(string coded);
string DeleteCheckBit(string code);
string Interference(string coded);
char Swap(char symb);

int main()
{
	system("chcp 1251");
	string code = getCode();
	getN(code);
	string coded = Coding(code);
	cout << "\nКод без разделения на блоки (результат кодирования): " << coded << "\n";
	coded = Interference(coded);
	cout << "Код без разделения на блоки (результат внесения помех): " << coded << "\n";
	string decoded = Decoding(coded);	
	cout << "\nКод без разбеления на блоки с удаленными проверочными битами (результат декодирования): " << decoded << "\n\n";
	return 0;
}

void getN(string code) {
	do
	{
		cout << "Введите длину блока информационных битов, кратную " << code.length() << ": ";
		cin >> n;
	} while (n < 1 || (code.length() % n) != 0);
}

string getCode() {
	string code;
	do
	{
		cout << "Введите код для шифрования: ";
		cin >> code;
	} while (!CorrectCode(code));
	return code;
}

bool CorrectCode(string code) {
	if (code.length() < 1) {
		return false;
	}
	for (int i = 0; i < code.length(); i++)
	{
		if (code[i] != '0' && code[i] != '1')
		{
			return false;
		}
	}
	return true;
}

string Coding(string code) {
	vector<string> coded(ceil(double(code.length()) / double(n)), "");
	int counter = n, index = 0;
	for (int i = 0; i < code.length(); i++)
	{
		coded[index].push_back(code[i]);
		counter--;
		if (counter == 0) {
			index++;
			counter = n;
		}
	}
	cout << "\nКодировние!\nРазбитый на блоки код: ";
	for (int i = 0; i < coded.size(); i++)
	{
		cout << coded[i];
		if (i != coded.size() - 1)
		{
			cout << "|";
		}
	}
	int checkBits = 0;
	for (int i = 0; i < coded.size(); i++)
	{
		string oldCodeBlock = coded[i];
		coded[i].clear();
		int powOf2 = 0, index = 0, j = 0;
		while ((index - powOf2) != oldCodeBlock.length())
		{
			//cout << " " << index + 1 << " " << pow(2, powOf2) << "  ";
			if ((index + 1) == pow(2, powOf2))
			{
				coded[i].push_back('0');
				powOf2++;
			}
			else {
				coded[i].push_back(oldCodeBlock[j]);
				j++;
			}
			index++;
		}
		checkBits = powOf2;
	}
	cout << "\nКоличество проверочных битов в каждом блоке: " << checkBits << "\n";
	for (int i = 0; i < coded.size(); i++)
	{
		int powOf2 = 0;
		for (int j = 0; j < coded[i].length(); j++)
		{
			if (j + 1 == pow(2, powOf2))
			{
				powOf2++;
				if (CheckBitValue(coded[i], (j+1)))
				{
					coded[i][j] = '1';
				}
				else coded[i][j] = '0';
			}
		}
	}
	string result;
	cout << "Разбитый на блоки код с проверочными битами: ";
	for (int i = 0; i < coded.size(); i++)
	{
		cout << coded[i];
		if (i != coded.size() - 1)
		{
			cout << "|";
		}
		result.append(coded[i]);
	}
	return result;
}

string Interference(string coded) {
	int powCounter = 0, vectorLeng = n;
	for (int i = 0; i < vectorLeng; i++)
	{
		if (i + 1 == pow(2, powCounter))
		{
			vectorLeng++;
			powCounter++;
		}
	}
	vector<string> newcoded(coded.length() / vectorLeng, "");
	int index = 0;
	cout << "\nВнесение помех!\nРазбитый на блоки код: ";
	for (int i = 0; i < newcoded.size(); i++)
	{
		int j = 0;
		while (j != vectorLeng)
		{
			newcoded[i].push_back(coded[index]);
			index++;
			j++;
		}
		cout << newcoded[i];
		if (i != newcoded.size() - 1)
		{
			cout << "|";
		}
		else cout << "\n";
	}
	cout << "Какой элемент (от 1 до "<< newcoded[0].length() << ") (0 - без помех) изменить \nв блоке \n";
	for (int i = 0; i < newcoded.size(); i++)
	{
		int index;
		do
		{
			cout << "  № " << i + 1 << ": ";
			cin >> index;
		} while (index < 0 || index > newcoded[i].length());
		if (index != 0)
		{
			newcoded[i][index - 1] = Swap(newcoded[i][index - 1]);
		}
	}
	string result;
	for (int i = 0; i < newcoded.size(); i++)
	{
		result.append(newcoded[i]);
	}
	return result;
}

string Decoding(string coded) {
	int powCounter = 0, vectorLeng = n;
	for (int i = 0; i < vectorLeng; i++)
	{
		if (i + 1 == pow(2, powCounter))
		{
			vectorLeng++;
			powCounter++;
		}
	}
	vector<string> decoded(coded.length() / vectorLeng, "");
	int index = 0;
	cout << "\nДекодирование!\nРазбитый на блоки код: ";
	for (int i = 0; i < decoded.size(); i++)
	{
		int j = 0;
		while (j != vectorLeng)
		{
			decoded[i].push_back(coded[index]);
			index++;
			j++;
		}
		cout << decoded[i];
		if (i != decoded.size() - 1)
		{
			cout << "|";
		}
	}
	for (int i = 0; i < decoded.size(); i++)
	{
		int powOf2 = 0, swap = 0;
		for (int j = 0; j < vectorLeng; j++)
		{
			if (j + 1 == pow(2, powOf2))
			{
				powOf2++;
				char symb;
				if (CheckBitValue(decoded[i], (j + 1)))
				{
					symb = '1';
				}
				else {
					symb = '0';
				}
				if (symb != decoded[i][j])
				{
					swap += j + 1;
				}
			}
		}
		cout << "\nНомер элемента замены (0 - замены нет) для " << i + 1 << " блока: " << swap;
		if (swap > 0)
		{
			if (decoded[i][swap - 1] == '1') {
				decoded[i][swap - 1] = '0';
			}
			else {
				decoded[i][swap - 1] = '1';
			}
		}
	}
	cout << "\nВосстановленный код по блокам: ";
	for (int i = 0; i < decoded.size(); i++)
	{
		cout << decoded[i];
		if (i != decoded.size() - 1)
		{
			cout << "|";
		}
		decoded[i] = DeleteCheckBit(decoded[i]);
	}
	string result;
	for (int i = 0; i < decoded.size(); i++)
	{
		result.append(decoded[i]);
	}
	return result;
}

bool CheckBitValue(string block, int index) {
	int i = index - 1;
	int counter = 0;
	while (i < block.length())
	{
		for (int j = i; j < i + index; j++)
		{
			if (j == block.length()) {
				if ((counter - 1) % 2 == 0)
				{
					return 1;
				}
				else {
					return 0;
				}
			}
			if (block[j] == '1' && j != (index - 1)) {
				counter++;
			}
		}
		i += (index * 2);
	}
	if ((counter - 1) % 2 == 0)
	{
		return 1;
	}
	else {
		return 0;
	}
}

char Swap(char symb) {
	if (symb == '1') {
		return '0';
	}
	else {
		return '1';
	}
}

string DeleteCheckBit(string code) {
	int powOf2 = 0;
	string result;
	for (int i = 0; i < code.length(); i++)
	{
		if (i + 1 != pow(2, powOf2))
		{
			result.push_back(code[i]);
		}
		else {
			powOf2++;
		}
	}
	return result;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
