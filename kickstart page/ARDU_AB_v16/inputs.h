#ifndef INPUTS_H
#define INPUTS_H

#include "globals.h"
#include "player.h"
#include "worlddata.h"
#include "items.h"
#include "battles.h"
#include "people.h"

bool checkPlayerCollision(byte orientation)
{
  int pointOne = player.x + pgm_read_byte(&collisionPoints[2 * orientation][0]);
  int pointTwo = player.y + pgm_read_byte(&collisionPoints[2 * orientation][1]);
  int pointThree = player.x + pgm_read_byte(&collisionPoints[(2 * orientation) + 1][0]);
  int pointFour = player.y + pgm_read_byte(&collisionPoints[(2 * orientation) + 1][1]);
  if (
    !getSolid(pointOne, pointTwo) &&
    !getSolid(pointThree, pointFour) &&
    !getCollisionPeople(pointOne, pointTwo) &&
    !getCollisionPeople(pointThree, pointFour)
  )
  {
    playerWalking = true;
    if (player.currentRegion < REGION_HOUSE_INTERIOR) playerSteps++;
    return true;
  }
  return false;
}

void buttonsUpDownA()
{
  if (arduboy.justPressed(UP_BUTTON)) cursorYesNoY = true;
  else if (arduboy.justPressed(DOWN_BUTTON)) cursorYesNoY = false;
  else if (arduboy.justPressed(A_BUTTON))
  {
    gameState = STATE_GAME_INVENTORY;
    yesNo = false;
    cursorY = 4;
    cursorYesNoY = true;
  }
}

void checkInputs()
{
  if (arduboy.justPressed(B_BUTTON)) textRollAmount = 0;
  switch (gameState)
  {
    case STATE_MENU_MAIN:
      if (arduboy.justPressed(UP_BUTTON) && (cursorY > 2 + firstGame)) cursorY--;
      else if (arduboy.justPressed(DOWN_BUTTON) && (cursorY < 5)) cursorY++;
      else if (arduboy.justPressed(B_BUTTON))
      {
        gameState = cursorY;
        clearCursor();
      }
      break;

    case STATE_MENU_CREDITS:
      if (arduboy.justPressed(B_BUTTON))
      {
        gameState = STATE_MENU_MAIN;
        cursorY = STATE_MENU_CONTINUE + firstGame;
      }
      break;

    case STATE_GAME_NEW:
      if (arduboy.justPressed(UP_BUTTON)) cursorY += (cursorY > 0) ? -1 : 4;
      else if (arduboy.justPressed(DOWN_BUTTON)) cursorY += (cursorY < 4) ? 1 : -4;
      else if (arduboy.justPressed(LEFT_BUTTON))cursorX += (cursorX > 0) ? -1 : 8;
      else if (arduboy.justPressed(RIGHT_BUTTON)) cursorX += (cursorX < 8) ? 1 : -8;
      if (currentLetter == 5) cursorY = 4;
      if (cursorY == 4) cursorX = 7;
      if (arduboy.justPressed(B_BUTTON))
      {
        byte selectedLetter = cursorX + (cursorY * 9) + 1;
        if (selectedLetter > 36)
        {
          player.name[0] = currentLetter;
          currentLetter = 0;
          clearCursor();
          gameState = STATE_GAME_INTRO;
          ATM.play(badNews);
          return;
        }
        else
        {
          player.name[currentLetter + 1] = selectedLetter;
          currentLetter = min(currentLetter + 1, 5);
        }
      }

      else if (arduboy.justPressed(A_BUTTON))
      {
        if (currentLetter > 0)
        {
          player.name[currentLetter] = 50;
          currentLetter--;
        }
        else
        {
          gameState = STATE_MENU_INTRO;
          globalCounter = 255;
        }
      }
      break;

    case STATE_GAME_INTRO:
      if (arduboy.justPressed(B_BUTTON ))
      {
        if (fadeCounter < 4)
        {
          fadeCounter++;
        }
      }
      break;

    case STATE_GAME_PLAYING:
      playerWalking = false;
      if (!investigating && !foundSomething && !talkingWithNPC) {
        if (arduboy.pressed(DOWN_BUTTON) && checkPlayerCollision(playerDirection = FACING_SOUTH)) player.y++;
        else if (arduboy.pressed(LEFT_BUTTON) && checkPlayerCollision(playerDirection = FACING_WEST)) player.x--;
        else if (arduboy.pressed(UP_BUTTON) && checkPlayerCollision(playerDirection = FACING_NORTH)) player.y--;
        else if (arduboy.pressed(RIGHT_BUTTON) && checkPlayerCollision(playerDirection = FACING_EAST)) player.x++;
        if (arduboy.justPressed(A_BUTTON)) gameState = STATE_GAME_INVENTORY;
        else if (arduboy.justPressed(B_BUTTON))
        {
          investigating = true;
          talkingWithNPC = true;
        }
      }
      else if (arduboy.justPressed(A_BUTTON | B_BUTTON)) foundSomething = false;
      break;

    case STATE_GAME_INVENTORY:
      if (arduboy.justPressed(UP_BUTTON) && (cursorY > 0)) cursorY--;
      else if (arduboy.justPressed(DOWN_BUTTON) && (cursorY < 4)) cursorY++;
      else if (arduboy.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
      else if (arduboy.justPressed(B_BUTTON))
      {
        switch (cursorY)
        {
          case 0:
            gameState = STATE_GAME_ITEMS;
            break;
          case 4:
            gameState = STATE_GAME_SAVE;
            break;
          default:
            gameState = STATE_GAME_ITEMS + cursorY - 5;
            break;
        }
        clearCursor();
        mini_cam.x = constrain((player.x / 96) * 8 - 64, 0, 128);
        mini_cam.y = constrain((player.y / 96) * 8 - 32, 0, 176);
      }
      break;
    case STATE_GAME_EQUIP:
      if (arduboy.justPressed(UP_BUTTON) && (cursorY > 0)) cursorY--;
      else if (arduboy.justPressed(DOWN_BUTTON) && (cursorY < 2)) cursorY++;
      else if (arduboy.justPressed(A_BUTTON))
      {
        gameState = STATE_GAME_INVENTORY;
        cursorY = 1;
      }
      else if (arduboy.justPressed(B_BUTTON))
      {
        gameState = STATE_GAME_WEAPON + cursorY;
        clearCursor();
      }
      break;
    case STATE_GAME_STATS:
      if (arduboy.justPressed(A_BUTTON | B_BUTTON))
      {
        gameState = STATE_GAME_INVENTORY;
        cursorY = 2;
      }
      break;


    case STATE_GAME_ITEMS:
    case STATE_GAME_WEAPON:
    case STATE_GAME_ARMOR:
    case STATE_GAME_AMULET:
      if (!yesNo)
      {
        if (arduboy.justPressed(UP_BUTTON) && (cursorY > 0)) cursorY--;
        else if (arduboy.justPressed(DOWN_BUTTON) && (cursorY < bitCount(player.hasStuff[2 * (gameState - STATE_GAME_ITEMS)]) - 1)) cursorY++;
        else if (arduboy.justPressed(A_BUTTON))
        {
          cursorY = (gameState == STATE_GAME_ITEMS) ? 0 : (gameState - 13);
          gameState = (gameState == STATE_GAME_ITEMS) ? STATE_GAME_INVENTORY : STATE_GAME_EQUIP;
        }
        else if (arduboy.justPressed(B_BUTTON) && player.hasStuff[(2 * (gameState - STATE_GAME_ITEMS))])
        {
          question = true;
          yesNo = true;
        }
      }
      else
      {
        buttonsUpDownA();
        if (arduboy.justPressed(B_BUTTON))
        {
          if (cursorYesNoY)
          {
            selectItemsEquipment();
            clearCursor();
            if (previousGameState > STATE_GAME_AMULET)
            {
              battleProgress = BATTLE_START;
              gameState = previousGameState;
            }
          }
          question = false;
          yesNo = false;
          cursorYesNoY = true;
        }
      }
      break;
    case STATE_GAME_MAP:
      if (arduboy.justPressed(B_BUTTON | A_BUTTON)) gameState = STATE_GAME_PLAYING;
      else if (arduboy.pressed(LEFT_BUTTON) && mini_cam.x > 0) mini_cam.x -= 2;
      else if (arduboy.pressed(UP_BUTTON) && mini_cam.y > 0) mini_cam.y -= 2;
      else if (arduboy.pressed(RIGHT_BUTTON) && mini_cam.x < 128) mini_cam.x += 2;
      else if (arduboy.pressed(DOWN_BUTTON) && mini_cam.y < 176) mini_cam.y += 2;
      break;

    case STATE_GAME_SAVE:
      buttonsUpDownA();
      if (arduboy.justPressed(B_BUTTON))
      {
        if (cursorYesNoY) saveGame();
        gameState = STATE_GAME_SOUND;
        yesNo = false;
        cursorYesNoY = false;
      }
      break;

    case STATE_GAME_SOUND:
      buttonsUpDownA();
      if (arduboy.justPressed(B_BUTTON))
      {
        if (cursorYesNoY) toggleSound();
        gameState = STATE_GAME_END;
        yesNo = false;
        cursorYesNoY = false;
      }
      break;

    case STATE_GAME_END:
      buttonsUpDownA();
      if (arduboy.justPressed(B_BUTTON))
      {
        if (cursorYesNoY)
        {
          gameState = STATE_GAME_OVER;
          ATM.play(youDied);
        }
        else
        {
          gameState = STATE_GAME_INVENTORY;
          cursorY = 4;
        }
        yesNo = false;
        cursorYesNoY = true;
      }
      break;

    case STATE_GAME_OVER:
      if (arduboy.justPressed(B_BUTTON))
      {
        gameState = STATE_MENU_MAIN;
        ATM.play(titleSong);
        cursorY = STATE_MENU_CONTINUE + firstGame;
      }
      break;
    case STATE_GAME_BATTLE:
      switch (battleProgress)
      {
        case BATTLE_START:
          if (arduboy.justPressed(LEFT_BUTTON) && cursorX > 0) cursorX--;
          else if (arduboy.justPressed(RIGHT_BUTTON) && cursorX < 1) cursorX++;
          else if (arduboy.justPressed(UP_BUTTON) && cursorY > 0) cursorY--;
          else if (arduboy.justPressed(DOWN_BUTTON) && cursorY < 1)cursorY++;
          else if (arduboy.justPressed(B_BUTTON | A_BUTTON)) battleProgress = 1 + cursorX + (2 * cursorY);
          break;
        case BATTLE_ATTACK:
          if (arduboy.justPressed(B_BUTTON | A_BUTTON)) battleProgress = BATTLE_START;
          break;
        case BATTLE_MAGIC:
          if (arduboy.justPressed(B_BUTTON | A_BUTTON)) battleProgress = BATTLE_START;
          break;
        case BATTLE_ESCAPE:
          if (arduboy.justPressed(B_BUTTON | A_BUTTON)) fadeCounter = 7;
          break;
        case BATTLE_ITEMS:
          if (arduboy.justPressed(B_BUTTON | A_BUTTON)) battleProgress = BATTLE_START;
          //fadeCounter++;
          break;
        case BATTLE_NO_ESCAPE:
          if (arduboy.justPressed(B_BUTTON | A_BUTTON)) battleProgress = BATTLE_ENEMY_TURN;
          break;
      }
    case STATE_GAME_BOSS:
      break;
  }
}

#endif
