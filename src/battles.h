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
#define BATTLE_BLINK_ENEMY        7

byte battleBlink = 0;

/*
 * Enemies stats are based on the player.currentRegion variable.
 */


/* Flash the screen with black.
 *  In void loop().
 */
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

/* The game's battle state.
 *  Initially fadeCounter is 0.
 *  Flash the screen black until fadeCounter is 6.
 */
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
        fillWithSentence(45);
        sprites.drawSelfMasked( 3 + (54 * cursorX), 52 + (6 * cursorY), font, 44);
        drawTextBox(4, 52, WHITE, TEXT_NOROLL);
        break;
      case BATTLE_ATTACK:
        //fadeCounter++;
        damageEnemy(player.attack, player.attackAddition);
        battleProgress = BATTLE_BLINK_ENEMY;
        battleBlink = 0;
        break;
      case BATTLE_MAGIC:
        fadeCounter++;
        break;
      case BATTLE_ESCAPE:
        if (player.currentRegion != REGION_CAVE_INTERIOR)
        {
          // Player speed VS enemy speeds combined (if higher: 100% chance, if lower: 50% chance)
          fillWithSentence(46);
        }
        else battleProgress = BATTLE_NO_ESCAPE;
        break;
      case BATTLE_ITEMS:
        previousGameState = gameState;
        gameState = STATE_GAME_ITEMS;
        break;
      case BATTLE_NO_ESCAPE:
        fillWithSentence(47);
        break;
      case BATTLE_ENEMY_TURN:
        if (enemy.health == 0)
        {
          gainExperience(enemy.level);
          fadeCounter++;
        }
        else
        {
          damagePlayer(enemy.attack);
          battleProgress = BATTLE_START;
        }
        break;
      case BATTLE_BLINK_ENEMY:
        if (battleBlink < 10) battleBlink++;
        else battleProgress = BATTLE_ENEMY_TURN;
    }
    //drawTextBox(4, 52, WHITE, TEXT_NOROLL);
    updateEnemies();
    if (battleBlink % 2 == 0)
      drawEnemies();
    fillWithSentence(64);
    fillWithNumber(4, player.health);
    fillWithWord(7, 43);
    fillWithNumber(8, player.healthTotal);
    fillWithNumber(14, player.magic);
    fillWithWord(17, 43);
    fillWithNumber(18, player.magicTotal);
    drawTextBox(0, 2, WHITE, TEXT_NOROLL);
    //drawBoss();
  }
  else endBattle();
}

/* Entry function to battle.
 *  When the player's steps are over 200
 *  and when a random element is true.
 *  
 *  Generate enemy stats. Enter battle.
 */
void checkBattle()
{
  if (playerSteps > 200)
  {
    if (player.currentRegion >= REGION_FIELDS && player.currentRegion <= REGION_CANYONS && generateRandomNumber(10) < 7)
    {
      ATM.play(battleSong);
      songPlaying = 0;
      gameState = STATE_GAME_BATTLE;
      battleProgress = BATTLE_START;
      createEnemy();
      clearCursor();
    }
    playerSteps = 0;
  }
}


#endif
