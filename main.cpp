#include<stdio.h>
#include"conio2.h"
#define BEGINNINGX 70 // beginning of board (x)
#define BEGINNINGY 3 // beginning of board (y)
#define LEGENDX 10 // beginning of legend (x)
#define LEGENDY 1 // beginning of legend (y)
#define BEGINNINGLETTERS 7 //number of letters 
/* Comment: in the final program declare appropriate constants, e.g.,
   to eliminate from your program numerical values by replacing them
   with well defined identifiers */

int main() {
        //number of letters in game
        int numberofletters = 100;
        int zn = 0, x = BEGINNINGX+1, y = BEGINNINGY+1, attr = 7, back = 0, zero = 0;
        char firstletter = 'a';
        char lettersrray[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','?'};
        //actual letters
        char player1[BEGINNINGLETTERS];
        //number of letter in sack
        //numers of each letter in alphabet and blank
        int lettercount[27] = {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1,2};
        //points for each letter in lettersarray
        int letterpoints[26] = { 1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10 };
        char txt[32];
        char pomocnicza[BEGINNINGLETTERS];
        int exchange[BEGINNINGLETTERS];
        int boardx = BEGINNINGX+1;
        int boardy = BEGINNINGY + 1;
        int firstword = 1;
        //actual position of letters
        
        // if the program is compiled in pure C, then we need to initialize
        // the library ourselves; __cplusplus is defined only if a C++ compiler
        // is used
#ifndef __cplusplus
        Conio2_Init();
#endif
        // settitle sets the window title
        settitle("SCCRABBLE by Lukasz Golojuch");
        //new_game(LEGENDX, LEGENDY, player2, player1, BEGINNINGLETTERS);
        // hide the blinking cursor
        _setcursortype(_NOCURSOR);
        new_game(LEGENDX, LEGENDY, player1, lettercount, BEGINNINGLETTERS, &numberofletters, lettersrray, numberofletters);
        zerowordonboard();
        for (int i = 0; i < BEGINNINGLETTERS; i++)
        {
                exchange[i] = 0;
        }
        beginning();
        do {

                // we set black to be the background color
                // check conio2.h for available colors
                textbackground(BLACK);
                // clear the screen: we fill it out with spaces with
                // the specified background color
                clrscr();
                // we set the text color (7 == LIGHTGRAY)
                textcolor(7);
                // we move the coursor to column 48 and row 1
                // rows and column are numbered starting with 1
                putpoints(LEGENDX, LEGENDY);

                board(BEGINNINGX, BEGINNINGY);
                gotoxy(LEGENDX, LEGENDY);
                // we print out a text at a given cursor position
                // the cursor will move by the length of the text
                cputs("SCCRABBLE by Lukasz Golojuch");
                gotoxy(LEGENDX, LEGENDY + 1);
                cputs("q or ESC      = exit");
                gotoxy(LEGENDX, LEGENDY + 2);
                cputs("cursors = moving");
                gotoxy(LEGENDX, LEGENDY + 3);
                cputs("w   = change letters");
                gotoxy(LEGENDX, LEGENDY + 4);
                cputs("1-7   = choose letter for exchange");;
                gotoxy(LEGENDX, LEGENDY + 5);
                cputs("n   = create new game");
                gotoxy(LEGENDX, LEGENDY + 6);
                cputs("i   = next move");
                
                gotoxy(LEGENDX, LEGENDY+8);
                cputs(txt);             
                
                gotoxy(LEGENDX, LEGENDY + 13);
                cputs("Your letters:");

                for (int i = 0; i < BEGINNINGLETTERS; i++)
                {
                        //print each letter you have actually
                        gotoxy(LEGENDX + (2 * i), LEGENDY + 15);
                        putch(player1[i]);
                }

                gotoxy(10, 8);
            // we draw a star
                gotoxy(x, y);
                textcolor(attr);
                textbackground(back);
                // putch prints one character and moves the cursor to the right
                putch('*');
                position(BEGINNINGX, BEGINNINGY, LEGENDX, LEGENDY, x, y);
                
                
                // we wait for key press and get its code
                // most key codes correspond to the characters, like
                // a is 'a', 2 is '2', + is '+', but some special keys
                // like cursors provide two characters, where the first
                // one is zero, e.g., "up arrow" is zero and 'H'
                zero = 0;

                zn = getch();
                // we do not want the key 'H' to play role of "up arrow"
                // so we check if the first code is zero
                if(zn == 0) {
                        zero = 1;               // if this is the case then we read
                        zn = getch();           // the next code knowing that this will be a special key
                        if(zn == 0x48 && down(BEGINNINGY, y)) y--;     // move cursor down
                        else if(zn == 0x50 && up(BEGINNINGY, y)) y++;   // move cursor up
                        else if(zn == 0x4b && left(BEGINNINGX, x)) x=x-2;   // move cursor left
                        else if(zn == 0x4d && right(BEGINNINGX, x)) x=x+2;  // move cursor right
                }
                else
                {
                        if (zn == 27)
                        {
                                return 0;
                        }
                else {
                        if (zn == 'n')
                        {
                            //press 'n' to start new game
                                new_game(LEGENDX, LEGENDY, player1, lettercount, BEGINNINGLETTERS, &numberofletters, lettersrray, numberofletters);
                                randaftermove(player1, BEGINNINGLETTERS, lettercount, lettersrray, &numberofletters);
                                int lettercount[27] = { 9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1,2 };
                        }
                        else
                        {
                                if (zn == 'i')
                                {
                                        //press 'i' to make your next move
                                        //firstly we put new word on board
                                        new_word(pomocnicza, player1, BEGINNINGLETTERS, LEGENDX, LEGENDY, BEGINNINGY, BEGINNINGX, &firstword,x,y,letterpoints,lettersrray);
                                        //after that we randomize our next letters
                                        randomaftermove(player1, BEGINNINGLETTERS, &numberofletters, lettersrray, lettercount);
                                }
                                else 
                                {
                                        if (zn == 'w')
                                        {
                                            //press 'w' to exchange letters for new ones
                                            exchangetable(player1, exchange, BEGINNINGLETTERS, lettersrray, lettercount, numberofletters, LEGENDX, LEGENDY);
                                        }
                                        
                                }
                                
                        }
                        
                }
                }
                

                
        } while (zn != 'q');
                        
        _setcursortype(_NORMALCURSOR);  // show the cursor so it will be
                                        // visible after the program ends
        return 0;
        }