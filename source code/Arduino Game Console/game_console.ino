#include <TVout.h>
#include "fontALL.h"
#include <math.h>
#include "schematic.h"
#include "Spaceship.h"
#include "mainchar.h"
#include "title.h"
#include "space_title.h"
#include "snake_title.h"
#include "pong_title.h"
#include "scenario1_partA.h"
#include "notes.h"
#include <Wire.h>
#include <SoftwareSerial.h>
  
TVout TV;


/***

| | | |          (_)     | |   | |           | (_)   | |
| | | | __ _ _ __ _  __ _| |__ | | ___  ___  | |_ ___| |_
| | | |/ _` | '__| |/ _` | '_ \| |/ _ \/ __| | | / __| __|
\ \_/ / (_| | |  | | (_| | |_) | |  __/\__ \ | | \__ \ |_
 \___/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/ |_|_|___/\__|

  //----------------------------
  //-----------Classes----------
  //----------------------------

  //-----------TETRIS-----------

    POSITION_CONTROL:

      -private members:

        >Variables:

        >Functions:

      -public members:

        >Variables:

        >Functions:

          *Right (int,int,int,int): Moves the current block to the right. Accepts 4 parameters. The first one is the current x-position of the block, the second one is the
                    current y-position of the block  the third last one is the type and the last one is the angle.

          *Left (int,int,int,int): Moves the current block to the left, accepts the same parameters of the previous functions

          *Down (int,int,int,int): Makes the block fall down. Accepts 5 parameters. The first one is the x-position of the block, the second one is the y-position, the third
                    parameter is the type, the fourth one is the angle and the last is the block falling "speed" (Pixels / interval of time).

    BLOCK_CONTROL:

      -private members:

        >Variables:

        >Functions:

      -public members:

        >Variables:

        >Functions:

          *Generate_block: Colors the block pixels' white, i.e creates a block. Accepts 4 arguments. The first and the second one are the X, and Y coordinates of
          the upper-left corner, the third one is the type of the block and the last is the angle.

                                #Possible types:

                                    #1: Square-shaped block
                                    #2: L-shaped block. Right orientation.
                                    #3: T-Shaped block.
                                    #4: |-Shaped block.

                                #Possible angles:

                                    #0: 0 Degrees. It's the default values, block with zero degrees appear as in the previous definition
                                    #90: 90 Degrees. Counter-clockwise direction.
                                    #180: 180 Degrees. Counter-clockwise direction.
                                    #270: 270 Degrees. Counter-clockwise direction.

          *Delete_block: Colors the block pixels' black, i.e, erases the block. Accepts the same 4 parameters of the previous function.

  //----------------------------
  //------Data Structures-------
  //----------------------------

  //-----------TETRIS-----------
    COORDINATES_CONTROL:

      - xpos: X-coordinate of the block's upper-left corner. Accepts a default value, i.e the place where the block will appear. In this project we will use '6' as the 'xpos' default value.

      - ypos: Y-coordinate of the block's upper-left corner. And like xpos, accepts a default value. In this project we will use '4' as the 'ypos' default value.

      - wdt: Width of the block.

      - hgt: Height of the block.

      -spd: Block's 'falling' speed, i.e, number of pixel/interval of time that it goes trough.

        JOYSTICK:

            - LeftB:  Left button.       ('←'bbutton). For joystick 1: Digital pin 02
            - RightB: Right button.      ('→'bbutton). For joystick 1: Digital pin 03
            - DownB:  Down button.       ('↓'bbutton). For joystick 1: Digital pin 04
            - UpB:    Up button.         ('↑'bbutton). For joystick 1: Digital pin 05
            - Act1B:  1st action button. ('A' button). For joystick 1: Digital pin 06
            - Act2B:  2nd action button. ('B' button). For joystick 1: Digital pin 08

              ______________________________
            // ___                  ___     \\
            | | A |                | ↑ |     |
            | |___| ___         ___|___|___  |
            |      | B |       | ← |   | → | |
            |      |___|       |___|___|___| |
            |                      | ↓ |     |
            |                      |___|     |
            \\______________________________//
***/

/******************************
*******************************
**CLASSES AND DATA STRUCTURES**
*******************************
******************************/

//-----------------------------
//-------DATA STRUCTURES-------
//-----------------------------

struct joystick{

  int LeftB;  // Left     ←
  int RightB; // Right    →
  int DownB;  // Up       ↑
  int UpB;    // Down     ↓
  int Act1B;  // Action 1 A
  int Act2B;  // Action 2 B

};

/***joystick objects***/
joystick joystick1;
joystick joystick2;

//TETRIS:

struct coordinates_control{

  int xpos; //X-coordinate
  int ypos; //Y-coordinate
  int wdt;  //Width
  int hgt;  //Height
  int spd;  //Speed

};

/*** coordinates and size objects ***/
coordinates_control block;

struct snake_struct{

    int head_x;
    int head_y;
    int body_x[50];
    int body_y[50];
    int direction;
    int bodysize;

};

/*** snake objects ***/
snake_struct snake;

//-----------------------------
//-----------CLASSES-----------
//-----------------------------

class block_control{

  public:
    void Generate_block (int,int,int,int);
    void Delete_block   (int,int,int,int);
};

  void block_control::Generate_block (int x,int y,int type,int angle){

        switch(type) {

          case 1://Square-shaped
              switch(angle) {
                        case 0: {;}

                  default:
                            TV.draw_rect(x,y,2,2,WHITE,BLACK);
                            TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                            TV.draw_rect(x,y+4,2,2,WHITE,BLACK);
                            TV.draw_rect(x+4,y+4,2,2,WHITE,BLACK);
                            block.wdt=7;
                            block.hgt=7;
                        break;
              }

          break;

          case 2://L-shaped
                    switch(angle) {

                            case 0:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y+4,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y+8,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y+8,2,2,WHITE,BLACK);
                                block.wdt=7;
                                block.hgt=11;
                            break;

                    case 90:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+8,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+8,y-4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                           break;

                   case 180:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-8,2,2,WHITE,BLACK);
                                TV.draw_rect(x-4,y-8,2,2,WHITE,BLACK);
                                block.wdt=7;
                                block.hgt=11;
                        break;

                    case 270:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x-4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x-8,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x-8,y+4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                            break;
                    }

          break;

          case 3://T-shaped
              switch(angle) {

                            case 0:
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y+4,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y+4,2,2,WHITE,BLACK);
                                TV.draw_rect(x+8,y+4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                            break;

                             case 90:
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+8,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x+8,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+8,y+4,2,2,WHITE,BLACK);
                                block.wdt=7;
                                block.hgt=11;
                            break;

                            case 180:
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x+8,y-4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                            break;

                            case 270:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y+4,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                block.wdt=7;
                                block.hgt=11;
                            break;
              }

          break;

          case 4://I-shaped
              switch(angle){
                            case 0:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y+4,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y+8,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y+12,2,2,WHITE,BLACK);
                                block.wdt=3;
                                block.hgt=15;
                            break;

                            case 90:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+8,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+12,y,2,2,WHITE,BLACK);
                                block.wdt=15;
                                block.hgt=3;
                            break;

                            case 180:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-8,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-12,2,2,WHITE,BLACK);
                                block.wdt=3;
                                block.hgt=15;
                            break;

                            case 270:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x-4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x-8,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x-12,y,2,2,WHITE,BLACK);
                                block.wdt=15;
                                block.hgt=3;
                            break;
              }

                    break;

                    case 5://L-shaped reverse
                    switch(angle) {

                            case 0:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y+4,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y+8,2,2,WHITE,BLACK);
                                TV.draw_rect(x-4,y+8,2,2,WHITE,BLACK);
                                block.wdt=7;
                                block.hgt=11;
                            break;

                    case 90:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+8,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+8,y+4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                           break;

                   case 180:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-8,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y-8,2,2,WHITE,BLACK);
                                block.wdt=7;
                                block.hgt=11;
                  break;

                       case 270:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x-4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x-8,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x-8,y-4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                            break;
                    }

                    break;

                    case 6://Strangely-shaped
                    switch(angle) {

                            case 0:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y+4,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y-4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;

                            break;

                    case 90:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x-4,y-4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;

                           break;

                   case 180:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y+4,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y-4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;

                        break;

                    case 270:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x-4,y-4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;

                             break;
                    }

                    break;

                    case 7://Strangely-shaped reverse
                    switch(angle) {

                            case 0:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y+4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                            break;

                    case 90:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x-4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y-4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                           break;

                    case 180:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y+4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                            break;

                    case 270:
                                TV.draw_rect(x,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x-4,y,2,2,WHITE,BLACK);
                                TV.draw_rect(x,y-4,2,2,WHITE,BLACK);
                                TV.draw_rect(x+4,y-4,2,2,WHITE,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                            break;
                    }

           break;

        }
      }

      void block_control::Delete_block (int x,int y,int type,int angle){


        switch(type) {

          case 1://Square-shaped
              switch(angle) {

                  default:
                            TV.draw_rect(x,y,2,2,BLACK,BLACK);
                            TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                            TV.draw_rect(x,y+4,2,2,BLACK,BLACK);
                            TV.draw_rect(x+4,y+4,2,2,BLACK,BLACK);
                            block.wdt=7;
                            block.hgt=7;
                        break;
              }

          break;

          case 2://L-shaped
                    switch(angle) {

                            case 0:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y+4,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y+8,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y+8,2,2,BLACK,BLACK);
                                block.wdt=7;
                                block.hgt=11;
                            break;

                        case 90:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+8,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+8,y-4,2,2,BLACK,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                            break;

                        case 180:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-8,2,2,BLACK,BLACK);
                                TV.draw_rect(x-4,y-8,2,2,BLACK,BLACK);
                                block.wdt=7;
                                block.hgt=11;
                        break;

                        case 270:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x-4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x-8,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x-8,y+4,2,2,BLACK,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                            break;
                    }

          break;

          case 3://T-shaped
              switch(angle) {

                            case 0:
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y+4,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y+4,2,2,BLACK,BLACK);
                                TV.draw_rect(x+8,y+4,2,2,BLACK,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                            break;

                             case 90:
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+8,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x+8,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+8,y+4,2,2,BLACK,BLACK);
                                block.wdt=7;
                                block.hgt=11;
                            break;

                            case 180:
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x+8,y-4,2,2,BLACK,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                            break;

                            case 270:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y+4,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                block.wdt=7;
                                block.hgt=11;
                            break;
              }

          break;

          case 4://I-shaped
              switch(angle){
                            case 0:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y+4,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y+8,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y+12,2,2,BLACK,BLACK);
                                block.wdt=3;
                                block.hgt=15;
                            break;

                            case 90:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+8,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+12,y,2,2,BLACK,BLACK);
                                block.wdt=15;
                                block.hgt=3;
                            break;

                            case 180:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-8,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-12,2,2,BLACK,BLACK);
                                block.wdt=3;
                                block.hgt=15;
                            break;

                            case 270:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x-4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x-8,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x-12,y,2,2,BLACK,BLACK);
                                block.wdt=15;
                                block.hgt=3;
                            break;
              }

                          break;

                    case 5://L-shaped reverse
                          switch(angle) {

                            case 0:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y+4,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y+8,2,2,BLACK,BLACK);
                                TV.draw_rect(x-4,y+8,2,2,BLACK,BLACK);
                                block.wdt=7;
                                block.hgt=11;
                            break;

                    case 90:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+8,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+8,y+4,2,2,BLACK,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                           break;

                   case 180:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-8,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y-8,2,2,BLACK,BLACK);
                                block.wdt=7;
                                block.hgt=11;
                        break;

                    case 270:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x-4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x-8,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x-8,y-4,2,2,BLACK,BLACK);
                                block.wdt=11;
                                block.hgt=7;
                            break;
                          }

                         break;

                case 6://Strangely-shaped
                    switch(angle) {

                            case 0:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y+4,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y-4,2,2,BLACK,BLACK);
                                block.wdt=11;
                                block.hgt=7;

                            break;

                    case 90:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x-4,y-4,2,2,BLACK,BLACK);
                                block.wdt=11;
                                block.hgt=7;

                           break;

                   case 180:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y+4,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y-4,2,2,BLACK,BLACK);
                                block.wdt=11;
                                block.hgt=7;

                        break;

                    case 270:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x-4,y-4,2,2,BLACK,BLACK);
                                block.wdt=11;
                                block.hgt=7;

                            break;
                    }

                    break;

                case 7://Strangely-shaped reverse
                    switch(angle) {

                        case 0:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y+4,2,2,BLACK,BLACK);
                        break;

                    case 90:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x-4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y-4,2,2,BLACK,BLACK);
                           break;

                    case 180:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y+4,2,2,BLACK,BLACK);
                            break;

                    case 270:
                                TV.draw_rect(x,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x-4,y,2,2,BLACK,BLACK);
                                TV.draw_rect(x,y-4,2,2,BLACK,BLACK);
                                TV.draw_rect(x+4,y-4,2,2,BLACK,BLACK);
                        break;
                    }

          break;

        }
      }

/***Block control object***/
block_control         obj_block_control;

class position_control{

  public:
    void Right (int,int,int,int);
    void Left  (int,int,int,int);
    void Down  (int,int,int,int,int);
    void Turn  (int,int,int,int);
};

  void position_control::Right (int x, int y,int type,int angle){

    obj_block_control.Delete_block(x,y,type,angle);
    obj_block_control.Generate_block(x+4,y,type,angle);
    block.xpos+=4;
  }

  void position_control::Left (int x, int y,int type,int angle){

    obj_block_control.Delete_block(x,y,type,angle);
    obj_block_control.Generate_block(x-4,y,type,angle);
    block.xpos-=4;
  }

    void position_control::Down (int x, int y,int type,int angle,int block_speed){

    obj_block_control.Delete_block(x,y,type,angle);
    obj_block_control.Generate_block(x,y+block_speed,type,angle);
    block.ypos+=block_speed;
  }


/***Position control object ***/
position_control       obj_position_control;

//INTERFACES

//GLOBAL:

class main_menu{

  int i;
  int j;

  public:
    void Generate_cursor(int,int,char);
    int Game_over();
};

/***Main menu object***/
main_menu             obj_main_menu;

        void main_menu::Generate_cursor(int posx,int posy, char color){

             //Creates a cursor
             if(color=='W') for(i=3;i>=0;i--)
               for(j=posy-i;j<=posy+i;j++) TV.set_pixel(posx+3-i,j,WHITE);

               //Erases the cursor
             else
             for(i=3;i>=0;i--)
               for(j=posy-i;j<=posy+i;j++) TV.set_pixel(posx+3-i,j,BLACK);
        }

        //Generates game over menu and returns 1 if the chosen option is "yes", else, returns 0
        int main_menu::Game_over(){

             joystick1.LeftB=2;
             joystick1.RightB=3;
             joystick1.Act1B=6;

             TV.clear_screen();
             joystick joystick1={2,3,4,5,6,7};

             //LINES
             TV.draw_line(0,20,120,20,WHITE);
             TV.draw_line(0,80,120,80,WHITE);
             TV.select_font(font8x8);

             TV.println(20,32,"GAME OVER");
             TV.select_font(font6x8);
             TV.println(25,47,"TRY AGAIN?");

             //OPTION
             TV.select_font(font4x6);
             TV.println(50,62,"YES");
             TV.println(50,72,"NO");
             obj_main_menu.Generate_cursor(44,64,'W');

             int gameoveroption=0;
             int option=1;

             for(int p=0;p<sizeof(game_over_theme)/sizeof(game_over_theme[0]);p++) {if(game_over_theme[p]!=0)TV.tone(game_over_theme[p],1*1000/game_over_theme_duration[p]*2); else TV.noTone(); delay(1.1*2*1000*1.9/game_over_theme_duration[p]); }TV.noTone();

             while(gameoveroption==0){

            char button=Serial.read();

            //Swap between options
                  if(button=='3') {
                          obj_main_menu.Generate_cursor(44,64,'W');
                          obj_main_menu.Generate_cursor(44,74,'B');
                          option=1;
                          cursorsound();
                  }
                  else if(button=='2'){
                          obj_main_menu.Generate_cursor(44,74,'W');
                          obj_main_menu.Generate_cursor(44,64,'B');
                          option=2;
                          cursorsound();
                  }

            //Chooses an option
                  if(button=='6') {selectionsound();gameoveroption=option;}
             }


             if(gameoveroption==1) return 1;    //Returns to the game
             else if(gameoveroption==2) return 0;     //Returns to the main menu
        }

//TETRIS:
class tetris_interface{

  int i;

  public:
    void Tetris_intro();
    void Tetris_HUD(int,int);
    void Tetris_score(long int);
};

        void tetris_interface::Tetris_intro(){

                TV.select_font(font8x8);

            for(i=0;i<40;i++){
                  TV.println(34,5+i,"TETRIS");
                  delay(30);
                  TV.clear_screen();
            }

        }

        void tetris_interface::Tetris_HUD(int xedge,int yedge){

             //Box where the blocks are confined
               TV.draw_rect(0,5,xedge,yedge,WHITE);
                 TV.select_font(font6x8);
                 TV.draw_line(0+1,5,xedge,5,BLACK);

             //Score-----------------------------
                 TV.draw_line(52,10,52,25,WHITE);

                 TV.draw_line(53,7,53,9,WHITE);
                 TV.draw_line(54,5,54,6,WHITE);
                 TV.set_pixel(55,4,WHITE);

                 TV.draw_line(53,26,53,28,WHITE);
                 TV.draw_line(54,29,54,30,WHITE);
                 TV.set_pixel(55,31,WHITE);

                 TV.draw_line(56,3,57,3,WHITE);
                 TV.draw_line(57,2,59,2,WHITE);

                 TV.draw_line(59,1,93,1,WHITE);

                 TV.draw_line(56,32,57,32,WHITE);
                 TV.draw_line(57,33,59,33,WHITE);

                 TV.draw_line(59,34,93,34,WHITE);

                 TV.draw_line(99,10,99,25,WHITE);

                 TV.draw_line(98,7,98,9,WHITE);
                 TV.draw_line(97,5,97,6,WHITE);
                 TV.set_pixel(96,4,WHITE);

                 TV.draw_line(96,3,95,3,WHITE);
                 TV.draw_line(95,2,93,2,WHITE);

                 TV.draw_line(93,33,95,33,WHITE);
                 TV.draw_line(95,32,96,32,WHITE);
                 TV.set_pixel(96,31,WHITE);

                 TV.draw_line(97,30,97,29,WHITE);
                 TV.draw_line(98,28,98,26,WHITE);

                 TV.println(60,10,"SCORE");
                 TV.select_font(font4x6);
                 //------------------------------------

                 //Lines-----------------------------
                 TV.draw_line(52,50,52,65,WHITE);

                 TV.draw_line(53,47,53,49,WHITE);
                 TV.draw_line(54,45,54,46,WHITE);
                 TV.set_pixel(55,44,WHITE);

                 TV.draw_line(53,66,53,68,WHITE);
                 TV.draw_line(54,69,54,70,WHITE);
                 TV.set_pixel(55,71,WHITE);

                 TV.draw_line(56,43,57,43,WHITE);
                 TV.draw_line(57,42,59,42,WHITE);

                 TV.draw_line(59,41,93,41,WHITE);

                 TV.draw_line(56,72,57,72,WHITE);
                 TV.draw_line(57,73,59,73,WHITE);

                 TV.draw_line(59,74,93,74,WHITE);

                 TV.draw_line(99,50,99,65,WHITE);

                 TV.draw_line(98,47,98,49,WHITE);
                 TV.draw_line(97,45,97,46,WHITE);
                 TV.set_pixel(96,44,WHITE);

                 TV.draw_line(96,43,95,43,WHITE);
                 TV.draw_line(95,42,93,42,WHITE);

                 TV.draw_line(93,73,95,73,WHITE);
                 TV.draw_line(95,72,96,72,WHITE);
                 TV.set_pixel(96,71,WHITE);

                 TV.draw_line(97,70,97,69,WHITE);
                 TV.draw_line(98,68,98,66,WHITE);

                TV.println(60,50,"Lines");
                TV.select_font(font4x6);
                 //------------------------------------

                 TV.println(60,80,"Next:");


        }

        void tetris_interface::Tetris_score(long int points){
                 TV.println(60,20,points);
        }

//Tetris interface object
tetris_interface      obj_tetris_interface;

class snake_interface{

    public:

        void Snake_intro();
        void Snake_HUD();
        void Snake_score(long int);
        int eiti,eitin;

};

        void snake_interface::Snake_intro(){

                TV.select_font(font8x8);

            for(int i=0;i<40;i++){
                  TV.println(34,5+i,"SNAKE");
                  delay(30);
                  TV.clear_screen();
            }

        }

        void snake_interface::Snake_HUD(){

                TV.select_font(font4x6);
                TV.println(0,0,"SCORE:");
                TV.draw_rect(45,45,25,25,WHITE);

        }

        void snake_interface::Snake_score(long int points){

                 if(points==9||points==19) if(eiti==1||eitin==1) {TV.draw_rect(23,0,70,40,BLACK,BLACK);eiti=0;eitin=0;}

                 TV.select_font(font4x6);

                 if(points!=8) TV.println(25,0,points);
                 else if(points==8) {TV.println(25,0,"EIIIITI");eiti=1;}
                 else if(points==18) {TV.println(25,0,"EIIIITIN");eitin=1;}
        }

//Snake interface object
snake_interface      obj_snake_interface;

//-----------------------------
//------ARDUINO CONTROL--------
//-----------------------------

void setup() {

  Serial.begin(9600);           // start serial for output

  /*
  joystick1.LeftB=2;  // Left
  joystick1.RightB=3; // Right    →
  joystick1.DownB=4;  // Up       ↑
  joystick1.UpB=5;    // Down     ↓
  joystick1.Act1B=6;  // Action 1 A
  joystick1.Act2B=7;  // Action 2 B
  */

  //Initializes
  TV.begin(PAL,120,96);
  TV.select_font(font6x8); //Size of the Font
  TV.clear_screen();

  randomSeed(analogRead(0));

            TV.bitmap(0,0,title_screen);
            
            TV.select_font(font6x8);
            TV.print(10,80,"Press any button"); 

           
            char button='0';

            while(Serial.available()) button=Serial.read();

            long int song_delay=0;
            long int song_time=0;
            long int start_delay1=100;
            long int start_time1=0;
            long int start_delay2=250;
            long int start_time2=0;
            long int start_on=1;
            long int p=0;

            while(true){     

                button=Serial.read();
                //button='2';
                
                if(millis()-song_time>song_delay) {
                  
                        if(MM3_intro[p]!=0) TV.tone(MM3_intro[p],2*1000/MM3_intro_duration[p]*2); 
                        else TV.noTone(); 
                        song_delay=(1000*.6/MM3_intro_duration[p]);                      
                        p++;
                        if(p>=sizeof(MM3_intro_duration)/sizeof(MM3_intro_duration[0])) p=0;
                        song_time=millis();                      
                  }
                    
                        if(start_on==1&&millis()-start_time2>start_delay2) {TV.draw_rect(10,80,100,16,0,0);start_on=0;start_time1=millis();}
                        if(start_on==0&&millis()-start_time1>start_delay1) {TV.print(10,80,"Press any button"); start_on=1;start_time2=millis();}

                  if(button=='2'||button=='3'||button=='4'||button=='5'||button=='6'||button=='7') break;
                 
            }

            TV.noTone(); 

            TV.clear_screen();
}

//-----------------------------
//---------MAIN MENU-----------
//-----------------------------

int Game_type;

void loop(){

   menuloop();

}
    //------MAIN MENU INTERFACE ------
    //--------------------------------

  void menuloop(){

      TV.clear_screen();
      TV.select_font(font4x6); //Font size

      //Menu art
      TV.bitmap(0,0,title);

      //OPTIONS:
      //1: Tetris
      //2: Snake
      //3: Pong

      //Options
      TV.println(40,50,"TETRIS");
      TV.println(40,60,"SNAKE");
      TV.println(40,70,"PONG");
      TV.println(40,80,"SPACE IMPACT");

      Game_type=0;  //Game_type. 1:Tetris, 2:Snake, 3:Pong
      int option=1; //Menu option

      char button='0';
      
      while(Serial.available()) button=Serial.read();

      long int button_delay=millis(),button_interval=100;      

      while(Game_type==0){

              
              //Generate a white cursor at x=0 and y=10*option+2
              obj_main_menu.Generate_cursor(35,40+10*option+2,'W');
        
              button=Serial.read();

              //Up
              if(option>1&&millis()-button_delay>button_interval) if(button=='3') {
        
                   //Generates cursor at current position. Formula for cursor position: y=40+10*option+4.
                   obj_main_menu.Generate_cursor(35,40+10*option+2,'B');
                   option--;
                   cursorsound();
                   button_delay=millis();
              
              }
        
              //Down
              if(option<4&&millis()-button_delay>button_interval) if(button=='2') {
              
                    obj_main_menu.Generate_cursor(35,40+10*option+2,'B');
                    option++;
                    cursorsound();
                    button_delay=millis();
              
              }
              
              //Serial.println(Serial.read());
        
              //Action button, chooses the
        
              if(button=='6'&&millis()-button_delay>button_interval+50) {
                        selectionsound();
                        Game_type=option;
                         break;
                         
              } 

      }

      TV.clear_screen();

      if(Game_type==1) tetris();
      else if(Game_type==2) snake_game();
      else if(Game_type==3) pong_game();//{while(true) 
                            //for(int p=0;p<sizeof(MM3_intro)/sizeof(MM3_intro[0]);p++) {if(MM3_intro[p]!=0)TV.tone(MM3_intro[p],1*1000/MM3_intro_duration[p]*2); else TV.noTone(); delay(3.7*1000/MM3_intro_duration[p]); }TV.noTone();}

      else if(Game_type==4) space_impact();

      delay(1000);

  }

/**********************
*TETRIS GAME MAIN LOOP*
**********************/

long long int score;  //Points
int lines=0;          //Cleared lines
int fall_interval;    //Time the block takes to go through 4 pixels in the vertical direction
int fast_fall;        //Fall interval when down button is pressed
int slow_fall;        //Fall interval when down button is not pressed, i.e, normal speed
int button_interval;  //Interval between the pressing of two buttons
int game_run;         //Tell if the game is being executed or not
int row_delay=0;

  void rowsound(){
       TV.tone(330,120);
       delay(50);
       TV.tone(520,95);
       delay(30);
       TV.tone(400,80);
       delay(60);
  }


void tetris(){

            delay(100);

            char button='0';

            while(Serial.available()) button=Serial.read();

            TV.bitmap(0,0,tetris_title);
            
            TV.select_font(font4x6);
            TV.print(24,72,"Press any button"); 
           
            

            while(Serial.available()) button=Serial.read();

            long int song_delay=0;
            long int song_time=0;
            long int start_delay1=100;
            long int start_time1=0;
            long int start_delay2=250;
            long int start_time2=0;
            long int start_on=1;
            long int p=0,play_once=0;

             button='0';


            while(true){     

                button=Serial.read();
                
                if(millis()-song_time>song_delay&&play_once==0) {
                  
                        if(teste[p]!=0) TV.tone(teste[p],2*1000/teste_duration[p]*2); 
                        else TV.noTone(); 
                        song_delay=(1000*.6/teste_duration[p]);                      
                        p++;
                        if(p>=sizeof(teste_duration)/sizeof(teste_duration[0])) p=0;//play_once=1;
                        song_time=millis();                      
                  }
                    
                        if(start_on==1&&millis()-start_time2>start_delay2) {TV.draw_rect(24,72,62,7,0,0);TV.bitmap(0,0,tetris_title);start_on=0;start_time1=millis();}
                        if(start_on==0&&millis()-start_time1>start_delay1) {TV.bitmap(0,0,tetris_title);TV.print(24,72,"Press any button"); start_on=1;start_time2=millis();}

                  if(button=='2'||button=='3'||button=='4'||button=='5'||button=='6'||button=='7') break;
                 
            }

            TV.noTone(); 

            TV.clear_screen();
      
      
    while(true){

         
        //Initialization of variables
        game_run=2;
        score=0;
        fall_interval=200;
        fast_fall=1;
        slow_fall=200;
        button_interval=30;

        //Place where the block is created
        int x_start=18;
        int y_start=7;

        //How many pixels the block goes through by interval of time
        block.spd=4;

        //Last coordinates of the block
        int x_last=-1;
        int y_last=-1;

        //Current block type (i.e, shape), and angle.
        int current_angle=0;
        int current_type;
        int next_current_type;

        //Interval of time in which the block 'falls' one pixel
        long long int Fall_delay=0;
        long long int buttondelay=0;

        //Initializes the interface
        obj_tetris_interface.Tetris_intro();
        obj_tetris_interface.Tetris_HUD(42,90);
        obj_tetris_interface.Tetris_score(score);


        //Chooses the first and second blocks, and puts the second block on the 'next' display
        next_current_type=random(1, 8);
        current_type=random(1,8);
        obj_block_control.Generate_block(86,80,next_current_type,0);

        //Generates the first block
        obj_block_control.Generate_block(x_start,y_start,current_type,current_angle);
        block.xpos=x_start;
        block.ypos=y_start;

        long int theme_delay=0;
        long int theme_interval=0;
        p=0;

        int one_more=1;
        long int one_more_delay=160,one_more_time=0;

        while(Serial.available()) button=Serial.read();

        while(game_run==2){

          if(millis()-theme_delay>theme_interval) {
                  TV.tone(theme_A[p],1000/duration_theme_A[p]);
                  theme_interval=.75*1000/duration_theme_A[p];
                  p++; 
                  if(p>sizeof(theme_A)/sizeof(theme_A[0])) p=0;
                  theme_delay=millis();
            }

          char button=Serial.read();

          obj_tetris_interface.Tetris_score(score); //Display the score
          TV.println(60,60,lines);                  //Display the number of cleared lines

                  //----------------------------------
                  //---Block movement conditionals----
                  //----------------------------------

                  //Checks if the blocks is whether able to go down or not
                  if(millis()-Fall_delay>=fall_interval&&collision_check_down(block.xpos,block.ypos,current_type,current_angle)==1) {

                          obj_position_control.Down(block.xpos,block.ypos,current_type,current_angle,block.spd);

                          Fall_delay=millis();

                          x_last=block.xpos;
                          y_last=block.ypos;

                          score+=10;
                  }

                  //Checks if the block is able to go down
                  if(collision_check_down(block.xpos,block.ypos,current_type,current_angle)==0&&one_more==0&&millis()-one_more_time>one_more_delay){

                          //Game over conditional
                          if(block.xpos==x_start&&block.ypos==y_start&&game_run==2) {
                                  obj_block_control.Delete_block(x_start,y_start,next_current_type,0);
                                  lines=0;
                                  game_run=obj_main_menu.Game_over();

                                  if(game_run==1) break;
                                  else if(game_run==0) return;
                          }

                          fall_interval=slow_fall; //Resets the fall_interval to default value

                          //Clear the completed rows. P.S: The two parameters in the function are the xedge and yedge values, respectively. P.S 2: It seems that this is is actually checking
                          //the total number of lines-4, so I had to add a '+4' in the second parameter.

                          row_check(42,90+4);
                          while(Serial.available()) button=Serial.read();

                          //Initial position
                          block.xpos=x_start;
                          block.ypos=y_start;

                          //Chooses the new block
                          current_type=next_current_type;
                          obj_block_control.Delete_block(85,80,next_current_type,0);

                          next_current_type=random(1, 8); //Chooses the next block
                          current_angle=0;                //Resets the angle to 0


                          obj_block_control.Generate_block(x_start,y_start,current_type,0); //Generate the new block in the initial position
                          TV.draw_rect(80,80,30,20,0,0);
                          obj_block_control.Generate_block(85,80,next_current_type,0);      //Display the next block

                          score+=50;

                          one_more=1;

                  }
                  else if(collision_check_down(block.xpos,block.ypos,current_type,current_angle)==0&&one_more==1) {one_more=0;one_more_time=millis();}

                  //Rotates the block in counter-clockwise direction. This conditional checks if the block will collide with something when rotated
                  if(millis()-buttondelay>50+button_interval&&check_turn(block.xpos,block.ypos,current_type,current_angle)==1) if (button=='6'){

                         obj_block_control.Delete_block(block.xpos,block.ypos,current_type,current_angle);

                         if(current_angle<270) current_angle+=90; //Rotates 90 degrees
                         else current_angle=0;                    //If angle=270, go back to 0

                         obj_block_control.Generate_block(block.xpos,block.ypos,current_type,current_angle);

                         buttondelay=millis();
                   }

                   //The block is accelerated very fast, then, the blocks falls almost instantly at the bottom
                   if(millis()-buttondelay>100+button_interval&&row_delay-millis()>1000) if (button=='2'){

                         fall_interval=fast_fall; //Fast_fall<fall_interval, hence, the block falls faster

                         buttondelay=millis();

                   }

                  //Checks if the block is able to go right
                  if(collision_check_right(block.xpos,block.ypos,current_type,current_angle)==1&&millis()-buttondelay>button_interval) if (button=='5')  {
                            
                            obj_position_control.Right(block.xpos,block.ypos,current_type,current_angle);
                            buttondelay=millis();

                  }

                  //Checks if the block is able to go left
                  if(collision_check_left(block.xpos,block.ypos,current_type,current_angle)==1&&millis()-buttondelay>button_interval) if(button=='4')  {
                             
                             obj_position_control.Left(block.xpos,block.ypos,current_type,current_angle);
                             buttondelay=millis();
                  }

                  //Block movement conditionals end
           }
    }
}

/**********************
*SNAKE GAME MAIN LOOP**
**********************/

void snake_game(){

    
    TV.clear_screen();

            char button='0';

            while(Serial.available()) button=Serial.read();;

            long int song_delay=0;
            long int song_time=0;
            long int start_delay1=100;
            long int start_time1=0;
            long int start_delay2=250;
            long int start_time2=0;
            long int start_on=1;
            int p=0;

            TV.bitmap(0,0,snake_title);
            TV.select_font(font6x8);
            TV.print(10,80,"Press any button"); 

            button='0';

            while(Serial.available()) button=Serial.read();

            while(true){     

                button=Serial.read();
                
                /*if(millis()-song_time>song_delay) {
                  
                        if(healing[p]!=0)TV.tone(healing[p],2*1000/healing_duration[p]*2); 
                        else TV.noTone(); 
                        song_delay=(1000*.6/healing_duration[p]);                      
                        p++;
                        if(p>sizeof(healing)/sizeof(healing[0])) p=0;
                        song_time=millis();                      
                  }if(p>sizeof(healing)/sizeof(healing[0])) p=0;*/
                    
                        if(start_on==1&&millis()-start_time2>start_delay2) {TV.draw_rect(10,80,100,16,0,0);start_on=0;start_time1=millis();}
                        if(start_on==0&&millis()-start_time1>start_delay1) {TV.print(10,80,"Press any button"); start_on=1;start_time2=millis();}

                  if(button=='2'||button=='3'||button=='4'||button=='5'||button=='6'||button=='7') break;
                 
            }

            TV.noTone(); 

            TV.clear_screen();


    obj_snake_interface.Snake_intro();
    obj_snake_interface.Snake_HUD();

    long long int creeping_interval;
    long long int creeping_delay;
    long long int button_interval;
    long long int button_delay;
    int applex,appley;
    bool takenapple;

    while(true){

        snake.bodysize=4;
        snake.head_x=50;
        snake.head_y=52;
        snake.body_x[0]=50;
        snake.body_y[0]=53;
        snake.body_x[1]=50;
        snake.body_y[1]=54;
        snake.body_x[2]=50;
        snake.body_y[2]=55;
        //int tail_x=1;
        //int tail_y=80;
        snake.direction=1;
        takenapple=true;

        creeping_interval=80;
        creeping_delay=0;
        button_interval=50;
        button_delay=0;
        score=0;
        game_run=2;
        obj_snake_interface.Snake_score(score);

        for(int i=0;i<snake.bodysize-1;i++) TV.set_pixel(snake.body_x[i],snake.body_y[i],WHITE);

        char button;

        while(true){

                button=Serial.read();

                while(takenapple==true){

                        applex=random(46,69);
                        appley=random(46,69);

                        if(TV.get_pixel(applex,appley)==0) {
                            TV.set_pixel(applex,appley,WHITE);
                            takenapple=false;
                        }
                }

                if(millis()-creeping_delay>creeping_interval){

                    TV.set_pixel(snake.body_x[snake.bodysize-2],snake.body_y[snake.bodysize-2],BLACK);
                    //TV.set_pixel(tail_x,tail_y,BLACK);

                    for(int i=snake.bodysize-2;i>0;i--) snake.body_x[i]=snake.body_x[i-1];
                    for(int i=snake.bodysize-2;i>0;i--) snake.body_y[i]=snake.body_y[i-1];

                    snake.body_x[0]=snake.head_x;
                    snake.body_y[0]=snake.head_y;

                    if(snake.direction==1)
                            if(TV.get_pixel(snake.head_x,snake.head_y-1)==1&&snake.head_x!=applex&&snake.head_y!=appley+1) {
                                  game_run=obj_main_menu.Game_over();
                                  if(game_run==1) break;
                                  else if(game_run==0) return;
                            }
                            else if(snake.head_x==applex&&snake.head_y-1==appley) {
                                   snake.bodysize++;
                                   snake.head_x=applex;
                                   snake.head_y=appley;
                                   takenapple=true;
                                   score++;
                                   applesound();
                                   obj_snake_interface.Snake_score(score);
                            }
                            else snake.head_y--;

                    else if(snake.direction==2)
                            if(TV.get_pixel(snake.head_x,snake.head_y+1)==1&&snake.head_x!=applex&&snake.head_y!=appley-1) {
                                  game_run=obj_main_menu.Game_over();
                                  if(game_run==1) break;
                                  else if(game_run==0) return;
                            }
                           else if(snake.head_x==applex&&snake.head_y+1==appley) {
                                   snake.bodysize++;
                                   snake.head_x=applex;
                                   snake.head_y=appley;
                                   takenapple=true;
                                   score++;
                                   applesound();
                                   obj_snake_interface.Snake_score(score);
                            }
                            else snake.head_y++;

                    else if(snake.direction==3)
                            if(TV.get_pixel(snake.head_x-1,snake.head_y)==1&&snake.head_x!=applex+1&&snake.head_y!=appley) {
                                  game_run=obj_main_menu.Game_over();
                                  if(game_run==1) break;
                                  else if(game_run==0) return;
                            }
                            else if(snake.head_x-1==applex&&snake.head_y==appley){
                                   snake.bodysize++;
                                   snake.head_x=applex;
                                   snake.head_y=appley;
                                   takenapple=true;
                                   score++;
                                   applesound();
                                   obj_snake_interface.Snake_score(score);
                            }
                            else snake.head_x--;

                    else if(snake.direction==4)
                            if(TV.get_pixel(snake.head_x+1,snake.head_y)==1&&snake.head_x!=applex-1&&snake.head_y!=appley) {
                                  game_run=obj_main_menu.Game_over();
                                  if(game_run==1) break;
                                  else if(game_run==0) return;
                            }
                            else if(snake.head_x+1==applex&&snake.head_y==appley) {
                                   snake.bodysize++;
                                   snake.head_x=applex;
                                   snake.head_y=appley;
                                   takenapple=true;
                                   score++;
                                   applesound();
                                   obj_snake_interface.Snake_score(score);
                            }
                            else snake.head_x++;


                    TV.set_pixel(snake.head_x,snake.head_y,WHITE);

                    creeping_delay=millis();

                }

                if(button=='4'&&millis()-button_delay>button_interval&&snake.direction!=4){
                    snake.direction=3;
                    button_delay=millis();
                }

                else if(button=='5'&&millis()-button_delay>button_interval&&snake.direction!=3){
                    snake.direction=4;
                    button_delay=millis();
                }

                else if(button=='3'&&millis()-button_delay>button_interval&&snake.direction!=2){
                    snake.direction=1;
                    button_delay=millis();
                }

                else if(button=='2'&&millis()-button_delay>button_interval&&snake.direction!=1){
                    snake.direction=2;
                    button_delay=millis();
                }


        }

        game_run=2;
        TV.clear_screen();
        obj_snake_interface.Snake_HUD();
    }
}


/*************************
***PONG GAME MAIN LOOP****
*************************/

void pong_game(){

        TV.clear_screen();

        TV.bitmap(0,0, pong_title);
        
            long int song_delay=0;
            long int song_time=0;
            long int start_delay1=100;
            long int start_time1=0;
            long int start_delay2=250;
            long int start_time2=0;
            long int start_on=1;
            long int p=0;
            
            char button;
            while(Serial.available()) Serial.read();
            button='0';

        while(true){

            
                button=Serial.read();
                
                /*if(millis()-song_time>song_delay) {
                  
                        if(teste[p]!=0)TV.tone(teste[p],2*1000/teste_duration[p]*2); 
                        else TV.noTone(); 
                        song_delay=(1000*1.4/teste_duration[p]);                      
                        p++;
                        if(p>sizeof(teste)/sizeof(teste[0])) p=0;
                        song_time=millis();                      
                  }if(p>sizeof(teste)/sizeof(teste[0])) p=0;*/
                    
                        if(start_on==1&&millis()-start_time2>start_delay2) {TV.draw_rect(10,78,95,17,0,0);start_on=0;start_time1=millis();}
                        if(start_on==0&&millis()-start_time1>start_delay1) {TV.print(27,79,"Press any button"); start_on=1;start_time2=millis();}

                  if(button=='2'||button=='3'||button=='4'||button=='5'||button=='6'||button=='7') break;
        
        ;
        }

        while(true){
        
        TV.clear_screen();

        int button_delay=0;
        long int button_time=0;

        long int ball_timex=0,ball_timey=0;
        long int ball_delayx,ball_delayy;
        int ball_directionx,ball_directiony;
        
        int paddle1_x=0,paddle1_y=40;
        int paddle2_x=117,paddle2_y=40;
        int ballx=30,bally=48;
        int erase_next=1;

        int points1=0,points2=0;

        int AI_time=0,AI_delay=15;
        int follow,slow_mode=1,reverse,reverse_moves=0,stop_paddle,reflection_position=0;

        TV.draw_rect(paddle1_x,paddle1_y,2,20,WHITE,WHITE);
        TV.draw_rect(paddle2_x,paddle2_y,2,20,WHITE,WHITE);

        TV.set_pixel(ballx,bally,WHITE);
        ball_delayx=15;ball_delayy=7;
        ball_directionx=1;ball_directiony=1;

        TV.print(40+23,15,0);
        TV.print(43,15,0);
        
        p=0;
        while(p<92) {TV.draw_line(54,p,54,p+3,WHITE); p=p+5;}
        
        while(true){

                  button=Serial.read();

                  if(button=='2'&&paddle1_y<=96-20-2){

                            TV.draw_rect(paddle1_x,paddle1_y,2,20,BLACK,BLACK);
                            paddle1_y++;
                            TV.draw_rect(paddle1_x,paddle1_y,2,20,WHITE,WHITE);
                            button_time=millis();
                  }

                  
                  if(button=='3'&&paddle1_y>0){

                            TV.draw_rect(paddle1_x,paddle1_y,2,20,BLACK,BLACK);
                            paddle1_y--;
                            TV.draw_rect(paddle1_x,paddle1_y,2,20,WHITE,WHITE);
                            button_time=millis();
                  }

                  if(TV.get_pixel(ballx+1,bally)==1&&ballx>=115) {
                              ball_directionx=-1;
                              if(bally==paddle2_y||bally==paddle2_y+1||bally==paddle2_y+20||bally==paddle2_y+20-1) {ball_delayx=15;ball_delayy=5;}
                              else if(bally==paddle2_y+2||bally==paddle2_y+3||bally==paddle2_y+20-2||bally==paddle2_y+20-3) {ball_delayx=13;ball_delayy=7;}
                              else if(bally==paddle2_y+4||bally==paddle2_y+5||bally==paddle2_y+20-4||bally==paddle2_y+20-5) {ball_delayx=11;ball_delayy=9;}
                              else if(bally==paddle2_y+6||bally==paddle2_y+7||bally==paddle2_y+20-6||bally==paddle2_y+20-7) {ball_delayx=9;ball_delayy=11;}
                              else if(bally==paddle2_y+8||bally==paddle2_y+9||bally==paddle2_y+20-8||bally==paddle2_y+20-9) {ball_delayx=7;ball_delayy=13;}
                              slow_mode=random(1,7);
                              if(slow_mode<5) AI_delay=15;
                              else AI_delay=500;
                              reflection_position=random(-8,28);
                  }
                  else if(TV.get_pixel(ballx-1,bally)==1&&ballx<=5) {
                              ball_directionx=1;
                              if(bally==paddle1_y||bally==paddle1_y+1||bally==paddle1_y+20||bally==paddle1_y+20-1) {ball_delayx=15;ball_delayy=5;}
                              else if(bally==paddle1_y+2||bally==paddle1_y+3||bally==paddle1_y+20-2||bally==paddle1_y+20-3) {ball_delayx=13;ball_delayy=7;}
                              else if(bally==paddle1_y+4||bally==paddle1_y+5||bally==paddle1_y+20-4||bally==paddle1_y+20-5) {ball_delayx=11;ball_delayy=9;}
                              else if(bally==paddle1_y+6||bally==paddle1_y+7||bally==paddle1_y+20-6||bally==paddle1_y+20-7) {ball_delayx=9;ball_delayy=11;}
                              else if(bally==paddle1_y+8||bally==paddle1_y+9||bally==paddle1_y+20-8||bally==paddle1_y+20-9) {ball_delayx=7;ball_delayy=13;}
                              slow_mode=random(1,7);
                              if(slow_mode<5) AI_delay=15;
                              else AI_delay=500;
                              reflection_position=random(-7,28);
                  }

                  if(millis()-ball_timex>ball_delayx){
                            if(erase_next==1) TV.set_pixel(ballx,bally,BLACK);
                            if(ball_directionx==1) ballx++;
                            else ballx--;
                            if(TV.get_pixel(ballx,bally)==1) erase_next=0;
                            else erase_next=1;
                            TV.set_pixel(ballx,bally,WHITE);
                            ball_timex=millis();
                  }

                 if(bally==95) {ball_directiony=-1;reflectionsound();}
                 else if (bally==0) {ball_directiony=1;reflectionsound();}
                  
                 if(millis()-ball_timey>ball_delayy){
                            if(erase_next==1)  TV.set_pixel(ballx,bally,BLACK);
                            if(ball_directiony==1) bally++;
                            else bally--;
                            if(TV.get_pixel(ballx,bally)==1) erase_next=0;
                            else erase_next=1;
                            TV.set_pixel(ballx,bally,WHITE);
                            ball_timey=millis();
                 }

                if(ballx==0){

                        points2++;
                        goalsound();
                        TV.print(40+23,15,points2);
                        TV.set_pixel(ballx,bally,BLACK);
                        ballx=30+60,bally=48;
                        ball_directionx=-1;ball_directiony=1;
                  
                 }
                 else if(ballx==119){

                        points1++;
                        goalsound();
                        TV.print(43,15,points1);
                        TV.set_pixel(ballx,bally,BLACK);
                        ballx=30+60,bally=48;
                        ball_directionx=-1;ball_directiony=1; 
                 }

                 if(millis()-AI_time>AI_delay){

                          if(paddle2_y<bally-reflection_position&&paddle2_y<=96-20-2) {                                  
                            TV.draw_rect(paddle2_x,paddle2_y,2,20,BLACK,BLACK);
                            paddle2_y++;
                            TV.draw_rect(paddle2_x,paddle2_y,2,20,WHITE,WHITE);
                            button_time=millis();                          
                          }
                          else  if(paddle2_y>bally-reflection_position&&paddle2_y>0) {                                  
                            TV.draw_rect(paddle2_x,paddle2_y,2,20,BLACK,BLACK);
                            paddle2_y--;
                            TV.draw_rect(paddle2_x,paddle2_y,2,20,WHITE,WHITE);
                            button_time=millis();                          
                          }
                 }

                   if(points1==5||points2==5) {
                              game_run=obj_main_menu.Game_over();
                              if(game_run==1) break;
                              else if(game_run==0) return;
                   }
                                                                
            }    
        }       
}

/*********************************
***SPACE IMPACT GAME MAIN LOOP****
*********************************/

void space_impact(){
 
            TV.clear_screen();

            char button='0';

            while(Serial.available()) button=Serial.read();

            long int song_delay=0;
            long int song_time=0;
            long int start_delay1=100;
            long int start_time1=0;
            long int start_delay2=250;
            long int start_time2=0;
            long int start_on=1;
            long int p=0;

            int k=0,fpos1,fpos2,fpos3;
            
            long int fire_time=0;
            long int fire_delay=7;
            long int anship_delay=15;
            long int anship_time=0;
            
            while(k<=81) {
                          
              if(millis()-anship_time>anship_delay) {
                
                      TV.draw_rect(k,5,31,30,BLACK,BLACK);
                      k++;
                      TV.bitmap(k,5,big_ship);
                      anship_time=millis();
                                           
              }

              if(k==10) {
                TV.draw_rect(k+32,5+15,3,2,WHITE,WHITE);
                fpos1=k;
                shot_sound();
                fire_time=0;
              }
              
              if(k==20) {
                TV.draw_rect(k+32,5+15,3,2,WHITE,WHITE);
                fpos2=k;
                shot_sound();
                fire_time=0;
              }

              
              if(k==30) {
                TV.draw_rect(k+32,5+15,3,2,WHITE,WHITE);
                fpos3=k;
                shot_sound();
                fire_time=0;
              }

              if(k>=10&&millis()-fire_time>fire_delay){
                
                     if(fpos1<=118-32) TV.draw_rect(fpos1+32,5+15,3,2,BLACK,BLACK);
                     fpos1++;
                     if(fpos1<118-32) TV.draw_rect(fpos1+32,5+15,3,2,WHITE,WHITE);
                     fire_time=millis();

                     if(k>=20){
                      
                            if(fpos2<=118-32) TV.draw_rect(fpos2+32,5+15,3,2,BLACK,BLACK);
                            fpos2++;
                            if(fpos2<118-32) TV.draw_rect(fpos2+32,5+15,3,2,WHITE,WHITE);       
                            fire_time=millis();
                     }

                     if(k>=30){
                      
                           if(fpos3<=118-32) TV.draw_rect(fpos3+32,5+15,3,2,BLACK,BLACK);
                           fpos3++;
                           if(fpos3<118-32) TV.draw_rect(fpos3+32,5+15,3,2,WHITE,WHITE);
                           fire_time=millis();
                     }
              }             
           }

            TV.noTone();delay(100);

            while(Serial.available()) button=Serial.read();

            TV.bitmap(0,0,space_title);
            
            TV.select_font(font6x8);
            TV.print(10,80,"Press any button"); 

            button='0';

            while(true){     

                button=Serial.read();
                
                if(millis()-song_time>song_delay) {
                  
                        if(cutman[p]!=0) TV.tone(cutman[p],2*1000/cutman_duration[p]*2); 
                        else TV.noTone(); 
                        song_delay=(1000*.6/cutman_duration[p]);                      
                        p++;
                        if(p>=sizeof(cutman_duration)/sizeof(cutman_duration[0])) p=0;
                        song_time=millis();                      
                  }
                    
                        if(start_on==1&&millis()-start_time2>start_delay2) {TV.draw_rect(10,80,100,16,0,0);start_on=0;start_time1=millis();}
                        if(start_on==0&&millis()-start_time1>start_delay1) {TV.print(10,80,"Press any button"); start_on=1;start_time2=millis();}

                  if(button=='2'||button=='3'||button=='4'||button=='5'||button=='6'||button=='7') break;
                 
            }

            TV.noTone(); 

            TV.clear_screen();

            long long int scenario_delay=50;
            long long int scenario_time=0;
            int scenario_speed=1;
            int scenario_x=120;
            int ship_y=30;
            int button_delay=10;
            int button_time=0;
            
            int nshots=0;
            int shot_x[3],shot_y[3];
            int shot_on[3];
            for(int i=0;i<3;i++) shot_on[i]=0;
            long long int shot_time[3];
            int shot_interval=10; 
            
            TV.bitmap(0,30, mainchar);

            TV.bitmap(0,0, heart);
            TV.bitmap(8,0, heart);
            TV.bitmap(16,0, heart);

            int enemy_x[4],enemy_y[4];
            int enemy_shot_x[20][20];
            int enemy_shot_y[20][20];
            int enemy_shot_delay=20;
            int enemy_shot_time[20][20];
            int enemy_nshots[20];
            for(int i=0;i<21;i++) for(int j=0;j<21;j++){                   
                   enemy_shot_time[i][j]=0;
                   enemy_nshots[i]=1;
            }
            
            bool enemy_alive[4];for(int i=0;i<4;i++) enemy_alive[i]=0;

           
            enemy_x[0]=112,enemy_y[0]=30;
            TV.bitmap(enemy_x[0],enemy_y[0],space_ship);

            while(true){

                button=Serial.read();

                if(millis()-scenario_time>scenario_delay){
                   scenario_time=millis();
                   scenario_x--;
                   if(scenario_x<0) scenario_x=120;
                   TV.bitmap(scenario_x,59,scenario2); 
                }

                if(button=='3'&&ship_y>6) {
                          TV.draw_rect(0,ship_y,16,16,BLACK);
                          ship_y--;
                          TV.bitmap(0,ship_y, mainchar);
                      
                           button_time=millis();

                }

                if(button=='2'&&ship_y<43) {
                          TV.draw_rect(0,ship_y,16,16,BLACK);
                          ship_y++;
                          TV.bitmap(0,ship_y, mainchar);
             
                           button_time=millis();

                }


                if(button=='6'&&millis()-button_time>button_delay){                             

                      nshots=0;
                      
                      for(int i=0;i<2;i++) nshots+=shot_on[i];
                      if(nshots==2&&shot_on[2]==0){   
                            shot_y[2]=ship_y+5;                     
                            shot_x[2]=16+1;
                            TV.set_pixel(shot_x[2],shot_y[2],WHITE);
                            shot_time[2]=millis();
                            shot_on[2]=1;
                      }  

                      nshots=0;

                      for(int i=0;i<2;i++) nshots+=shot_on[i];
                      if(shot_on[0]==1&&shot_on[1]==0){   
                            shot_y[1]=ship_y+5;                     
                            shot_x[1]=16+1;
                            TV.set_pixel(shot_x[1],shot_y[1],WHITE);
                            shot_time[1]=millis();
                            shot_on[1]=1;
                      }  

                      nshots=0;
                         
                      if(shot_on[0]==0){   
                            shot_y[0]=ship_y+5;                     
                            shot_x[0]=16+1;
                            TV.set_pixel(shot_x[0],shot_y[0],WHITE);
                            shot_time[0]=millis();
                            shot_on[0]=1;
                      }

                      for(int i=0;i<2;i++) nshots+=shot_on[i];
                }

                for(int i=0;i<2;i++) if(millis()-shot_time[i]>shot_interval&&shot_on[i]==1){
                       TV.set_pixel(shot_x[i],shot_y[i],BLACK);                    
                       shot_x[i]++;
                       TV.set_pixel(shot_x[i],shot_y[i],WHITE);                    
                       shot_time[i]=millis();

                       if(shot_x[i]==120) {TV.set_pixel(shot_x[i],shot_y[i],BLACK);shot_on[i]=0;nshots--;}
                }
                  
        
                for(int i=0;i<4;i++)  for(int j=0;j<4;j++)  if(shot_x[i]==enemy_x[j]) if(shot_y[i]==enemy_y[j]||shot_y[i]==enemy_y[j]+1||shot_y[i]==enemy_y[j]+2||shot_y[i]==enemy_y[j]+3||shot_y[i]==enemy_y[j]+4||shot_y[i]==enemy_y[j]+5||shot_y[i]==enemy_y[j]+6) {
                       enemy_alive[j]=false;
                       TV.draw_rect(enemy_x[j],enemy_y[j],7,7,BLACK,BLACK);                                               
                }

                

               
                
      }
}

/***************************************/
/**Tetris collision system functions ***/
/***************************************/

//----------------------------
//----------------------------
//----COLLISION FUNCTIONS-----
//----------------------------
//----------------------------

int collision_check_right(int x,int y,int type,int angle){

        switch(type){
                case 1://Square
                         for(int j=0;j<block.hgt;j++) if(TV.get_pixel(x+block.wdt+1,y+j)==1) return 0;
                         return 1;
                break;

                case 2://L
                         switch(angle){
                                case 0:
                                        if(TV.get_pixel(x+4,y)==1||TV.get_pixel(x+4,y+4)==1||TV.get_pixel(x+8,y+8)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x+12,y)==1||TV.get_pixel(x+12,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x+4,y)==1||TV.get_pixel(x+4,y-4)==1||TV.get_pixel(x+4,y-8)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x+4,y)==1||TV.get_pixel(x-4,y+4)==1) return 0;
                                        return 1;
                                break;
                        }
                break;

                case 3://T
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x+8,y)==1||TV.get_pixel(x+12,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x+12,y-4)==1||TV.get_pixel(x+12,y)==1||TV.get_pixel(x+12,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x+8,y)==1||TV.get_pixel(x+12,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x+4,y-4)==1||TV.get_pixel(x+8,y)==1||TV.get_pixel(x+4,y+4)==1) return 0;
                                        return 1;
                                break;

                        }
                break;

                case 4://I
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x+4,y)==1||TV.get_pixel(x+4,y+4)==1||TV.get_pixel(x+4,y+8)==1||TV.get_pixel(x+4,y+12)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x+16,y)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x+4,y)==1||TV.get_pixel(x+4,y-4)==1||TV.get_pixel(x+4,y-8)==1||TV.get_pixel(x+4,y-12)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x+4,y)==1) return 0;
                                        return 1;
                                break;

                        }
                break;

                case 5://L reverse
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x+4,y)==1||TV.get_pixel(x+4,y+4)==1||TV.get_pixel(x+4,y+8)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x+12,y)==1||TV.get_pixel(x+12,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x+4,y)==1||TV.get_pixel(x+4,y-4)==1||TV.get_pixel(x+8,y-8)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x+4,y)==1) return 0;
                                        return 1;
                                break;

                        }
                break;

                case 6://Strangely shaped
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x+8,y)==1||TV.get_pixel(x+8,y-4)==1||TV.get_pixel(x+4,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x+8,y)==1||TV.get_pixel(x+4,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x+8,y)==1||TV.get_pixel(x+8,y-4)==1||TV.get_pixel(x+4,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x+8,y)==1||TV.get_pixel(x+4,y-4)==1) return 0;
                                        return 1;
                                break;

                        }
                break;

                case 7://Strangely shaped reverse
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x+8,y)==1||TV.get_pixel(x+8,y+4)==1||TV.get_pixel(x+4,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x+4,y)==1||TV.get_pixel(x+8,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x+8,y)==1||TV.get_pixel(x+8,y+4)==1||TV.get_pixel(x+4,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x+4,y)==1||TV.get_pixel(x+8,y-4)==1) return 0;
                                        return 1;
                                break;

                        }
                break;
        }

}


int collision_check_left(int x,int y,int type,int angle){

        switch(type){
                case 1:
                         for(int j=0;j<block.hgt;j++) if(TV.get_pixel(x-2,y+j)==1) return 0;
                         return 1;
                break;

                case 2:
                         switch(angle){
                                case 0:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x-2,y+4)==1||TV.get_pixel(x-2,y+8)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x+6,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x-2,y-4)==1||TV.get_pixel(x-6,y-8)==1) return 0;
                                        return 1;
                                case 270:
                                        if(TV.get_pixel(x-10,y)==1||TV.get_pixel(x-10,y+4)==1) return 0;
                                        return 1;
                        }
                break;

                case 3:
                      switch(angle){
                                case 0:
                                        if(TV.get_pixel(x,y)==1||TV.get_pixel(x-2,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x+8-4,y-4)==1||TV.get_pixel(x,y)==1||TV.get_pixel(x+8-4,y+4)==1||TV.get_pixel(x+2,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x+2,y)==1||TV.get_pixel(x-2,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x-2,y-4)==1||TV.get_pixel(x-2,y)==1||TV.get_pixel(x-2,y+4)==1) return 0;
                                        return 1;
                                break;

                        }
                break;

                case 4:
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x-2,y+4)==1||TV.get_pixel(x-2,y+8)==1||TV.get_pixel(x-2,y+12)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x-2,y)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x-2,y-4)==1||TV.get_pixel(x-2,y-8)==1||TV.get_pixel(x-2,y-12)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x-14,y)==1) return 0;
                                        return 1;
                                break;

                        }
                break;

                case 5://L reverse
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x-2,y+4)==1||TV.get_pixel(x-6,y+8)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x-2+8,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x-2,y-4)==1||TV.get_pixel(x-2,y-8)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x-10,y)==1||TV.get_pixel(x-10,y-4)==1) return 0;
                                        return 1;
                                break;

                        }
                break;

                case 6://Strangely shaped
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x,y-4)==1||TV.get_pixel(x-2,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x-6,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x,y-8)==1||TV.get_pixel(x-2,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x-6,y-4)==1) return 0;
                                        return 1;
                                break;

                        }
                break;

                case 7://Strangely shaped reverse
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x-2,y-4)==1||TV.get_pixel(x,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x-6,y)==1||TV.get_pixel(x-2,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x-2,y-4)==1||TV.get_pixel(x,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x-6,y)==1||TV.get_pixel(x-2,y-4)==1) return 0;
                                        return 1;
                                break;

                        }
                break;
        }

}

int collision_check_down(int x,int y,int type,int angle){

        switch(type){
                case 1:
                         for(int i=0;i<block.wdt;i++) if(TV.get_pixel(x+i,y+block.hgt+1)==1) return 0;
                         return 1;
                break;

                case 2:
                         switch(angle){
                                case 0:
                                        if(TV.get_pixel(x,y+12)==1||TV.get_pixel(x+4,y+12)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x+4,y+4)==1||TV.get_pixel(x+8,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x-4,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x-4,y+4)==1||TV.get_pixel(x-8,y+8)==1) return 0;
                                        return 1;
                                break;
                        }
                break;

                case 3:
                       switch(angle){
                                case 0:
                                        if(TV.get_pixel(x,y+8)==1||TV.get_pixel(x+4,y+8)==1||TV.get_pixel(x+8,y+8)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x+4,y+4)==1||TV.get_pixel(x+8,y+8)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x,y)==1||TV.get_pixel(x+4,y+4)==1||TV.get_pixel(x+8,y)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x,y+8)==1||TV.get_pixel(x+4,y+4)==1) return 0;
                                        return 1;
                                break;

                        }
                break;

                case 4:
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x,y+16)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x+4,y+4)==1||TV.get_pixel(x+8,y+4)==1||TV.get_pixel(x+12,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x-4,y+4)==1||TV.get_pixel(x-8,y+4)==1||TV.get_pixel(x-12,y+4)==1) return 0;
                                        return 1;
                                break;

                        }
                 break;

                 case 5://L reverse
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x,y+12)==1||TV.get_pixel(x-4,y+12)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x+4,y+4)==1||TV.get_pixel(x+8,y+8)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x+4,y-4)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x-4,y+4)==1||TV.get_pixel(x-8,y+4)==1) return 0;
                                        return 1;
                                break;

                        }
                break;

                case 6://Strangely shaped
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x,y+8)==1||TV.get_pixel(x+4,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x-4,y)==1||TV.get_pixel(x,y+4)==1||TV.get_pixel(x+4,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x,y+8)==1||TV.get_pixel(x+4,y+4)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x-4,y)==1||TV.get_pixel(x,y+4)==1||TV.get_pixel(x+4,y+4)==1) return 0;
                                        return 1;
                                break;

                        }
                break;

                case 7://Strangely shaped reverse
                     switch(angle){
                                case 0:
                                        if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x+4,y+8)==1) return 0;
                                        return 1;
                                break;

                                case 90:
                                        if(TV.get_pixel(x-4,y+4)==1||TV.get_pixel(x,y+4)==1||TV.get_pixel(x+4,y)==1) return 0;
                                        return 1;
                                break;

                                case 180:
                                        if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x+4,y+8)==1) return 0;
                                        return 1;
                                break;

                                case 270:
                                        if(TV.get_pixel(x-4,y+4)==1||TV.get_pixel(x,y+4)==1||TV.get_pixel(x+4,y)==1) return 0;
                                        return 1;
                                break;

                        }
                break;

        }

}

//-----------------------
//---ROTATION FUNCTION---
//-----------------------

int check_turn(int x,int y,int type,int angle){

    if(y<8) return 0;

    switch(type){
            case 2:
                    switch(angle){

                            case 0:
                                    if(TV.get_pixel(x+4,y)==1||TV.get_pixel(x+8,y)==1||TV.get_pixel(x+8,y-4)==1||x>90-5) return 0;
                                    return 1;
                            break;

                            case 90:
                                    if(TV.get_pixel(x,y-4)==1||TV.get_pixel(x,y-8)==1||TV.get_pixel(x-4,y-8)==1||x<0+5) return 0;
                                    return 1;
                            break;

                            case 180:
                                    if(TV.get_pixel(x-4,y)==1||TV.get_pixel(x-8,y)==1||TV.get_pixel(x-8,y+4)==1||x<0+10||y>90-10) return 0;
                                    return 1;
                            break;

                            case 270:
                                    if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x,y+8)==1||TV.get_pixel(x+4,y+8)==1||x>90-5||y>90-10) return 0;
                                    return 1;
                            break;
                    }
            break;

            case 3:
                    switch(angle){

                            case 0:
                                    if(TV.get_pixel(x+8,y-4)==1||TV.get_pixel(x+8,y)==1) return 0;
                                    return 1;
                            break;

                            case 90:
                                    if(TV.get_pixel(x,y-4)==1||TV.get_pixel(x+4,y-4)==1||x<0+2) return 0;
                                    return 1;
                            break;

                            case 180:
                                    if(TV.get_pixel(x,y)==1||TV.get_pixel(x,y+4)==1||y>90-5) return 0;
                                    return 1;
                            break;

                            case 270:
                                    if(TV.get_pixel(x+4,y+4)==1||TV.get_pixel(x+8,y+4)==1) return 0;
                                    return 1;
                            break;

                    }

            break;

            case 4:
                    switch(angle){

                            case 0:
                                    if(TV.get_pixel(x+4,y)==1||TV.get_pixel(x+8,y)==1||TV.get_pixel(x+12,y)==1||x>90-15) return 0;
                                    return 1;
                            break;

                            case 90:
                                    if(TV.get_pixel(x,y-4)==1||TV.get_pixel(x,y-8)==1||TV.get_pixel(x-12,y)==1||y<15) return 0;
                                    return 1;
                            break;

                            case 180:
                                    if(TV.get_pixel(x-4,y)==1||TV.get_pixel(x-8,y)==1||TV.get_pixel(x-12,y)==1||x<13) return 0;
                                    return 1;
                            break;

                            case 270:
                                    if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x,y+8)==1||TV.get_pixel(x,y+12)==1||y>90-15) return 0;
                                    return 1;
                            break;

                    }

            break;

            case 5:
                    switch(angle){

                            case 0:
                                    if(TV.get_pixel(x+4,y)==1||TV.get_pixel(x+8,y)==1||TV.get_pixel(x+8,y+4)==1||x>90-15) return 0;
                                    return 1;
                            break;

                            case 90:
                                    if(TV.get_pixel(x,y-4)==1||TV.get_pixel(x,y-8)==1||TV.get_pixel(x-4,y-8)==1||x<0+5) return 0;
                                    return 1;
                            break;

                            case 180:
                                    if(TV.get_pixel(x-4,y)==1||TV.get_pixel(x-8,y)==1||TV.get_pixel(x-8,y+4)==1||x<0+10||y>90-10) return 0;
                                    return 1;
                            break;

                            case 270:
                                    if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x,y+8)==1||TV.get_pixel(x+4,y+8)==1||x>90-5||y>90-10) return 0;
                                    return 1;
                            break;
                    }
            break;

            case 6:
                    switch(angle){

                            case 0:
                                    if(TV.get_pixel(x,y-4)==1||TV.get_pixel(x-2,y-4)==1) return 0;
                                    return 1;
                            break;

                            case 90:
                                    if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x+4,y-4)==1) return 0;
                                    return 1;
                            break;

                            case 180:
                                    if(TV.get_pixel(x,y-4)==1||TV.get_pixel(x-2,y-4)==1) return 0;
                                    return 1;
                            break;

                            case 270:
                                    if(TV.get_pixel(x,y+4)==1||TV.get_pixel(x+4,y-4)==1) return 0;
                                    return 1;
                            break;
                    }
            break;

            case 7:
                    switch(angle){

                            case 0:
                                    if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x+4,y-4)==1) return 0;
                                    return 1;
                            break;

                            case 90:
                                    if(TV.get_pixel(x-2,y-4)==1||TV.get_pixel(x,y+4)==1) return 0;
                                    return 1;
                            break;

                            case 180:
                                    if(TV.get_pixel(x-2,y)==1||TV.get_pixel(x+4,y-4)==1) return 0;
                                    return 1;
                            break;

                            case 270:
                                    if(TV.get_pixel(x-2,y-4)==1||TV.get_pixel(x,y+4)==1) return 0;
                                    return 1;
                            break;
                    }
            break;


    }
}

//Clears the row
bool row_check(int xedge,int yedge){

  while(true){

          int ymin=100;
          bool white_row=true;

          for(int j=yedge-1;j>=3;j-=4){

                  white_row=true;

                  for(int i=2;i<xedge-3;i+=4)
                          if(TV.get_pixel(i,j)==0){
                                  white_row=false;
                          }

                  if(white_row==true&&j<ymin) ymin=j;
          }

          if(ymin==100) return false;

          rowsound();

          for(int i=2;i<xedge;i++)
                  for(int j=ymin;j>ymin-3;j--) TV.set_pixel(i,j,BLACK);

          for(int i=xedge-1;i>=2;i--)
                  for(int j=ymin-4;j>=3;j--)
                          if(TV.get_pixel(i,j)==1){
                                  TV.set_pixel(i,j,BLACK);
                                  TV.set_pixel(i,j+4,WHITE);
                          }

           score+=200;
           lines++;
           if(lines%5==0&&fall_interval>20&&lines>0) {
                   fall_interval-=20;
                   slow_fall-=20;
           }

           //Kludge, last row is never erased. It seems that the yedge value is actually 4 pixels smaller than it ought to be
           row_check(xedge,yedge+4);

   }

   row_delay=millis();
   fall_interval=slow_fall;

}


/*****************************
*******SOUND FUNCTIONS********
*****************************/

//----------MAIN MENU---------
//----------------------------


  void cursorsound(){
       TV.tone(300,100);
       delay(50);
       TV.tone(250,100);
       delay(50);
       TV.tone(200,100);
       delay(50);
  }

  void selectionsound(){
       TV.tone(500,100);
       delay(50);
       TV.tone(400,80);
       delay(40);
  }


  //-----TETRIS SOUND EFFECTS ------
  //--------------------------------


  //-----SNAKE SOUND EFFECTS -------
  //--------------------------------

  void applesound(){
       TV.tone(1000,120);
       delay(50);
       TV.tone(800,95);
       delay(30);
       TV.tone(500,80);
       delay(60);
       TV.tone(300,80);
       delay(30);
  }

  //-----PONG SOUND EFFECTS --------
  //--------------------------------

  void reflectionsound(){
       TV.tone(200,120);
       delay(20);
       TV.tone(100,95);
       delay(30);
  }

  void goalsound(){
       TV.tone(700,120);
       delay(50);
       TV.tone(800,95);
       delay(30);
       TV.tone(900,80);
       delay(20);
  }

  //-----SPACE IMPACT SOUND EFFECTS-----
  //------------------------------------

  void shot_sound(){
        TV.tone(1400,600);
        delay(30);
        TV.tone(800,600);
        delay(20);
        TV.tone(600,1000);
        delay(50);
        TV.tone(800,600);
        delay(30);  
  }

/******************************
*******************************
**********GAME MUSIC***********
*******************************
******************************/

int theme_A[]={
    NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
    NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
    NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
    NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
    NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
    NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
    NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
    NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
    NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
    NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
    NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
    NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
    NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
    NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
    NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
    NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
    NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
    NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
    NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
    NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
    NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3, 
    NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3
};

int duration_theme_A[]={
    8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
    8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
    8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
};


int cutman[]={

   NOTE_A5,NOTE_A5,0,NOTE_B4,NOTE_C5,NOTE_D5,0,NOTE_C5,NOTE_B4,
   //
   0,NOTE_C5,NOTE_E4,
   NOTE_A5,NOTE_A5,0,NOTE_B4,NOTE_C5,NOTE_D5,0,NOTE_C5,NOTE_B4,
   0,NOTE_D5,NOTE_E5,
   //
   NOTE_F5,NOTE_F5,0,NOTE_F5,NOTE_G5,NOTE_F5,0,NOTE_E5,NOTE_D5,
   NOTE_E5,NOTE_E5,0,NOTE_E5,NOTE_F5,NOTE_E5,0,NOTE_D5,NOTE_C5,
   NOTE_DS5,NOTE_E5,0,NOTE_B4,NOTE_B4,NOTE_CS5,NOTE_E5,
   //
   NOTE_E5,
   NOTE_A5,NOTE_A5,0,NOTE_B4,NOTE_C5,NOTE_D5,0,NOTE_C5,NOTE_B4,
   0,NOTE_C5,NOTE_E4,
   //
   NOTE_A5,NOTE_A5,0,NOTE_B4,NOTE_C5,NOTE_D5,0,NOTE_C5,NOTE_B4, 
   0,NOTE_D5,NOTE_E5,
   NOTE_F5,NOTE_F5,0,NOTE_F5,NOTE_G5,NOTE_F5,0,NOTE_E5,NOTE_D5,
   //
   NOTE_F5,NOTE_F5,0,NOTE_F5,NOTE_G5,NOTE_F5,0,NOTE_E5,NOTE_D5,
   NOTE_B4,NOTE_A4,NOTE_GS4,NOTE_FS4,NOTE_A4,
   NOTE_A4,NOTE_A3,NOTE_A3,NOTE_B3,NOTE_C4,NOTE_D4,NOTE_F4,NOTE_G4,NOTE_A4,
   //
   NOTE_B4,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5,NOTE_B5,NOTE_A5,
   NOTE_G5,
   NOTE_F5,NOTE_G5,NOTE_F5,
   //
   NOTE_E5,NOTE_F5,NOTE_FS5,NOTE_G5,0,
   NOTE_A5,NOTE_A5,NOTE_A5,NOTE_B5,NOTE_A5,
   NOTE_G5,NOTE_G5,NOTE_D6,NOTE_C6,
   //
   NOTE_A5,NOTE_A5,NOTE_A5,NOTE_A5,NOTE_A5,NOTE_A5,0,NOTE_A5,NOTE_A5,NOTE_A5,NOTE_B5,NOTE_A5,
   NOTE_A5,NOTE_GS5
  
};

float cutman_duration[]={

    16,16/3,16,8,16,8,16,8,16,
    //
    16,16,8/7,
    16,16/3,4,16,8,16,16,8,16,
    16,16,8/7,
    //
    16,16/3,4,16,8,16,16,8,16,
    16,16/3,4,16,8,16,16,8,16,
    16,16/3,8,4,8,8,8,
    //
    1,
    16,16/3,4,16,8,16,16,8,16,
    16,16,8/7,
    //
    16,16/3,4,16,8,16,16,8,16,
    16,16,8/7,
    16,16/3,4,16,8,16,16,8,16,
    //
    16,16/3,4,16,8,16,16,8,16,
    8/3,4,8,8,8,
    2,16,16,16,16,16,16,16,16,
    //
    16,16,16,16,16,16/5,4,8,
    8/5,4,8,
    //
    8,8,8,8,2,
    8,4,4,4,8,
    8,8,8,8/5,
    //
    16,8,16,8,16,16,16,16,8,8,8,
    2,2
        
};


int game_over_theme[]={
    
     0,NOTE_B3,NOTE_C4,NOTE_E4,NOTE_D4,NOTE_E4,NOTE_FS4,NOTE_GS4,NOTE_E4,NOTE_F4,NOTE_A4,NOTE_C5,NOTE_F4,NOTE_A4,NOTE_C5,NOTE_DS5,
     0,NOTE_G5,0,NOTE_FS5,NOTE_D5,0,
         
};

float game_over_theme_duration[]={

       16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
       8,8,16,16/3,4,4
      
 };

 int MM3_intro[]={
   
        //MM3 TITLE Delay 3.7
        NOTE_CS5,0,NOTE_F4,NOTE_A4,NOTE_B4,
        NOTE_CS5,NOTE_A4,NOTE_F4,NOTE_FS5,NOTE_E4,
        NOTE_D4,0,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_A4,
        NOTE_G4,NOTE_A4,NOTE_G4,
        NOTE_CS5,NOTE_A4,NOTE_F4,NOTE_E4,NOTE_F4,NOTE_A4,
        NOTE_G4,NOTE_A4,NOTE_B4,NOTE_CS5,NOTE_B4,
        NOTE_B4,NOTE_A4,NOTE_F4,NOTE_A4,NOTE_C6,NOTE_B5,
        NOTE_B5,NOTE_A5,NOTE_FS5,NOTE_A5,0,NOTE_A5,NOTE_B5,
        NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_CS5,NOTE_DS5,NOTE_FS5,
        NOTE_CS5,NOTE_D5,NOTE_FS5,NOTE_B5,
        NOTE_A5,NOTE_FS5,NOTE_D5,NOTE_FS5,NOTE_D5,NOTE_CS5,NOTE_E5,NOTE_FS5,//13th*/
        NOTE_B4,NOTE_CS5,NOTE_E5,NOTE_F5,NOTE_A5,NOTE_B5,
        NOTE_CS6,NOTE_B5,0,NOTE_B5,NOTE_A5,NOTE_FS5,NOTE_A5,NOTE_GS5,
        NOTE_C6,NOTE_F6,NOTE_G6,NOTE_A5,NOTE_B5,NOTE_E6,
        NOTE_CS5,0,NOTE_CS5,NOTE_B4,NOTE_CS5,0,NOTE_B4,NOTE_CS5,0,NOTE_B4,NOTE_CS5,0,NOTE_CS5,NOTE_B4,
        NOTE_CS5,0,NOTE_CS5,NOTE_B4,NOTE_CS5,0,NOTE_B4,NOTE_CS5,0,NOTE_B4,NOTE_CS5,0,NOTE_CS5,NOTE_B4,
        NOTE_A4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_CS5,NOTE_A4,NOTE_B4,NOTE_CS5,NOTE_DS5,NOTE_D5,NOTE_CS5,NOTE_B4,
        NOTE_GS5,NOTE_FS5,NOTE_CS5,NOTE_GS5,NOTE_FS5,NOTE_CS5,NOTE_GS5,NOTE_FS5,NOTE_CS5,NOTE_GS5,NOTE_FS5,NOTE_CS5,NOTE_GS5,NOTE_FS5,NOTE_DS5,NOTE_CS5,
        //Intro ends
        0,NOTE_B4,NOTE_CS5,NOTE_B4,NOTE_E5,NOTE_DS5,
        NOTE_B4,NOTE_E5,0,NOTE_DS5,0,NOTE_CS5,0,NOTE_B4,
        0,NOTE_B4,NOTE_CS5,NOTE_B4,NOTE_E5,NOTE_DS5,
        NOTE_B4,NOTE_E5,0,NOTE_DS5,0,NOTE_CS5,NOTE_E5,NOTE_GS5,
        NOTE_FS5,NOTE_E5,0,NOTE_CS5,NOTE_E5,NOTE_GS5,
        NOTE_FS5,NOTE_E5,0,NOTE_DS5,0,NOTE_E5,
        NOTE_DS5,NOTE_CS5,NOTE_DS5,NOTE_B4,0,
        NOTE_B4,NOTE_CS5,0,NOTE_CS5,
        //29
        0,NOTE_CS5,NOTE_E5,NOTE_CS5,NOTE_B5,NOTE_CS5,NOTE_A5,NOTE_CS5,
        NOTE_GS5,NOTE_CS5,NOTE_FS5,NOTE_CS5,NOTE_E5,NOTE_FS5,0,NOTE_GS5,
        NOTE_E5,NOTE_CS5,NOTE_B4,NOTE_CS5,NOTE_E5,0,NOTE_FS5,
        NOTE_E5,NOTE_CS5,NOTE_B4,NOTE_CS5,0,NOTE_CS5,0,NOTE_CS5,
        0,NOTE_CS5,NOTE_E5,NOTE_CS5,NOTE_B5,NOTE_CS5,NOTE_A5,NOTE_CS5,
        NOTE_GS5,NOTE_CS5,NOTE_FS5,NOTE_CS5,NOTE_E5,NOTE_FS5,
        NOTE_GS5,0,NOTE_GS5,NOTE_FS5,NOTE_FS5,0,NOTE_GS5,NOTE_FS5,NOTE_GS5,
        NOTE_C6,0,NOTE_C6,NOTE_B5,NOTE_C6,0,NOTE_B5,NOTE_C6,
 };


float MM3_intro_duration[]={

      2,8,8,8,8,
      2,8,8,8,8,
      2,128,8,8,8,8/5,
      8,8,8,
      8,8,8,8,8,4,
      4,4,4,8,8,
      8,8,8,4,16,16,
      8,8,8,4,128,8,8,
      8,8,8,8,8,8,4,
      4,4,4,4,
      4,8,4,4,8,2,8,8,//13*/
      6,6,6,6,6,6,
      16,16,128,8,16/3,16/3,16/3,16/3,
      6,6,6,6,6,6,
      16,128,16,16,16,16,8,16,16,8,16,128,8,8,
      16,128,16,16,16,16,8,16,16,8,16,128,8,8,
      16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
      16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
      //Intro ends
      8,8,8,8,4,4,
      8,8,8,8,8,8,8,8,
      8,8,8,8,4,4,
      8,8,8,8,8,8,8,16/3,
      8,8,8,8,8,16/3,
      8,8,8,8,8,16/3,
      8,4,4,4,128,
      8,8,8,8/5,
      8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,16/3,
      8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,
      8,8,8,8,8,16/3,
      8,128,8,8,4,8,128,8,8,
      8,128,8,8,8,8,8,4,        
};


