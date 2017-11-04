#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "globals.h"

#define CHAR_A  1
#define CHAR_B  2
#define CHAR_C  3
#define CHAR_D  4
#define CHAR_E  5
#define CHAR_F  6
#define CHAR_G  7
#define CHAR_H  8
#define CHAR_I  9
#define CHAR_J  10
#define CHAR_K  11
#define CHAR_L  12
#define CHAR_M  13
#define CHAR_N  14
#define CHAR_O  15
#define CHAR_P  16
#define CHAR_Q  17
#define CHAR_R  18
#define CHAR_S  19
#define CHAR_T  20
#define CHAR_U  21
#define CHAR_V  22
#define CHAR_W  23
#define CHAR_X  24
#define CHAR_Y  26
#define CHAR_Z  27

unsigned char textBox[75];

PROGMEM const unsigned char library[] =
{
  // PLACE  0 : empty
  1,
  SPACE,
  // PLACE  1 : CONTINUE
  8,
  3, 15, 14, 20, 9, 14, 21, 5,
  // PLACE  2 : NEW
  3,
  14, 5, 23,
  // PLACE  3 : GAME
  4,
  7, 1, 13, 5,
  // PLACE  4 : SND
  3,
  19, 14, 4,
  // PLACE  5 : OFF
  3,
  15, 6, 6,
  // PLACE  6 : ON
  2,
  15, 14,
  // PLACE  7 : YOUR
  4,
  25, 15, 21, 18,
  // PLACE  8 : NAME
  4,
  14, 1, 13, 5,
  // PLACE  9 : END
  3,
  5, 14, 4,
  // PLACE 10 : WORTH
  5,
  23, 15, 18, 20, 8,
  // PLACE 11 : SOME
  4,
  19, 15, 13, 5,
  // PLACE 12 : ATTACK
  6,
  1, 20, 20, 1, 3, 11,
  // PLACE 13 : AMOUNT
  6,
  1, 13, 15, 21, 14, 20,
  // PLACE 14 : DEFEND
  6,
  4, 5, 6, 5, 14, 4,
  // PLACE 15 : SLOWLY
  6,
  19, 12, 15, 23, 12, 25,
  // PLACE 16 : RECOVER
  7,
  18, 5, 3, 15, 22, 5, 18,
  // PLACE 17 : FIND
  4,
  6, 9, 14, 4,
  // PLACE 18 : FASTER
  6,
  6, 1, 19, 20, 5, 18,
  // PLACE 19 : MORE
  4,
  13, 15, 18, 5,
  // PLACE 20 : DOUBLE
  6,
  4, 15, 21, 2, 12, 5,
  // PLACE 21 : ENEMIES
  7,
  5, 14, 5, 13, 9, 5, 19,
  // PLACE 22 : MISS
  4,
  13, 9, 19, 19,
  // PLACE 23 : EVERY
  5,
  5, 22, 5, 18, 25,
  // PLACE 24 : FIGHT
  5,
  6, 9, 7, 8, 20,
  // PLACE 25 : SELL
  4,
  19, 5, 12, 12,
  // PLACE 26 : PRICE
  5,
  16, 18, 9, 3, 5,


  // PLACE 27 : CHARACTER 0
  1,
  27,
  // PLACE 28 : CHARACTER 1
  1,
  28,
  // PLACE 29 : CHARACTER 2
  1,
  29,
  // PLACE 30 : CHARACTER 3
  1,
  30,
  // PLACE 31 : CHARACTER 4
  1,
  31,
  // PLACE 32 : CHARACTER 5
  1,
  32,
  // PLACE 33 : CHARACTER 6
  1,
  33,
  // PLACE 34 : CHARACTER 7
  1,
  34,
  // PLACE 35 : CHARACTER 8
  1,
  35,
  // PLACE 36 : CHARACTER 9
  1,
  36,
  // PLACE 37 : CHARACTER .
  1,
  37,
  // PLACE 38 : CHARACTER ,
  1,
  38,
  // PLACE 39 : CHARACTER !
  1,
  39,
  // PLACE 40 : CHARACTER ?
  1,
  40,
  // PLACE 41 : CHARACTER '
  1,
  41,
  // PLACE 42 : CHARACTER :
  1,
  42,
  // PLACE 43 : CHARACTER /
  1,
  43,
  // PLACE 44 : arrow right
  1,
  44,
  // PLACE 45 : arrow left
  1,
  45,
  // PLACE 46 : arrow up
  1,
  46,
  // PLACE 47 : arrow down
  1,
  47,
  // place 48 : diamond
  1,
  48,
  // place 49 : €
  1,
  49,
  // place 50 : _
  1,
  50,
  // place 51 : *
  1,
  51,
  // place 52 : (
  1,
  52,
  // place 53 : )
  1,
  53,
  // place 54 : +
  1,
  54,
  // place 55 : -
  1,
  55,
  // place 56 : full
  1,
  56,


  // PLACE 57 : LOTS
  4,
  12, 15, 20, 19,
  // PLACE 58 : A
  1,
  1,
  // PLACE 59 : PILE
  4,
  16, 9, 12, 5,
  // PLACE 60 : S
  1,
  19,
  // PLACE 61 : TO
  2,
  20, 15,
  // PLACE 62 : YOU
  3,
  25, 15, 21,
  // PLACE 63 : THERE
  5,
  20, 8, 5, 18, 5,
  // PLACE 64 : DANGER
  6,
  4, 1, 14, 7, 5, 18,
  // PLACE 65 : RESTORES
  8,
  18, 5, 19, 20, 15, 18, 5, 19,
  // PLACE 66 : ALL
  3,
  1, 12, 12,
  // PLACE 67 : SAVE
  4,
  19, 1, 22, 5,
  // PLACE 68 : PROGRESS
  8,
  16, 18, 15, 7, 18, 5, 19, 19,
  // PLACE 69 : USE
  3,
  21, 19, 5,
  // PLACE 70 : EQUIP
  5,
  5, 17, 21, 9, 16,
  // PLACE 71 : ITEM
  4,
  9, 20, 5, 13,
  // PLACE 72 : LEVEL
  5,
  12, 5, 22, 5, 12,
  // PLACE 73 : UP
  2,
  21, 16,
  // PLACE 74 : IN
  2,
  9, 14,
  // PLACE 75 : THE
  3,
  20, 8, 5,
  // PLACE 76 : IS
  2,
  9, 19,
  // PLACE 77 : AIR
  3,
  1, 9, 18,
  // PLACE 78 : MONSTER
  7,
  13, 15, 14, 19, 20, 5, 18,
  // PLACE 79 : ARE
  3,
  1, 18, 5,
  // PLACE 80 : ROAMING
  7,
  18, 15, 1, 13, 9, 14, 7,
  // PLACE 81 : EQUIPPED
  8,
  5, 17, 21, 9, 16, 16, 5, 4,
  // PLACE 82 : STATS
  5,
  19, 20, 1, 20, 19,
  // PLACE 83 : HP
  2,
  8, 16,
  // PLACE 84 : MP
  2,
  13, 16,
  // PLACE 85 : EXP
  3,
  5, 24, 16,
  // PLACE 86 : LV
  2,
  12, 22,
  // PLACE 87 : ATK
  3,
  1, 20, 11,
  // PLACE 88 : DEF
  3,
  4, 5, 6,
  // PLACE 89 : SPD
  3,
  19, 16, 4,
  // PLACE 90 : YES
  3,
  25, 5, 19,
  // PLACE 91 : NO
  2,
  14, 15,
  // PLACE 92 : OF
  2,
  15, 6,


  // PLACE 93 : ITEMS
  5,
  9, 20, 5, 13, 19,
  // PLACE 94 : WEAPON
  6,
  23, 5, 1, 16, 15, 14,
  // PLACE 95 : ARMOR
  5,
  1, 18, 13, 15, 18,
  // PLACE 96 : AMULET
  6,
  1, 13, 21, 12, 5, 20,


  // PLACE 97 : APPLE
  5,
  1, 16, 16, 12, 5,
  // PLACE 98 : CIDER
  5,
  3, 9, 4, 5, 18,
  // PLACE 99 : ANISE
  5,
  1, 14, 9, 19, 5,
  // PLACE 100 : ABSINTHE
  8,
  1, 2, 19, 9, 14, 20, 8, 5,
  // PLACE 101 : RUBY
  4,
  18, 21, 2, 25,
  // PLACE 102 : SAPPHIRE
  8,
  19, 1, 16, 16, 8, 9, 18, 5,
  // PLACE 103 : EMERALD
  7,
  5, 13, 5, 18, 1, 12, 4,
  // PLACE 104 : DIAMOND
  7,
  4, 9, 1, 13, 15, 14, 4,
  // PLACE 105 : SLING
  5,
  19, 12, 9, 14, 7,
  // PLACE 106 : KNIFE
  5,
  11, 14, 9, 6, 5,
  // PLACE 107 : RAPIER
  6,
  18, 1, 16, 9, 5, 18,
  // PLACE 108 : SWORD
  5,
  19, 23, 15, 18, 4,
  // PLACE 109 : AXE
  3,
  1, 24, 5,
  // PLACE 110 : LANCE
  5,
  12, 1, 14, 3, 5,
  // PLACE 111 : SPEAR
  5,
  19, 16, 5, 1, 18,
  // PLACE 112 : BOW
  3,
  2, 15, 23,
  // PLACE 113 : WOOL
  4,
  23, 15, 15, 12,
  // PLACE 114 : LINEN
  5,
  12, 9, 14, 5, 14,
  // PLACE 115 : LEATHER
  7,
  12, 5, 1, 20, 8, 5, 18,
  // PLACE 116 : BONE
  4,
  2, 15, 14, 5,
  // PLACE 117 : COPPER
  6,
  3, 15, 16, 16, 5, 18,
  // PLACE 118 : BRONZE
  6,
  2, 18, 15, 14, 26, 5,
  // PLACE 119 : IRON
  4,
  9, 18, 15, 14,
  // PLACE 120 : STEEL
  5,
  19, 20, 5, 5, 12,
  // PLACE 121 : FIRE
  4,
  6, 9, 18, 5,
  // PLACE 122 : LEAFS
  4,
  12, 5, 1, 6,// 19,
  // PLACE 123 : WATER
  5,
  23, 1, 20, 5, 18,
  // PLACE 124 : LUCK
  4,
  12, 21, 3, 11,
  // PLACE 125 : GOLD
  4,
  7, 15, 12, 4,
  // PLACE 126 : CLOAK
  5,
  3, 12, 15, 1, 11,
  // PLACE 127 : ESCAPE
  6,
  5, 19, 3, 1, 16, 5,
  // PLACE 128 : RUBY
  4,
  18, 21, 2, 25,
  // PLACE 129 : OUR
  3,
  15, 21, 18,
  // PLACE 130 : LAND
  4,
  12, 1, 14, 4,
  // PLACE 131 : ONLY
  4,
  15, 14, 12, 25,
  // PLACE 132 : HOPE
  4,
  8, 15, 16, 5,
  // PLACE 133 : ...
  3,
  37, 37, 37,
  // PLACE 134 : SPACE, SPACE, SPACE, SPACE, SPACE,
  5,
  SPACE, SPACE, SPACE, SPACE, SPACE,
  // PLACE 135 : NOW
  3,
  14, 15, 23,
  // PLACE 136 : GO
  2,
  7, 15,
  // PLACE 137 : BEFORE
  6,
  2, 5, 6, 15, 18, 5,
  // PLACE 138 : IT
  2,
  9, 20,
  // PLACE 139 : LATE
  4,
  12, 1, 20, 5,
  // PLACE 140 : CREDITS
  7,
  3, 18, 5, 4, 9, 20, 19,
  // PLACE 141 : SIEGFRIED CROES
  15,
  19, 9, 5, 7, 6, 18, 9, 5, 4, SPACE, 3, 18, 15, 5, 19,
  // PLACE 142 : GAVIN ATKIN
  11,
  7, 1, 22, 9, 14, SPACE, 1, 20, 11, 9, 14,
  // PLACE 143 : JO3RI GANTOIS
  13,
  10, 15, 30, 18, 9, SPACE, 7, 1, 14, 20, 15, 9, 19,
  // PLACE 144 : MAP
  3,
  13, 1, 16,
  // PLACE 145 : NOTHING
  7,
  14, 15, 20, 8, 9, 14, 7,
  // PLACE 146 : TAKE
  4,
  20, 1, 11, 5,
  // PLACE 147 : FOR
  3,
  6, 15, 18,
  // PLACE 148 : START
  5,
  19, 20, 1, 18, 20,
  // PLACE 149 : OVER
  4,
  15, 22, 5, 18,
  // PLACE 150 : RUN
  3,
  18, 21, 14,
  // PLACE 151 : CAN
  3,
  3, 1, 14,
  // PLACE 152 : NOT
  3,
  14, 15, 20,
  // PLACE 153 : ESCAPE
  6,
  5, 19, 3, 1, 16, 5,
  // PLACE 154 : GOT
  3,
  7, 15, 20,
  // PLACE 155 : AWAY
  4,
  1, 23, 1, 25,
  // PLACE 156 : SAFELY
  6,
  19, 1, 6, 5, 12, 25,
  // PLACE 157 : NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE,
  5,
  NEWLINE, NEWLINE, NEWLINE, NEWLINE, NEWLINE,
  // PLACE 158 : FOUND
  5,
  6, 15, 21, 14, 4,
  // PLACE 159 : AN
  2,
  1, 14,
  // PLACE 160 : SPACE SPACE SPACE
  3,
  SPACE, SPACE, SPACE,
  // PLACE 161 : NEWLINE NEWLINE
  2,
  NEWLINE, NEWLINE,
  // PLACE 162 : SPACE, SPACE,
  2,
  SPACE, SPACE,
  // PLACE 163 : WELCOME
  7,
  23, 5, 12, 3, 15, 13, 5,
  // PLACE 164 : ARDUVILLE
  9,
  1, 18, 4, 21, 22, 9, 12, 12, 5,
  // PLACE 165 : PROPERTY
  8,
  16, 18, 15, 16, 5, 18, 20, 25,
  // PLACE 166 : THIS
  4,
  20, 8, 9, 19,
  // PLACE 167 : ROAD
  4,
  18, 15, 1, 4,
  // PLACE 168 : FIELDS
  6,
  6, 9, 5, 12, 4, 19,
  // PLACE 169 : SWAMP
  5,
  19, 23, 1, 13, 16,
  // PLACE 170 : FOREST
  6,
  6, 15, 18, 5, 19, 20,
  // PLACE 171 : CANYONS
  7,
  3, 1, 14, 25, 15, 14, 19,
  // PLACE 172 : ROCK
  4,
  18, 15, 3, 11,
  // PLACE 173 : HAS
  3,
  8, 1, 19,
  // PLACE 174 : SYMBOLS
  7,
  19, 25, 13, 2, 15, 12, 19,
  // PLACE 175 : RESEMBLING
  10,
  18, 5, 19, 5, 13, 2, 12, 9, 14, 7,

  // PLACE 176 : LIGHT
  5,
  12, 9, 7, 8, 20,
  // PLACE 177 : BEAM
  4,
  2, 5, 1, 13,
  // PLACE 178 : EMERGE
  6,
  5, 13, 5, 18, 7, 5,
  // PLACE 179 : FROM
  4,
  6, 18, 15, 13,
  // PLACE 180 : MAGIC
  5,
  13, 1, 7, 9, 3,
  // PLACE 181 : SUMMON
  6,
  19, 21, 13, 13, 15, 14,
  // PLACE 182 : THESE
  5,
  20, 8, 5, 19, 5,
  // PLACE 183 : BOOK
  4,
  2, 15, 15, 11,
  // PLACE 184 : LOOK
  4,
  12, 15, 15, 11,
  // PLACE 185 : SAME
  4,
  19, 1, 13, 5,
  // PLACE 186 : ME
  2,
  13, 5,
  // PLACE 187 : GPS
  3,
  7, 16, 19,
  // PLACE 188 : INSIDE
  6,
  9, 14, 19, 9, 4, 5,
  // PLACE 189 : YEST
  3,
  25, 5, 20,
  // PLACE 190 : WILL
  4,
  23, 9, 12, 12,
  // PLACE 191 : NEED
  4,
  14, 5, 5, 4,
  // PLACE 192 : I
  1,
  9,
  // PLACE 193 : SAW
  3,
  19, 1, 23,
  // PLACE 194 : SHOP
  4,
  19, 8, 15, 16,
  // PLACE 195 : EXTRA
  5,
  5, 24, 20, 18, 1,
  // PLACE 196 : TOGGLE
  6,
  20, 15, 7, 7, 12, 5,
  // PLACE 197 : ARDUBOY
  7,
  1, 18, 4, 21, 2, 15, 25,
  // PLACE 198 : TEAM a.r.g.
  11,
  20, 5, 1, 13, SPACE, 1, 37, 18, 37, 7, 37,
  // PLACE 199 : one
  3,
  15, 14, 5,
  // PLACE 200 : OLIVIER HUARD
  13,
  15, 12, 9, 22, 9, 5, 18, SPACE, 8, 21, 1, 18, 4,
  // PLACE 201 : BLADE
  5,
  2, 12, 1, 4, 5,
  // PLACE 202 : PIECES
  6,
  16, 9, 5, 3, 5, 19,
  // PLACE 203 : BOSS
  4,
  2, 15, 19, 19,
  // PLACE 204 : CARDS
  5,
  3, 1, 18, 4, 19,
  // PLACE 205 : CARRYING
  8,
  3, 1, 18, 18, 25, 9, 14, 7,
  // PLACE 206 : LEADS
  5,
  12, 5, 1, 4, 19,
  // PLACE 207 : FISHING ROD
  11,
  6, 9, 19, 8, 9, 14, 7, SPACE, 18, 15, 4,
  // PLACE 208 : PRESENT
  7,
  16, 18, 5, 19, 5, 14, 20,
  // PLACE 209 : UPLOAD
  6,
  21, 16, 12, 15, 1, 4,
  // PLACE 210 : CONNECT
  7,
  3, 15, 14, 14, 5, 3, 20,
  // PLACE 211 : PC
  2,
  16, 3,
  // PLACE 212 : KEEP
  4,
  11, 5, 5, 16,
  // PLACE 213 : PRESSING
  8,
  16, 18, 5, 19, 19, 9, 14, 7,
  // PLACE 214 : KEY
  3,
  11, 5, 25,
  // PLACE 215 : SELECT
  6,
  19, 5, 12, 5, 3, 20,
  // PLACE 216 : AND
  3,
  1, 14, 4,
  // PLACE 217 : WHEN
  4,
  23, 8, 5, 14,
  // PLACE 218 : READY
  5,
  18, 5, 1, 4, 25,
  // PLACE 219 : RELEASE
  7,
  18, 5, 12, 5, 1, 19, 5,
  // PLACE 220 : LOST
  4,
  12, 15, 19, 20,
  // PLACE 221 : WORM
  4,
  23, 15, 18, 13,
  // PLACE 222 : BOUG
  4,
  2, 15, 21, 7,
  // PLACE 223 : SNAK
  4,
  19, 14, 1, 11,
  // PLACE 224 : SERP
  4,
  19, 5, 18, 16,
  // PLACE 225 : VINE
  4,
  22, 9, 14, 5,
  // PLACE 226 : ROOT
  4,
  18, 15, 15, 12,
  // PLACE 227 : FLAM
  4,
  6, 12, 1, 13,
  // PLACE 228 : DEFEATED
  8,
  CHAR_D, CHAR_E, CHAR_F, CHAR_E, CHAR_A, CHAR_T, CHAR_E, CHAR_D,
  // PLACE 229 : APPEARED
  8,
  CHAR_A, CHAR_P, CHAR_P, CHAR_E, CHAR_A, CHAR_R, CHAR_E, CHAR_D,
  // PLACE 230 : FOURSPACE
  4,
  SPACE, SPACE, SPACE, SPACE,
  // PLACE 231 : SELF
  4,
  CHAR_S, CHAR_E, CHAR_L, CHAR_F,
  // PLACE 232 : ED
  2,
  CHAR_E, CHAR_D,
  // PLACE 233 : WENT
  4,
  CHAR_W, CHAR_E, CHAR_N, CHAR_T,
  // PLACE 234 : LVL
  3,
  CHAR_L, CHAR_V, CHAR_L,
  // PLACE 235 : CRITICAL
  8,
  CHAR_C, CHAR_R, CHAR_I, CHAR_T, CHAR_I, CHAR_C, CHAR_A, CHAR_L,
};


PROGMEM const unsigned char sentences[] =
{
  // PLACE 0 : NEW GAME    SND   CREDITS!
  15,
  134, TRIPLESPACE, DOUBLENEWLINE, 2, SPACE, 3, DOUBLENEWLINE, 4, 134, DOUBLENEWLINE, 140, 39, DOUBLENEWLINE, SPACE, 209,

  // PLACE 1 : WELCOME TO ARDUVILLE PROPERTY OF
  11,
  163, SPACE, 61, SPACE, 164, NEWLINE, 165, SPACE, 92, 134, 134,

  // PLACE  2 : TEAM  A.R.G.///..PRESENT..
  5,
  198, 157, SPACE, SPACE, 208,

  // PLACE 3 : YOUR NAME? _____             END
  13,
  7, SPACE, 8, 40, DOUBLESPACE, 134, 157, 157, NEWLINE, 134, 134, FOURSPACE, 9,

  // PLACE 4 : ITEMS EQUIP STATS MAP EXTRA
  9,
  93, DOUBLENEWLINE, 70, DOUBLENEWLINE, 82, DOUBLENEWLINE, 144, DOUBLENEWLINE, 195,

  // PLACE 5 : NO MAP FOUND YET
  7,
  91, SPACE, 144, SPACE, 158, SPACE, 189,

  // PLACE 6 : GOLD:€       HP:       MP:       EXP TO LV UP:
  29,
  125, 42, 49, 134, SPACE, DOUBLENEWLINE, 83, DOUBLESPACE, 42, 134, DOUBLESPACE, DOUBLENEWLINE, 84, DOUBLESPACE, 42, 134, DOUBLESPACE, DOUBLENEWLINE, NEWLINE, 85, SPACE, 61, SPACE, 86, SPACE, 73, 42, 134, DOUBLESPACE,

  // PLACE 7 : LV: ATK: DEF: SPD:
  16,
  86, SPACE, 42, 134, DOUBLENEWLINE, 87, 42, 134, NEWLINE, 88, 42, 134, NEWLINE, 89, 42, 134,

  // PLACE 8 : STATS OF (name)
  5,
  82, SPACE, 92, 134, 134,

  // PLACE 9 : YES NO
  3,
  90, NEWLINE, 91,

  // PLACE 10 : WEAPON ARMOR AMULET
  5,
  94, DOUBLENEWLINE, 95, DOUBLENEWLINE, 96,

  // PLACE 11 : USE ITEM?
  4,
  69, SPACE, 71, 40,

  // PLACE 12 : EQUIP WEAPON?
  4,
  70, SPACE, 94, 40,

  // PLACE 13 : EQUIP ARMOR?
  4,
  70, SPACE, 95, 40,

  // PLACE 14 : EQUIP AMULET?
  4,
  70, SPACE, 96, 40,

  // PLACE 15 : NO ITEMS!
  4,
  91, SPACE, 93, 39,

  // PLACE 16 : NO WEAPONS!
  5,
  91, SPACE, 94, 60, 39,

  // PLACE 17 : NO ARMOR!
  4,
  91, SPACE, 95, 39,

  // PLACE 18 : NO AMULETS!
  5,
  91, SPACE, 96, 60, 39,


  // PLACE 19 : RESTORES 5 HP
  5,
  65, SPACE, 32, SPACE, 83,

  // PLACE 20 : RESTORES 15 HP
  6,
  65, SPACE, 28, 32, SPACE, 83,

  // PLACE 21 : RESTORES 5 MP
  5,
  65, SPACE, 32, SPACE, 84,

  // PLACE 22 : RESTORES 15 MP
  6,
  65, SPACE, 28, 32, SPACE, 84,

  // PLACE 23 : WORTH SOME GOLD
  5,
  10, SPACE, 11, SPACE, 125,

  // PLACE 24 : WORTH MORE GOLD
  5,
  10, SPACE, 19, SPACE, 125,

  // PLACE 25 : WORTH LOTS OF GOLD
  7,
  10, SPACE, 57, SPACE, 92, SPACE, 125,

  // PLACE 26 : WORTH A PILE OF GOLD
  9,
  10, SPACE, 58, SPACE, 59, SPACE, 92, SPACE, 125,


  // PLACE 27 : ATTACK AMOUNT_____
  4,
  12, SPACE, 13, 134,

  // PLACE 28 : DEFEND AMOUNT_____
  4,
  14, SPACE, 13, 134,

  // PLACE 29 : SUMMON FIRE MAGIC
  5,
  181, SPACE, 121, SPACE, 180,

  // PLACE 30 : SUMMON LEAFS MAGIC
  5,
  181, SPACE, 122, SPACE, 180,

  // PLACE 31 : SUMMON WATER MAGIC
  5,
  181, SPACE, 123, SPACE, 180,

  // PLACE 32 : FIND MORE ITEMS
  5,
  17, SPACE, 19, SPACE, 93,

  // PLACE 33 : FIND DOUBLE GOLD
  5,
  17, SPACE, 20, SPACE, 125,

  // PLACE 34 : ENEMIES MISS MORE
  5,
  21, SPACE, 22, SPACE, 19,

  // PLACE 35 : ESCAPE EVERY FIGHT
  5,
  127, SPACE, 23, SPACE, 24,

  // PLACE 36 : SELL PRICE IS DOUBLE
  7,
  25, SPACE, 26, SPACE, 76, SPACE, 20,


  // PLACE 37 : THERE IS DANGER IN THE AIR... v
  15,
  63, SPACE, 76, SPACE, 64, NEWLINE, 74, SPACE, 75, SPACE, 77, 133, SPACE, 134, 47,

  // PLACE 38 : MONSTERS ARE ROAMING OUR LANDS... v
  15,
  78, 60, SPACE, 79, SPACE, 80, NEWLINE, 129, SPACE, 130, 60, 133, 134, DOUBLESPACE, 47,

  // PLACE 39 : YOU ARE OUR ONLY HOPE v
  13,
  62, SPACE, 79, SPACE, 129, SPACE, 131, NEWLINE, 132, 134, 134, 134, 47,

  // PLACE 40 : NOW GO BEFORE IT'S TO LATE!
  14,
  135, SPACE, 136, SPACE, 137, SPACE, 138, 41, 60, NEWLINE, 61, SPACE, 139, 39,

  // PLACE 41 : CREDITS : JO3RI GANTOIS GAVIN ATKIN OLIVIER HUARD SIEGFRIED CROES
  13,
  FOURSPACE, 140, DOUBLENEWLINE, SPACE, 143, DOUBLENEWLINE, DOUBLESPACE, 142, DOUBLENEWLINE, SPACE, 200, DOUBLENEWLINE, 141,

  // PLACE 42 : NO GPS MAGIC INSIDE
  7,
  91, SPACE, 187, SPACE, 180, SPACE, 188,

  // PLACE 43 : GAME OVER
  3,
  3, SPACE, 149,

  // PLACE 44 : NOTHING THERE FOR ME TO TAKE
  11,
  145, SPACE, 63, SPACE, 147, NEWLINE, 186, SPACE, 61, SPACE, 146,

  // PLACE 45 : ATTACK    USE MAGIC ESCAPE    USE ITEMS
  13,
  SPACE, 12, TRIPLESPACE, 69 , SPACE, 180, NEWLINE, SPACE, 127, TRIPLESPACE, 69, SPACE, 71,

  // PLACE 46 : YOU GOT AWAY SAFELY!
  8,
  62, SPACE, 154, SPACE, 155, SPACE, 156, 39,

  // PLACE 47 : YOU CAN NOT ESCAPE!
  8,
  62, SPACE, 151, SPACE, 152, SPACE, 153, 39,

  // PLACE 48 : YOU FOUND__________/AMOUNT:_____
  9,
  62, SPACE, 158, 134, 134, NEWLINE, 13, 42, 134,

  // PLACE 49 : YOU FOUND AN ITEM:___/__________
  12,
  62, SPACE, 158, SPACE, 159, SPACE, 71, 42, TRIPLESPACE, NEWLINE, 134, 134,

  // PLACE 50 : YOU FOUND A WEAPON:__/__________
  12,
  62, SPACE, 158, SPACE, 58, SPACE, 94, 42, DOUBLESPACE, NEWLINE, 134, 134,

  // PLACE 51 : YOU FOUND ARMOR:_____/__________
  10,
  62, SPACE, 158, SPACE, 95, 42, 134, NEWLINE, 134, 134,

  // PLACE 52 : YOU FOUND AN AMULET:_/__________
  12,
  62, SPACE, 158, SPACE, 159, SPACE, 96, 42, SPACE, NEWLINE, 134, 134,

  // PLACE 53 : THIS ROAD LEADS TO THE__________
  11,
  166, SPACE, 167, SPACE, 206, SPACE, 61, NEWLINE, 75, 134, 134,

  // PLACE 54 : THE ROCK HAS SYMBOLS/RESEMBLING__________
  11,
  75, SPACE, 172, SPACE, 173, SPACE, 174, NEWLINE, 175, 134, 134,

  // PLACE 55 : A LIGHTBEAM EMERGES/FROM YOUR AMULET...
  14,
  58, SPACE, 176, 177, SPACE, 178, 60, NEWLINE, 179 , SPACE, 7, SPACE, 96, 133,

  // PLACE 56 : ALL THESE BOOKS LOOK/THE SAME TO ME...
  17,
  66, SPACE, 182, SPACE, 183, 60, SPACE, 184, NEWLINE, 75, SPACE, 185, SPACE, 61, SPACE, 186, 133,

  // PLACE 57 : SAVE PROGRESS?
  4,
  67, SPACE, 68, 40,

  // PLACE 58 : TOGGLE SND?
  4,
  196, SPACE, 4, 40,

  // PLACE 59 : END YOUR GAME?
  6,
  9, SPACE, 7, SPACE, 3, 40,

  // PLACE 60 : SHOPS SELL BOOKS
  7,
  194, 60, SPACE, 25, SPACE, 183, 60,

  // PLACE 61 : BLADE PIECES FOUND:..
  7,
  201, SPACE, 202, SPACE, 158, 42, DOUBLESPACE,

  // PLACE 62 : BOSS CARDS FOUND:///CARRYING:
  13,
  203, SPACE, 204, SPACE, 158, 42, DOUBLENEWLINE, DOUBLENEWLINE, 205, 42, FOURSPACE, FOURSPACE,  FOURSPACE,

  // PLACE 63 : YOU WILL NEED A MAP!/I SAW ONE IN A BOOK
  22,
  62, SPACE, 190, SPACE, 191, SPACE, 58, SPACE, 144, 39, NEWLINE, 9, SPACE, 193, SPACE, 199, SPACE, 74, SPACE, 58, SPACE, 183,

  // PLACE 64 : HP:___/___MP:___/___
  8,
  83, 42, TRIPLESPACE, FOURSPACE, 84, 42, TRIPLESPACE, FOURSPACE,

  // PLACE 65 : CONNECT YOUR ARDUBOY TO THE PC. KEEP PRESSING THE UP KEY.
  23,
  210, SPACE, 7, SPACE, 197, NEWLINE, 61, SPACE, 75, SPACE, 211, 37, SPACE, 212, NEWLINE, 213, SPACE, 75, SPACE, 73, SPACE, 214, 37,

  // PLACE 66 : SELECT YOUR GAME AND UPLOAD. WHEN DONE RELEASE THE UP KEY
  28,
  215, SPACE, 7, SPACE, 3, SPACE, 216, NEWLINE, 209, 37, SPACE, 217, SPACE, 209, NEWLINE, 76, SPACE, 218, 38, SPACE, 219, NEWLINE, 75, SPACE, 73, SPACE, 214, 47,

  // PLACE 67 : YOU/<monster name> LOST <amount> HP
  5,
  SPACE, FOURSPACE, 220, TRIPLESPACE, 83,

  // Place 68 : YOU DEFEATED <monster name>!
  6,
  62, SPACE, 228, FOURSPACE, SPACE, 39,

  // Place 69 : A <monster name> APPEARED!
  6,
  58, FOURSPACE, DOUBLESPACE, 229, 39, FOURSPACE,

  // PLACE 70 : <monster name> ATTACKS!
  5,
  FOURSPACE, SPACE, 12, 60, 39,

  // PLACE 71 : YOU ATTACK!
  4,
  62, SPACE, 12, 39,

  // PLACE 72 : YOU/<monster name> MISSED
  4,
  FOURSPACE, SPACE, 22, 232,

  // PLACE 73 : <monster name> DEFENDS ITSELF
  7,
  FOURSPACE, SPACE, 14, 60, SPACE, 138, 231,

  // PLACE 74 : <monster name>S DEF WENT UP
  8,
  FOURSPACE, 60, SPACE, 88, SPACE, 233, SPACE, 73,

  // PLACE 75 : <monster name>NEWLINE LVL <monster level>
  4,
  FOURSPACE, NEWLINE, 234, FOURSPACE,

  // PLACE 76 : YOU LEVELED UP!
  7,
  62, SPACE, 72, 232, SPACE, 73, 39,

  // PLACE 77 : CRITICAL!
  2,
  235, 39,
};


#endif
