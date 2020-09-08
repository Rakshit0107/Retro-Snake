#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <fstream>
#include <iomanip>
using namespace std;
bool gameOver;
const int width = 30;
const int height = 25;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int lenTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void Draw()
{
    system("cls");
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < lenTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
                 
 
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    } 
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input()
{
	
    if (kbhit())
    {
        switch (getch())
        {
        case 'a':
            dir = LEFT;
        	break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logic()
{
	static int flar,flal,flau,flad;
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < lenTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        flau=0;
    	flad=0;
		if(flar==0)
		{
			x--;
			flal = 1;
		}
		else
		{
			x++;
			
		}
        break;
    case RIGHT:
    	flau=0;
    	flad=0;
		if(flal==0)
		{
        	x++;
        	flar = 1;
        }
        else
        {
        	x--;
		}    
        break;
    case UP:
        flar = 0;
        flal = 0;
        if(flad==0)
        {
        	y--;
        	flau=1;
		}
		else
		{
			y++;
		}
        break;
    case DOWN:
        flar = 0;
        flal = 0;
        if(flau==0)
        {
        	y++;
        	flad=1;
		}
		else
		{
			y--;
		}
        break;
    default:
        break;
	}
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
 	//if(x>=width||x<0||y>=height||y<0)
 	//gameOver=true;
    for (int i = 0; i < lenTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            {
				gameOver = true;
				system("cls");
				cout<<"game over";
				cout<<"score is"<<score<<endl;
		}
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        lenTail++;
    }
}
void record()
{
	char name[100];
	ofstream of;
	ifstream ifs;
	ifs.open("record.txt");
	of.open("record.txt",ios::app);
	cout<<"enter your name"<<endl;
	cin.getline(name,1000);
	of<<"NAME:"<<name<<endl;
	of<<"SCORE:"<<score<<endl;
	of<<"###################################################"<<endl;
	of.close();
}
int main()
{
	for(int i=0;i<10;i++)
	{
		cout<<endl;
	}
	cout<<setw(50)<<"SNAKE"<<endl;
	cout<<setw(58)<<"press any key to play"<<endl;
	getch();
	system("cls");
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        //Sleep(5);
    }
    record();
    cout<<"wanna see past records!!??"<<endl;
    cout<<"press y/n"<<endl;
    char c;
    cin>>c;
    if(c=='y')
    {
    	system("cls");
    	ifstream ifs;
    	ifs.open("record.txt");
    	while(ifs.eof()==0)
  		{
  		    ifs.get(c);
    		cout<<c;
  		}
    	ifs.close();
	}
	else
    return 0;
}
