#ifndef TERMINALFUNCTIONS_H_INCLUDED
#define TERMINALFUNCTIONS_H_INCLUDED

#define cursorInterval 2
#define characterMax 37
#define line1 30
#define line2 60
#define line3 90
#define line4 120
#define line5 150

int count EWRAM_DATA;
int keyCount EWRAM_DATA;
int keyCountB EWRAM_DATA;
bool LPressed EWRAM_DATA;
bool startPressed EWRAM_DATA;
int variable1 EWRAM_DATA;


const void cursorDisplay(int position)
{
    int posX = position%TB_Width;
    int posy = position/TB_Width;
    count = (count+1)%cursorInterval;
    if (count < cursorInterval/2)
    {
        if (posX % 2 == 0)
        {
            u16 tile = ((bg2Map[posX/2+32*posy]>>8)<<8);
            bg2Map[posX/2+32*posy] = 200 + tile;
        }
        else
        {
            u8 tile = (u8)bg2Map[posX/2+32*posy];
            bg2Map[posX/2+32*posy] =  (200<<8)+ tile;
        }
        //bg2Map[x/2+32*y] = charToInt(TB_Text[y][x])
    }
}

const void cursorMove(int *pos)
{
    if (IS_DOWN(KEY_RIGHT))
    {
        keyCount +=1;
        if (keyCount == 1 || (keyCount > 20 && (keyCount%5)==1) || (keyCount > 100 && (keyCount%3)==1)) {*pos +=1;}
    }
    else if (IS_DOWN(KEY_LEFT))
    {
        keyCount +=1;
        if (keyCount == 1 || (keyCount > 20 && (keyCount%5)==1) || (keyCount > 100 && (keyCount%3)==1)) {*pos -=1;}
    }
    ////moving up and down
    else if (IS_DOWN(KEY_DOWN))
    {
        keyCount +=1;
        if ((keyCount%30)==1) {*pos += TB_Width;}
    }
    else if (IS_DOWN(KEY_UP))
    {
        keyCount +=1;
        if ((keyCount%30)==1) {*pos -= TB_Width;}
    }

    else {keyCount = 0;}
    while (*pos > TB_Width*TB_Height) {pos -= TB_Width*TB_Height;}
    if (*pos < 0) {*pos = 0;}
    if (keyCount > 1000) {keyCount -= 900;}
}

const void changeTB_Char(int pos)
{
    int posX = pos%TB_Width;
    int posY = pos/TB_Width;
    if (IS_DOWN(KEY_A) && !(IS_DOWN(KEY_B)))
    {
        keyCountB += 1;
        if (keyCountB%20 == 1 || (keyCountB > 60 && keyCountB%10 == 1))
        {
            int old = charToInt(TB_Text[posY][posX]);
            old +=1;
            if (old > characterMax) {old = 0;}
            TB_Text[posY][posX] = intToChar(old);
            //TB_Text[posY][posX] = 'c';
        }
    }
    else if (IS_DOWN(KEY_B) && !(IS_DOWN(KEY_A)))
    {
        keyCountB += 1;
        if (keyCountB%20 == 1 || (keyCountB > 60 && keyCountB%5 == 1))
        {
            int old = charToInt(TB_Text[posY][posX]);
            old -=1;
            if (old < 0) {old = characterMax;}
            TB_Text[posY][posX] = intToChar(old);
            //TB_Text[posY][posX] = 'c';
        }
    }
    else keyCountB = 0;
}

const void fixCursorPosition(int *pos, int Max, int Min)
{
    if (*pos > Max) {*pos = Max;}
    if (*pos < Min) {*pos = Min;}
}

const void addTerminalTitles()
{
    copyCharArrayToTBArray("Input-", 0, 6);
    copyCharArrayToTBArray("Output-", 300, 7);
}

const void wipeTB(int position, int numberToWipe)
{
    for (int i=0; i < numberToWipe; i +=1)
    {
        putLetterToTBArray(' ', position+i);
    }
}

const void wipeOutPut()
{
    for (int i = 330; i < 600; i +=1)
    {
        putLetterToTBArray(' ', i);
    }
}
//////////////////////////////////
///////////////////////////////
/////////////////////////////////////
////////////////////////////////
////////////////////////////
const void speen()
{

    for (int i = 0; i < 29535; i += 128)
    {
        REG_BG2PB = i;
        REG_BG2PC = i;
        printTBArrayToMap();
        VBlankIntrWait();
    }
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PA = 256;
    REG_BG2X = 0;
}

bool italics EWRAM_DATA;
const void italicize()
{
    if (italics == false)
    {
        italics = true;
        REG_BG2PB = 100;
        REG_BG2PA = 300;
        REG_BG2X = -60*256;
    }
    else
    {
        REG_BG2PB = 0;
        REG_BG2PA = 256;
        REG_BG2X = 0;
        italics = false;
    }
}
const void setVariable(char strang[], int lineStart)
{
    long address = 0;
    if (strang[5] != '0' || strang [6] != 'X')
    {
        copyCharArrayToTBArray("Error -Set Fail", lineStart+300, 15);
        return;
    }

    address = numberFromHexString(strang, 7,15);

    //if (address != 0x02000000) {copyCharArrayToTBArray("Error Address not 0x02000000", lineStart+300, 30); return;}


    int value = numberFromString(strang, 17, 28);
    //variable1 = 0;
    *(int*)address = value;
    if (*(int*)address != value) {copyCharArrayToTBArray("Not value", lineStart+300, 30); return;}
    copyCharArrayToTBArray("Value Set", lineStart+300, 10);

}

const void printVariable(char strang[], int lineStart)
{
    //long address = 0;
    if (strang[5] != '0' || strang [6] != 'X')
    {
        copyCharArrayToTBArray("Error -Get Fail", lineStart+300, 15);
        return;
    }

    long address = numberFromHexString(strang, 7,15);
    //if (address != 0x02000000) {copyCharArrayToTBArray("Not 0X02000000", lineStart+300, 30); return;}
    int val = *(int*)address;
    //val = 432100;
    copyCharArrayToTBArray("VALUE IS-", lineStart+300, 9);

    char dog[10];
    int curVal = 0;
    int dogCount = 0;
    for (int i = 1000000000; i > 0; i = i/10)
    {
        curVal = ((val/i) - (val/(10*i)*10));
        dog[dogCount] = intToChar(curVal + 1);
        dogCount +=1;
    }
    copyCharArrayToTBArray(dog, lineStart+300, 10);
}

const void printTile(char strang[], int lineStart, int lineNum)
{
    if (lineNum == 1)
    {
        CopyBGTileToTB(numberFromString(strang, 7, 11), 250, 1);
        TB_Text[11][0] = '[';
    }
    else if (lineNum == 2)
    {
        CopyBGTileToTB(numberFromString(strang, 7, 11), 251, 1);
        TB_Text[12][0] = ']';
    }
    else if (lineNum == 3)
    {
        CopyBGTileToTB(numberFromString(strang, 7, 11), 252, 1);
        TB_Text[13][0] = '{';
    }
    else if (lineNum == 4)
    {
        CopyBGTileToTB(numberFromString(strang, 7, 11), 253, 1);
        TB_Text[14][0] = '}';
    }

    copyCharArrayToTBArray("-PTILE", lineNum*30 + 301, 8);
}

const void printBGMode(int lineStart)
{
    copyCharArrayToTBArray("BG MODE ", lineStart+300, 8);
    u16 val = REG_DISPCNT%8;
    char dog[2];
    int curVal = 0;
    int dogCount = 0;
    for (int i = 10; i > 0; i = i/10)
    {
        curVal = ((val/i) - (val/(10*i)*10));
        dog[dogCount] = intToChar(curVal + 1);
        dogCount +=1;
    }
    copyCharArrayToTBArray(dog, lineStart+308, 2);
}

const void readAndCallFunctions(int lineNum)
{

    char strang [30];
    //readTBToString(strang, 30, 20);
    //if (compareStringToTB("DOG",30,3)) {TB_Text[0][0] = 'a';}
    if(IS_PRESSED(KEY_START) && startPressed == false)
    {
        if (lineNum == 1) {wipeOutPut();}
        startPressed = true;
        readTBToString(strang,30*lineNum,30);
        if (compareTwoStrings("-SET",strang,4)) {setVariable(strang,30*lineNum);}
        if((compareTwoStrings("-PTILE",strang,6)))
        {
            //copyCharArrayToTBArray(strang, 300+30*lineNum, 5);
            printTile(strang, 30*lineNum, lineNum);
        }
        if (compareTwoStrings("-GET", strang, 4)) {printVariable(strang,30*lineNum);}
        if (compareTwoStrings("-BGMODE", strang, 7)) {printBGMode(lineNum*30);}
        if (compareTwoStrings("-SPEEND", strang, 7)) {speen();}
        if (compareTwoStrings("-ITAL", strang, 5)) {italicize();}
    }

    if (!(IS_DOWN(KEY_START)) && startPressed == true)
    {
        startPressed = false;
    }
    if (lineNum != 4)
    {
        startPressed = false;
    }

}

const void pasteCommands(int *pos)
{
    if(IS_DOWN(KEY_L))
    {
        if (LPressed == true) {return;}
        int lineStart = *pos - (*pos%TB_Width);
        LPressed = true;

        if ((compareStringToTB("-SPEEND                       ", lineStart, 10)))
        {
            copyCharArrayToTBArray("-ITAL                       ", lineStart, 30);
            return;
        }

        if ((compareStringToTB("-BGMODE                        ", lineStart, 9)))
        {
            copyCharArrayToTBArray("-SPEEND                       ", lineStart, 30);
            return;
        }

        if ((compareStringToTB("-PTILE 0000                   ", lineStart, 26)))
        {
            copyCharArrayToTBArray("-BGMODE                        ", lineStart, 30);
            return;
        }

        if ((compareStringToTB("-GET 0X02000000                 ", lineStart, 26)))
        {
            copyCharArrayToTBArray("-PTILE 0000                   ", lineStart, 30);
            return;
        }

        if ((compareStringToTB("-SET 0X02000000 00000000000", lineStart, 26)))
        {
            copyCharArrayToTBArray("-GET 0X02000000                 ", lineStart, 30);
            return;
        }

        if (!(compareStringToTB("-SET 0X02000000 00000000000", lineStart, 26)))
        {
            copyCharArrayToTBArray("-SET 0X02000000 00000000000    ", lineStart, 30);
            return;
        }

    }
    else LPressed = false;
}

const void rToWipeLine(int pos)
{
    int lineStart = pos - (pos%TB_Width);
    if (IS_DOWN(KEY_R))
    {
        wipeTB(lineStart,30);
    }
}
#endif // TERMINALFUNCTIONS_H_INCLUDED
