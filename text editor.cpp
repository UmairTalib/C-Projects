#include<iostream>
#include<conio.h>
#include<windows.h>
#include<fstream>
using namespace std;
void gotoRowCol(int rpos, int cpos);
struct line{ int noc; char*cs; };
struct doc{ int nol; line*lines; };
void print(doc d1);
void edditer(doc d1, int &cr, int &cc, line*cp);
void growch(line*cp, int &cc, char  c);
void growbetween(line*cp, int  cr, int &cc, char  c);
void shrink(line*cp, int  cr, int &cc);
char* wordstoline(char**ptr, int*wl, int count);
char** linetowords(int &count, int *&wl, line*cp);
void savefile(doc d1,char*fname);
void growline(doc &d1,int &cr);
void tolower(doc &d1);
void toupper(doc &d1);
void replace_with_given(doc &d1);
void postfix(doc &d1);
void highlight(char *word, int* positions, int  h_mny_times, char** ptr, int row);
void searchword(char*&word, char**ptr, int *&positions, int *wl, int count, int &h_mny_times);
void prefix(doc &d1);
void menu(doc &d1,int &l);
void regrowarray(int *&Arr, int &size);
void deleteline(doc &d1);
void readfile(doc &d1, int &cr, int &cc);
void ChangeColor(int color);
void init(doc &d1, line *&CP)
{
	d1.nol = 1;
	d1.lines = new line[d1.nol];
	d1.lines[0].cs = nullptr;
	d1.lines[0].noc = 0;
	CP = d1.lines;



}
int main()
{
	cout << "HI my name is umair" << endl << "welcome to the text editor you can write right know and save it and implement functions" << endl << "and  the text you are reading will be cleared automatically when you start writing" << endl << "ctrl j is for function implementation menu"<<endl;
	doc d1;
	line*cp;
	int cr, cc;
	cr = cc = 0;
	init(d1, cp);
	edditer(d1, cr, cc, cp);
	system("pause");

}
void edditer(doc d1,int &cr,int &cc,line*cp)
{
	char c;
	while (1)
	{
		if (_kbhit())
		{
			c = _getch();
			if (c == -32)
			{
				c = _getch();
				switch (c)
				{
				case (72) : {
					cr--;
					if (cr < 0)
						cr = 0;
					gotoRowCol(cr, cc); break; }//up
				case (80) : {
					cr++;
					gotoRowCol(cr, cc); break; }//down
				case (77) : {
					cc++;
					if (cc >167)
					{
						cr++; cc = 0;
					}
					gotoRowCol(cr, cc); break; }//right
				case (75) : {
					cc--;
					if (cr == 0 && cc<0)
					{
						cc = d1.lines[cr].noc;
					}
					else if (cc <0)
					{
						cr--; cc = d1.lines[cr].noc;
					}
					gotoRowCol(cr, cc); break; }//left
				}
			}
			else  if (c == 19)
			{
				char*fname = new char[50];
				savefile(d1,fname);

			}
			else if (c == 8)  //Backspace
			{ 
				if (cr < 0){

					cr = cc = 0;
				}
				cp = &d1.lines[cr];
				
				shrink(cp, cr, cc);
				system("cls");
				print(d1);

				if (cc <0)
				{
					cr--; cc = d1.lines[cr].noc;
					deleteline(d1);
					system("cls");
					print(d1);
					
					if (cr< 0)
					
						cr = cc = 0;
				}
				gotoRowCol(cr, cc);
			}
			else if (c == 15)
			{
				init(d1, cp);
				readfile(d1, cr, cc);
				system("cls");
				print(d1);
				cr = d1.nol;
				cc = d1.lines[d1.nol].noc;
				gotoRowCol(cr,cc);
			
			}
			else if (c == 10)
			{
				int l = 0;
				system("cls");
				
				menu(d1,l);
				if (l != 1){
					system("cls");
					print(d1); }
				gotoRowCol(cr, cc);
				
			}

			else if (c == 13) // enter or next line
			{
				growline(d1,cr);
				system("cls");
				print(d1);
				cc = 0;
				gotoRowCol(cr, cc);
				


				
			}
			else
			{
				if (cc > 128)
				{
					growline(d1,cr);
					system("cls");
					print(d1);
					cc = 0;
					gotoRowCol(cr, cc);

				}
				else
				{
					cp = &d1.lines[cr];
					if (cc < cp->noc)
					{
						growbetween(cp, cr, cc, c);
						system("cls");
						print(d1);
						gotoRowCol(cr, cc);
						
					}
					else{
						growch(cp, cc, c);

						system("cls");
						print(d1);
						gotoRowCol(cr, cc);
				
					}
				}
				}
				
			}
		}
	}


void growch(line*cp, int &cc, char  c)
{
	int i = 0;
	int d1 = cp->noc;
	char *temp = new char[d1 + 2];
	if (cp ->noc > 0){
		for (i = 0; i < d1; i++)
		{
			temp[i] = cp->cs[i];

		}
	}
	temp[i] = c;
	temp[i + 1] = NULL;
	if (cp->noc > 0)
	{
		delete[] cp->cs;
	}
	cp->cs = temp;
	cp->noc++;
	cc++;

}

void shrink(line*cp, int  cr, int &cc)
{


	int i = 0;
	int d1 = cp->noc;
	char *temp = new char[d1];
	temp = cp->cs;
		for (i = cc - 1; i < d1; i++)
			temp[i] = temp[i + 1];

		temp[i] = NULL;
		cp->cs = temp;
		cp->noc--;
		cc--;
	}

void growline(doc &d1,int &cr)
{
	int i;
	line*temp = new line[d1.nol + 1];

	for (i = 0; i < d1.nol; i++)
	{
			temp[i].noc = d1.lines[i].noc;
			temp[i].cs = new char[temp[i].noc+1];

			strcpy_s(temp[i].cs,d1.lines[i].noc+1, d1.lines[i].cs);
			

		
	}
	temp[i].noc = 0;
	temp[i].cs = nullptr;
	d1.lines = temp;
	d1.nol++;
	cr++;



}
void print(doc d1)
{
	for (int i = 0; i < d1.nol; i++)
	{
		for (int j = 0; j<d1.lines[i].noc; j++)
		{
			cout << d1.lines[i].cs[j];


		}
		cout << endl;
	}


}
void savefile(doc d1,char*fname)
{
	system("cls");
	cout << "enter file name" << endl;
	cin >> fname;
	
	ofstream fout(fname,ios::app);
	for (int i = 0; i < d1.nol; i++)
	{
		for (int j = 0; j < d1.lines[i].noc; j++)
		{
			fout << d1.lines[i].cs[j];


		}
		fout << endl;
	}}



void gotoRowCol(int rpos, int cpos)
{
	int xpos = cpos, ypos = rpos;
	COORD scrn;

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos; scrn.Y = ypos;

	SetConsoleCursorPosition(hOuput, scrn);
}
void growbetween(line*cp, int  cr, int &cc, char  c)
{
	int i = 0;
	int d1 = cp->noc;
	char *temp = new char[d1 + 2];
	if (cp->noc > 0){
		for (i = 0; i < cc; i++)
		{
			temp[i] = cp->cs[i];

		}
	}
	temp[cc] = c;
	for (i = cc + 1; i < cp->noc; i++)
	{
		temp[i] = cp->cs[i-1];

	}
	temp[i] = NULL;
	if (cp->noc > 0)
	{
		delete[] cp->cs;
	}
	cp->cs = temp;
	cp->noc++;

}

void menu(doc &d1, int &l)
{


	int n;
	double avg_w_len;
	line*cp;
	int *wl = nullptr;
	char* word = nullptr;
	int *positions = nullptr; int  h_mny_times;
	int count;
	char**ptr1 = nullptr;
	cout << "enter 1 to 8 for test each of 10 function" << endl;
	cout <<  "1 0r 2 for add prefix" << endl << "3 for postfix" << endl << "4 for replace word" << endl << "5 for convert to uppercase" << endl << "6 for convert to lowercase" << endl << "7 for average word length" << endl << "8 for two functions search and highlight"
		<< endl;
	cin >> n;
	system("cls");
	switch (n)
	{
	case 1:
	{

	}
	case 2:
	{

		prefix(d1);
		break;

	}
	case 3:
	{

		postfix(d1);
		break;
	}
	case 4:
	{


		replace_with_given(d1);
		break;

	}
	case 5:
	{

		toupper(d1);

		break;

	}
	case 6:
	{

		tolower(d1);
		break;

	}
	case 7:
	{
		
		//avg_w_len = find_avg_word_lenth(wl, count);
		//cout << avg_w_len << endl;
		break;
	}
	case 8:
	{
	 l = 1;
	 word = new char[100];
	 cout << "enter the word you want to find and highlight " << endl;
	 cin >> word;
		system("cls");
		print(d1);

		for (int i = 0; i < d1.nol; i++)
		{
			cp = &d1.lines[i];
			ptr1 = linetowords(count, wl, cp);
			for (int k= 0; k < count; k++)
			{

				if (strcmp(ptr1[k], word) == 0)
				{
					searchword(word, ptr1, positions, wl, count, h_mny_times);
					highlight(word, positions, h_mny_times, ptr1,i );

				}

			}
		}break; }
	}
}
void replace_with_given(doc &d1){

	char *replaced_word = new char[100];
	char*word = new char[100];
	cout << "enter the correct word you want to replace" << endl;
	cin >> word;
	char**ptr1 = nullptr;
	line*cp;
	int count = 0;
	int* wl = nullptr;
	cout << "enter replaced word" << endl;
	cin >> replaced_word;
	for (int i = 0; i < d1.nol; i++)
	{
		cp = &d1.lines[i];
		ptr1 = linetowords(count, wl, cp);
		for (int i = 0; i < count; i++)
		{

			if (strcmp(ptr1[i], word) == 0)
			{
				int d1 = strlen(replaced_word);
				char*temp = new char[d1 + 1];
				for (int j = 0; j < d1; j++)
				{
					temp[j] = replaced_word[j];

				}
				wl[i] = d1;
				ptr1[i] = temp;
			}

		}
		cp->cs = wordstoline(ptr1, wl, count);
	}
}
void postfix(doc &d1)
{
	int k;
	char**ptr1 = nullptr;
	line*cp;
	int count = 0;
	int* wl = nullptr;
	char *postfix = new char[100];
	char*word = new char[100];
	cout << "enter word you want to add postfix" << endl;
	cin >> word;
	cout << "enter postfix" << endl;
	cin >> postfix;
	int d12 = strlen(postfix);
	
	for (int i = 0; i < d1.nol; i++)
	{
		cp = &d1.lines[i];
		ptr1 = linetowords(count, wl, cp);

		for (int i = 0; i < count; i++)
		{

			if (strcmp(ptr1[i], word) == 0)
			{

				char*temp = new char[wl[i] + d12 + 1];

				for (int l = 0; l < wl[i]; l++)
				{
					*(temp + l) = ptr1[i][l];
				}
				for (k = wl[i]; k < wl[i] + d12; k++)
				{
					*(temp + k) = postfix[k - wl[i]];

				}
				wl[i] = d12 + wl[i];
				*(temp + k) = NULL;
				ptr1[i] = temp;
		
			}

		}
		cp->cs = wordstoline(ptr1, wl, count);
	}
}
void prefix(doc &d1)
{
	int k;
	char**ptr1 = nullptr;
	line*cp;
	int count = 0;
	int* wl = nullptr;
	char *prefix = new char[100];
	char*word = new char[100];
	cout << "enter word you want to add prefix" << endl;
	cin >> word;
	cout << "enter postfix" << endl;
	cin >> prefix;
	int d12 = strlen(prefix);

	for (int i = 0; i < d1.nol; i++)
	{
		cp = &d1.lines[i];
		ptr1 = linetowords(count, wl, cp);

		for (int i = 0; i < count; i++)
		{

			if (strcmp(ptr1[i], word) == 0)
			{
				
				char*temp = new char[wl[i] + d12 + 1];
				for (int l = 0; l <d12; l++)
				{
					*(temp + l) = prefix[l];
				}
				for (k = d12; k < wl[i] + d12; k++)
				{
					*(temp + k) = ptr1[i][k - d12];

				}
				wl[i] = d12 + wl[i];
				*(temp + k) = NULL;
				ptr1[i] = temp;
				break;

			}

		}
		cp->cs = wordstoline(ptr1, wl, count);
	}
}
void tolower(doc &d1) // converting string to lower case
{
	char**ptr1 = nullptr;
	line*cp;
	int count = 0;
	char*word = new char[30];
	cout << "enter word" << endl;
	cin >> word;
	int* wl = nullptr;
	for (int i = 0; i < d1.nol; i++)
	{
		cp = &d1.lines[i];
		ptr1 = linetowords(count, wl, cp);

		for (int i = 0; i <count; i++)
		{
			if (strcmp(ptr1[i], word) == 0){
				for (int j = 0; ptr1[i][j] != NULL; j++)
				{
					if (ptr1[i][j] >= 'A'&&ptr1[i][j] <= 'Z')
					{

						ptr1[i][j] = ptr1[i][j] + 32;
					}


				}
			}


		}
		cp->cs = wordstoline(ptr1, wl, count);

	}
}
void toupper(doc &d1) // converting string to lower case
{
	char**ptr1 = nullptr;
	line*cp;
	int count = 0;
	char*word = new char[30];
	cout << "enter word" << endl;
	cin >> word;
	int* wl = nullptr;
	for (int i = 0; i < d1.nol; i++)
	{
		cp = &d1.lines[i];
		ptr1 = linetowords(count, wl, cp);

		for (int i = 0; i < count; i++)
		{
			if (strcmp(word, ptr1[i]) == 0){
				for (int j = 0; ptr1[i][j] != NULL; j++)
				{
					if (ptr1[i][j] >= 'a'&&ptr1[i][j] <= 'z')
					{

						ptr1[i][j] = ptr1[i][j] - 32;
					}


				}
			}


		}
		cp->cs = wordstoline(ptr1, wl, count);

	}
}


char** linetowords(int &count, int *&wl, line*cp)
{
	char*ptr = cp->cs;
	count = 1; int j = 0, b = 0;
	for (int i = 0; ptr[i] != NULL; i++)
	{
		if (ptr[i] == 32)
		{
			count++;
		}

	}

	char**ptr1 = new char*[count];
	wl = new int[count];
	for (int i = 0; i < count; i++)
	{
		wl[i] = 0;

	}

	for (int i = 0; ptr[i] != NULL; i++)
	{
		if (ptr[i] == ' ')
		{
			j++;
		}
		else
		{
			wl[j]++;
		}


	}
	for (int i = 0; i < count; i++)
	{
		*(ptr1 + i) = new char[wl[i]];
	}
	j = 0;
	for (int i = 0; i < count; i++)
	{

		for (j; ptr[j] != NULL; j++)
		{
			if (ptr[j] == ' ')
			{
				ptr1[i][b] = '\0';
				b = 0; j++;
				break;
			}
			else
			{
				ptr1[i][b] = ptr[j];
				b++;
			}

		}


	}



	return ptr1;
}
char* wordstoline(char**ptr, int*wl, int count)
{
	int tl = 0; int b = 0;
	for (int i = 0; i < count; i++)
	{
		tl = tl + wl[i];
	}
	char*inte = new char[count + tl];
	for (int i = 0; i < count; i++)
	{
		if (b != 0){
			b++;
		}
		for (int j = 0; j < wl[i]; j++)
		{
			inte[b] = ptr[i][j];
			b++;
		}
		inte[b] = ' ';
	}
	inte[b] = NULL;


	return inte;
}
void readfile(doc &d1,int &cr,int &cc)
{
	cr = cc = 0;
	char*fname = new char[30];
	cout<< "enter file name" << endl;
	cin >> fname;
	ifstream sin(fname);
	char c;
	line *cp;
	while (!sin.eof())
	{
		while (!sin.eof())
		{
			sin.get(c);
			cp = &d1.lines[cr];
			growch(cp, cc, c);
			if (c == NULL){
				break;
			}
			

		}
		
		growline(d1, cr);
		cc = 0;

	}
	


}
void deleteline(doc &d1)
{
	int i;
	line*temp = new line[d1.nol - 1];

	for (i = 0; i < d1.nol-1; i++)
	{
		temp[i].noc = d1.lines[i].noc;
		temp[i].cs = new char[temp[i].noc +1];

		strcpy_s(temp[i].cs, d1.lines[i].noc + 1, d1.lines[i].cs);



	}
	temp[i].noc = 0;
	temp[i].cs = nullptr;
	d1.lines = temp;
	d1.nol--;


}
void searchword(char*&word, char**ptr, int *&positions, int *wl, int count, int &h_mny_times)
{
	h_mny_times = 0;
	positions = nullptr;
	for (int i = 0; i < count; i++)
	{
		if (strcmp(word, ptr[i]) == 0)
		{
			regrowarray(positions, h_mny_times);
			positions[h_mny_times - 1] = i;




		}
	}
}
void highlight(char *word, int* positions, int  h_mny_times, char** ptr,int row)
{
	int  c = 0;
	for (int i = 0; i < h_mny_times; i++)
	{
		c = 0;
		for (int j = 0; j <positions[i]; j++)
		{
			c += strlen(ptr[j]);
		}
		if (positions[i] != 0)
			c += positions[i];

		gotoRowCol(row, c);
		ChangeColor(10);
		cout << word;
		ChangeColor(7);
	}
}
void regrowarray(int *&Arr, int &size)
{
	int *temp = new int[size + 1];
	for (int i = 0; i < size; i++)
	{
		temp[i] = Arr[i];
	}
	delete[] Arr;
	size++;
	Arr = temp;
}
void ChangeColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;
	SetConsoleTextAttribute(hConsole, color);
}
double find_avg_word_lenth(int*wl, int count)
{
	double *ptr = new double[count];
	double avg = 0, b = 0;
	for (int i = 0; i < count; i++)
	{

		avg += wl[i];

	}
	avg = avg / count;
	for (int i = 0; i < count; i++)
	{

		ptr[i] = wl[i] / avg;

	}
	for (int i = 0; i < count; i++)
	{

		b += ptr[i];

	}

	return b / avg;


}