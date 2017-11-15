#ifndef INVENTORY_H
#define INVENTORY_H

#include "globals.h"

void showInventory()
{
  fillWithSentence(4);
  drawTextBox(96, 2, WHITE, TEXT_NOROLL);
}

//byte returnObject

void investigateObjects(byte object)
{
  if (object == TILE_ROCK)          //31
  {
    if (bitRead(player.hasStuff[7], player.currentRegion))
    {
      bitSet(player.gameTriggers[3], player.currentRegion);
      fillWithSentence(55); // "a lightbeam emerges from your amulet..."
      flashWhite = true;
    }
    else
    {
      fillWithSentence(54); // "the rock has symbols resembling ______"
      fillWithWord(33, 121 + player.currentRegion); // fire,leaf,water
    }
    foundSomething = true;
  }
  
  if (object > TILE_WALL && object != TILE_BLACK)
  {
    byte regionComingFrom = (player.lastDoor - 28);
    switch (object)
    {
      case TILE_BED_LOW:            // 48
      case TILE_BED_UP:             // 49
        break;
      case TILE_SHELVE_LOW:         // 50
        if ((bitRead(player.gameTriggers[3], 3) == 0) && (player.x / 16 == 63) && (player.lastDoor == 24))
        {
          bitSet(player.gameTriggers[3], 3); // map?
          fillWithSentence(49);
          fillWithWord(23, 144);
        }
        else fillWithSentence(56);
        break;
      case TILE_TABLE:              // 52
        switch (player.lastDoor)
        {

          case 28:                  // CAVE FIELDS
          case 29:                  // CAVE SWAMP
          case 30:                  // CAVE FOREST
          case 31:                  // CAVE CANYON
            if (bitRead(player.bossActiveAlive, player.lastDoor - 28))
            {
              if (bitRead(player.bossCardRegionRoaming, player.lastDoor - 28))
              {
                gameState = STATE_GAME_BOSS;
              }
              else fillWithSentence(60);  // "shops sell books"
            }
            else fillWithSentence(44); // "nothing there to take"
            break;
          default:
            fillWithSentence(44); // "nothing there to take"
            break;
        }
        break;
      case TILE_SIGN:               // 56
        if ((player.currentRegion) == REGION_YOUR_GARDEN)
        {
          fillWithSentence(78);
          //fillWithName(34);
        }
        else
        {
          fillWithSentence(53);
          fillWithWord(24, 171  - player.currentRegion);
        }
        break;
      case TILE_CLOSED_BOX:         //57
        if ((player.lastDoor) == 48)
        {
          bitSet(player.hasStuff[2], 0);
          bitSet(player.gameTriggers[2], 4);
          fillWithSentence(50);
          fillWithWord(23, 105);
        }
        else
        {
          bitSet(player.gameTriggers[player.lastDoor / 8], player.lastDoor % 8);
          byte amount = ((player.lastDoor / 5) * 2) + 1;
          if ((player.lastDoor % 5) == 0)       // 1, 3, 5, 7 gold  lastDoor 0, 5, 10, 15
          {
            fillWithSentence(48);
            fillWithWord(11, 125);
            fillWithNumber(28, amount);
            player.gold += amount;
          }
          else if ((player.lastDoor % 5) == 1)  // 1, 3, 5, 7 Apples lastDoor 1, 6, 11, 16
          {
            fillWithSentence(48);
            fillWithWord(11, 97);
            fillWithNumber(28, amount);
            bitSet(player.hasStuff[0], 0);
            player.itemsAmount[0] += amount;
          }

          else if ((player.lastDoor % 5) == 2)  // 1, 3, 5, 7 Anise lastDoor 2, 7, 12, 17
          {
            fillWithSentence(48);
            fillWithWord(11, 99);
            fillWithNumber(28, amount);
            bitSet(player.hasStuff[0], 2);
            player.itemsAmount[2] += amount;
          }

          else if ((player.lastDoor % 5) == 3)  // Weapons 1, 3, 5, 7 lastDoor 3, 8, 13, 18
          {
            fillWithSentence(50);
            fillWithWord(23, 105 + amount);
            bitSet(player.hasStuff[2], amount);
          }

          else if ((player.lastDoor % 5) == 4)  // Armor 1, 3, 5, 7 lastDoor 4, 9, 14, 19
          {
            fillWithSentence(51);
            fillWithWord(23, 113 + amount);
            bitSet(player.hasStuff[4], amount);
          }
        }
        break;
      default:
        fillWithSentence(44);
        break;
    }
    foundSomething = true;
  }
  investigating = false;
}


#endif
