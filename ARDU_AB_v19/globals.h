#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
#include <ATMlib.h>
#include "bitmaps.h"


#define EEPROM_START                  16

//define menu states (on main menu)
#define STATE_MENU_INTRO              0  // stateMenuIntro
#define STATE_MENU_MAIN               1  // stateMenuMain
#define STATE_MENU_CONTINUE           2  // stateMenuContinue
#define STATE_MENU_NEW                3  // stateMenuNew
#define STATE_MENU_SOUND              4  // stateMenuSound
#define STATE_MENU_CREDITS            5  // stateMenuCredits

//define game states (on main menu)
#define STATE_GAME_PLAYING            6  // stateGamePlaying
#define STATE_GAME_INVENTORY          7  // stateGameInventory
#define STATE_GAME_EQUIP              8  // stateGameEquip
#define STATE_GAME_STATS              9  // stateGameStats
#define STATE_GAME_MAP                10  // stateGameMap
#define STATE_GAME_OVER               11  // stateGameOver


#define STATE_GAME_ITEMS              12  // showSubMenuStuff
#define STATE_GAME_WEAPON             13  // showSubMenuStuff
#define STATE_GAME_ARMOR              14  // showSubMenuStuff
#define STATE_GAME_AMULET             15  // showSubMenuStuff

#define WALKING_THROUGH_DOOR          16  // walkingThroughDoor

#define STATE_GAME_BATTLE             17  // stateGameBattle

#define STATE_GAME_BOSS               18  // stateGameBattle

#define STATE_GAME_INTRO              19  // stateGameIntro
#define STATE_GAME_NEW                20  // stateGameNew
#define STATE_GAME_SAVE               21  // stateGameSaveSoundEnd
#define STATE_GAME_SOUND              22  // stateGameSaveSoundEnd
#define STATE_GAME_END                23  // stateGameSaveSoundEnd
#define STATE_GAME_OBJECTS            24  // stateGameObjects

#define STATE_REBOOT                  25  // reprogramming instructions

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

#define TYPE_NORMAL                   0
#define TYPE_WATER                    1
#define TYPE_LEAF                     2
#define TYPE_FIRE                     3

#define BIT_1                         1
#define BIT_2                         2
#define BIT_3                         4
#define BIT_4                         8
#define BIT_5                         16
#define BIT_6                         32
#define BIT_7                         64
#define BIT_8                         128


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
byte globalFrame = 0;
byte songPlaying = 0;

// Keep track of last damage dealt
int lastDamageDealt = 0;
bool playerFirst = true;
byte attackType = 0; // 0 = physical, 1 = magic
bool levelup = false;

byte miniCamX = 0;
byte miniCamY = 0;
int camX = 0;
int camY = 0;

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

/*
 * !!!Maximum input value is 26!!!
 */
byte generateRandomNumber(byte maxValue)
{
  randomCounter += arduboy.frameCount;
  unsigned int nr = randomCounter;
  nr *= maxValue * 10;
  nr /= 2560;

  return nr;
}

void blinkingEyes(byte x, byte y)
{
  byte blinking = (globalFrame % 40 < 4) ? (globalFrame % 40 ) : 0;
  sprites.drawSelfMasked(x, y, eyesBlinking, pgm_read_byte(&eyesSeq[blinking]));
}

void updateEyes()
{
  if (arduboy.everyXFrames(EYES_SPEED)) globalFrame = (++globalFrame) % 80;
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
