#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "inputs.h"
#include "inventory.h"
#include "items.h"
#include "worlddata.h"
#include "battles.h"
#include "people.h"

byte miniMapPlayerFrame = 0;

void drawMap()
{
  if (bitRead(player.gameTriggers[3], 3))
  {
    if (player.currentRegion > 12)
    {
      fillWithSentence(0, 42);
      drawTextBox(7, 29, BLACK, TEXT_ROLL);
    }
    else
    {
      if (arduboy.everyXFrames(3)) miniMapPlayerFrame = (++miniMapPlayerFrame) % 4;
      for (byte miniMapOnScreenX = 0; miniMapOnScreenX <= 128; miniMapOnScreenX += 8)
      {
        for (byte miniMapOnScreenY = 0; miniMapOnScreenY <= 64; miniMapOnScreenY += 8)
        {
          byte chunk_pos_x = (mini_cam.x + miniMapOnScreenX) >> 3;
          byte chunk_pos_y = (mini_cam.y + miniMapOnScreenY) >> 3;
          int ccx = ((mini_cam.x >> 3) << 3) + miniMapOnScreenX;
          int ccy = ((mini_cam.y >> 3) << 3) + miniMapOnScreenY;
          sprites.drawOverwrite(ccx - mini_cam.x, ccy - mini_cam.y, miniMapSheet, 0);
          if (getMapFog(chunk_pos_x, chunk_pos_y))
          {
            byte miniMapTile;
            // Regional chunk
            if (getChunk(chunk_pos_x, chunk_pos_y) < 128)
            {
              if (getChunkBit(chunk_pos_x, chunk_pos_y))
              {
                // draw region icon
                switch (getRegion(chunk_pos_x, chunk_pos_y))
                {
                  case REGION_CANYONS:          // 12
                    miniMapTile = 1;
                    break;
                  case REGION_FOREST:           // 11
                  case REGION_FOREST_CANYON:    // 0
                  case REGION_SWAMP_FOREST:     // 1
                  case REGION_FIELDS_SWAMP:     // 2
                  case REGION_FIELDS_CANYONS:   // 3
                    miniMapTile = 2;
                    break;
                  case REGION_SWAMP_ISLAND_ONE: // 4
                  case REGION_SWAMP_ISLAND_TWO: // 5
                  case REGION_SWAMP:            // 10
                    miniMapTile = 3;
                    break;
                  case REGION_LONG_ROAD:        // 6
                  case REGION_APPLE_FARM:       // 7
                  case REGION_YOUR_GARDEN:      // 8
                  case REGION_FIELDS:           // 9
                    miniMapTile = 4;
                    break;
                }
              }
              else miniMapTile = 10;
            }
            // Specific chunk
            else
            {
              switch (getChunk(chunk_pos_x, chunk_pos_y))
              {
                case 170: // Big Tree
                case 171: // Shop
                case 172: // Battle Cave
                case 173: // Inn
                  miniMapTile = getChunk(chunk_pos_x, chunk_pos_y) - 165;
                  break;
                default:
                  miniMapTile = 9;
                  break;
              }
            }
            sprites.drawOverwrite((((mini_cam.x >> 3) << 3) + miniMapOnScreenX) - mini_cam.x, (((mini_cam.y >> 3) << 3) + miniMapOnScreenY) - mini_cam.y, miniMapSheet, miniMapTile);
          }
          // Player
          sprites.drawOverwrite((player.x / 96) * 8  - mini_cam.x, (player.y / 96) * 8 - mini_cam.y, miniMapPlayer, miniMapPlayerFrame);
        }
      }
    }
  }
  else
  {
    fillWithSentence(0, 5);
    drawTextBox(16, 29, BLACK, TEXT_ROLL);
  }
}

void stateGameNew()
{
  arduboy.fillScreen(1);
  byte alphabetX = 12;
  byte alphabetY = 17;
  for (byte i = 0; i < 36; i++)
  {
    sprites.drawErase( alphabetX, alphabetY, font, i + 1);
    alphabetX += 12;
    if (alphabetX > 119)
    {
      alphabetY += 10;
      alphabetX = 12;
    }
  }

  fillWithSentence(0, 3);
  fillWithName(13);
  drawTextBox(12, 3, BLACK, TEXT_NOROLL);

  sprites.drawErase(6 + (cursorX * 12), 17 + (cursorY * 10), font, 44);
};


void stateGameIntro()
{
  fillWithSentence(0, 37 + fadeCounter);
  if (fadeCounter == 2) fillWithName(23);

  if (fadeCounter < 4)
  {
    arduboy.fillScreen(0);
    drawRectangle(0, 48, 130, 64, BLACK);
    drawTextBox(6, 50, WHITE, TEXT_ROLL);
  }
  else
  {
    showFadeOutIn();
    if (arduboy.everyXFrames(6)) fadeCounter++;
    if (fadeCounter > 7)
    {
      fadeCounter = 0;
      gameState = STATE_GAME_PLAYING;
    }
  }
  drawPlayer();
  checkCam();
}


void stateGamePlaying()
{
  updatePeople();

  checkRegion();
  checkBoss();
  //checkBattle();
  if (arduboy.everyXFrames(15)) frameBoolean = !frameBoolean;
  drawPeople();
  drawPlayer();
  // Reveal map area around player
  discoverMap(player.x, player.y);
  checkDoors();
  checkCam();
  int investigate_x = player.x - 3 + pgm_read_byte(&collisionPoints[8 + playerDirection][0]);
  int investigate_y = player.y - 1 + pgm_read_byte(&collisionPoints[8 + playerDirection][1]);
  if (talkingWithNPC) investigatePeople(investigate_x, investigate_y);
  if (investigating) investigateObjects(getTileID(investigate_x, investigate_y));

  if (foundSomething)
  {
    drawRectangle(0, 48, 130, 64, BLACK);
    drawTextBox(6, 50, WHITE, TEXT_ROLL);
  }
};

void stateGameInventory()
{
  drawRectangle(83, 0, 130, 64, BLACK);
  fillWithSentence(0, 4);
  drawTextBox(93, 5, WHITE, TEXT_NOROLL);
  sprites.drawSelfMasked(86, 5 + (cursorY * 12), font, 44);
};

void stateGameEquip()
{
  drawRectangle(83, 0, 130, 64, BLACK);
  fillWithSentence(0, 10);
  drawTextBox(93, 5, WHITE, TEXT_NOROLL);
  sprites.drawSelfMasked(86, 5 + (cursorY * 12), font, 44);
}

void stateGameStats()
{
  arduboy.fillScreen(0);
  drawPlayerStats();
}

void stateGameMap()
{
  arduboy.fillScreen(1);
  drawMap();
}

void stateGameSaveSoundEnd()
{
  drawRectangle(0, 48, 130, 64, BLACK);
  fillWithSentence(0, gameState + 36);
  drawTextBox(6, 50, WHITE, TEXT_ROLL);
  yesNo = true;
}

void showSubMenuStuff()
{
  arduboy.fillScreen(1);
  drawRectangle(0, 0, 130, 8, BLACK);
  drawRectangle(0, 57, 130, 64, BLACK);

  drawList();

  if (player.hasStuff[(2 * (gameState - STATE_GAME_ITEMS))]) sprites.drawErase(5, 9 + (6 * cursorY), font, 44);

  fillWithWord(0, 93 + (gameState - STATE_GAME_ITEMS));
  drawTextBox(6, 0, WHITE, TEXT_NOROLL);
}

void walkingThroughDoor()
{
  showFadeOutIn();
  if (arduboy.everyXFrames(6)) fadeCounter++;
  if (counterDown == false && fadeCounter == 4)
  {
    counterDown = true;
    if (playerDirection == FACING_SOUTH)
    {
      player.x = (pgm_read_byte(&doors[player.lastDoor * 2]) * 16);
      player.y = (pgm_read_byte(&doors[(player.lastDoor * 2)] + 1) * 16) + 12;
    }
    else
    {
      if ((getChunk(player.x / 96, player.y / 96) & 0x7F) == 34)  player.x = 336;
      else player.x = (720 + (384 * ((getChunk(player.x / 96, player.y / 96) & 0x7F) - 42)));
      player.y = 3048;
    }
    checkCam();
  }
  else if (fadeCounter > 6)
  {
    fadeCounter = 0;
    playerSteps = 0;
    gameState = STATE_GAME_PLAYING;
    counterDown = false;
  }
}


void stateGameOver()
{
  arduboy.fillScreen(1);
  sprites.drawErase(56, 30, playerDead, 0);
  fillWithSentence(0, 43);
  drawTextBox(37, 16, BLACK, TEXT_ROLL);
};



#endif
