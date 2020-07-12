#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <gba_base.h>
#include <gba_dma.h>
#include <gba_sprites.h>



///////////include setup file and custom library
#include "PaletteTileMapFunctions.h"
#include "GameFunctions.h"
//#include "BackGroundFunctions.h"
#include "../MyLibrary/backgroundSetup.h"
#include "../MyLibrary/keypad.h"
#include "../MyLibrary/mapFunctions.h"
#include "../MyLibrary/toncStuff.h"
#include "../MyLibrary/tileFunctions.h"
#include "../MyLibrary/spriteTileFunctions.h"
#include "../MyLibrary/paletteFunctions.h"
#include "../MyLibrary/textBoxFunctions.h"
//////////Tile arrays
#include "../tiles/AllTiles.h"
#include "../tiles/Tiles1.h"


//////////Map arrays
#include "../maps/AllMaps.h"


//////////Palette arrays
#include "../palette/AllPalettes.h"

//////////Test functions
#include "../test/TestFunctions.h"
//---------------------------------------------------------------------------------
// Game Variables
//---------------------------------------------------------------------------------
#include "PlayerVariables.h"
#include "MapVariables.h"


////////////////
//The terminal file
///////////////

#include "terminal.h"

int main()
{
////////////////////////////////////////////////////////////
///---------Initial Code Before Loop------------------//////
////////////////////////////////////////////////////////////
	//initializeSettings1();
	initializeSettings2();
    SetGameBGSettings();
    OAM->attr0 = 32;
    OAM->attr1 = 0;
    OAM->attr2 = 0;

	//CopyPalToBgRam(Palette, Palette_Size);
	CopyPalToSpRam(Palette, Palette_Size);
    CopyBGTileToBG2(Tiles);
    //CopyBGTileToBG2Sized(Char_A, 255, 1);
    CopyBGTileToBG1(Tiles);
    CopyBGTileToBG0(Tiles);
    CopyTilesToSpTileset(SpriteTile1,128);

	wipeRotMap1();
    //doubleSizedMapToBG0( const u8 mapArray [][16], int height, int startX, int startY)
	//doubleSizedMapToBG2(Zelda_map, 11, 0, 0);
    //doubleSizedMapToBG0(Zelda_map, 11, 0, 0);
    //doubleSizedMapToBG1(Zelda_map, 11, 10, 10);
    CopyTilesToSpTileset(SpriteTile1,128);



    runTerminal();
	//REG_BG2PA = 293;
	//REG_BG2PD = 293;
	//bool flash = false;
	//Gameplay loop
	int x = 0;
    int y = 0;





	while (1)
    {

		VBlankIntrWait();

		int g = x * 256;
        int h = y * 256;
        //const char dog[4]= {'a','o','g',' '};


		if(IS_DOWN(KEY_RIGHT)) {REG_BG2X = g; x += 1;}
		if(IS_DOWN(KEY_LEFT)) {REG_BG2X = g; x -= 1;} //scrolling adjusts with pixel size automatically
        if(IS_DOWN(KEY_UP)) {REG_BG2Y = h; y -=1;}
        if(IS_DOWN(KEY_DOWN)) {REG_BG2Y = h; y+=1;}





	}
}
