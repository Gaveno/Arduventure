#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
#include <ATMlib.h>
#include "bitmaps.h"


#define EEPROM_START                  16

//define menu states (on main menu)
#define STATE_MENU_INTRO              0
#define STATE_MENU_MAIN               1
#define STATE_MENU_CONTINUE           2
#define STATE_MENU_NEW                3
#define STATE_MENU_SOUND              4
#define STATE_MENU_CREDITS            5

//define game states (on main menu)
#define STATE_GAME_PLAYING            6
#define STATE_GAME_INVENTORY          7
#define STATE_GAME_EQUIP              8
#define STATE_GAME_STATS              9
#define STATE_GAME_MAP                10
#define STATE_GAME_OVER               11


#define STATE_GAME_ITEMS              12
#define STATE_GAME_WEAPON             13
#define STATE_GAME_ARMOR              14
#define STATE_GAME_AMULET             15

#define WALKING_THROUGH_DOOR          16

#define STATE_GAME_BATTLE             17

#define STATE_GAME_BOSS               18

#define STATE_GAME_INTRO              19
#define STATE_GAME_NEW                20
#define STATE_GAME_SAVE               21
#define STATE_GAME_SOUND              22
#define STATE_GAME_END                23

#define FACING_SOUTH                  0 //0B00000000
#define FACING_WEST                   1 //0B00000001
#define FACING_NORTH                  2 //0B00000010
#define FACING_EAST                   3 //0B00000011

#define LIST_SHOP_SELLS               0
#define LIST_SHOP_BUYS                1
#define LIST_OF_ITEMS                 2
#define LIST_OF_WAEPON                3
#define LIST_OF_ARMOR                 4
#define LIST_OF_AMULET                5

#define PLAYER_START_X                2240  //140
#define PLAYER_START_Y                2976  //186

#define TOTAL_REGIONS                 20
#define LEVEL_CHUNK_W                 32
#define LEVEL_CHUNK_H                 33
#define TOTAL_DOORS                   56

#define REGION_FOREST_CANYON          0
#define REGION_SWAMP_FOREST           1
#define REGION_FIELDS_SWAMP           2
#define REGION_FIELDS_CANYONS         3
#define REGION_SWAMP_ISLAND_ONE       4
#define REGION_SWAMP_ISLAND_TWO       5
#define REGION_LONG_ROAD              6
#define REGION_APPLE_FARM             7
#define REGION_YOUR_GARDEN            8

#define REGION_FIELDS                 9
#define REGION_SWAMP                  10
#define REGION_FOREST                 11
#define REGION_CANYONS                12

#define REGION_HOUSE_INTERIOR         13
#define REGION_INN_INTERIOR           14
#define REGION_YOUR_INTERIOR          15
#define REGION_SHOP_INTERIOR          16
#define REGION_TREE_INTERIOR          17
#define REGION_CAVE_INTERIOR          18

#define REGION_ALL_BLACK              19

#define EYES_SPEED                    4


Arduboy2Base arduboy;
Sprites sprites;
ATMsynth ATM;

byte gameState = STATE_MENU_INTRO;           // start the game with the TEAM a.r.g. logo
byte previousGameState = STATE_MENU_INTRO;
byte globalCounter = 0;
byte currentLetter = 0;
byte cursorX = 0;
byte cursorY = 0;
boolean cursorYesNoY = true;
boolean question = false;
boolean yesNo = false;
boolean frameBoolean = true;
boolean counterDown = false;
boolean investigating = false;
boolean talkingWithNPC = false;
boolean foundSomething = false;
boolean firstGame = true;
boolean flashBlack = false;
boolean flashWhite = false;
byte fadeCounter = 0;
byte randomCounter = 0;
byte battleProgress;
byte textRollAmount = 0;
byte eyesFrame = 0;
byte songPlaying = 0;


Point cam = {.x = 0, .y = 0 };
Point mini_cam = {.x = 0, .y = 0 };

const unsigned char PROGMEM eyesSeq[] = { 2, 1, 0, 1 };

void clearCursor()
{
  cursorY = 0;
  cursorX = 0;
}

void drawRectangle(byte startX, byte startY, byte endX, byte endY, byte color )
{
  byte rectangleX = startX;
  while (startY < endY)
  {
    if (!color)sprites.drawErase(rectangleX, startY, font, 56);
    else sprites.drawSelfMasked(rectangleX, startY, font, 56);
    rectangleX += 5;
    if (rectangleX > endX - 5)
    {
      startY += 8;
      rectangleX = startX;
    }
  }
}

byte bitCount(byte toCount)
{
  byte amountOfBits = 0;
  for (byte i = 0; i < 8; i++) amountOfBits += bitRead(toCount, i);
  return amountOfBits;
}



void showFadeOutIn()
{
  byte transitionTileX = 0;
  byte transitionTileY = 0;
  for (byte i = 0; i < 128; i++)
  {
    sprites.drawErase(transitionTileX, transitionTileY, transitionSet, fadeCounter % 7);
    transitionTileX += 8;
    if (transitionTileX > 127)
    {
      transitionTileX = 0;
      transitionTileY += 8;
    }
  }
}

byte generateRandomNumber(byte maxValue)
{
  randomCounter += arduboy.frameCount;
  int nr = randomCounter;
  nr *= maxValue * 10;
  nr /= 2560;

  return nr;
}

void blinkingEyes(byte x, byte y)
{
  byte blinking = (eyesFrame % 40 < 4) ? (eyesFrame % 40 ) : 0;
  sprites.drawSelfMasked(x, y, eyesBlinking, pgm_read_byte(&eyesSeq[blinking]));
}

void updateEyes()
{
  if (arduboy.everyXFrames(EYES_SPEED)) eyesFrame = (++eyesFrame) % 80;
}

void flashScreen(byte color)
{
  if (fadeCounter < 6)
  {
    if (arduboy.everyXFrames(12))
    {
      counterDown = !counterDown;
      fadeCounter++;
    }
    if (counterDown) arduboy.fillScreen(color);
  }
  else
  {
    flashBlack = false;
    flashWhite = false;
  }
}


#endif
