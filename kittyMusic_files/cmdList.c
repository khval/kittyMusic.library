
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __amigaos4__
#include <proto/exec.h>
#include <proto/retroMode.h>
#endif

#include <amosKittens.h>

#include "cmdList.h"


struct cmdData AMOSPro_Music[]={
		{0x0006,"Mubase",0,musicMubase},
		{0x0012,"Vumeter",0,musicVumeter},
		{0x0020,"Voice",0,musicVoice},
		{0x002C,"Music Off",0,musicMusicOff},
		{0x003C,"Music Stop",0,musicMusicStop},
		{0x004C,"Tempo",0,musicTempo},
		{0x0058,"Music",0,musicMusic},
		{0x0064,"Noise To",0,musicNoiseTo},
		{0x0074,"Boom",0,musicBoom},
		{0x007E,"Shoot",0,musicShoot},
		{0x008A,"Sam Bank",0,musicSamBank},
		{0x009A,"Sam Loop On",0,musicSamLoopOn},
		{0x00AC,"Sam Loop On",0,musicSamLoopOn},
		{0x00B4,"Sam Loop Off",0,musicSamLoopOff},
		{0x00C6,"Sam Loop Off",0,musicSamLoopOff},
		{0x00CE,"Sample",0,musicSample},
		{0x00DE,"Sam Play",0,musicSamPlay},
		{0x00EE,"Sam Play",0,musicSamPlay},
		{0x00F8,"Sam Play",0,musicSamPlay},
		{0x0104,"Sam Raw",0,musicSamRaw},
		{0x0118,"Bell",0,musicBell},
		{0x0124,"Bell",0,musicBell},
		{0x012C,"Play Off",0,musicPlayOff},
		{0x013C,"Play Off",0,musicPlayOff},
		{0x0144,"Play",0,musicPlay},
		{0x0152,"Play",0,musicPlay},
		{0x015E,"Set Wave",0,musicSetWave},
		{0x0170,"Del Wave",0,musicDelWave},
		{0x0180,"Set Envel",0,musicSetEnvel},
		{0x0196,"Mvolume",0,musicMvolume},
		{0x01A4,"Volume",0,musicVolume},
		{0x01B2,"Volume",0,musicVolume},
		{0x01BC,"Wave",0,musicWave},
		{0x01CA,"Led On",0,musicLedOn},
		{0x01D6,"Led Off",0,musicLedOff},
		{0x01E4,"Say",0,musicSay},
		{0x01F0,"Say",0,musicSay},
		{0x01FA,"Set Talk",0,musicSetTalk},
		{0x0210,"Sload",0,musicSload},
		{0x0220,"Sam Swapped",0,musicSamSwapped},
		{0x0232,"Sam Swap",0,musicSamSwap},
		{0x0246,"Sam Stop",0,musicSamStop},
		{0x0256,"Sam Stop",0,musicSamStop},
		{0x025E,"Track Stop",0,musicTrackStop},
		{0x026E,"Track Loop On",0,musicTrackLoopOn},
		{0x0282,"Track Loop Of",0,musicTrackLoopOf},
		{0x0296,"Track Play",0,musicTrackPlay},
		{0x02A8,"Track Play",0,musicTrackPlay},
		{0x02B0,"Track Play",0,musicTrackPlay},
		{0x02BA,"Track Load",0,musicTrackLoad},
		{0x02CE,"Mouth Width",0,musicMouthWidth},
		{0x02E0,"Mouth Height",0,musicMouthHeight},
		{0x02F2,"Mouth Read",0,musicMouthRead},
		{0x0302,"Talk Stop",0,musicTalkStop},
		{0x0312,"Talk Misc",0,musicTalkMisc},
		{0x0324,"Ssave",0,musicSsave},
		{0x0334,"Med Load",0,musicMedLoad},
		{0x0346,"Med Play",0,musicMedPlay},
		{0x0356,"Med Play",0,musicMedPlay},
		{0x035E,"Med Play",0,musicMedPlay},
		{0x0368,"Med Stop",0,musicMedStop},
		{0x0376,"Med Cont",0,musicMedCont},
		{0x0384,"Med Midi On",0,musicMedMidiOn},
		{0x0000,NULL,0,0}};

