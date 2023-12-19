#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h> 
#include <stdlib.h>

int hight = 25;
int width = 100;
int ballDegree = -90;

int playerPlatform[3] = {11, 12, 13};
int enemyPlatform[3] = {10, 11, 12};
int platformLength = *(&playerPlatform + 1) - playerPlatform;
int ball[2] = {12, 37};

bool gameover = false; 

void draw();
bool platformOnCoordinates(int *, int);
void movePlatform();
void moveBall();
void bounceTheBall();
void bounceOutOfPlatform(int *);
void chageBallsDegree();
void delay();

int main(){
    int i;
    while (!gameover){
        movePlatform(playerPlatform);
        moveBall();
        draw();
    }

    return 0;
}

bool platformOnCoordinates(int * platform, int yCoordinates){
    bool isOnCoordinates = false;

    for (int i = 0; i < platformLength; i++){
        if(*(platform + i) == yCoordinates){
            isOnCoordinates = true;
        }
    }

    return isOnCoordinates;
}

void moveBall(){
    int absoluteDegree = abs(ballDegree);
    int xStep = ballDegree < 0 ? -1 : 1;
    int yStep = absoluteDegree < 90 ? -1 : absoluteDegree > 90 ? 1 : 0;

    ball[0] = *ball + yStep;
    ball[1] = *(ball + 1) + xStep;
    bounceTheBall();
}

void bounceTheBall(){
    bool ballHitXWall = *(ball + 1) + 1 == 1 || *(ball + 1) + 1 == width - 1;
    bool ballHitYWall = *ball == 1 || *ball == hight - 1;
    bool ballHitPlayerPlatform = *(ball + 1) - 1 == 2 && platformOnCoordinates(playerPlatform, *ball);
    bool ballHitEnemyPlatform = *(ball + 1) + 1 == width - 3 && platformOnCoordinates(enemyPlatform, *ball);

    if(ballHitXWall){
        ballDegree = -ballDegree;
    } else if (ballHitPlayerPlatform){
        bounceOutOfPlatform(playerPlatform);
    } else if (ballHitEnemyPlatform){
        bounceOutOfPlatform(enemyPlatform);
    } else if (ballHitYWall){
        chageBallsDegree();
    }
}

void bounceOutOfPlatform(int * platform){
    if(*ball == *(platform + 1)){ 
        ballDegree = ballDegree < 0 ? 90 : -90;
        return;
    } else { 
        ballDegree = -ballDegree;
        chageBallsDegree();
    }
}

void chageBallsDegree(){
    int absoluteDegree = abs(ballDegree);
    int newDegree = absoluteDegree == 45 ? 135 : 45;
    ballDegree = ballDegree < 0 ? -newDegree : newDegree;
}

void movePlatform(int *platform){
    delay();
    if(kbhit()){
        char keyButton = getch();
        int i = 0;
        int step = keyButton == 'w' || keyButton == 'H' ? -1 : keyButton == 's' || keyButton == 'P' ? 1 : 0;

        if(keyButton == 'x'){
            gameover = true;
        };

        if(step == -1 && *platform == 1 || step == 1 && *(platform + 2) == hight - 2 ){
            return ;
        };

        for (i; i < 3; i++){
            platform[i] = *(platform + i) + step;
        }
    }
}

void delay(){
    int i = 0;
    for (i; i < 25000000; i++){
        i = i;
    }
}

void draw(){
    int i;
    int j;

    char border[] = "*";
    char emptySpace[] =" ";
    char middle[] = "|";
    char newLine[] = "\n";
    char platform[] = "I";
    char circle[] = "o";

    char field[10000] = ""; 
    char* fieldPtr = field;

    for (i = 0; i < hight; i++){
        for (j = 0; j < width; j++){
            if( i == 0 || i == hight - 1 || j == 0 || j == width - 1){
                *fieldPtr = *border;
                fieldPtr++;
            } else if(j == *(ball + 1) && i == *ball){
                *fieldPtr = *circle;
                fieldPtr++;
            }
            else if(j == width/2 && i > 0 && i < hight - 1){
                *fieldPtr = *middle;
                fieldPtr++;
            } else if(j == 2 && platformOnCoordinates(playerPlatform, i)){
                *fieldPtr = *platform;
                fieldPtr++;
            } else if(j == width - 3 && platformOnCoordinates(enemyPlatform, i)){
                *fieldPtr = *platform;
                fieldPtr++;
            }else {
                *fieldPtr = *emptySpace;
                fieldPtr++;
            }
            
        };
        *fieldPtr = *newLine;
        fieldPtr++;
    }

    *fieldPtr = '\0'; // Null-terminate the string manually
    printf("%s", field);
}