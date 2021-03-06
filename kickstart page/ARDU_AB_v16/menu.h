#ifndef MENU_H
#define MENU_H

#include "globals.h"
#include "player.h"
#include "text.h"
#include "songs.h"
#include "people.h"

void stateMenuIntro()
{
  arduboy.fillScreen(0);
  if (globalCounter < 128)
  {
    fillWithWord(0, 197);
    globalCounter++;
    drawTextBox(43, 28, WHITE, TEXT_ROLL);
  }
  else if (globalCounter < 254)
  {
    globalCounter++;
    sprites.drawSelfMasked(34, 4, T_arg, 0);
  }
  else
  {
    if (arduboy.everyXFrames(48)) frameBoolean = !frameBoolean;
    sprites.drawSelfMasked(52, 16, titleSwordGuard, 0);
    sprites.drawSelfMasked(60, 0, titleSwordGrip, 0);
    sprites.drawSelfMasked(16, 24, titleText, 0);
    sprites.drawSelfMasked(61, 48, titleSword, 0);
    if (frameBoolean)
    {
      sprites.drawErase(61, 52, titleStartMask, 0);
      fillWithWord(0, 148);
      drawTextBox(49, 53, WHITE, TEXT_NOROLL);
    }
    if (arduboy.justPressed(A_BUTTON | B_BUTTON))
    {
      globalCounter = 0;
      gameState = STATE_MENU_MAIN;
      if (EEPROM.read(EEPROM_START) == GAME_ID) firstGame = false;
      cursorY = STATE_MENU_CONTINUE + firstGame;
      textspeed = TEXT_ROLL_DELAY;
    }
  }
}


void stateMenuMain()
{
  byte locationMenu = firstGame ? 5 : 11;
  arduboy.fillScreen(0);
  fillWithSentence(0, 0);
  if (!firstGame) fillWithWord(1, 1);
  if (arduboy.audio.enabled()) fillWithWord(27, 6);
  else fillWithWord(26, 5);
  drawTextBox(40, locationMenu, WHITE, TEXT_NOROLL);
  sprites.drawSelfMasked( 32, locationMenu + (cursorY - 2) * 12, font, 44);
  sprites.drawSelfMasked( 90, locationMenu + (cursorY - 2) * 12, font, 45);
}

void stateMenuContinue()
{
  loadGame();
  gameState = STATE_GAME_PLAYING;
  ATM.stop();
}

void stateMenuNew()
{
  setPlayer();
  gameState = STATE_GAME_NEW;
  ATM.play(nameSong);
}

void toggleSound()
{
  if (!arduboy.audio.enabled()) arduboy.audio.on();
  else arduboy.audio.off();
  arduboy.audio.saveOnOff();
  cursorY = STATE_MENU_CONTINUE + firstGame;
}

void stateMenuSound()
{
  arduboy.fillScreen(0);
  // if sound is not enabled, put it ON, otherwise put it OFF
  toggleSound();
  gameState = STATE_MENU_MAIN;
}

void stateMenuCredits()
{
  arduboy.fillScreen(0);
  fillWithSentence(0, 41);
  drawTextBox(18, 11, WHITE, TEXT_ROLL);
}


#endif
