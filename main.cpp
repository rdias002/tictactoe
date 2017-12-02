#include<iostream>
using namespace std;

void createGrid(char *xANDo); //Creates the grid for the playing
int acceptPosition(char *xANDo, char player); //Accepts user input for placing the mark
int checkIfWinner(char *xANDo, char player); //Checks if a particular plays won
int cpuPlay(char *xANDo);
template <class A> //A template for checking equality of 3 variables
bool Equal(A a, A b, A c){
    return (a==b)?((a==c)?true:false):false;
}

int main(){
    int gameNumber=0; //For the purpose of who plays first
    int roundNumber,option;
    char xANDo[9]; //Stores the position of all the x's and o's
    char player[]={'X','O'}, playAgain;
    bool cpu=false;
    cout<<"1. Player vs CPU\n2. Player vs Player\nChoose an option: "; //PvP or PvC
    cin>>option;
    switch(option){
    case 1:
        cpu = true;
        break;
    case 2:
        break;
    default:
        cout<<"Invalid Option\n\n";
        goto Start;

    }
    Start:
    for(int i=0;i<9;i++){
        xANDo[i] = i+'0'+1;
    }
    createGrid(xANDo);
    roundNumber=0;
    while(roundNumber<9){
        if(gameNumber%2){
            roundNumber += acceptPosition(xANDo,player[roundNumber%option]);
            if(cpu && roundNumber<9){
                roundNumber += cpuPlay(xANDo);
            }
        }
        else{
            if(cpu){
                roundNumber += cpuPlay(xANDo);
            }
            if(roundNumber<9)
                roundNumber += acceptPosition(xANDo,player[roundNumber%option]);
        }
    }
    cout<<"Play again?(Y/N):";
    cin>>playAgain;
    if(playAgain == 'Y' || playAgain == 'y'){
        gameNumber++;
        goto Start;
    }
}

void createGrid(char *xANDo){
    int squareNumber=0;
    //Clears the screen
    for(int k=0; k<100; k++){
        cout<<endl;
    }
    for(int i=0; i<13; i++){
        cout<<"\t\t\t\t";
        for(int j=0; j<25; j++){
            //For the + sign in the grid
            if((i==4 || i==8)&& (j==8 || j==16))
                cout<<"+";
            //For the - sign in the grid
            else if(i%4==0 && i!=0 && i!=12)
                cout<<"-";
            else{
                //For the | sign in the grid
                if(j%8==0 && j!=0 && j!=24)
                    cout<<"|";
                //For the X or O in the grid
                else if((j+4)%8==0 && (i-2)%4==0){
                    cout<<xANDo[squareNumber++];
                }
                else
                    cout<< " ";
            }
        }
        cout<<endl;
    }
    for(int i=0;i<15;i++)//For space after the grid
        cout<<endl;
}

int acceptPosition(char *xANDo, char player){
    int position;
    cout<<"Enter position for "<<player<<":";
    cin>>position;
    if(xANDo[position-1] != 'X' && xANDo[position-1] != 'O' && position>0 && position<10)
        xANDo[position-1]=player;
    else
        return 0;

    createGrid(xANDo);
    return checkIfWinner(xANDo,player);
}

int checkIfWinner(char *xANDo, char player){
    int ret=0,i;
    for(i=0;i<=6;i++){
        if( (i == 0 || i == 3 || i == 6)    && Equal(xANDo[i],xANDo[i+1],xANDo[i+2]) ) //Positions incremented by 1
            ret = 1;
        if( (i == 2)                        && Equal(xANDo[i],xANDo[i+2],xANDo[i+4]) ) //Positions incremented by 2
            ret = 1;
        if( (i == 0 || i == 1 || i == 2)    && Equal(xANDo[i],xANDo[i+3],xANDo[i+6]) ) //Positions incremented by 3
            ret = 1;
        if( (i == 0)                        && Equal(xANDo[i],xANDo[i+4],xANDo[i+8]) ) //Positions incremented by 4
            ret = 1;
    }
    if(ret){
        cout<<player<<" wins!!!\n\n\n";
        return 5;
    }
    return 1;
}

int cpuPlay(char *xANDo){

    return checkIfWinner(xANDo, 'O');
}
