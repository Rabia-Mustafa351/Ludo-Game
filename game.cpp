//============================================================================
// Name        : .cpp
// Author      : Rabia Mustafa
//	Roll no    : 20i-1853
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
//#include "Board.h"
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include <cstdlib>
using namespace std;
 bool pieceSelected=false;
int GetRand = 0;
bool work = true;
int turn=-1;
 int playerPos[4][4]={ {-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}};
int movePiece=-1;
int defaultPlayerPos[4][4][2]={
                            {{802,630},{862,630},{802,560},{862,560}}, //1 turn=0
                            {{802,195},{862,195},{802,125},{862,125}}, //2 turn=1
                            {{370,125},{430,125},{370,195},{430,195}},//3 turn=2
                            {{370,630},{430,630},{370,560},{430,560}}//4 turn=3
                            };

int array_X[56]={670,670,670,670,670,
                717,765,813,861,909,957,957,
                957,909,861,813,765,717,
                670,670,670,670,670,670,623,
                574,574,574,574,574,574,
                525,478,431,382,334,284,284,
                284,334,382,437,478,525,
                574,574,574,574,574,574,
                623,670};

               //using array for location
int array_Y[56]={ 670,622,574,526,478,
                  430,430,430,430,430,430,382,
                  334,334,334,334,334,334,
                  285,237,189,141,93,45,45,
                  45 ,93,141,189,237,285,
                  334,334,334,334,334,334,382,
                  430,430,430,430,430,430,
                  478,526,574,622,670,718,
                  718,718 };

  int homeRun[4][5][2]= { {{623,670},{623,622},{623,574},{623,526},{623,478}},
                            {{909,382},{861,382},{813,382},{765,382},{717,382}},
                            {{623,93},{623,141},{623,189},{623,237},{623,285}},
                            {{334,382},{382,382},{431,382},{478,382},{525,382}}
                          };

    int startLoc[4]={0,13,26,39};

    int endLoc[4]={50,11,24,37};
    int playerColor[4]={ YELLOW_GREEN ,STEEL_BLUE,DARK_GREEN,PERU  };

    void drawPiece(int trn, int piece, int oldLoc, bool isOldLocHomeRun, int newLoc, bool isNewLocHomeRun){
      cout<<"trn="<<trn<<" piece="<<piece<<" oldLoc="<<oldLoc<<" isOldLocHomeRun="<<isOldLocHomeRun<<" newLoc="<<newLoc<<" isNewLocHomeRun="<<isNewLocHomeRun<<endl;
        if(isOldLocHomeRun==false){
          if(oldLoc==-1){
            //defaultPlayerPos
            DrawCircle(defaultPlayerPos[trn][piece][0], defaultPlayerPos[trn][piece][1], 20, colors[WHITE]); //693 ....261
          }
          else {
            DrawCircle(array_X[oldLoc], array_Y[oldLoc], 20, colors[WHITE]);  //693 ....261
          }
        }
        else{
          DrawCircle(homeRun[trn][oldLoc][0], homeRun[trn][oldLoc][1], 20, colors[WHITE]); //693 ....261
        }
        if (isNewLocHomeRun==false){
          if (newLoc==-1){
            DrawCircle(defaultPlayerPos[trn][piece][0], defaultPlayerPos[trn][piece][1], 20, colors[playerColor[trn]]); //693 ....261
            Torus2d(defaultPlayerPos[trn][piece][0], defaultPlayerPos[trn][piece][1], 15, 800, 10, 7, 8, colors[WHITE]);
          }
          else {
            DrawCircle(array_X[newLoc], array_Y[newLoc], 20, colors[playerColor[trn]]); //693 ....261
            Torus2d(array_X[newLoc], array_Y[newLoc], 15, 800, 10, 7, 8, colors[WHITE]);
          }
        }
        else {
          DrawCircle(homeRun[trn][newLoc][0], homeRun[trn][newLoc][1], 20, colors[playerColor[trn]]); //693 ....261
          Torus2d(homeRun[trn][newLoc][0], homeRun[trn][newLoc][1], 15, 800, 10, 7, 8, colors[WHITE]);
        }
    }

void drawMove(int diceVal){
  if (pieceSelected==false){
    return;
  }
  if(playerPos[turn][movePiece]==-1){
    int oldPos=-1;
    playerPos[turn][movePiece]=startLoc[turn]+diceVal;
    drawPiece( turn, movePiece ,oldPos ,  false, playerPos[turn][movePiece],  false);
  }
  else {
    drawPiece( turn, movePiece ,playerPos[turn][movePiece] ,  false, playerPos[turn][movePiece]+diceVal,  false);
    playerPos[turn][movePiece]+=diceVal;
  }
  pieceSelected=false;
}
void redrawPieces(){
  for (int trn = 0; trn < 4; trn++) {
    for (int piece = 0; piece < 4; piece++){
        drawPiece(trn,piece,playerPos[trn][piece],false,playerPos[trn][piece],false); //to do:fixthis when implementing home run pieces
    }
  }

}
void logPieces(){
  for (int trn = 0; trn < 4; trn++) {
    for (int piece = 0; piece < 4; piece++){
      cout<<"Player"<<trn<<" piece "<<piece<<" = "<<playerPos[trn][piece]<<endl;
    }
    cout<<endl;
  }
}

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void dice(int q) {


    if (q == 1)
    {
        DrawCircle(175, 75, 5, colors[BLACK]); //ceter for 1 }
    }
    else if (q == 2) {
        //for 2
        DrawCircle(163, 75, 5, colors[BLACK]); //ceter for 2
        DrawCircle(187, 75, 5, colors[BLACK]); //ceter for 2
    }


    else if (q == 3)
    {
        //for 3
        DrawCircle(162, 68, 6, colors[BLACK]);  //downward
        DrawCircle(188, 68, 6, colors[BLACK]);  //downward
        DrawCircle(175, 84, 6, colors[BLACK]); //ceter for 3


    }

    else if (q == 4)
    {
        //for 4
        DrawCircle(160, 65, 5, colors[BLACK]);  //downward
        DrawCircle(190, 65, 5, colors[BLACK]);  //downward
        DrawCircle(160, 85, 5, colors[BLACK]);  //upward
        DrawCircle(190, 85, 5, colors[BLACK]);  //upward

    }
    else if (q == 5)
    {
        //for 5
        DrawCircle(160, 65, 5, colors[BLACK]);  //downward
        DrawCircle(190, 65, 5, colors[BLACK]);  //downward
        DrawCircle(175, 75, 5, colors[BLACK]); //ceter for 1
        DrawCircle(160, 85, 5, colors[BLACK]);  //upward
        DrawCircle(190, 85, 5, colors[BLACK]);  //upward


    }


    else if (q == 6)
    {
        //for 6
        DrawCircle(161, 62, 5, colors[BLACK]);  //downward
        DrawCircle(189, 62, 5, colors[BLACK]);  //downward
        DrawCircle(161, 75, 5, colors[BLACK]); //ceter for 1
        DrawCircle(189, 75, 5, colors[BLACK]); //ceter for 1
        DrawCircle(161, 88, 5, colors[BLACK]);  //upward
        DrawCircle(189, 88, 5, colors[BLACK]);  //upward
    }
}

bool open;

int playerMove(){
  int var1 = 0, var2 = 0, var3 = 0;
  int  score = 0;

      if ( work == true) {//first move

          DrawRectangle(4, 110 , 170, 50, colors[ WHITE]);
          switch(turn){

          case 0:
             DrawString(4, 120 , "PLAYER_1 turn", colors[ORANGE_RED]);
             break;
          case 1:
             DrawString(4, 120 , "PLAYER_2 turn", colors[ORANGE_RED]);
             break;
          case 2:
              DrawString(4, 120 , "PLAYER_3 turn", colors[ORANGE_RED]);
              break;
          case 3:
              DrawString(4, 120 , "PLAYER_4 turn", colors[ORANGE_RED]);
              break;
          }

          var1 = rand() % 6 + 1;
          DrawRoundRect(150, 50, 50, 50, colors[WHITE], 10);
          dice(var1);
          string scores;
          ostringstream convert;
          convert << var1;
          scores = convert.str();
          DrawRectangle(10, 50 , 70, 40, colors[ WHITE]);
          DrawString(10, 60, scores, colors[BLACK]);  ////display on canvas

        }
    work = false;
    return var1;

}


void displayDiceNumber(int n) {


    string scores;
    int l = n;

    ostringstream convert;
    convert << l;
    scores = convert.str();

    DrawString(70, 800, scores, colors[ORANGE_RED]);
//PALE_VIOLET_RED ........pink
    /*  DrawString( 70, 800, scores , colors[ORANGE_RED]);
        DrawString( 50, 800, "Score=", colors[ORANGE_RED]);

    */
}
void pieces1(){
// for player 1
DrawCircle(802, 560, 20, colors[YELLOW_GREEN]);
DrawCircle(862, 560, 20, colors[YELLOW_GREEN]);    // {802,630},{862,630},{802,560},{862,560}
//upper  circles
DrawCircle(802, 630, 20, colors[YELLOW_GREEN]);
DrawCircle(862, 630, 20, colors[YELLOW_GREEN]);

//torus indise yellow circle
Torus2d(802, 560, 15, 800, 10, 7, 8, colors[WHITE]);
Torus2d(862, 560, 15, 800, 10, 7, 8, colors[WHITE]);
Torus2d(802, 630, 15, 800, 10, 7, 8, colors[WHITE]);
Torus2d(862, 630, 15, 800, 10, 7, 8, colors[WHITE]);
 // for piece 1
string scores;
int l = 1;
ostringstream convert;
convert << l;
scores = convert.str();

DrawString(795, 623, scores, colors[RED]);
//for piece 2
string square2;
int m = 2;
ostringstream box2;
box2 << m;
square2 = box2.str();

DrawString(855, 623, square2, colors[RED]);
//for piece 3
string square3;
int n = 3;
ostringstream box3;
box3 << n;
square3 = box3.str();

DrawString(795, 553 , square3, colors[RED]);
// for piece 4
string square4;
int o = 4;

ostringstream box4;
box4 << o;
square4 = box4.str();

DrawString(855, 553, square4, colors[RED]);

/*if(movePiece==true){

    DrawCircle (array_X[pos ] ,array_Y[pos], 20, colors[YELLOW_GREEN]);
    Torus2d (array_X[pos] ,array_Y[pos], 15, 800, 10, 7, 8, colors[WHITE]);
    cout<<"Player1 Piece= "<<pos<<endl;
}
    movePiece=false; */


/*DrawCircle (array_X[pos ] ,array_Y[pos], 20, colors[YELLOW_GREEN]);
Torus2d (array_X[pos] ,array_Y[pos], 15, 800, 10, 7, 8, colors[WHITE]);
                // open=false;
                cout<<"Player1 Piece0= "<<pos<<endl;*/

}
void pieces2(){
// for player 1
//lower to circles in BLUE
DrawCircle(802, 125, 20, colors[STEEL_BLUE]);   //2 {802,195},{862,195},{802,125},{802,195}//4 {370,630},{430,630},{370,560},{430,560},
DrawCircle(862, 125, 20, colors[STEEL_BLUE]);
//upper  circles
DrawCircle(802, 195, 20, colors[STEEL_BLUE]);   // YELLOW_GREEN , STEEL_BLUE ,PERU
DrawCircle(862, 195, 20, colors[STEEL_BLUE]);
//torus indise BLUE circle
Torus2d(802, 125, 15, 800, 10, 7, 8, colors[WHITE]);
Torus2d(862, 125, 15, 800, 10, 7, 8, colors[WHITE]);
Torus2d(802, 195, 15, 800, 10, 7, 8, colors[WHITE]);
Torus2d(862, 195, 15, 800, 10, 7, 8, colors[WHITE]);
 // for piece 1
string square1;
int l = 1;
ostringstream box1;
box1 << l;
square1 = box1.str();
DrawString(855, 187, square1, colors[RED]);
//for piece 2
string square2;
int m = 2;
ostringstream box2;
box2 << m;
square2 = box2.str();

DrawString(795, 187, square2, colors[RED]);
//for piece 3
string square3;
int n = 3;
ostringstream box3;
box3 << n;
square3 = box3.str();

DrawString(855, 120 , square3, colors[RED]);
// for piece 4
string square4;
int o = 4;
ostringstream box4;
box4 << o;
square4 = box4.str();

DrawString(795, 120, square4, colors[RED]);

/* if(MovePiece2==true){

    DrawCircle (array_X[pos2 ] ,array_Y[pos2], 20, colors[YELLOW_GREEN]);
    Torus2d (array_X[pos2] ,array_Y[pos2], 15, 800, 10, 7, 8, colors[WHITE]);
    cout<<"PLAYER_2 Piece= "<<pos2<<endl;
}
    MovePiece2=false;   */



}

void pieces3(){
// for player 1
//lower to circles in BLUE
//lower to circles in GREEN
DrawCircle(370, 125, 20, colors[DARK_GREEN]);  // {370,125},{430,125},{370,430},{430,195}
DrawCircle(430, 125, 20, colors[DARK_GREEN]);
  //upper  circles
DrawCircle(370, 195, 20, colors[DARK_GREEN]);
DrawCircle(430, 195, 20, colors[DARK_GREEN]); //693 ....261
  //torus indise GREEN circle
Torus2d(370, 125, 15, 800, 10, 7, 8, colors[WHITE]);
Torus2d(430, 125, 15, 800, 10, 7, 8, colors[WHITE]);
Torus2d(370, 195, 15, 800, 10, 7, 8, colors[WHITE]);
Torus2d(430, 195, 15, 800, 10, 7, 8, colors[WHITE]);
 // for piece 1
string square1;
int l = 1;
ostringstream box1;
box1 << l;
square1 = box1.str();
DrawString(425,187, square1, colors[RED]);
// for piece 2
string square2;
int m = 2;
ostringstream box2;
box2 << m;
square2 = box2.str();

DrawString(365, 187, square2, colors[RED]);
//for piece 3
string square3;
int n = 3;
ostringstream box3;
box3 << n;
square3 = box3.str();

DrawString(425, 117 , square3, colors[RED]);
// for piece 4
string square4;
int o = 4;
ostringstream box4;
box4 << o;
square4 = box4.str();

DrawString(365, 117, square4, colors[RED]);


}

void pieces4(){
      // for player 1
      //lower to circles in CHOCOLATE
      DrawCircle(370 , 560, 20, colors[PERU]);   // {370,630},{430,630},{370,560},{430,560},
      DrawCircle(430, 560, 20, colors[PERU]);
      //upper  circles
      DrawCircle(370, 630, 20, colors[PERU]);
      DrawCircle(430, 630, 20, colors[PERU]);
      //torus indise CHOCOLATE circle
      Torus2d(370, 560, 15, 800, 10, 7, 8, colors[WHITE]);
      Torus2d(430, 560, 15, 800, 10, 7, 8, colors[WHITE]);
      Torus2d(370, 630, 15, 800, 10, 7, 8, colors[WHITE]);
      Torus2d(430, 630, 15, 800, 10, 7, 8, colors[WHITE]);
       // for piece 1
      string square1;
      int l = 1;
      ostringstream box1;
      box1 << l;
      square1 = box1.str();//553..623
      DrawString(425,553, square1, colors[RED]);
      // for piece 2
      string square2;
      int m = 2;
      ostringstream box2;
      box2 << m;
      square2 = box2.str();

      DrawString(365, 553, square2, colors[RED]);
      //for piece 3
      string square3;
      int n = 3;
      ostringstream box3;
      box3 << n;
      square3 = box3.str();
      DrawString(425, 623 , square3, colors[RED]);
      // for piece 4
      string square4;
      int o = 4;
      ostringstream box4;
      box4 << o;
      square4 = box4.str();

      DrawString(365, 623, square4, colors[RED]);
/*      if(MovePiece4==true){

      DrawCircle (array_X[pos4] ,array_Y[pos4], 20, colors[YELLOW_GREEN]);
      Torus2d (array_X[pos4] ,array_Y[pos4], 15, 800, 10, 7, 8, colors[WHITE]);
          cout<<"Player4 Piece= "<<pos4<<endl;
        }
          MovePiece4=false;  */


}




void DrawDice() {



    DrawSquare(140, 40, 70, colors[GREEN]);
    // DrawSquare( 50, 50,50,colors[WHITE]);
    DrawRoundRect(150, 50, 50, 50, colors[WHITE], 10);
    cout<<"666"<<endl;



}
static int moveAnimation=0,moveBorder=0;
    bool check1=true;

void Loading(int i){

//     }
      DrawRectangle(150, 170+50+20, 720, 600, colors[SILVER]);//back ground
      DrawRectangle(170, 200+50+20, 680, 550, colors[BLACK]);//background
//L
      DrawRectangle(200, 600, 110, 20, colors[BLUE]);
      DrawRectangle(200, 600, 20, 150, colors[PINK]);
//U
      DrawRectangle(330, 600, 20, 130, colors[BLUE]);
      DrawRectangle(440, 600, 20, 130, colors[BLUE]);
      DrawRectangle(330, 600, 130, 20, colors[BLUE]);
//D
      DrawRectangle(480, 600, 20, 130, colors[BLUE]);
      DrawRectangle(590, 600, 20, 110, colors[BLUE]);
      DrawRectangle(480, 600, 130, 20, colors[BLUE]);
      DrawRectangle(480, 710, 110, 20, colors[BLUE]);
//O
      DrawRectangle(630, 600, 130, 20, colors[BLUE]);
      DrawRectangle(630, 710, 130, 20, colors[BLUE]);
      DrawRectangle(630, 600, 20, 130, colors[BLUE]);
      DrawRectangle(760, 600, 20, 130, colors[BLUE]);





  //Right side
    DrawRectangle(980, 0, 10, 1022, colors[LIGHT_SKY_BLUE]);
    DrawRectangle(960, 0, 10, 1022, colors[RED]);
    DrawRectangle(940, 0, 10, 1022, colors[GREEN]);
    
    DrawRectangle(980, 600+i, 10, 30, colors[SKY_BLUE]);//1st
    DrawRectangle(960, 160+i, 10, 30, colors[LIGHT_PINK]);//2nd
    DrawRectangle(940, 0+i, 10, 30, colors[LIGHT_GREEN]);//3rd

    DrawRectangle(980, (-400)+i, 10, 30, colors[SKY_BLUE]);//1st
    DrawRectangle(960, (-60)+i, 10, 30, colors[LIGHT_PINK]);//2nd
    DrawRectangle(940, (-800)+i, 10, 30, colors[LIGHT_GREEN]);//3rd

  //left side
    DrawRectangle(20, 0, 10, 1022, colors[LIGHT_SKY_BLUE]);
    DrawRectangle(40, 0, 10, 1022, colors[RED]);
    DrawRectangle(60, 0, 10, 1022, colors[GREEN]);

    DrawRectangle(20, 600+i, 10, 30, colors[SKY_BLUE]);//1st
    DrawRectangle(40, 160+i, 10, 30, colors[LIGHT_PINK]);//2nd
    DrawRectangle(60, 0+i, 10, 30, colors[LIGHT_GREEN]);//3rd

    DrawRectangle(20, (-400)+i, 10, 30, colors[SKY_BLUE]);//1st
    DrawRectangle(40, (-60)+i, 10, 30, colors[LIGHT_PINK]);//2nd
    DrawRectangle(60, (-800)+i, 10, 30, colors[LIGHT_GREEN]);//3rd


  //Up side
    DrawRectangle(0, 980, 1020, 10, colors[LIGHT_SKY_BLUE]);
    DrawRectangle(0, 960, 1020, 10, colors[RED]);
    DrawRectangle(0, 940, 1020, 10, colors[GREEN]);

    DrawRectangle(600+i, 980, 30, 10, colors[SKY_BLUE]);//1st
    DrawRectangle(100+i, 960, 30, 10, colors[LIGHT_PINK]);//1st
    DrawRectangle(0+i, 940, 30, 10, colors[LIGHT_GREEN]);//1st

   DrawRectangle((-400)+i, 980, 30, 10, colors[SKY_BLUE]);//1st
    DrawRectangle((-60)+i, 960, 30, 10, colors[LIGHT_PINK]);//1st
    DrawRectangle((-800)+i, 940, 30, 10, colors[LIGHT_GREEN]);//1st


  //Down side
    DrawRectangle(0, 20, 1020, 10, colors[LIGHT_SKY_BLUE]);
    DrawRectangle(0, 40, 1020, 10, colors[RED]);
    DrawRectangle(0, 60, 1020, 10, colors[GREEN]);

    DrawRectangle(600+i, 20, 30, 10, colors[SKY_BLUE]);//1st
    DrawRectangle(100+i, 40, 30, 10, colors[LIGHT_PINK]);//1st
    DrawRectangle(0+i, 60, 30, 10, colors[LIGHT_GREEN]);//1st

    DrawRectangle((-400)+i, 20, 30, 10, colors[SKY_BLUE]);//1st
    DrawRectangle((-60)+i, 40, 30, 10, colors[LIGHT_PINK]);//1st
    DrawRectangle((-800)+i, 60, 30, 10, colors[LIGHT_GREEN]);//1st

//loading side
//Torus2d(int x /*Starting position x*/, int y /*Starting position Y*/,
  //float angle, // starting angle in degrees
  //float length,           // length of arc in degrees, >0
 // float radius,           // inner radius, >0
 // float width,            // width of torus, >0
 // unsigned int samples,   // number of circle samples, >=3
  //float *color)
    Torus2d(500, 405, 15, 600+i, 100, 7, 10, colors[WHITE]);
    check1 = false;
}


void TakingName(int j){
    //DrawRectangle(825, 0, 200, 850, colors[WHITE]);// Border
    //DrawRectangle(825, 0, 50, 850, colors[BLACK]);// Border

    for(int j=-50000;j<50000;j+=50){
      //DrawRectangle(850, 25+j+moveBorder, 25, 25, colors[RED]);// Border
      DrawRectangle(900, 25+j+moveBorder, 25, 25, colors[WHITE]);// Border
      DrawRectangle(950, 25+j+moveBorder, 25  , 25, colors[WHITE]);// Border
      DrawRectangle(1000, 25+j+moveBorder, 25, 25, colors[WHITE]);// Border

    }
    for(int j=-50000;j<50000;j+=50){
      DrawRectangle(975, j+moveBorder, 25, 25, colors[WHITE]);// Border
      DrawRectangle(925, j+moveBorder, 25, 25, colors[WHITE]);// Border
      DrawRectangle(875, j+moveBorder, 25, 25, colors[WHITE]);// Border
      //DrawRectangle(825, j+moveBorder, 25, 25, colors[RED]);// Border
    }
    //for Left side
  //  DrawRectangle(0, 0, 200, 850, colors[WHITE]);// Border
  //  DrawRectangle(150, 0, 50, 850, colors[BLACK]);// Border

    for(int j=-50000;j<50000;j+=50){
      //DrawRectangle(850, 25+j+moveBorder, 25, 25, colors[RED]);// Border
      DrawRectangle(0, 25+j+moveBorder, 25, 25, colors[WHITE]);// Border
      DrawRectangle(50, 25+j+moveBorder, 25 , 25, colors[WHITE]);// Border
      DrawRectangle(100, 25+j+moveBorder, 25, 25, colors[WHITE]);// Border

    }
    for(int j=-50000;j<50000;j+=50){
      DrawRectangle(25, j+moveBorder, 25, 25, colors[WHITE]);// Border
      DrawRectangle(75, j+moveBorder, 25, 25, colors[WHITE]);// Border
      DrawRectangle(125, j+moveBorder, 25, 25, colors[WHITE]);// Border
      //DrawRectangle(175, j+moveBorder, 25, 25, colors[RED]);// Border
    }

}

void Menu(){
        DrawRectangle(150, 90, 720, 850, colors[SILVER]);//back ground
      DrawRectangle(170, 130, 680, 800, colors[BLACK]);//background
//L
      DrawRectangle(200, 770, 110, 20, colors[BLUE]);
      DrawRectangle(200, 770, 20, 150, colors[PINK]);
//U
      DrawRectangle(330, 770, 10, 65, colors[BLUE]);
      DrawRectangle(395, 770, 10, 65, colors[BLUE]);
      DrawRectangle(330, 770, 65, 10, colors[BLUE]);
//D
      DrawRectangle(420, 770, 10, 65, colors[BLUE]);
      DrawRectangle(485, 770, 10, 55, colors[BLUE]);
      DrawRectangle(420, 770, 65, 10, colors[BLUE]);
      DrawRectangle(420, 830, 65, 10, colors[BLUE]);
//O
      DrawRectangle(500, 770, 65, 10, colors[BLUE]);
      DrawRectangle(500,  830, 65, 10, colors[BLUE]);
      DrawRectangle(500, 770, 10, 65, colors[BLUE]);
      DrawRectangle(565, 770, 10, 70, colors[BLUE]);

//M
      DrawRectangle(480, 600, 20, 130, colors[BLUE]);
      DrawRectangle(580, 600, 20, 130, colors[BLUE]);
      DrawLine(483, 730, 540, 680, 10, colors[BLUE]);
      DrawLine(540, 680, 580, 730, 10, colors[BLUE]);

//E
      DrawRectangle(620, 600, 10, 65, colors[BLUE]);
      DrawRectangle(620, 625, 65, 10, colors[BLUE]);
      DrawRectangle(620, 600, 65, 10, colors[BLUE]);
      DrawRectangle(620, 660, 65, 10, colors[BLUE]);
//N
      DrawRectangle(700, 600, 10, 70, colors[BLUE]);
      DrawRectangle(750, 600, 10, 70, colors[BLUE]);
      DrawLine(705, 670, 750, 610, 10, colors[BLUE]);

//U
      DrawRectangle(770, 600, 10, 70, colors[BLUE]);
      DrawRectangle(820, 600, 10, 70, colors[BLUE]);
      DrawRectangle(770, 600, 50, 10, colors[BLUE]);

    DrawString( 440, 500, "New Game", colors[RED]);
    DrawString( 440, 470, "High Scores", colors[RED]);
    DrawString( 440, 440, "Help", colors[RED]);
    DrawString( 440, 410, "Exit", colors[RED]);

}


void Help(){
        DrawRectangle(150, 90, 720, 850, colors[SILVER]);//back ground
      DrawRectangle(170, 130, 680, 800, colors[BLACK]);//background
//L
      DrawRectangle(200, 770, 110, 20, colors[BLUE]);
      DrawRectangle(200, 770, 20, 150, colors[PINK]);
//U
      DrawRectangle(330, 770, 10, 65, colors[BLUE]);
      DrawRectangle(395, 770, 10, 65, colors[BLUE]);
      DrawRectangle(330, 770, 65, 10, colors[BLUE]);
//D
      DrawRectangle(420, 770, 10, 65, colors[BLUE]);
      DrawRectangle(485, 770, 10, 55, colors[BLUE]);
      DrawRectangle(420, 770, 65, 10, colors[BLUE]);
      DrawRectangle(420, 830, 65, 10, colors[BLUE]);
//O
      DrawRectangle(500, 770, 65, 10, colors[BLUE]);
      DrawRectangle(500,  830, 65, 10, colors[BLUE]);
      DrawRectangle(500, 770, 10, 65, colors[BLUE]);
      DrawRectangle(565, 770, 10, 70, colors[BLUE]);

//H
      DrawRectangle(480, 600, 20, 130, colors[BLUE]);
      DrawRectangle(580, 600, 20, 130, colors[BLUE]);
      DrawRectangle(480, 665, 120, 10, colors[BLUE]);
//E
      DrawRectangle(620, 600, 10, 65, colors[BLUE]);
      DrawRectangle(620, 625, 65, 10, colors[BLUE]);
      DrawRectangle(620, 600, 65, 10, colors[BLUE]);
      DrawRectangle(620, 660, 65, 10, colors[BLUE]);
//L
      DrawRectangle(690, 600, 10, 70, colors[BLUE]);
      DrawRectangle(690, 600, 60, 10, colors[BLUE]);
//P
      DrawRectangle(750, 600, 10, 70, colors[BLUE]);
      DrawRectangle(750, 660, 50, 10, colors[BLUE]);
      DrawRectangle(750, 630, 50, 10, colors[BLUE]);
      DrawRectangle(790, 630, 10, 40, colors[GREEN]);
    
     DrawString( 440, 500, "Press Spacebar to roll the Dice", colors[RED]);

}




/*
 * Main Canvas drawing function.
 * */
 //Board *b;
void GameDisplay()/**/ {
    // set the background color using function glClearColor.
    // to change the background play with the red, green and blue values below.
    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
    cout<<"555"<<endl;

 if(moveAnimation<1000){
  glClearColor(0/*Red Component*/, 0, //148.0/255/*Green Component*/,
    0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
    glClear (GL_COLOR_BUFFER_BIT); //Update the colors
    Loading(moveAnimation);
    check1 =false;
}
else if(check1==false){
  glClearColor(1/*Red Component*/, 0, //148.0/255/*Green Component*/,
    1.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
    glClear (GL_COLOR_BUFFER_BIT); //Update the colors
    Menu();
    check1=true;
}
else{
    glClearColor(0.75/*Red Component*/, 1,  //148.0/255/*Green Component*/,
        1/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT); //Update the colors
    //Fire Gun
      //////////second code
      //HOME BOXES
      //  DrawRoundRect(123, 144, 40, 20, colors[GREEN], 10);
    DrawSquare(261, 20, 720, colors[WHITE]); //white square
    DrawSquare(261, 452, 288, colors[CHOCOLATE]);  /// color for piece PERU
    DrawSquare(261, 20, 288, colors[GREEN]);
    DrawSquare(693, 452, 288, colors[YELLOW]);
    DrawSquare(693, 20, 288, colors[BLUE]);
    //inner square for path on left side
    //2nd
    DrawSquare(309, 404, 48, colors[CHOCOLATE]);
    DrawSquare(309, 356, 48, colors[CHOCOLATE]);
    //3rd
    DrawSquare(357, 356, 48, colors[CHOCOLATE]);
    DrawSquare(357, 308, 48, colors[GRAY]);
    //4th
    DrawSquare(405, 356, 48, colors[CHOCOLATE]);
    //2nd
    DrawSquare(453, 356, 48, colors[CHOCOLATE]);
    //3rd
    DrawSquare(501, 356, 48, colors[CHOCOLATE]);
    //triangle for winnig
    DrawTriangle(621, 380, 549, 452, 549, 308, colors[CHOCOLATE]);
    //inner square for path on right side
    DrawSquare(693, 356, 48, colors[BLUE]);
    //2nd
    DrawSquare(741, 356, 48, colors[BLUE]);
    //3rd
    DrawSquare(789, 356, 48, colors[BLUE]);
    //4th
    DrawSquare(837, 356, 48, colors[BLUE]);
    DrawSquare(837, 404, 48, colors[GRAY]);
    //2nd
    DrawSquare(885, 308, 48, colors[BLUE]);
    DrawSquare(885, 356, 48, colors[BLUE]);
    //triangle for winnig
    DrawTriangle(621, 380, 693, 452, 693, 308, colors[BLUE]);
    //squares for path downward
    //first 2
    DrawSquare(597, 68, 48, colors[GREEN]);
    DrawSquare(549, 68, 48, colors[GREEN]);
    //3rd
    DrawSquare(597, 116, 48, colors[GREEN]);
    //4th
    DrawSquare(597, 164, 48, colors[GREEN]);
    DrawSquare(645, 116, 48, colors[GRAY]);
    //5th
    DrawSquare(597, 212, 48, colors[GREEN]);
    //6th
    DrawSquare(597, 260, 48, colors[GREEN]);
    //triangle for winnig
    DrawTriangle(621, 380, 549, 308, 693, 308, colors[GREEN]);
    //inner square for path on upward
    DrawSquare(597, 452, 48, colors[YELLOW]);
    // 2nd
    DrawSquare(597, 500, 48, colors[YELLOW]);
    //3rd
    DrawSquare(597, 548, 48, colors[YELLOW]);
    //4th
    DrawSquare(597, 596, 48, colors[YELLOW]);
    DrawSquare(549, 596, 48, colors[GRAY]);


    //5th  .......starting square
    DrawSquare(645, 644, 48, colors[YELLOW]);
    DrawSquare(597, 644, 48, colors[YELLOW]);
    //triangle for winnig
    DrawTriangle(621, 380, 549, 452, 693, 452, colors[YELLOW]);



    //horizontal line inside path left 2
    DrawRectangle(261, 356, 288, 3, colors[BLACK]);
    DrawRectangle(261, 404, 288, 3, colors[BLACK]);

    //horizontal line inside path left 3
    DrawRectangle(693, 356, 288, 3, colors[BLACK]);
    DrawRectangle(693, 404, 288, 3, colors[BLACK]);


    //horizontal line inside path left 1
    DrawRectangle(261, 452, 288, 3, colors[BLACK]);
    DrawRectangle(261, 308, 288, 3, colors[BLACK]);

    //horizontal line inside path left 4
    DrawRectangle(693, 452, 288, 3, colors[BLACK]);
    DrawRectangle(693, 308, 288, 3, colors[BLACK]);


    //Boxing line left
    DrawRectangle(309, 308, 3, 144, colors[BLACK]);
    DrawRectangle(357, 308, 3, 144, colors[BLACK]);
    DrawRectangle(405, 308, 3, 144, colors[BLACK]);
    DrawRectangle(453, 308, 3, 144, colors[BLACK]);
    DrawRectangle(501, 308, 3, 144, colors[BLACK]);
    DrawRectangle(549, 308, 3, 144, colors[BLACK]);
    //Boxing line left  RIGHT
    DrawRectangle(693, 308, 3, 144, colors[BLACK]);
    DrawRectangle(741, 308, 3, 144, colors[BLACK]);
    DrawRectangle(789, 308, 3, 144, colors[BLACK]);
    DrawRectangle(837, 308, 3, 144, colors[BLACK]);
    DrawRectangle(885, 308, 3, 144, colors[BLACK]);
    DrawRectangle(933, 308, 3, 144, colors[BLACK]);
    //center line  upward 0n path
    DrawRectangle(549, 452, 3, 288, colors[BLACK]);
    DrawRectangle(597, 452, 3, 288, colors[BLACK]);
    DrawRectangle(645, 452, 3, 288, colors[BLACK]);
    DrawRectangle(693, 452, 3, 288, colors[BLACK]);
    //center line downward on path
    DrawRectangle(549, 20, 3, 288, colors[BLACK]);
    DrawRectangle(597, 20, 3, 288, colors[BLACK]);
    DrawRectangle(645, 20, 3, 288, colors[BLACK]);
    DrawRectangle(693, 20, 3, 288, colors[BLACK]);
    //Boxing line up
    DrawRectangle(549, 68, 144, 3, colors[BLACK]);
    DrawRectangle(549, 116, 144, 3, colors[BLACK]);
    DrawRectangle(549, 164, 144, 3, colors[BLACK]);
    DrawRectangle(549, 212, 144, 3, colors[BLACK]);
    DrawRectangle(549, 260, 144, 3, colors[BLACK]);
    DrawRectangle(549, 308, 144, 3, colors[BLACK]);
    //Boxing line down
    DrawRectangle(549, 452, 144, 3, colors[BLACK]);
    DrawRectangle(549, 500, 144, 3, colors[BLACK]);
    DrawRectangle(549, 548, 144, 3, colors[BLACK]);
    DrawRectangle(549, 596, 144, 3, colors[BLACK]);
    DrawRectangle(549, 644, 144, 3, colors[BLACK]);
    DrawRectangle(549, 692, 144, 3, colors[BLACK]);
    //  FOR CHOCOLATE CIRCLE
    DrawCircle(400, 595, 98, colors[WHITE]);

    //FOR GREEN CIRCLE
    DrawCircle(400, 160, 98, colors[WHITE]);
      //torus indise GREEN circle
    Torus2d(370, 125, 15, 800, 10, 7, 8, colors[WHITE]);
    Torus2d(430, 125, 15, 800, 10, 7, 8, colors[WHITE]);
    Torus2d(370, 195, 15, 800, 10, 7, 8, colors[WHITE]);
    Torus2d(430, 195, 15, 800, 10, 7, 8, colors[WHITE]);
       //FOR BLUE CIRCLE
    DrawCircle(832, 160, 98, colors[WHITE]);




    //FOR YELLOW CIRCLE
    DrawCircle(832, 595, 98, colors[WHITE]);
  //  pieces1();

  /*  DrawCircle(802, 560, 20, colors[YELLOW_GREEN]);
    DrawCircle(862, 560, 20, colors[YELLOW_GREEN]);
    //upper  circles
    DrawCircle(802, 630, 20, colors[YELLOW_GREEN]);
    DrawCircle(862, 630, 20, colors[YELLOW_GREEN]);

    //torus indise yellow circle
    Torus2d(802, 560, 15, 800, 10, 7, 8, colors[WHITE]);
    Torus2d(862, 560, 15, 800, 10, 7, 8, colors[WHITE]);
    Torus2d(802, 630, 15, 800, 10, 7, 8, colors[WHITE]);
    Torus2d(862, 630, 15, 800, 10, 7, 8, colors[WHITE]);
    //lower to circles in yellow
    // for displayig number on Piece0

        string scores;
        int l = 1;

        ostringstream convert;
        convert << l;
        scores = convert.str();

        DrawString(795, 62, scores, colors[BLACK]);
  */
    //Making DICE
       //  DrawSquare( 25, 700,48,colors[GRAY]);
    //  int l=dice();
    /*  string scores;
       ostringstream convert;
       convert<<l;
       scores=convert.str();*/

    DrawDice();

  //  player_1();
    // pieces1();
    // pieces2();
    // pieces3();
    // pieces4();
    logPieces();
    redrawPieces();
    if(turn==-1){
      turn=0;
    }
    int rv= playerMove();
    redrawPieces();
    drawMove(rv);
    if(rv!=6){

      turn=(turn+1)%4;
    }
    cout<<"turn "<<turn<<endl;
}

/*

          DrawSquare( 140, 40,70,colors[GREEN]);
                  // DrawSquare( 50, 50,50,colors[WHITE]);
          DrawRoundRect(150 , 50, 50, 50, colors[WHITE],10) ;

*/
//pieces1();





  //  DrawString(50, 800, "Score=", colors[ORANGE_RED]);




    //  Torus2d(int x /*Starting position x*/, int y /*Starting position Y*/,
   // float angle, // starting angle in degrees
   // float length,           // length of arc in degrees, >0
   // float radius,           // inner radius, >0
   // float width,            // width of torus, >0
   // unsigned int samples,   // number of circle samples, >=3
   // float *color)    */



       //white
  //  DrawCircle(73, 900, 10, colors[RED]);
  //  DrawCircle(90, 670, 10, colors[RED]);
  //  DrawRoundRect(123, 144, 40, 20, colors[GREEN], 10);
    glutSwapBuffers(); // do not modify this line..



}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
    if (key
        == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
        // what to do when left key is pressed...


    }
    else if (key
        == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

    }
    else if (key
        == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

    }

    else if (key
        == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

    }

    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/

  //  glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */

void PrintableKeys(unsigned char key, int x, int y) {
    if (key == 32 /* Escape=27 key ASCII*/) {
        work = true;
        cout<<"333"<<endl;
    }
    if(key==49){
      movePiece=0;
      work = true;
      pieceSelected=true;
    }
      if(key==50){
        movePiece=1;
        work = true;
        pieceSelected=true;
      }
      if(key==51){
        movePiece=2;
        pieceSelected=true;
        work = true;
      }
      if(key==52){
        movePiece=3;
        pieceSelected=true;
        work = true;

      }

      cout<<"movePiece="<<movePiece<<endl;

    if (key == 27)
    {

        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'b' || key == 'B') //Key for placing the bomb
    {
        //do something if b is pressed
        cout << "b pressed" << endl;


    }
    glutPostRedisplay();
    cout<<"444"<<endl;

}
/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
 void TimerForAnimation(int m) {

    if(moveAnimation<1000) {

        moveAnimation+=10;
      // if(moveAnimation==1000){
       //   moveAnimation=200;
        //  cout<<"asfsd"<<endl;
        //}

   }




       moveBorder++;
  glutTimerFunc(10.0, TimerForAnimation, 100);
  glutPostRedisplay();
  }

void Timer(int m) {

    // implement your functionality here

    // once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
    cout << x << " " << y << endl;
  //  glutPostRedisplay();
}
void MouseMoved(int x, int y) {

  //s  glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON) // dealing only with left button

    {
  if ( ( x>783&&x<819)   )
        open=true;


    }

    else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
    {

    }
  //  glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char* argv[]) {

    //b = new Board(60, 60); // create a new board object to use in the Display Function ...
  //  cout<<"rabia"<<endl;
    int width = 1020, height = 840; // i have set my window size to be 800 x 600
    //b->InitalizeBoard(width, height);
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("PF Project"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...

    // Register your functions to the library,
    // you are telling the library names of function to call for different tasks.
    //glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

    glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    cout<<"1111"<<endl;

    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
    cout<<"2222"<<endl;

    // This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(1000.0, Timer, 0);
    glutTimerFunc(100.0, TimerForAnimation, 0);

    glutMouseFunc(MouseClicked);
    glutPassiveMotionFunc(MouseMoved); // Mouse
    glutMotionFunc(MousePressedAndMoved); // Mouse

    // now handle the control to library and it will call our registered functions when
    // it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* AsteroidS_CPP_ */
