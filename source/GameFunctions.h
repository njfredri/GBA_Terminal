
const void initializeSettings1()
{
	irqInit();
	irqEnable(IRQ_VBLANK);
	REG_DISPCNT = BG_ALL_ON| MODE_0|OBJ_1D_MAP;
}

const void initializeSettings2()
{
	irqInit();
	irqEnable(IRQ_VBLANK);
	REG_DISPCNT = BG_ALL_ON| MODE_1|OBJ_1D_MAP;
}

////////////////
const void BackGround0Setup1()
{
	
	int bgMapStart = 1; //map starts at 0x6000000 + 1 * 0x800
	int bgTileData = 0; //tiles start at 0x6000000 + 0 * 0x4000
	
	REG_BG0CNT = BG_16_COLOR|BG_SIZE(0)|(bgMapStart << 8)|(bgTileData << 2);
}
//






/////////////shrek
//fdsafds