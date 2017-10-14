#ifndef SONG_H
#define SONG_H

#define Song const uint8_t PROGMEM

Song music[] = {
0x07,						// Number of tracks
0x00, 0x00,					// Address of track 0
0x03, 0x00,					// Address of track 1 03
0x36, 0x00,					// Address of track 2 54
0x45, 0x00,					// Address of track 3 66
0x48, 0x00,					// Address of track 4 69
0x51, 0x00,					// Address of track 5 78
0x5C, 0x00,					// Address of track 6 89
0x01,						// Channel 0 entry track
0x02,						// Channel 1 entry track
0x00,						// Channel 2 entry track
0x00,						// Channel 3 entry track
			
//"Track 0"		
0x40, 0,            		// FX: SET VOLUME: volume = 0
0x9F,						// FX: STOP CURRENT CHANNEL
			
//"Track 1"			
0x9D, 20,					// FX: SET TEMPO: tempo = 20
0x40, 48,					// FX: SET VOLUME: volume = 48
0x41, -8,					// FX: SLIDE VOLUME ON: -8
0xFD, 6, 3,					// REPEAT: count = 6 + 1 / track = 3
0x4C, -2,					// FX: SET TRANSPOSITION: -2
0xFC, 3,					// GOTO track 3
0x4C, -4,					// FX: SET TRANSPOSITION: -4
0xFC, 3,					// GOTO track 3
0xFD, 5, 3,					// REPEAT: count = 5 + 1 / track = 3
0x4C, -5,					// FX: SET TRANSPOSITION: -5
0xFC, 3,					// GOTO track 3
0x4C, -7,					// FX: SET TRANSPOSITION: -7
0xFC, 3,					// GOTO track 3
0xFD, 6, 3,					// REPEAT: count = 6 + 1 / track = 3
0x4C, -2,					// FX: SET TRANSPOSITION: -2
0xFC, 3,					// GOTO track 3
0xFD, 2, 3,					// REPEAT: count = 2 + 1 / track = 3
0x4C, -1,					// FX: SET TRANSPOSITION: -1
0xFC, 3,					// GOTO track 3
0xFD, 2, 3,					// REPEAT: count = 2 + 1 / track = 3
0x9E, 1, 2, 0, 0,			// FX: GOTO advanced: ch0 = 0x01 / ch1 = 0x02 / ch2 = 0x00 / ch3 = 0x00
0x9F,						// FX: STOP CURRENT CHANNEL
			
//"Track 2"			
0x40, 48,						// FX: SET VOLUME: volume = 48
0x47, 0xc0, 0x40 + 0x20 + 0,	// FX: SET ARPEGGIO: true true 12 0 0
0x41, -2,						// FX: SLIDE VOLUME ON: -2
0xFD, 1, 4,					// REPEAT: count = 1 + 1 / track = 4
0xFC, 5,					// GOTO track 5
0xFC, 6,					// GOTO track 6
0x9F,						// FX: STOP CURRENT CHANNEL
			
//"Track 3"			
0x00 + 10,					// NOTE ON: note = 10
0x9F + 8,					// DELAY: ticks = 8
0xFE,						// RETURN
			
//"Track 4"			
0x00 + 34,					// NOTE ON: note = 34
0x9F + 4,					// DELAY: ticks = 4
0x00 + 37,					// NOTE ON: note = 37
0x9F + 4,					// DELAY: ticks = 4
0x00 + 39,					// NOTE ON: note = 39
0x9F + 4,					// DELAY: ticks = 4
0x00 + 41,					// NOTE ON: note = 41
0x9F + 52,					// DELAY: ticks = 52
0xFE,						// RETURN
			
//"Track 5"			
0x00 + 34,					// NOTE ON: note = 34
0x9F + 4,					// DELAY: ticks = 4
0x00 + 37,					// NOTE ON: note = 37
0x9F + 4,					// DELAY: ticks = 4
0x00 + 39,					// NOTE ON: note = 39
0x9F + 4,					// DELAY: ticks = 4
0x00 + 41,					// NOTE ON: note = 41
0x9F + 44,					// DELAY: ticks = 44
0x00 + 39,					// NOTE ON: note = 39
0x9F + 8,					// DELAY: ticks = 8
0xFE,						// RETURN
			
//"Track 6"			
0x00 + 37,					// NOTE ON: note = 37
0x9F + 24,					// DELAY: ticks = 24
0x00 + 39,					// NOTE ON: note = 39
0x9F + 4,					// DELAY: ticks = 4
0x00 + 37,					// NOTE ON: note = 37
0x9F + 4,					// DELAY: ticks = 4
0x00 + 36,					// NOTE ON: note = 36
0x9F + 16,					// DELAY: ticks = 16
0x00 + 33,					// NOTE ON: note = 33
0x9F + 16,					// DELAY: ticks = 16
0xFE,						// RETURN
};



#endif
