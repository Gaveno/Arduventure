#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"
#include "text.h"


#define PLAYER_START_X               2240  //140
#define PLAYER_START_Y               2976  //170
#define ANIMATION_SPEED              8                  // higher number = slower animation
#define MAX_LEVEL                    40
#define HP_PER_LEVEL                 6
#define MP_PER_LEVEL                 6
#define ATK_PER_LEVEL                3
#define DEF_PER_LEVEL                4
#define SPD_PER_LEVEL                5
#define EXP_MULTIPLIER               30


const unsigned char PROGMEM animSeq[] = { 0, 1, 2, 1 };
const unsigned char PROGMEM collisionPoints[][2] =
{
  // Collision points for walking {x, y}
  // FACING_SOUTH
  {12, 16},
  {3, 16},
  // FACING_WEST
  {1, 14},
  {1, 9},
  // FACING_NORTH
  {3, 7},
  {12, 7},
  // FACING_EAST
  {14, 9},
  {14, 14},

  // Collision points for investigating {x, y}
  // FACING_SOUTH
  {11, 19},
  // FACING_WEST
  {0, 9},
  // FACING_NORTH
  {11, 0},
  // FACING_EAST
  {21, 9},
};


struct Player
{
  int x, y;
  byte health, healthTotal, magic, magicTotal;
  int gold;
  byte experience, experienceTotal;
  byte currentRegion, level, attack, attackAddition, defense, defenseAddition, speed, speedAddition, lastDoor, bossCardRegionRoaming, bossActiveAlive;
  unsigned char gameTriggers[4];
  unsigned char hasStuff[8];
  unsigned char itemsAmount[8];
  unsigned char name[6];
  unsigned char mapFog[2];
};

Player player;

byte playerFrame;
byte playerDirection;
byte playerSteps;
boolean playerWalking;

byte playerReducedX;
byte playerReducedY;

void updatePlayer()
{
  playerReducedX = player.x / 96;
  playerReducedY = player.y / 96;
}

void setPlayer()
{
  playerDirection = FACING_SOUTH;
  playerSteps = 0;
  playerWalking = false;
  player =
  {
    PLAYER_START_X, PLAYER_START_Y,           // position
    20, 20,                                   // health
    10, 10,                                   // magic
    0,                                        // gold
    0, 200,                                   // experience
    REGION_YOUR_INTERIOR,                     // currentRegion
    1,                                        // level
    5, 0,                                     // attack
    7, 0,                                     // defense
    3, 0,                                     // speed
    48,                                       // lastDoor is your house
    0B00010000,                               // bossCardRegionRoaming
    //|||||||└---------------------------------> 0 YOU HAVE BOSS CARD ONE   (0 = false / 1 = true)
    //||||||└----------------------------------> 1 YOU HAVE BOSS CARD TWO   (0 = false / 1 = true)
    //|||||└-----------------------------------> 2 YOU HAVE BOSS CARD THREE (0 = false / 1 = true)
    //||||└------------------------------------> 3 YOU HAVE BOSS CARD FOUR  (0 = false / 1 = true)
    //|||└-------------------------------------> 4  \
    //||└--------------------------------------> 5   | ROAMING REGION  (1 = FIELDS, 2 = SWAMP, 3= FORREST, 4 = CANYON)
    //|└---------------------------------------> 6  /
    //└----------------------------------------> 7

    0B00000000,                               // bossActiveAlive
    //|||||||└-------------------------------->  0 BOSS ONE is alive        (0 = false / 1 = true)
    //||||||└--------------------------------->  1 BOSS TWO is alive        (0 = false / 1 = true)
    //|||||└---------------------------------->  2 BOSS THREE is alive      (0 = false / 1 = true)
    //||||└----------------------------------->  3 BOSS FOUR is alive       (0 = false / 1 = true)
    //|||└------------------------------------>  4
    //||└------------------------------------->  5 \
    //|└-------------------------------------->  6  | amount of blade pieces found : 0 till 4
    //└--------------------------------------->  7 /

    { // gameTriggers
      0B00000000,                             // chests
      //|||||||└-------------------------------> 0 chest  0 has been opened (0 = false / 1 = true) Tree Last.Door 0 FIELDS
      //||||||└--------------------------------> 1 chest  1 has been opened (0 = false / 1 = true) Tree Last.Door 1 FIELDS
      //|||||└---------------------------------> 2 chest  2 has been opened (0 = false / 1 = true) Tree Last.Door 2 FIELDS
      //||||└----------------------------------> 3 chest  3 has been opened (0 = false / 1 = true) Tree Last.Door 3 FIELDS
      //|||└-----------------------------------> 4 chest  4 has been opened (0 = false / 1 = true) Tree Last.Door 4 FIELDS
      //||└------------------------------------> 5 chest  5 has been opened (0 = false / 1 = true) Tree Last.Door 5 FIELDS
      //|└-------------------------------------> 6 chest  6 has been opened (0 = false / 1 = true) Tree Last.Door 6 FIELDS
      //└--------------------------------------> 7 chest  7 has been opened (0 = false / 1 = true) Tree Last.Door 7 FIELDS

      0B00000000,                             // chests
      //|||||||└-------------------------------> 0 chest  8 has been opened (0 = false / 1 = true) Tree Last.Door 8  SWAMP
      //||||||└--------------------------------> 1 chest  9 has been opened (0 = false / 1 = true) Tree Last.Door 9  SWAMP
      //|||||└---------------------------------> 2 chest 10 has been opened (0 = false / 1 = true) Tree Last.Door 10 SWAMP
      //||||└----------------------------------> 3 chest 11 has been opened (0 = false / 1 = true) Tree Last.Door 11 SWAMP
      //|||└-----------------------------------> 4 chest 12 has been opened (0 = false / 1 = true) Tree Last.Door 12 SWAMP
      //||└------------------------------------> 5 chest 13 has been opened (0 = false / 1 = true) Tree Last.Door 13 FOREST
      //|└-------------------------------------> 6 chest 14 has been opened (0 = false / 1 = true) Tree Last.Door 14 FOREST
      //└--------------------------------------> 7 chest 15 has been opened (0 = false / 1 = true) Tree Last.Door 15 FOREST

      0B00000000,                             // chests
      //|||||||└-------------------------------> 0 chest 16 has been opened (0 = false / 1 = true) Tree Last.Door 16 CANYON
      //||||||└--------------------------------> 1 chest 17 has been opened (0 = false / 1 = true) Tree Last.Door 17 CANYON
      //|||||└---------------------------------> 2 chest 18 has been opened (0 = false / 1 = true) Tree Last.Door 18 CANYON
      //||||└----------------------------------> 3 chest 19 has been opened (0 = false / 1 = true) Tree Last.Door 19 CANYON
      //|||└-----------------------------------> 4 chest 20 has been opened (0 = false / 1 = true) Chest in your house
      //||└------------------------------------> 5 chest 21 has been opened (0 = false / 1 = true) Chest on the Long Road
      //|└-------------------------------------> 6 chest 22 has been opened (0 = false / 1 = true) Chest in Swamp North
      //└--------------------------------------> 7 chest 23 has been opened (0 = false / 1 = true) Chest in Forrest Middle

      0B00001111,                             // Special triggers
      //|||||||└-------------------------------> 0 used amulet of fire  on rock       (0 = false / 1 = true)
      //||||||└--------------------------------> 1 used amulet of leafs on rock       (0 = false / 1 = true)
      //|||||└---------------------------------> 2 used amulet of water on rock       (0 = false / 1 = true)
      //||||└----------------------------------> 3 map in the shop has been found     (0 = false / 1 = true)
      //|||└-----------------------------------> 4 you have a fishing rod             (0 = false / 1 = true)
      //||└------------------------------------> 5 you have a fish                    (0 = false / 1 = true)
      //|└-------------------------------------> 6 you have a fire spark              (0 = false / 1 = true)
      //└--------------------------------------> 7                                    (0 = false / 1 = true)
    },
    {
      0B00000000,                             // hasItem
      0B00000000,                             // using the item
      //|||||||└-------------------------------> 0 apple
      //||||||└--------------------------------> 1 cider
      //|||||└---------------------------------> 2 anise
      //||||└----------------------------------> 3 absinthe
      //|||└-----------------------------------> 4 ruby
      //||└------------------------------------> 5 sapphire
      //|└-------------------------------------> 6 emerald
      //└--------------------------------------> 7 diamond

      0B00000000,                             // hasWeapon
      0B00000000,                             // equipedWaepon
      //|||||||└-------------------------------> 0 sling
      //||||||└--------------------------------> 1 knife
      //|||||└---------------------------------> 2 rapier
      //||||└----------------------------------> 3 sword
      //|||└-----------------------------------> 4 axe
      //||└------------------------------------> 5 lance
      //|└-------------------------------------> 6 spear
      //└--------------------------------------> 7 bow

      0B00000001,                             // hasArmorType
      0B00000001,                             // equipedArmorType
      //|||||||└-------------------------------> 0 wool
      //||||||└--------------------------------> 1 linen
      //|||||└---------------------------------> 2 leathr
      //||||└----------------------------------> 3 bone
      //|||└-----------------------------------> 4 copper
      //||└------------------------------------> 5 bronze
      //|└-------------------------------------> 6 iron
      //└--------------------------------------> 7 steel

      0B00000000,                             // hasAmulet
      0B00000000,                             // equipedAmulet
      //|||||||└-------------------------------> 0 fire
      //||||||└--------------------------------> 1 leafs
      //|||||└---------------------------------> 2 water
      //||||└----------------------------------> 3 luck
      //|||└-----------------------------------> 4 gold
      //||└------------------------------------> 5 cloak
      //|└-------------------------------------> 6 escape
      //└--------------------------------------> 7 ruby
    },

    //{1, 5, 3, 4, 7, 6, 9, 64},                 // amount of each item (max 64)
    {0, 0, 0, 0, 0, 0, 0, 0,},                   // amount of each item (max 64)

    {5, 50, 50, 50, 50, 50},                     // name
    { 0B00000000, 0B00000000},                   // Fog x and y coördinates
  };
}

/*
 * Give the player experience based on the level of the monster slain.
 * Handle level up if experience goes over experience needed.
 */
void gainExperience(byte enemy_level)
{
  int ex = (int)player.experience + enemy_level * EXP_MULTIPLIER / (player.level * (player.currentRegion - REGION_YOUR_GARDEN));
  if (ex > player.experienceTotal) {
    ex -= player.experienceTotal;
    player.level++;
    player.healthTotal += HP_PER_LEVEL;
    player.health = player.healthTotal;
    player.magicTotal += MP_PER_LEVEL;
    player.magic = player.magicTotal;
    player.attack += ATK_PER_LEVEL;
    player.defense += DEF_PER_LEVEL;
    player.speed += SPD_PER_LEVEL;
    levelup = true;
  }
  player.experience = (byte)ex;
}

/*
 * Cause damage to the player reducing health.
 */
void damagePlayer(byte enemy_attack)
{
  lastDamageDealt = max((int)enemy_attack * (int)player.level / (int)player.defense, 1);
  int php = (int)player.health - lastDamageDealt;
  player.health = max(php, 0);
}

void fillWithName(byte startPoint)
{
  for (byte i = 0; i < 7; i++)
  {
    if (i < player.name[0] + (startPoint ? 0 : 1)) textBox[startPoint + i] = player.name[i + (startPoint ? 1 : 0)];
    else textBox[startPoint + i] = SPACE;
  }
}

/*
 * Fill sentence helper.
 * Fill in player stat values to sentence.
 */
void fillWithPlayerStats(byte startPoint, byte value, byte valueTotal)
{
  byte xOffset = startPoint;
  fillWithNumber(xOffset, value);
  xOffset += 3;
  fillWithWord(xOffset, 43);
  xOffset++;
  fillWithNumber(xOffset, valueTotal);
}

void drawPlayer()
{
  if (playerWalking) {
    if (arduboy.everyXFrames(ANIMATION_SPEED)) playerFrame = (++playerFrame) % 4;
  }
  else playerFrame = 1;

  byte spriteFrame = (foundSomething) ? 1 : (pgm_read_byte(&animSeq[playerFrame]) + 3 * playerDirection);
  sprites.drawPlusMask(player.x - camX + 2, player.y - camY - (playerFrame % 2) + 1, playerHead_plus_mask, spriteFrame / 3);
  sprites.drawPlusMask(player.x - camX + 2, player.y - camY + 8, playerFeet_plus_mask, spriteFrame);
  if (spriteFrame == 1) blinkingEyes(player.x - camX + 6, player.y - camY + 7);
}

void showStatsTitle()
{
  fillWithSentence(8);
  fillWithName(10);
  drawTextBox(4, 2, WHITE, TEXT_NOROLL);

  drawRectangle(0, 10, 130, 64, WHITE);
}

void drawPlayerStats()
{
  showStatsTitle();

  fillWithSentence(6);
  fillWithNumber(7, player.gold);
  fillWithPlayerStats(20, player.health, player.healthTotal);
  fillWithPlayerStats(34, player.magic, player.magicTotal);
  fillWithPlayerStats(57, player.experience, player.experienceTotal);
  drawTextBox(4, 14, BLACK, TEXT_NOROLL);

  fillWithSentence(7);
  fillWithNumber(5, player.level);
  fillWithNumber(16, player.attack);
  fillWithNumber(26, player.defense);
  fillWithNumber(36, player.speed);
  drawTextBox(84, 14, BLACK, TEXT_NOROLL);
}

void drawPlayerObjects()
{
  showStatsTitle();
  fillWithSentence(61);
  fillWithNumber(20, player.bossActiveAlive >> 5);
  drawTextBox(4, 14, BLACK, TEXT_NOROLL);

  fillWithSentence(62);
  for (byte i = 0; i < 4; i++)
  {
    sprites.drawErase(34 + (i*24), 34, tileSheet, 0);
    if (player.bossCardRegionRoaming & (1 << i))
      sprites.drawSelfMasked(36 + (i*24), 38, miniMapSheet, (4 - i));
  }
  fillWithWord(31, 207);
  drawTextBox(4, 28, BLACK, TEXT_NOROLL);
}

void checkCam()
{
  camX = max(player.x - 56, 0);
  camY = max(player.y - 24, 0);

}

/*
 * Fill in bits allowing player to see on map.
 */
void discoverMap(int world_x, int world_y)
{
  // Make sure within map area (not inside)
  if (world_y > 2880) return;

  byte x = (world_x / 768);
  byte y = ((world_y / 768) * 4);

  player.mapFog[(x + y) / 8] |= _BV((x + y) % 8);

}

boolean getMapFog(byte fog_x, byte fog_y)
{
  byte x = (fog_x / 8);
  byte y = ((fog_y / 8) * 4);

  return (player.mapFog[(x + y) / 8] & _BV((x + y) % 8));
}

void saveGame()
{
  firstGame = false;
  EEPROM.write(EEPROM_START, GAME_ID);
  EEPROM.put(EEPROM_START + 1, player);
}

void loadGame()
{
  EEPROM.get(EEPROM_START + 1, player);
}

#endif