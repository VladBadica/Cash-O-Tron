#include <iostream>
#include <windows.h>
#include <ctime>
#include <iomanip>

using namespace std;

bool GameOver, taken;
const int width = 10;
const int height = 30;
int x, y, Money, choice;
char Map[width][height], player_icon = '@';
int columns, rows;
struct coordonate
{
    int x, y;
};
coordonate player, dollar, new_wall, write_wall;

void Interface()
{
    cout<<"\n\n\n\n";
    cout<<setw(columns / 2 + 11)<<"Welcome to Cash-O-Tron!";
    cout<<endl;
    cout<<setw(columns / 2 + 10)<<"Press enter to start!";
    while(!GetAsyncKeyState(VK_RETURN));

}

void SetUp()
{
    GameOver = false;
    player.x = width / 2 - 1;
    player.y = height / 2;
    choice = 1;
    Money = 0;
    srand(time(NULL));
    dollar.x = rand() % (width - 2) + 1;
    dollar.y = rand() % (height - 2) + 1;
    for(x = 0; x < width; x++)
        for(y = 0; y < height; y++)
            Map[x][y] = ' ';
    for(x = 0; x < width; x++)
    {
        for(y = 0; y < height; y++)
        {
            if(x == 0 || x == width -1 || y == 0 || y == height - 1) Map[x][y] = '#';
            if(x == player.x && y == player.y) Map[x][y] = player_icon;
            if(x == dollar.x && y == dollar.y) Map[x][y] = '$';
        }
    }
}

void Draw()
{
    system("cls");
    cout<<"\n\n\n\n\n\n";
    for(x = 0; x < width; x++)
    {
        cout<<setw(columns / 2 - height / 2)<<Map[x][0];
        for(y = 1; y < height; y++)
            cout<<Map[x][y];

        cout<<endl;
    }
    cout<<"\n\n   Money: "<<Money;
}

void Input()
{

    if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
    {
        Map[player.x][player.y] = ' ';
        player.x--;
    }
    if(GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
    {
        Map[player.x][player.y] = ' ';
        player.x++;
    }
    if(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
    {
        Map[player.x][player.y] = ' ';
        player.y--;
    }
    if(GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
    {
        Map[player.x][player.y] = ' ';
        player.y++;
    }
}

void Logic()
{
    if(Map[player.x][player.y] == '#') GameOver = true;
    if(Map[player.x][player.y] == '$')
    {

            Money += 50;
            write_wall.x = new_wall.x;
            write_wall.y = new_wall.y;
            new_wall.x = player.x;
            new_wall.y = player.y;
            do{
            dollar.x = rand() % (width - 2) + 1;
            dollar.y = rand() % (height - 2) + 1;
            }while(Map[dollar.x][dollar.y] == '#');

    }
}

void Update()
{

    Map[player.x][player.y] = '@';
    if(write_wall.x != 0 && write_wall.y != 0)
        Map[write_wall.x][write_wall.y] = '#';
    Map[dollar.x][dollar.y] = '$';

}

void LeaderBoard()
{

}

void End_Game(int &choice)
{
    while(!GetAsyncKeyState(VK_RETURN))
    {
        system("cls");
        cout<<"\n\n\n\n\n";
        cout<<setw(columns / 2 + 5)<<"Game Over!";
        cout<<"\n\n";
        cout<<setw(columns / 2 + 5)<<"Start over?";
        cout<<"\n";
        if(choice) cout<<setw(columns / 2 + 5)<<">Yes<    No";
        else cout<<setw(columns / 2 + 5)<<"Yes    >No<";
        if(GetAsyncKeyState(VK_LEFT)) choice = 1;
        else if(GetAsyncKeyState(VK_RIGHT)) choice = 0;
        else Sleep(500);
    }

}

int main()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    Interface();
    start:
    SetUp();

    while(!GameOver)
    {
        Draw();
        Input();
        Logic();
        Update();
        Sleep(55);
    }

    End_Game(choice);
    if(choice) goto start;


    return 0;
}
