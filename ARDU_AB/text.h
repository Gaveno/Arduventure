#ifndef TEXT_H
#define TEXT_H

#define WORD                          0
#define SENTENCE                      1
#define STARTPOINT                    0

#define TEXT_NOROLL                   0
#define TEXT_ROLL                     1
#define TEXT_ROLL_DELAY               2

#define SPACE                         0
#define TRIPLESPACE                   160
#define FOURSPACE                     230
#define DOUBLENEWLINE                 161
#define DOUBLESPACE                   162
#define NEWLINE                       254
#define NONE                          255

#include "globals.h"
#include "dictionary.h"

byte textspeed = 5;
byte prevSentence = 255;
bool lastRollText = false;

int findBegin(byte searchObject, boolean wordOrSentence)
{
  int i = 0;
  while (searchObject != 0)
  {
    if (!wordOrSentence) i += pgm_read_byte(&library[i]) + 1;
    else i += pgm_read_byte(&sentences[i]) + 1;
    searchObject--;
  }
  return i;
}

void fillWithWord(byte startPoint, byte wordOfLibrary)
{
  byte totalCharacters = 0;
  int startWord = findBegin(wordOfLibrary, WORD);
  byte sizeWord = pgm_read_byte(&library[startWord]);
  for (int i = startWord + 1; i < startWord + 1 + sizeWord; i++)
  {
    textBox[(startPoint ? startPoint : 1) + totalCharacters] = pgm_read_byte(&library[i]);
    totalCharacters++;
  }
  if (!startPoint) textBox[0] = totalCharacters;
}

void fillWithNumber(byte startPoint, int number)
{
  byte totalCharacters = 0;
  char buf[6];
  itoa(number, buf, 10);
  char charLen = strlen(buf);
  for (byte i = 0; i < charLen; i++)
  {
    char digit = buf[i];
    textBox[(startPoint ? startPoint : 1) + totalCharacters] = digit - 21;
    totalCharacters++;
  }
  if (!startPoint) textBox[0] = totalCharacters;
}


void fillWithSentence(byte sentenceOfLibrary)
{
  if (lastRollText)
  {
    if (prevSentence != sentenceOfLibrary)
      textRollAmount = 0;
    prevSentence = sentenceOfLibrary;
  }
  byte totalCharacters = 0;
  int startSentence = findBegin(sentenceOfLibrary, SENTENCE);
  byte sizeSentence = pgm_read_byte(&sentences[startSentence]);
  for (int i = startSentence + 1 ; i < startSentence + 1 + sizeSentence; i++)
  {
    byte wordOfLibrary = pgm_read_byte(&sentences[i]);
    if (wordOfLibrary == NEWLINE)
    {
      textBox[1 + totalCharacters] = NEWLINE;
      totalCharacters++;
    }
    else
    {
      int startWord = findBegin(wordOfLibrary, WORD);
      byte sizeWord = pgm_read_byte(&library[startWord]);
      for (int k = startWord + 1; k < startWord + 1 + sizeWord; k++)
      {
        textBox[1 + totalCharacters] = pgm_read_byte(&library[k]);
        totalCharacters++;
      }
    }
  }
  textBox[0] = totalCharacters;
}


void drawTextBox(byte x, byte y, boolean color, boolean rollText)
{
  lastRollText = rollText;
  byte xOffset = 0;
  byte yOffset = 0;

  if (rollText && (textRollAmount < textBox[0]))
  {
    if (arduboy.everyXFrames(textspeed)) textRollAmount++;
  }

  for (byte i = 1; i < ((rollText) ? (textRollAmount + 1) : (textBox[0] + 1)); i++)
  {
    if (textBox[i] == NEWLINE)
    {
      yOffset += 6;
      xOffset = 0;
    }
    else {
      if (color) sprites.drawSelfMasked(x + xOffset, y + yOffset, font, textBox[i]);
      else sprites.drawErase(x + xOffset, y + yOffset, font, textBox[i]);
      xOffset += 6;
    }
  }
}

void drawQuestion()
{
  drawRectangle(0, 45, 130, 64, BLACK);
  fillWithSentence(gameState - 1);
  drawTextBox(4, 50, WHITE, TEXT_ROLL);
}

void drawYesNo()
{
  fillWithSentence(9);
  drawTextBox(106, 50, WHITE, TEXT_NOROLL);
  sprites.drawSelfMasked( 98, 50 + (6 * !cursorYesNoY), font, 44);
}

#endif