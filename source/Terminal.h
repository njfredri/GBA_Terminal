#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED

#include "TerminalFunctions.h"



const void runTerminal()
{
    //TextBoxStuff
    //char shrek[100] = {"0123456789Aa Bb Cc Dd Ee Ff Gg Hh IiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"};
    //char line[32] = {"Hello-my name Jeff69"};
    //shrek[0] = intToChar(37);
    setBG2ToTextBox(30,20,1,1);
    //putLetterToTBArray('A', 2);
    //putLetterToTBArray('A', 0);
    //putLetterToTBArray('b', 4);
    //copyCharArrayToTBArray(shrek, 0, 100);
    //copyCharArrayToTBArray(line, 100, 32);
    printTBArrayToMap();

    //readTBToString(shrek, 3, 6);
    //if (compareTwoStrings(shrek,"345678", 6)) {CopyPalToBgRam(Palette, Palette_Size);}
    //if (numberFromString("-PTILE 1234",7,11)==1234) {CopyPalToBgRam(Palette, Palette_Size);}
    if (numberFromHexString("-SET 0X02000000 88888888",7,15) == 0x02000000) {CopyPalToBgRam(Palette, Palette_Size);}

    /////////////////
    //Looop
    /////////
    int cursorPos = 0;
    while (1)
    {
        UpdatePrevKeyPad();
        VBlankIntrWait();


        printTBArrayToMap();


        pasteCommands(&cursorPos);
        cursorMove(&cursorPos);
        fixCursorPosition(&cursorPos, 149, 30);
        changeTB_Char(cursorPos);
        cursorDisplay(cursorPos);
        addTerminalTitles();
        rToWipeLine(cursorPos);
        //setVariable("-SET 0X02000000 88888888",30);
        //printVariable("-GET 0X02000000",30);
        //italicize();
        readAndCallFunctions(1);
        readAndCallFunctions(2);
        readAndCallFunctions(3);
        readAndCallFunctions(4);
        //printTile("-PTILE 0007", 30, 0);
    }
}

#endif // TERMINAL_H_INCLUDED
