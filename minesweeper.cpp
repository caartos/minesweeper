#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

void CleanScreen();
void Config();
void PlayGame();
bool CheckBoxs();
void ShowBoard(bool showBombs);
int ShowBox();
void FillBoard();
void EmptySector(int y, int x);

vector<vector<int>> board;

char selected;
vector<int> sizeBoard(2);
vector<int> boxPosition(2);
int minesAmount = 0;
bool BombsOnBoard = false;
vector<vector<int>> operations = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};


int main() {
    while(true){
        CleanScreen();
        cout<<"::::MINESWEEPER::::"<<endl;
        cout<<"1) Play"<<endl;
        cout<<"2) Quit"<<endl;
        cout<<"Select: ";
        cin>>selected;
        switch(selected){
            case '1': 
            Config();
            PlayGame();
            break;
            case '2':
            return 0;
            break;
        }
    }
    return 0;
}

void CleanScreen(){
    if(system("clear") == -1){
        cout<<"Error on screen cleaning"<<endl;
    }
}

void Config (){
    CleanScreen();
    cout<<"::::CONFIG::::"<<endl;
    cout<<"Select size: ";
    cin>>sizeBoard[0]>>sizeBoard[1];
    cout<<"Select amount of mines: ";
    cin>>minesAmount;
    board.resize(sizeBoard[0],(vector<int>(sizeBoard[1])));
    for(int i=0; i < sizeBoard[0]; i++){
        for(int j = 0; j < sizeBoard[1]; j++){
            board[i][j] = -1;
        }
    }
}

void PlayGame(){
    BombsOnBoard = false;
    while(CheckBoxs()){
        ShowBoard(false);
        cout<<"\n1) Show box"<<endl;
        cout<<"2) Check a box"<<endl;
        cout<<"3) Uncheck a box"<<endl;
        cout<<"Select: ";
        cin>>selected;
        int ret;
        switch (selected){
        case '1':
            cout<<"Enter the position of the box to show: ";
            cin>>boxPosition[0]>>boxPosition[1];
            ret = ShowBox();
            if(ret == -1){
                return;
            }else if(ret == 2 && BombsOnBoard){
                EmptySector(boxPosition[0],boxPosition[1]);
            }
            if(!BombsOnBoard){
                FillBoard();
                board[boxPosition[0]][boxPosition[1]] = -1;
                BombsOnBoard = true;
                ret = ShowBox();
                if(ret == -1){
                    return;
                }else if(ret == 2 && BombsOnBoard){
                    EmptySector(boxPosition[0],boxPosition[1]);
                }
            }
            EmptySector(boxPosition[0],boxPosition[1]);
            break;
        case '2':
            cout<<"Enter the position of the box to check: ";
            cin>>boxPosition[0]>>boxPosition[1];
            if(board[boxPosition[0]][boxPosition[1]] == 10){
                board[boxPosition[0]][boxPosition[1]] = 1011;
            }else if(board[boxPosition[0]][boxPosition[1]] == -1){
                board[boxPosition[0]][boxPosition[1]] = 11;
            }
            break;
        case '3':
            cout<<"Enter the position of the box to uncheck: ";
            cin>>boxPosition[0]>>boxPosition[1];
            if(board[boxPosition[0]][boxPosition[1]] == 11){
                board[boxPosition[0]][boxPosition[1]] = -1;
            }else if(board[boxPosition[0]][boxPosition[1]] == 1011){
                board[boxPosition[0]][boxPosition[1]] = 10;
            }
            break;
        }
    }
    cout<<"\n CONGRATULATION, YOU WIN, press OK to continue: ";
    cin>>selected;
}

bool CheckBoxs(){
    for(int i=0; i < sizeBoard[0]; i++){
        for(int j = 0; j < sizeBoard[1]; j++){
            if(board[i][j] == -1){

                return true;
            }
        }
    }
    return false;
}

void ShowBoard(bool showBombs){
    CleanScreen();
    for(int i = 0; i < sizeBoard[1]; i++){
        cout<<" "<<i;
    }
    cout<<endl;
    for(int i = 0; i < sizeBoard[0]; i++){
        for(int j = 0; j < sizeBoard[1]; j++){
                switch (board[i][j]){
                case -1:
                cout<<"⬜";
                    break;
                case 0:
                cout<<"⬛";
                    break;
                case 1:
                cout<<"1️⃣ ";
                break;
                case 2:
                cout<<"2️⃣ ";
                break;
                case 3:
                cout<<"3️⃣ ";
                break;
                case 4:
                cout<<"4️⃣ ";
                break;
                case 5:
                cout<<"​5️⃣ ";
                break;
                case 6:
                cout<<"6️⃣ ";
                break;
                case 7:
                cout<<"7️⃣ ";
                break;
                case 8:
                cout<<"8️⃣ ";
                break; 
                case 10:
                if(showBombs){
                    cout<<"💣";                    
                }else{
                    cout<<"⬜";
                };
                    break;
                case 1011:
                    if(showBombs){
                        cout<<"💣";
                    }else{
                        cout<<"🚩";
                    };
                    break;
                case 11:
                cout<<"🚩";
                break;
                }
            }
            cout<<" "<<i;
            cout<<endl;
        }
    }

int ShowBox(){
    int cont = 0;
    switch(board[boxPosition[0]][boxPosition[1]]){
        case 11:
        case 1011:
        cout<<"Box already checked, can't show it. Press OK: ";
        cin>>selected;
        break;
        case 10:
        ShowBoard(true);
        cout<<"\n You lost. Press OK: ";
        cin>>selected;
        return -1;
        break;
        case -1:
        for(int i = 0; i< 8; i++){
            if(boxPosition[0]+ operations[i][0] >= 0 && boxPosition[0]+ operations[i][0] < sizeBoard[0]){
                if(boxPosition[1]+ operations[i][1] >= 0 && boxPosition[1]+ operations[i][1] < sizeBoard[1]){
                    if(board[boxPosition[0]+ operations[i][0]][boxPosition[1]+operations[i][1]] == 10 || board[boxPosition[0]+ operations[i][0]][boxPosition[1]+operations[i][1]] == 1011){
                        cont ++;
                    }
                }
            }
        }
        board[boxPosition[0]][boxPosition[1]] = cont;
        return 2;
        break;
        default:
        cout<<"Box already shown. Press OK: ";
        cin>>selected;
        break;
    }
    return 0;
}

void FillBoard(){
    srand(time(NULL));
    for(int i = 0; i < minesAmount; i++){
        int x,y;
        do{
            y= rand() % sizeBoard[0];
            x= rand() % sizeBoard[1];
        }while(board[y][x] == 0 || board[y][x] == 10);
            
        board[y][x] = 10;
    }
}

void EmptySector(int y, int x){
    int cont = 0;
    for(int i = 0; i< 8; i++){
        if(y + operations[i][0] >= 0 && y + operations[i][0] < sizeBoard[0]){
            if(x + operations[i][1] >= 0 && x + operations[i][1] < sizeBoard[1]){
                if(board[y+ operations[i][0]][x +operations[i][1]] == 10 || board[y + operations[i][0]][x +operations[i][1]] == 1011){
                       cont ++;
               }
           }
       }
   }
   if (cont == 0){
       board[y][x] = 0;
       for(int i = 0; i < 8; i++){
       if(y + operations[i][0] >= 0 && y + operations[i][0] < sizeBoard[0]){
           if(x + operations[i][1] >= 0 && x + operations[i][1] < sizeBoard[1]){
               if(board[y+ operations[i][0]][x +operations[i][1]] == -1){
                   EmptySector(y+ operations[i][0],x+ operations[i][1]);
                }
            }
        }
    }
    }else{
        board[y][x] = cont;
        return;
    }
}