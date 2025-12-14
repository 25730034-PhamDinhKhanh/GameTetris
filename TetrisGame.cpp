#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
#define H 15
#define W 20
char board[H][W] = {};

int x, y, b;
char blocks[][4][4] ={
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'I','I','I','I'},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}}
};
//Kiem tra neu khoi co the di chuyen
bool canMove(int dx, int dy){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (blocks[b][i][j] != ' ') {   //xet cac o khong trong
                int xt = x + j + dx;        //tinh toa do moi cua board
                int yt = y + i + dy;        //tinh toa do moi cua board
                if (xt < 1 || xt >= W-1 || yt >= H-1 ) return false;    //khong the di chuuyen
                if (board[yt][xt] != ' ') return false;                 //khong the di chuuyen
            }
    return true;    //co the di chuyen
}

//Ve khoi 
void block2Board(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (blocks[b][i][j] != ' ')
                board[y+i][x+j] = blocks[b][i][j];
}


void boardDelBlock(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (blocks[b][i][j] != ' ')
                board[y+i][x+j] = ' ';
}


//Khoi tao bang tro choi
void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if (i == 0 || i == H-1 || j ==0 || j == W-1) board[i][j] = '#';
            else board[i][j] = ' ';
}


void draw(){
    system("cls");

    for (int i = 0 ; i < H ; i++) {
        for (int j = 0 ; j < W ; j++) {
            char cell = board[i][j];
            
            if (cell == ' ') {
                cout << "  ";
            } 
            else if (cell == '#') {
                cout << "##";
            }
            else {
                cout << cell << cell;
            }
        }
        cout << endl;
    }
}


void removeLine(){
     for (int i = H - 2; i >= 0; i--) {

        bool full = true;
        for (int j = 0; j < W; j++) {
            if (board[i][j] == ' ') {
                full = false;
                break;
            }
        }

        if (full) {
            for (int ii = i; ii > 0; ii--) {
                for (int jj = 0; jj < W; jj++) {
                    board[ii][jj] = board[ii - 1][jj];
                }
            }

            for (int jj = 0; jj < W; jj++)
                board[0][jj] = ' ';

            draw();
            Sleep(100);
            i++;  
        }
    }
}

int main()
{
    srand(time(0));
    x = 5; y = 0; b = rand()%7;
    initBoard();

    while (1){
        boardDelBlock();

        // Xử lý bàn phím
        if (kbhit()){
            char c = getch();
            if (c == 'a' && canMove(-1,0)) x--;
            if (c == 'd' && canMove( 1,0)) x++;
            if (c == 'x' && canMove( 0,1)) y++;
            if (c == 'q') break;
        }

         // Khối tự rơi xuống
        if (canMove(0,1)) y++;
        else{
            block2Board();
            removeLine();
            x = 5; y = 0; b = rand()%7;
        }
        block2Board();
        draw();
        Sleep(400);
    }
    return 0;
}
