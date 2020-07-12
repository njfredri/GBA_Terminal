//in order to assign the section attribute as found in <gba_base.h>
#define playerUnits_To_Pixel = (int) 100; //this is the constant to use so that you can get the actual pixel coordinates
#define playerUnits_To_Tile = (int) 100 * 8;

short playerFloor IWRAM_DATA; // this is the current floor that the player is on. Just integers. NOT multiplied
int playerX IWRAM_DATA; // this is the x position of the player multiplied by 1000
int playerY IWRAM_DATA; // this is the y position of the player multiplied by 1000

int playerX_Speed IWRAM_DATA; // this is the x speed of the player multiplied by 100
int playerY_Speed IWRAM_DATA; // this si the y speed of the player multiplied by 100

int playerX_Acc IWRAM_DATA; // this is the y acceleration of the player muliplied by 100
int playerY_Acc IWRAM_DATA; // this is the y acceleration of the player muliplied by 100