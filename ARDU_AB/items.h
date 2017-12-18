#ifndef ITEMS_H
#define ITEMS_H

#include "globals.h"
#include "text.h"

#define ITEM_APPLE                    0
#define ITEM_CIDER                    1
#define ITEM_ANISE                    2
#define ITEM_ABSINTH                  3
#define ITEM_RUBY                     4
#define ITEM_SAPPHIR                  5
#define ITEM_EMERALD                  6
#define ITEM_DIAMOND                  7

#define WEAPON_SLING                  0
#define WEAPON_KNIFE                  1
#define WEAPON_RAPIER                 2
#define WEAPON_SWORD                  3
#define WEAPON_AXE                    4
#define WEAPON_LANCE                  5
#define WEAPON_SPEAR                  6
#define WEAPON_BOW                    7

#define AMULET_HEALTH                 0
#define AMULET_MAGIC                  1
#define AMULET_SPEED                  2
#define AMULET_LUCK                   3
#define AMULET_GOLD                   4
#define AMULET_CLOAK                  5
#define AMULET_ESCAPE                 6
#define AMULET_RUBY                   7

#define TILE_CHEST

#define TOTAL_SHOP_ITEMS              4

/*const byte shopItems[] ={
  0, 1, 2, 3,            // Apple, Cider, Anise, Absinthe
  8+4, 8+7,              // Axe, Bow
  16+3, 16+6             // Bone, Iron
};*/

const unsigned int shopPrices[] = {
  10, 20, 10, 20
  //199, 999,
  //99, 499 
};

void buyItem()
{
  needMoreMoney = true;
  if (player.gold >= shopPrices[cursorY])
  {
    question = false;
    needMoreMoney = false;
    player.gold -= shopPrices[cursorY];
    bitSet(player.hasStuff[0], cursorY);
    ++player.itemsAmount[cursorY];
    /*switch (shopItems[cursorY])
    {
      case 0: case 1: case 2: case 3:
      bitSet(player.hasStuff[0], cursorY);
      ++player.itemsAmount[cursorY];
      break;
      case 12: case 15:
      bitSet(player.hasStuff[2], shopItems[cursorY] - 8);
      break;
      default:
      bitSet(player.hasStuff[4], shopItems[cursorY] - 16);
      break;
    }*/
  }
}

void drawShop()
{
  byte positionText = (TOTAL_SHOP_ITEMS-1) * 6;
  rollText = false;
  for (byte i = TOTAL_SHOP_ITEMS-1; i < TOTAL_SHOP_ITEMS; --i)
  {
    // Item name
    fillWithWord(0, 97 + i);
    drawTextBox(12, 9 + positionText, BLACK);
    // Item cost
    fillWithNumber(0, shopPrices[i]);
    drawTextBox(110, 9 + positionText, BLACK);
    positionText -= 6;
  }
}

void drawList()
{
  byte positionText = 0;
  rollText = false;
  for (byte i = 0; i < 8; i++)
  {
    if (bitRead (player.hasStuff[(2 * (gameState - STATE_GAME_ITEMS))], i))
    {
      // LIST
      fillWithWord(0, 97 + (8 * (gameState - STATE_GAME_ITEMS)) + i);
      drawTextBox(12, 9 + (6 * positionText), BLACK);
      // When ITEMS, show: x amount of items
      if (gameState == STATE_GAME_ITEMS)
      {
        sprites.drawErase(92, 9 + (6 * positionText), font, 24);
        fillWithNumber(0, player.itemsAmount[i]);
        drawTextBox(116 , 9 + (6 * positionText), BLACK);
      }
      // when NOT ITEMS, show: equipped
      else if (bitRead(player.hasStuff[(2 * (gameState - STATE_GAME_ITEMS)) + 1], i))
      {
        fillWithWord(0, 81);
        drawTextBox(48, 9 + (6 * positionText), BLACK);
      }
      // show: explaination of selected item
      if (positionText == cursorY)
      {
        inventorySelection = i;
        switch (gameState)
        {
          case STATE_GAME_ITEMS:
            fillWithSentence(19 + i);
            break;
          case STATE_GAME_WEAPON:
            fillWithSentence(27);
            fillWithNumber(15,(i+1)*3);
            break;
          case STATE_GAME_ARMOR:
            fillWithSentence(28);
            fillWithNumber(15,(i+1)*3);
            break;
          default://case STATE_GAME_AMULET:
            fillWithSentence(29 + i);
            break;

        }
        drawTextBox(4, 59, WHITE);
      }
      positionText++;
    }
  }

  if (!player.hasStuff[(2 * (gameState - STATE_GAME_ITEMS))])
  {
    fillWithSentence(gameState + 3);
    drawTextBox(34, 29, BLACK);
  }
}


void selectItemsEquipment()
{
  // Set item equipped or used
  player.hasStuff[(2 * (gameState - STATE_GAME_ITEMS)) + 1] = _BV(inventorySelection);
  // Hand which menu?
  switch (gameState)
  {
    case STATE_GAME_ITEMS:
    // Subtract item, use effect
    player.itemsAmount[inventorySelection] -= 1;
    if (player.itemsAmount[inventorySelection] == 0) bitClear(player.hasStuff[0], inventorySelection);
    // Item Effects
    switch (inventorySelection)
    {
      case 0: // Apple
      player.health = min(player.health+5, player.healthTotal);
      break;
      case 1: // Cider
      player.health = min(player.health+15, player.healthTotal);
      break;
      case 2: // Anise
      player.magic = min(player.magic+5, player.magicTotal);
      break;
      case 3: // Absinthe
      player.magic = min(player.magic+15, player.magicTotal);
      break;
    }
    break;
    case STATE_GAME_WEAPON:
    player.attackAddition = (inventorySelection + 1) * 3;
    break;
    case STATE_GAME_ARMOR:
    player.defenseAddition = (inventorySelection + 1) * 3;
    break;
  }
}

#endif
