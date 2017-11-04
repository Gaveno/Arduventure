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
#define BATTLE_NEXT_TURN          11    // Reset turn order
#define BATTLE_ENEMY_DEFEND       12    // show enemy defends itself
#define BATTLE_LEVEL_UP           13

// Chances are not in percentages
#define CRIT_CHANCE               18    // higher is lower chance to crit
#define ENEMY_MISS_CHANCE         4    // higher is greater chance to miss
#define PLAYER_MISS_CHANCE        2   // higher is greater chance to miss

byte battleBlink = 0;
byte offsetIndex = 0;
byte crit;

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
  textRollAmount = 0;
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
    case BATTLE_LEVEL_UP:
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
    
    arduboy.fillScreen(0);
    drawRectangle(0, 8, 130, 44, WHITE);
    
    if (battleProgress != BATTLE_BLINK_ENEMY || lastDamageDealt == 0 || battleBlink < 30 || battleBlink % 2 == 0)
      drawEnemies(getEnemyOffset());
    
    drawRectangle(0, 44, 130, 64, BLACK);
    
    switch (battleProgress)
    {
      
      /*
       * Player uses physical attack.
       */
      case BATTLE_ATTACK:
      {
        byte chancetotal = 20;
        if (player.speed > enemy.speed)
          chancetotal += 5;
        byte chance = generateRandomNumber(chancetotal);
        if (chance < PLAYER_MISS_CHANCE)
        {
          // Missed
          lastDamageDealt = 0;
        }
        else
        {
          // Landed hit
          crit = 1;
          if (chance > CRIT_CHANCE)
            crit = 2;
          damageEnemy(player.attack * crit, player.attackAddition, player.level);
        }
        battleProgress = BATTLE_BLINK_ENEMY;
        battleBlink = 0;
      }
      break;
      /*
       * Player uses magic (amulet) attack.
       */
      case BATTLE_MAGIC:
      {
        damageEnemy(player.attack, player.attackAddition, player.level);
        battleProgress = BATTLE_BLINK_ENEMY;
        battleBlink = 0;
      }
      break;
      /*
       * Player tries to escape.
       */
      case BATTLE_ESCAPE:
      {
        if (player.currentRegion != REGION_CAVE_INTERIOR)
        {
          // Player speed VS enemy speeds combined (if higher: 100% chance, if lower: 50% chance)
          fillWithSentence(46);
          drawTextBox(4, 52, WHITE, TEXT_ROLL);
        }
        else
        {
          playerFirst = true;
          battleProgress = BATTLE_NO_ESCAPE;
        }
      }
      break;
      /*
       * Player selected item.
       */
      case BATTLE_ITEMS:
      {
        previousGameState = gameState;
        gameState = STATE_GAME_ITEMS;
      }
      break;
      /*
       * Player is unable to escape.
       *  Let enemy attack.
       */
      case BATTLE_NO_ESCAPE:
      {
        fillWithSentence(47);
        drawTextBox(4, 52, WHITE, TEXT_ROLL);
      }
      break;
      /* 
       *  If enemy is alive, take a turn.
       *  Otherwise display defeated and progress.
       */
      case BATTLE_ENEMY_TURN:
      {
        battleBlink = 0;
        offsetIndex = 0;
        battleProgress = BATTLE_PLAYER_HURT;
        if (generateRandomNumber(20) < 4)
        {
          battleProgress = BATTLE_ENEMY_DEFEND;
          enemy.defense += enemy.defense / 2;
          enemy.specDefense += enemy.specDefense / 2;
        }
        //textRollAmount = 0;
      }
      break;
      /* 
       *  Make enemy blink showing damage taken
       */
      case BATTLE_BLINK_ENEMY:
      {
        battleBlink++;
        if (battleBlink > 30)
        {
          if (crit > 1)
          {
            fillWithSentence(77);
            drawTextBox(70, 10, BLACK, TEXT_NOROLL);
          }
          if (lastDamageDealt > 0)
          {
            // Landed hit
            fillWithSentence(67);
            fillWithWord(1, (enemy.images >> 4) + 221);
            fillWithNumber(11, lastDamageDealt);
          }
          else
          {
            // Missed
            fillWithSentence(72);
            fillWithWord(2, 62);
          }
        }
        else
        {
          fillWithSentence(71);
          //fillWithWord(2, 62); // YOU
        }
        drawTextBox(0, 52, WHITE, TEXT_NOROLL);
        if (battleBlink > 60)
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
              battleProgress =  BATTLE_NEXT_TURN;
          }
        }
      }
      break;
      /*
       * The player was hurt, blink HP.
       * If player died end battle.
       */
      case BATTLE_PLAYER_HURT:
      {
        ++battleBlink;
        if (battleBlink == 30)
        {
          byte chancetotal = 20;
          if (player.speed > enemy.speed)
            chancetotal -= 5;
          // Enemy missed... Unless it didn't
          lastDamageDealt = 0;
          if (generateRandomNumber(chancetotal) > ENEMY_MISS_CHANCE)
          {
            // Enemy landed hit, subtract health
            damagePlayer(enemy.attack);   
          }
        }
        if (battleBlink < 60)
        {
          // Display text
          if (battleBlink > 30)
          {
            if (lastDamageDealt > 0)
            {
              // Landed hit
              fillWithSentence(67);
              fillWithWord(2, 62); // YOU
              fillWithNumber(11, lastDamageDealt);
            }
            else
            {
              // Missed
              fillWithSentence(72);
              fillWithWord(1, (enemy.images >> 4) + 221);
            }
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
              battleProgress =  BATTLE_NEXT_TURN;
          }
          else
          {
            ++fadeCounter;    // Player is dead.
          }
        }
      }
      break;
      /*
       * The player defeated the enemy, show message
       * then exit battle.
       */
      case BATTLE_ENEMY_DEAD:
      {
        if (battleBlink < 50)
        {
          ++battleBlink;
          fillWithSentence(68);
          fillWithWord(14, (enemy.images >> 4) + 221);
          drawTextBox(0, 52, WHITE, TEXT_ROLL);
        }
        else {
          if (levelup)
          {
            levelup = false;
            battleProgress = BATTLE_LEVEL_UP;
            battleBlink = 0;
          }
          else
            ++fadeCounter;
        }
      }
      break;
      /*
       * Introduce the enemy appearing.
       */
      case BATTLE_ENEMY_INTRO:
      {
        battleProgress = BATTLE_NEXT_TURN;
        if (battleBlink < 50) {
          fillWithSentence(69);
          fillWithWord(3, (enemy.images >> 4) + 221);
          drawTextBox(0, 52, WHITE, TEXT_ROLL);
          ++battleBlink;
          battleProgress = BATTLE_ENEMY_INTRO;
        }
      }
      break;
        /*
       * Default start state (after the enemy's intro)
       * The menu for the player to select a move.
       */
      case BATTLE_START:
      {
        fillWithSentence(45);
        sprites.drawSelfMasked( 3 + (54 * cursorX), 52 + (6 * cursorY), font, 44);
        drawTextBox(4, 52, WHITE, TEXT_NOROLL);
      }
      break;
      /*
       * Reset the turn order based on speed and random element.
       */
      case BATTLE_NEXT_TURN:
      {
        byte chancetotal = 15;
        if (player.speed > enemy.speed)
          chancetotal += 5;
        playerFirst = (generateRandomNumber(chancetotal) > 7);
        battleProgress = BATTLE_START;
      }
      break;
      /*
       * Show message enemy defends itself
       */
       case BATTLE_ENEMY_DEFEND:
       {
        ++battleBlink;
        
        if (battleBlink < 60)
        {
          fillWithSentence(74);
          if (battleBlink < 30)
          {
            // The enemy is defending itself
            fillWithSentence(73);
          }
          fillWithWord(1, (enemy.images >> 4) + 221);
          drawTextBox(4, 52, WHITE, TEXT_NOROLL);
        }
        else if (!playerFirst)
        {
          battleProgress = attackType;
        }
        else
          battleProgress =  BATTLE_NEXT_TURN;
        
       }
       break;
       /*
        * The player leveled up.
        */
       case BATTLE_LEVEL_UP:
       {
        ++battleBlink;
        fillWithSentence(76);
        drawTextBox(4, 52, WHITE, TEXT_NOROLL);
        if (battleBlink > 60)
        {
          ++fadeCounter;
        }
       }
    }
    fillWithSentence(64);
    if (battleProgress != BATTLE_PLAYER_HURT || lastDamageDealt == 0 || battleBlink < 30 || battleBlink % 2 == 0) {
      fillWithNumber(4, player.health);
    }
    fillWithWord(7, 43);
    fillWithNumber(8, player.healthTotal);
    fillWithNumber(14, player.magic);
    fillWithWord(17, 43);
    fillWithNumber(18, player.magicTotal);
    if (battleProgress != BATTLE_LEVEL_UP || battleBlink % 4 != 0)
    {
      drawTextBox(0, 2, WHITE, TEXT_NOROLL);
    }
    fillWithSentence(75);
    fillWithWord(1, (enemy.images >> 4) + 221);
    fillWithNumber(10, enemy.level);
    drawTextBox(5, 15, BLACK, TEXT_NOROLL);
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
      textRollAmount = 0;
      gameState = STATE_GAME_BATTLE;
      battleProgress = BATTLE_ENEMY_INTRO;
      battleBlink = 0;
      createEnemy(player.level);
      clearCursor();
    }
    playerSteps = 0;
  }
}


#endif
