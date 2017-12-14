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


void drawList()
{
  byte positionText = 0;

  for (byte i = 0; i < 8; i++)
  {
    if (bitRead (player.hasStuff[(2 * (gameState - STATE_GAME_ITEMS))], i))
    {
      rollText = false;
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
        switch (gameState)
        {
          case STATE_GAME_ITEMS:
            fillWithSentence(19 + i);
            break;
          case STATE_GAME_WEAPON:
            fillWithSentence(27);
            fillWithNumber(15,i+1);
            break;
          case STATE_GAME_ARMOR:
            fillWithSentence(28);
            fillWithNumber(15,i+1);
            break;
          case STATE_GAME_AMULET:
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
  // set the equipped flag or item used flag
  player.hasStuff[(2 * (gameState - STATE_GAME_ITEMS)) + 1] = 0;
  // because the list is dynamic, we need to count the objects that are shown.
  byte AmountOfObjectsShown = 0;
  for (byte i = 0; i < 8; i++)
  {
    if (bitRead (player.hasStuff[(2 * (gameState - STATE_GAME_ITEMS))], i)) AmountOfObjectsShown++;
    if (AmountOfObjectsShown - 1 == cursorY) bitSet(player.hasStuff[(2 * (gameState - STATE_GAME_ITEMS)) + 1], i);

    // if an item is used decrease the item amount
    if (gameState == STATE_GAME_ITEMS)
    {
      if (bitRead(player.hasStuff[1], i))
      {
        player.itemsAmount[i] -= 1;
        if (player.itemsAmount[i] < 1) bitClear(player.hasStuff[0], i);
      }
    }
  }
}

#endif
