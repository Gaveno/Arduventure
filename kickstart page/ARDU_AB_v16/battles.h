#ifndef BATTLES_H
#define BATTLES_H

#include "globals.h"
#include "player.h"
#include "enemies.h"
#include "game.h"

#define BATTLE_START              0
#define BATTLE_ATTACK             1
#define BATTLE_MAGIC              2
#define BATTLE_ESCAPE             3
#define BATTLE_ITEMS              4
#define BATTLE_NO_ESCAPE          5
#define BATTLE_ENEMY_TURN         6


void startBattle()
{
  flashBlack = true;
}

void endBattle()
{
  fadeCounter = 0;
  counterDown = false;
  if (player.health < 1) gameState = STATE_GAME_OVER;
  else gameState = STATE_GAME_PLAYING;
}

void stateGameBattle()
{
  if (fadeCounter < 6) startBattle();
  else if (fadeCounter == 6)
  {
    arduboy.fillScreen(0);
    drawRectangle(0, 8, 130, 44, WHITE);
    switch (battleProgress)
    {
      case BATTLE_START:
        fillWithSentence(0, 45);
        sprites.drawSelfMasked( 3 + (54 * cursorX), 52 + (6 * cursorY), font, 44);
        break;
      case BATTLE_ATTACK:
        fadeCounter++;
        break;
      case BATTLE_MAGIC:
        fadeCounter++;
        break;
      case BATTLE_ESCAPE:
        if (player.currentRegion != REGION_CAVE_INTERIOR)
        {
          // Player speed VS enemy speeds combined (if higher: 100% chance, if lower: 50% chance)
          fillWithSentence(0, 46);
        }
        else battleProgress = BATTLE_NO_ESCAPE;
        break;
      case BATTLE_ITEMS:
        previousGameState = gameState;
        gameState = STATE_GAME_ITEMS;
        break;
      case BATTLE_NO_ESCAPE:
        fillWithSentence(0, 47);
        break;
      case BATTLE_ENEMY_TURN:
        fadeCounter++;
        break;
    }
    drawTextBox(6, 52, WHITE, TEXT_NOROLL);
    updateEnemies();
    drawEnemies();
  }
  else endBattle();
}


void checkBattle()
{
  if (playerSteps > 200)
  {
    if (generateRandomNumber(10) < 7)
    {
      ATM.play(battleSong);
      songPlaying = 0;
      gameState = STATE_GAME_BATTLE;
      battleProgress = BATTLE_START;
      clearCursor();
    }
    playerSteps = 0;
  }
}


#endif
