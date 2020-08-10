#ifndef CONIO2_H
#define CONIO2_H


#define BLACK           0
#define BLUE            1
#define GREEN           2
#define CYAN            3
#define RED             4
#define MAGENTA         5
#define BROWN           6
#define LIGHTGRAY       7
#define DARKGRAY        8
#define LIGHTBLUE       9
#define LIGHTGREEN      10
#define LIGHTCYAN       11
#define LIGHTRED        12
#define LIGHTMAGENTA    13
#define YELLOW          14
#define WHITE           15

#define _NOCURSOR       0
#define _SOLIDCURSOR    1
#define _NORMALCURSOR   2

#ifndef EOF
#define EOF             -1
#endif

#define LASTMODE        -1
#define C80             3
#define C4350           8

extern int _wscroll;            // 1 = enable scroll
                                // 0 = disable scroll

struct text_info {
        unsigned char curx;
        unsigned char cury;
        unsigned short attribute;
        unsigned short normattr;
        unsigned char screenwidth;
        unsigned char screenheight;
        };

#ifdef __cplusplus
extern "C" {
#endif

// move cursor to the position (x,y)
void gotoxy(int x, int y);
// return x coordinate of the cursor
int wherex(void);           
// return y coordinate of the cursor 
int wherey(void);      
// set cursor type: _NOCURSOR, _SOLIDCURSOR or _NORMALCURSOR
void _setcursortype(int cur_t);         
// set foreground and background color at once (newattr = background * 16 + foreground)
void textattr(int newattr);    
// set background color of new characters
void textbackground(int newcolor);   
// set foreground color of new characters
void textcolor(int newcolor);           
// clear till the end of current line
void clreol(void);            
// clear entire screen
void clrscr(void);     
// delete current line
void delline(void);                     
// insert empty line at cursor position
void insline(void);                     

int getch(void);                        // wait for keyboard input and return the read character
int getche(void);                       // as above, but also write the read character to screen
int kbhit(void);                        // test if a key was pressed; if kbhit returns nonzero,
                                        // the next getch will return immediately
int ungetch(int ch);                    // return character ch to input buffer; the
                                        // next getch will return this character

// write string str to screen at current cursor position
int cputs(const char *str);          
// write single character to screen at current cursor position
int putch(int c);                       
// save a portion of screen to buffer dest; dest must be large enough to hold
// two bytes per every saved character
int gettext(int left, int top, int right, int bottom, void *dest);
// write a saved portion from buffer to screen
int puttext(int left, int top, int right, int bottom, void *source);
// move a portion of screen to position (delstleft, desttop)
int movetext(int left, int top, int right, int bottom, int destleft, int desttop);
// get information about the state of screen
// see the text_info structure
void gettextinfo(struct text_info *info);
// set screen size: C80, C4350 or LASTMODE
void textmode(int mode);
//display position of cursor
void position(int beginninx, int beginningy, int legendx, int legendy, int x, int y);
// bonus functions
void settitle(const char *title);
// write board on screen
void board( int x, int y);
//creating new game with choosing number of players
void new_game(int legendx, int legendy, char player1[], int lettercount[], int beginningletters, int* numberofletters, char lettersarray[], int p);
//writting word
void new_word(char pomocnicza[], char player1[], int beginningletters, int legendx, int legendy, int beginningy, int beginningx, int* firstword, int x, int y, int letterpoint[], char letterarray[]);
//color board
void color(int x, int y);
//checking if place on board is empty
bool isempty(int x, int y);
//coloring two main crosses
void colorcross(int i, int px);
//combination of textbackoun()+putch()
void colorputch(char zn, int color);
//color function coloring small rectangle
void colorsmall(int i);
//function created to exchange letters 
void exchangetable(char player1[], int exchange[], int beginningletters, char lettersarray[], int letterscount[], int p, int legendx, int legendy);
//ranomize new letters to exchange
void random(int exchange[], char player1[], char lettersarray[], int letterscount[], int beginningletters, int p);
//end of letters exchange
void putchexchange(int array[], int beginningletters, int legendx, int legendy,char player1[]);
//putting everything in base position
void beginning();
//checking if we wont go from our board (down)
bool down(int BEGINNINGY, int y);
//checking if we wont go from our board (up)
bool up(int BEGINNINGY, int y);
//checking if we wont go from our board (left)
bool left(int BEGINNINGX, int x);
//checking if we wont go from our board (right)
bool right(int BEGINNINGX, int x);
//exchanging blank for letter
void unknown(char word[], int elnumber, int legendx, int legendy);
//put first word on board
void firstwordfunction(char word[], int length, int beginningx, int beginningy,char player1[], int beginningletters, int legendx, int legendy);
//write actualboard on screen
void writeactualboard(int x, int y);
//random after move
void randomaftermove(char player1[], int beginningletters, int* numberofletters, char lettersarray[], int letterscount[]);
//put word on screen
void putword(int beginningx, int beginningy, char word[], int length, int x, int y, int letterpoints[], char lettersarray[], int beginningletters, char player1[]);
//zero wordonboard array
void zerowordonboard();
//first part of checking if we can put word
bool canputword();
//second part of checking if we can put word
bool canputword2();
//change orientation of word you are putting
void changeorientation(int *orientetion, int length);
//checking if we can move our word (up down right left)
bool wordpositiondown();
bool wordpositionup();
bool wordpositionright();
bool wordpositionleft();
//end of checking
void zerocheck();
//checking possibility of moving word 90 degrees, and doing it
bool possibilitycheckpart();
bool possibilitycheck(int length, char word[]);
int whichplace(char zn, char lettersarray[]);
//counting points
void pointscount(int length, int letterpoints[], char lettersarray[]);
//write points on screen
void putpoints(int legendx, int legendy);
//checking if we can have letters we declared
bool haveallletters(int length, char word[], char player1[], int beginningletters);
//randomizing new letters after move
void randaftermove(char player1[], int beginningletters, int letterscount[], char lettersarray[], int* numberofletters);


int Conio2_Init(void);
#ifdef __cplusplus
}
#endif

#endif