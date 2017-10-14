#ifndef ENEMIES_H
#define ENEMIES_H

#include "globals.h"

#define ENEMY_WORM                              0
#define ENEMY_BEETLE                            1
#define ENEMY_BIRD                              2

const unsigned char PROGMEM enemyStartHealth[] =
{
  1,                    //ENEMY_WORM
  1, 2, 1 };

byte bossesActiveAlive = 0B00001111;
//                         ||||||||
//                         |||||||└->  0 BOSS ONE is alive     (0 = false / 1 = true)
//                         ||||||└-->  1 BOSS TWO is alive     (0 = false / 1 = true)
//                         |||||└--->  2 BOSS THREE is alive   (0 = false / 1 = true)
//                         ||||└---->  3 BOSS FOUR is alive    (0 = false / 1 = true)
//                         |||└----->  4 BOSS ONE is active    (0 = false / 1 = true)
//                         ||└------>  5 BOSS TWO is active    (0 = false / 1 = true)
//                         |└------->  6 BOSS THREE is active  (0 = false / 1 = true)
//                         └-------->  7 BOSS FOUR is active   (0 = false / 1 = true)

byte enemyAmount = 3;

//////// BOSS functions ////////////////////
////////////////////////////////////////////
struct Enemies
{
  byte enemyType,health;
};

Enemies enemy[5];

void checkBoss()
{
  // Check if we are in a cave and if the player is away from the entrance
  if ((player.currentRegion == REGION_CAVE_INTERIOR) && (player.y < 2936))
  {
    //check if the Boss in the current Region is Active and Alive
    if (bossesActiveAlive & (0B00010001 << (player.lastDoor - 28)) == (0B00010001 << (player.lastDoor - 28))) gameState = STATE_GAME_BOSS;
  }
}

void drawEnemies()
{
  for (byte i = 0; i < enemyAmount; i++)
  {
    sprites.drawSelfMasked(12 + (20*i), 16, enemySprites, i);
  }
}

void updateEnemies()
{
  
}




#endif
