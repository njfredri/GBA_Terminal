//////////////////////////////////////////////////////////
///////////////--These are functions related to setting and reading palette, tiles, map, etc////
/////////////////////////////////////////////////////////////////
#include <gba_dma.h>

#ifndef	_PalletTileMapFunctions_h_
#define	_PalletTileMapFunctions_h_




////////This function is used to change a specific color//////////
const void SetBGColor(int r, int g, int b, int colorNumber)
{
	(*(u16*)(0x05000000 + (0x02 * colorNumber))) = RGB5(r,g,b);
}
//
//
///////copy a 1-dimensional u32 array to the tile ram // actual offset = offset * 0x4000
///////This only works in 16 color mode
////                          (u32 array, array size, int offset)
const void CopyTileToRam1d4bpp(const u32 tileArray[], const int tileArraySize, const int startOffset)
{
	for (int index = 0; index < tileArraySize; index += 1)
	{
		(*(u32*)(0x06000000 + (startOffset * 0x4000) + (index * 0x4))) = tileArray[index];
	}
}
//
const void CopyTileToRam1d8bpp(const long long tileArray[], const int tileArraySize, const int startOffset)
{
	for (int index = 0; index < tileArraySize; index += 1)
	{
		(*(long long*)(0x06000000 + (startOffset * 0x4000) + (index * 0x8))) = tileArray[index];
	}
}

static inline void CopyBGTileToRam1d8bppDMA(const void * tileAddress, int offSet, u32 numOfTiles) {

	DMA_Copy(3, tileAddress, (0x06000000+offSet*0x40000), DMA16 | (numOfTiles*128)>>1);
}
//
///////copy an array to the map ram. /// actual offest = offset * 0x800
//                     (u16 array, int array size, int offset)
const void CopyMapToRam(const u16 mapArray [], const int mapArraySize, const int startOffset)
{
	//paletteNum = paletteNum%16;  Need to add in palette choice later.
	//This will have to be either in the function using another source of data, or edited into the map entry

	for (long index = 0; index < mapArraySize; index += 1)
	{
		(*(u16*) (0x06000000 + (0x800 * startOffset) + (0x2 * index))) = mapArray [index];
	}
}

const void Copy2dMapToRam32x32(const u16 mapArray [16][16], const int startOffset)
{
	for (int x = 0; x < 32; x += 1)
	{
		for (int y = 0; y < 32; y += 1)
		{
			(*(u16*) (0x06000000 + (0x800 * startOffset) + (2 * x) + (64 * y))) = mapArray[y][x];
		}
	}
}

const void Copy2dMapToRam32x32rot(const u16 mapArray [32][32], const int startOffset)
{
	for (short x = 0; x < 64; x += 1)
	{
		for (short y = 0; y < 64; y += 1)
		{
			if (x == 2 && y == 2) {(*(u16*) (0x06000000 + (0x800 * startOffset) + (0x01*x) + (64 * y))) = 2<<8;}
			if (x == 2 && y == 3) {(*(u8*) (0x06000000 + (0x800 * startOffset) + (0x01*x) + (64 * y))) = 2;}
			(*(u8*) (0x06000000 + (0x800 * startOffset) + 2)) = 2;
		}
	}
}
//
//
///////copy an array to the bg palette ram.
//						(u16 palette array,    int array size)
const void CopyPalToBgRam(const u16 palArray [], const int palArraySize)
{
	for (int index = 0; index < palArraySize; index += 1)
	{
		(*(u16*) (0x05000000 + (0x2 * index))) = palArray [index];
	}
}
//
//
//////Copy an array to the sprite palette ram.
//						 (u16 palette array,    int array size)
const void CopyPalToSpRam(const u16 palArray [], const int palArraySize)
{
	for (int index = 0; index < palArraySize; index += 1)
	{
		(*(u16*) (0x05000200 + (0x2 * index))) = palArray [index];
	}
}



#endif
