#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;
#define H 15
#define W 20

int speed = 400; //tốc độ ban đầu 
int minSpeed = 80;  //tốc độ nhanh nhất (giới hạn)

char board[H][W] = {};

int score = 0; //biến cho điểm số
int level = 1; //biến cho level
int totalLines = 0;  //biến cho tổng lines

int x, y, b;
char currentBlock[4][4];  // Luu trang thai hien tai cua khoi
char blocks[][4][4] ={
        // I-piece (vertical)
        {{' ','B',' ',' '},
         {' ','B',' ',' '},
         {' ','B',' ',' '},
         {' ','B',' ',' '}},
        // O-piece
        {{' ',' ',' ',' '},
         {' ','B','B',' '},
         {' ','B','B',' '},
         {' ',' ',' ',' '}},
        // T-piece
        {{' ',' ',' ',' '},
         {' ','B',' ',' '},
         {'B','B','B',' '},
         {' ',' ',' ',' '}},
        // S-piece
        {{' ',' ',' ',' '},
         {' ','B','B',' '},
         {'B','B',' ',' '},
         {' ',' ',' ',' '}},
        // Z-piece
        {{' ',' ',' ',' '},
         {'B','B',' ',' '},
         {' ','B','B',' '},
         {' ',' ',' ',' '}},
        // J-piece
        {{' ',' ',' ',' '},
         {'B',' ',' ',' '},
         {'B','B','B',' '},
         {' ',' ',' ',' '}},
        // L-piece
        {{' ',' ',' ',' '},
         {' ',' ','B',' '},
         {'B','B','B',' '},
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
//Kiem tra khoi co the di chuyen
bool canRotate(char tmp[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (tmp[i][j] != ' ') {
                int xt = x + j;
                int yt = y + i;
                if (xt < 1 || xt >= W - 1 || yt < 0 || yt >= H - 1) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}

void rotateBlock() {
    char tmp[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            tmp[i][j] = blocks[b][3 - j][i];

    if (canRotate(tmp))
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                blocks[b][i][j] = tmp[i][j];
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


void VeManHinh() {
    // Thay thế system("cls") để tối ưu tốc độ và giảm giật hình
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(hConsole, cursorPosition);

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            char cell = board[i][j];

            if (cell == ' ') {
                SetConsoleTextAttribute(hConsole, 7);
                cout << ' ';
            } 
            else if (cell == '#') {
                SetConsoleTextAttribute(hConsole, 7);
                cout << '#';
            } 
            else {
                SetConsoleTextAttribute(hConsole, 15);
                cout << (char)219;
            }
        }

        if (i == 2) cout << " SCORE: " << score;
        if (i == 4) cout << " LEVEL: " << level;
        if (i == 6) cout << " LINES: " << totalLines;

            
        cout << '\n';
    }
    SetConsoleTextAttribute(hConsole, 7);
}


int removeLine(){
    int removed = 0;

    for (int i = H - 2; i > 0; i--) {

        bool full = true;
        for (int j = 1; j < W - 1; j++) {   // ❗ bỏ tường
            if (board[i][j] == ' ') {
                full = false;
                break;
            }
        }

        if (full) {
            removed++;

            for (int ii = i; ii > 0; ii--) {
                for (int jj = 1; jj < W - 1; jj++) {
                    board[ii][jj] = board[ii - 1][jj];
                }
            }

            for (int jj = 1; jj < W - 1; jj++)
                board[0][jj] = ' ';

            VeManHinh();
            Sleep(80);
            i++;  // kiểm tra lại dòng này
        }
    }
    return removed;
}


//hàm tính điểm
void updateScore(int lines) {
    if (lines == 1) score += 100 * level;
    else if (lines == 2) score += 300 * level;
    else if (lines == 3) score += 500 * level;
    else if (lines >= 4) score += 800 * level;

    totalLines += lines;

    // Mỗi 5 dòng lên 1 level
    level = totalLines / 5 + 1;
}


bool isGameOver = false;

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
            if (c == 'w') rotateBlock();
            if (c == 'q') break;
        }

         // Khối tự rơi xuống
        if (canMove(0,1)) y++;
        else{
            if (y <= 1) {
                isGameOver = true;
                break;
            }
            block2Board();
            int lines = removeLine();
            if (lines > 0) {
                updateScore(lines);
                
                speed -= lines * 30;     // mỗi line nhanh hơn 30ms
                if (speed < minSpeed)
                    speed = minSpeed;
        }

        x = 5; 
        y = 0; 
        b = rand() % 7;
        }
        block2Board();
        VeManHinh();
        Sleep(speed);
    }
        if (isGameOver) {
        system("cls");
        cout << "\n\n    GAME OVER\n";
        cout << "Nhan phim bat ky de thoat";
        getch();
    }
    return 0;
}
