#ifndef ENEMIES_H
#define ENEMIES_H

#include "globals.h"

/* Enemy Data
 *  Element type determines head image.
 *  Attack, defense, and 
 */

byte enemyAmount = 3;

//////// BOSS functions ////////////////////
////////////////////////////////////////////
struct Enemies
{
  byte type;
  byte health;
  byte defense;
  byte specDefense;
  byte attack;
  byte images;
  byte level;
  byte speed;
};

//Enemies enemy[5];
Enemies enemy;    // only one at a time for now

void createEnemy( )
{
  byte region = player.currentRegion - REGION_YOUR_GARDEN;
  byte lvlRange = (region) * 2;
  byte monster = generateRandomNumber(min(7, lvlRange));
  byte statType = generateRandomNumber(3);
  // get random level offset
  enemy.level = generateRandomNumber(lvlRange);
  enemy.images = ((enemy.level % 4) + statType * 4)  | (monster << 4);
  enemy.level++;
  region--;
  enemy.level += region * 5;
  enemy.type = (monster - 1) / 2;
  switch (statType)
  {
    case 0: // neutral
    enemy.defense = 3;
    enemy.specDefense = 3;
    enemy.health = 3;
    enemy.attack = 3;
    enemy.speed = 5;
    break;
    case 1: // high specDefense, high attack, low defense and health
    enemy.defense = 1;
    enemy.specDefense = 5;
    enemy.health = 2;
    enemy.attack = 6;
    enemy.speed = 6;
    break;
    default: // high defense and health, low specDefense and attack
    enemy.defense = 5;
    enemy.specDefense = 1;
    enemy.health = 4;
    enemy.attack = 2;
    enemy.speed = 4;
  }
  enemy.health *= enemy.level;
  enemy.defense *= enemy.level;
  enemy.specDefense *= enemy.level;
  enemy.attack *= enemy.level;
  enemy.speed *= enemy.level;
}

void damageEnemy(byte player_attack, byte player_attack_addition)
{
  lastDamageDealt = max(player_attack + player_attack_addition - enemy.defense, 1);
  int8_t ehp = (int8_t)enemy.health - lastDamageDealt;
  enemy.health = max(ehp, 0);
}

void drawEnemies(byte yoffset)
{
  sprites.drawOverwrite(57, 16 + yoffset, enemyHeads, enemy.images & 0x0F);
  sprites.drawOverwrite(56, 24 + yoffset, enemyFeet, enemy.images >> 4);
  //sprites.drawErase(58, 16, enemyHeads, 0);
  //sprites.drawErase(56, 24, enemyFeet, 0);
  /*for (byte i = 0; i < enemyAmount; i++)
  {
    sprites.drawSelfMasked(12 + (20*i), 16, enemyHeads, i);
  }*/
}

void updateEnemies()
{
  
}

void drawBoss()
{
  sprites.drawSelfMasked(52, 16, bossSprites, 0);
}




#endif
