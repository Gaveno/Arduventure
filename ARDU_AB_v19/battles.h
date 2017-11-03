#ifndef BATTLES_H
#define BATTLES_H

#include "globals.h"
#include "player.h"
#include "enemies.h"
#include "game.h"

#define BATTLE_ATTACK             0
#define BATTLE_MAGIC              1
#define BATTLE_ESCAPE             2
#define BATTLE_ITEMS              3
#define BATTLE_NO_ESCAPE          4
#define BATTLE_ENEMY_TURN         5
#define BATTLE_BLINK_ENEMY        6
#define BATTLE_PLAYER_HURT        7
#define BATTLE_ENEMY_DEAD         8
#define BATTLE_ENEMY_INTRO        9
#define BATTLE_START              10

byte battleBlink = 0;
byte offsetIndex = 0;

const int8_t offsetattack[] = {0, -2, -4, -5, -4, -2, 0};
const int8_t offsetdead[] = {2, 5, 9, 14, 20, 26, 32};

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

int8_t getEnemyOffset( )
{
  // Offset enemy when it attacks
  
  int8_t offset = 0;
  if (offsetIndex < 6)
    ++offsetIndex;
  switch (battleProgress)
  {
    case BATTLE_ENEMY_DEAD:
      offset = offsetdead[offsetIndex];
      break;
    case BATTLE_PLAYER_HURT:
      offset = offsetattack[offsetIndex];
      break;
    //default:
      //offsetIndex = 0;
  }
  return offset;
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
    playerFirst = player.speed > enemy.speed;
    arduboy.fillScreen(0);
    drawRectangle(0, 8, 130, 44, WHITE);
    
    if (battleProgress != BATTLE_BLINK_ENEMY || battleBlink < 30 || battleBlink % 2 == 0)
      drawEnemies(getEnemyOffset());
    
    drawRectangle(0, 44, 130, 64, BLACK);
    switch (battleProgress)
    {
      
      /*
       * Player uses physical attack.
       */
      case BATTLE_ATTACK:
        damageEnemy(player.attack, player.attackAddition);
        battleProgress = BATTLE_BLINK_ENEMY;
        battleBlink = 0;
        break;
      /*
       * Player uses magic (amulet) attack.
       */
      case BATTLE_MAGIC:
        damageEnemy(player.attack, player.attackAddition);
        battleProgress = BATTLE_BLINK_ENEMY;
        battleBlink = 0;
        break;
      /*
       * Player tries to escape.
       */
      case BATTLE_ESCAPE:
        if (player.currentRegion != REGION_CAVE_INTERIOR)
        {
          // Player speed VS enemy speeds combined (if higher: 100% chance, if lower: 50% chance)
          fillWithSentence(46);
        }
        else
        {
          playerFirst = true;
          battleProgress = BATTLE_NO_ESCAPE;
        }
        break;
      /*
       * Player selected item.
       */
      case BATTLE_ITEMS:
        previousGameState = gameState;
        gameState = STATE_GAME_ITEMS;
        break;
      /*
       * Player is unable to escape.
       *  Let enemy attack.
       */
      case BATTLE_NO_ESCAPE:
        fillWithSentence(47);
        break;
      /* 
       *  If enemy is alive, take a turn.
       *  Otherwise display defeated and progress.
       */
      case BATTLE_ENEMY_TURN:
        battleBlink = 0;
        offsetIndex = 0;
        battleProgress = BATTLE_PLAYER_HURT;
        //textRollAmount = 0;
        break;
      /* 
       *  Make enemy blink showing damage taken
       */
      case BATTLE_BLINK_ENEMY:
        
        if (battleBlink < 60)
        {
          battleBlink++;
          if (battleBlink > 30)
          {
            fillWithSentence(67);
            fillWithWord(1, (enemy.images >> 4) + 221);
            fillWithNumber(11, lastDamageDealt);
          }
          else
          {
            fillWithSentence(71);
            //fillWithWord(2, 62); // YOU
          }
          drawTextBox(0, 52, WHITE, TEXT_NOROLL);
        }
        else
        {
          if (enemy.health == 0)
          {
            gainExperience(enemy.level);
            offsetIndex = 0;
            battleProgress = BATTLE_ENEMY_DEAD;
            battleBlink = 0;
            textRollAmount = 0;
          }
          else
          {
            textRollAmount = 0;
            if (playerFirst)
              battleProgress = BATTLE_ENEMY_TURN;
            else
              battleProgress = BATTLE_START;
          }
        }
        break;
      /*
       * The player was hurt, blink HP.
       * If player died end battle.
       */
      case BATTLE_PLAYER_HURT:
        ++battleBlink;
        if (battleBlink == 30)
          damagePlayer(enemy.attack);   // Subtract health
        if (battleBlink < 60)
        {
          // Display text
          if (battleBlink > 30)
          {
            fillWithSentence(67);
            fillWithWord(2, 62); // YOU
            fillWithNumber(11, lastDamageDealt);
            
          } 
          else
          {
            fillWithSentence(70);
            fillWithWord(1, (enemy.images >> 4) + 221);
          }
          drawTextBox(0, 52, WHITE, TEXT_NOROLL);
        }
        else
        {
          // Move on to next state
          if (player.health > 0)
          {
            if (!playerFirst)
            {
              battleProgress = attackType;
            }
            else
              battleProgress = BATTLE_START;
          }
          else
          {
            ++fadeCounter;    // Player is dead.
          }
        }
        break;
      /*
       * The player defeated the enemy, show message
       * then exit battle.
       */
      case BATTLE_ENEMY_DEAD:
        if (battleBlink < 50)
        {
          ++battleBlink;
          fillWithSentence(68);
          fillWithWord(14, (enemy.images >> 4) + 221);
          drawTextBox(0, 52, WHITE, TEXT_ROLL);
        }
        else {
          ++fadeCounter;
        }
        break;
      case BATTLE_ENEMY_INTRO:
        if (battleBlink < 50) {
          fillWithSentence(69);
          fillWithWord(3, (enemy.images >> 4) + 221);
          drawTextBox(0, 52, WHITE, TEXT_ROLL);
          ++battleBlink;
        }
        else {
          battleProgress = BATTLE_START;
        }
        break;
          /*
         * Default start state (after the enemy's intro)
         * The menu for the player to select a move.
         */
        case BATTLE_START:
          fillWithSentence(45);
          sprites.drawSelfMasked( 3 + (54 * cursorX), 52 + (6 * cursorY), font, 44);
          drawTextBox(4, 52, WHITE, TEXT_NOROLL);
          break;
    }
    //drawTextBox(4, 52, WHITE, TEXT_NOROLL);
    updateEnemies();
    
    fillWithSentence(64);
    if (battleProgress != BATTLE_PLAYER_HURT || battleBlink < 30 || battleBlink % 2 == 0) {
      fillWithNumber(4, player.health);
    }
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
      battleProgress = BATTLE_ENEMY_INTRO;
      battleBlink = 0;
      createEnemy();
      clearCursor();
    }
    playerSteps = 0;
  }
}


#endif
