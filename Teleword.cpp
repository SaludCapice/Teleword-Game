#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
// \x1b[A
char words[10000], grid[15][15];
int nums[15][15], hl = 0, hr = 0, vu = 0, vd = 0, df = 0, db = 0, smallest = RAND_MAX, largest = 0, scatter = 0, row, column;
string tellyword = "";
int word_size(int& start, float& sum, float& count)
{
	int size = 0;
	start += 1;
	while (1)
	{
		size++;
		if (words[start + size] == ',' || words[start + size] == '.')
			break;
	}
	if (size < smallest)
		smallest = size;
	if (size > largest)
		largest = size;
	sum += size; count++;
	return size;
}
int check(int m, int n, int start, int size)
{
	// horizontal right
	int s = start, capice = 0;
	for (int i = n + 1;1; i++)
	{
		if (words[s++] == grid[m][i] + 32)
			capice++;
		else
			break;
	}
	if (capice == size - 1)
	{
		hr++;
		for (int i = n ; i < n + size; i++)
		{
			nums[m][i]++;
		}
		return 1;
	}
	// horizontal left
	s = start, capice = 0;
	for (int i = n - 1; 1; i--)
	{
		if (words[s++] == grid[m][i] + 32)
			capice++;
		else
			break;
	}
	if (capice == size - 1)
	{
		hl++;
		for (int i = n; i > n - size; i--)
		{
			nums[m][i]++;
		}
		return 1;
	}
	// vertical up
	s = start, capice = 0;
	for (int i = m - 1; 1; i--)
	{
		if (words[s++] == grid[i][n] + 32)
			capice++;
		else
			break;
	}
	if (capice == size - 1)
	{
		vu++;
		for (int i = m; i > m - size; i--)
		{
			nums[i][n]++;
		}
		return 1;
	}
	// vertical down
	s = start, capice = 0;
	for (int i = m + 1; 1; i++)
	{
		if (words[s++] == grid[i][n] + 32)
			capice++;
		else
			break;
	}
	if (capice == size - 1)
	{
		vd++;
		for (int i = m; i < m + size; i++)
		{
			nums[i][n]++;
		}
		return 1;
	}
	// diagonal up left
	s = start, capice = 0;
	for (int i = m - 1, j = n - 1; 1; i--, j--)
	{
		if (words[s++] == grid[i][j] + 32)
			capice++;
		else
			break;
	}
	if (capice == size - 1)
	{
		db++;
		for (int i=m, j=n; i > m - size; i--, j--)
		{
			nums[i][j]++;
		}
		return 1;
	}
	//Diagonal up right
	s = start, capice = 0;
	for (int i = m - 1, j = n + 1; 1; i--, j++)
	{
		if (words[s++] == grid[i][j] + 32)
			capice++;
		else
			break;
	}
	if (capice == size - 1)
	{
		df++;
		for (int i = m, j = n; i > m - size; i--, j++)
		{
			nums[i][j]++;
		}
		return 1;
	}
	// Diagonal down left
	s = start, capice = 0;
	for (int i = m + 1, j = n - 1; 1; i++, j--)
	{
		if (words[s++] == grid[i][j] + 32)
			capice++;
		else
			break;
	}
	if (capice == size - 1)
	{
		db++;
		for (int i = m, j = n; i < m + size; i++, j--)
		{
			nums[i][j]++;
		}
		return 1;
	}
	// diagonal down right
	s = start, capice = 0;
	for (int i = m + 1, j = n + 1; 1; i++, j++)
	{
		if (words[s++] == grid[i][j] + 32)
			capice++;
		else
			break;
	}
	if (capice == size - 1)
	{
		df++;
		for (int i = m, j = n; i < m + size; i++, j++)
		{
			nums[i][j]++;
		}
		return 1;
	}
	return 0;
}
void row_column()
{
	int max = 0, max1 = 0, salud = 0, capice = 0;
	for (int i = 0; i < 15; i++)
	{
		int temp = 0, temp1 = 0;
		salud = 0;
		for (int j = 0; j < 15; j++)
		{
			if (nums[i][j] == 0)
			{
				if (salud == 0)
					scatter++;
				if (capice == 0) 
					tellyword += grid[i][j];
				else 
					tellyword += grid[i][j] + 32;
				capice = salud = 1;
			}
			temp += nums[i][j];
			temp1 += nums[j][i];
		}
		if (temp > max)
		{
			max = temp;
			row = i + 1;
		}
		if (temp1 > max1)
		{
			max1 = temp1;
			column = i + 1;
		}
	}
}
void statistics(float sum, float count)
{
	cout << "\nWord Statistic:\n";
	cout << "\tLongest word length: " << largest << "\n\tSmallest word length: " << smallest;
	cout << "\n\tAverage word length: " << sum / count;
	cout << "\nWord Distribution:\n";
	cout << "\tHorizontal: " << hr + hl << "(" << hr << "," << hl << ")\n\t";
	cout << "Vertical: " << vu + vd << "(" << vu << "," << vd << ")\n\t";
	cout << "Diagonal: " << db + df << "(" << df << "," << db << ")\n";
	row_column();
	cout << "Teleword Scatter: " << scatter;
	cout << "\nHeaviest row: " << row;
	cout << "\nHeavies column: " << column << "\n";
}
void inputpuzzle()
{
	ifstream readfile("teleword.txt");
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			readfile >> grid[i][j];
			nums[i][j] = 0;
		}
	}
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; 1; i++)
	{
		readfile >> words[i];
		if (words[i] == '.')
		{
			words[i + 1] = '\0';
			cout << endl;
			break;
		}
	}
	for (int i = 0; words[i] != '\0'; i++)
	{
		cout << words[i];
		if (words[i] == ',')
			cout << " ";
	}
	readfile.close();
}
void printpuzzle()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (nums[i][j] == 0)
			{
				cout << " \x1B[37m";
				cout << grid[i][j];
			}
			else if (nums[i][j] == 1)
			{
				cout << " \x1B[33m";
				cout << grid[i][j];
			}
			else if (nums[i][j] == 2)
			{
				cout << " \x1B[34m";
				cout << grid[i][j];
			}
			else
			{
				cout << " \x1B[31m";
				cout << grid[i][j];
			}
		}
		cout << endl;
	}
}
void choice(char& choice)
{
	cout << "\n\n1. Press S to solve the puzzle at once.\n2. Press T to solve the puzzle step by step.\n";
	cout << "3. Press X to print puzzle statistics.\nEnter your choice: ";
	cin >> choice;
}
int main()
{
	int start = -1, n;
	float sum = 0, count = 0;
	char ch;
	
	inputpuzzle();
	choice(ch);
	system("cls");
	cout << endl;
	while(1)
	{
		for (int i = 0; i < 50; i++)
			cout << "\x1b[A\b\b\b";
		n = word_size(start, sum, count);
		int c = 0;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (grid[i][j] == words[start])
					c = check(i, j, start + 1, n);
				if (c == 1) break;
			}
			if (c == 1) break;
		}
		if (ch == 'T' || ch == 't')
		{
			printpuzzle();
			cout << endl << "Words Checked:\n";
			for (int i = 0; i <= start + n; i++)
			{
				cout << words[i];
				if (words[i] == ',') cout << " ";
			}
			_getch();
		}
		start += n;
		if (words[start + 1] == '\0')
			break;
	} 
	if (ch == 'X' || ch == 'x')
	{
		cout << "\x1B[37m";
		printpuzzle();
		statistics(sum, count);
	}
	else if (ch == 'S' || ch == 's')
	{
		cout << "\x1B[37m";
		printpuzzle();
		row_column();
		cout << "\nTellyword is : " << tellyword;
	}
	else if (ch != 'T' || ch != 't')
		cout << "Invalid Input.";
}
