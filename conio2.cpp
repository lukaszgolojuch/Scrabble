#include<stdio.h>
#include<malloc.h>
#include<time.h>
#include<string.h>
#include<windows.h>
#include"conio2.h"
#ifdef __GNUC__
#include<stdlib.h>
#endif

#define numberofchars 27
#define SIZE 15

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

int _wscroll;
//word we put already on our board
char actualboard[SIZE][SIZE];
//array helping us to put word in actualboard
char wordonboard[SIZE][SIZE];
//word is array with new word
char word[SIZE];
char pionowa[SIZE][SIZE];
char checktable[SIZE][SIZE];
//beginning end eding positions of our new word in array... 
int beginx, beginy, endx, endy, points;
int mnozniki[SIZE][SIZE];
int mnoznikliter;
int mnoznikslow;
void zerocheck()
{
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        checktable[i][j] = ' ';
                        mnozniki[i][j] = 0;
                }
        }
};

void beginning()
{
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        actualboard[j][i] = ' ';
                }
        }
};
void zerowordonboard()
{
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        wordonboard[j][i] = ' ';
                }
        }
};
typedef struct _Conio2ThreadData {
        int attrib;
        int charCount;
        int charValue;
        int charFlag;
        int ungetCount;
        int ungetBuf[16];
        int _wscroll;
        int width;
        int height;
        int origwidth;
        int origheight;
        int origdepth;
        int lastmode;
        HANDLE output;
        HANDLE input;
        DWORD prevOutputMode;
        DWORD prevInputMode;
        } Conio2ThreadData;


static Conio2ThreadData thData;


static void UpdateWScroll() {
        if(_wscroll != thData._wscroll) {
                if(_wscroll) SetConsoleMode(thData.output, ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
                else SetConsoleMode(thData.output, ENABLE_PROCESSED_OUTPUT);
                thData._wscroll = _wscroll;
                };
        };


static WORD ToWinAttribs(int attrib) {
        WORD rv = 0;
        if(attrib & 1) rv |= FOREGROUND_BLUE;
        if(attrib & 2) rv |= FOREGROUND_GREEN;
        if(attrib & 4) rv |= FOREGROUND_RED;
        if(attrib & 8) rv |= FOREGROUND_INTENSITY;
        if(attrib & 16) rv |= BACKGROUND_BLUE;
        if(attrib & 32) rv |= BACKGROUND_GREEN;
        if(attrib & 64) rv |= BACKGROUND_RED;
        if(attrib & 128) rv |= BACKGROUND_INTENSITY;
        return rv;
        };


static int FromWinAttribs(WORD attrib) {
        int rv = 0;
        if(attrib & FOREGROUND_BLUE) rv |= 1;
        if(attrib & FOREGROUND_GREEN) rv |= 2;
        if(attrib & FOREGROUND_RED) rv |= 4;
        if(attrib & FOREGROUND_INTENSITY) rv |= 8;
        if(attrib & BACKGROUND_BLUE) rv |= 16;
        if(attrib & BACKGROUND_GREEN) rv |= 32;
        if(attrib & BACKGROUND_RED) rv |= 64;
        if(attrib & BACKGROUND_INTENSITY) rv |= 128;
        return rv;
        };


static void GetCP(int *x, int *y) {
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(thData.output, &info);
        if(x) *x = info.dwCursorPosition.X + 1;
        if(y) *y = info.dwCursorPosition.Y + 1;
        };


static int HandleKeyEvent(INPUT_RECORD *buf) {
        int ch;
        ch = (int)(buf->Event.KeyEvent.uChar.AsciiChar) & 255;
        if(ch == 0) ch = 0x8000 + buf->Event.KeyEvent.wVirtualKeyCode;
        if(ch == 0x8010 || ch==0x8011 || ch==0x8012 || ch==0x8014
           || ch==0x8090 || ch==0x8091) return 0;
        thData.charCount = buf->Event.KeyEvent.wRepeatCount;
        thData.charFlag = ch & 0x8000 ? 1 : 0;
        if(thData.charFlag) thData.charCount *= 2;
        int alt = (buf->Event.KeyEvent.dwControlKeyState & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED)) != 0;
        int ctrl = (buf->Event.KeyEvent.dwControlKeyState & (LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED)) != 0;
        switch(ch) {
                case 0x8000 + 33:       ch = 0x8000 + 73; break;
                case 0x8000 + 34:       ch = 0x8000 + 81; break;
                case 0x8000 + 35:       ch = 0x8000 + 79; break;
                case 0x8000 + 36:       ch = 0x8000 + 71; break;
                case 0x8000 + 37:       if(ctrl) ch = 0x8073;
                                        else if(alt) ch = 0x809b;
                                        else ch = 0x8000 + 75; break;
                case 0x8000 + 38:       if(ctrl) ch = 0x808d;
                                        else if(alt) ch = 0x8098;
                                        else ch = 0x8000 + 72; break;
                case 0x8000 + 39:       if(ctrl) ch = 0x8074;
                                        else if(alt) ch = 0x809d;
                                        else ch = 0x8000 + 77; break;
                case 0x8000 + 40:       if(ctrl) ch = 0x8091;
                                        else if(alt) ch = 0x80a0;
                                        else ch = 0x8000 + 80; break;
                case 0x8000 + 46:       ch = 0x8000 + 83; break;
                case 0x8000 + 112:      ch = 0x8000 + 59; break;
                case 0x8000 + 113:      ch = 0x8000 + 60; break;
                case 0x8000 + 114:      ch = 0x8000 + 61; break;
                case 0x8000 + 115:      ch = 0x8000 + 62; break;
                case 0x8000 + 116:      ch = 0x8000 + 63; break;
                case 0x8000 + 117:      ch = 0x8000 + 64; break;
                case 0x8000 + 118:      ch = 0x8000 + 65; break;
                case 0x8000 + 119:      ch = 0x8000 + 66; break;
                case 0x8000 + 120:      ch = 0x8000 + 67; break;
                case 0x8000 + 121:      ch = 0x8000 + 68; break;
                case 0x8000 + 122:      ch = 0x8000 + 133; break;
                case 0x8000 + 123:      ch = 0x8000 + 134; break;
                };
        thData.charValue = ch & 0x7fff;
        return 1;
        };


static void ResizeConsole(HANDLE con, int w, int h, int d) {
        int cw, ch;
        COORD s;
        SMALL_RECT r;
        CONSOLE_SCREEN_BUFFER_INFO info;

        BOOL res = GetConsoleScreenBufferInfo(con, &info);
        cw = info.srWindow.Right - info.srWindow.Left + 1;
        ch = info.srWindow.Bottom - info.srWindow.Top + 1;

        if(w < cw || h < ch) {
                r.Top = 0;
                r.Left = 0;
                r.Right = (SHORT)(min(w, cw) - 1);
                r.Bottom = (SHORT)(min(h, ch) - 1);
                SetConsoleWindowInfo(con, TRUE, &r);
                };

        if(d < h) d = h;
        s.X = (SHORT)w;
        s.Y = (SHORT)d;
        SetConsoleScreenBufferSize(con, s);
        r.Top = 0;
        r.Left = 0;
        r.Right = (SHORT)(w - 1);
        r.Bottom = (SHORT)(h - 1);
        SetConsoleWindowInfo(con, TRUE, &r);
        };


static void ReloadConsoleSize() {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if(GetConsoleScreenBufferInfo(thData.output, &info)) {
                thData.width = info.srWindow.Right - info.srWindow.Left + 1;
                thData.height = info.srWindow.Bottom - info.srWindow.Top + 1;
                };
        };


static void InitConio2(Conio2ThreadData *data) {
        data->output = GetStdHandle(STD_OUTPUT_HANDLE); 
        data->input = GetStdHandle(STD_INPUT_HANDLE); 
        data->ungetCount = 0;
        data->charCount = 0;
        
        CONSOLE_SCREEN_BUFFER_INFO info;
        BOOL rc = GetConsoleScreenBufferInfo(data->output, &info);
        if(rc) {
                data->origwidth = info.srWindow.Right - info.srWindow.Left + 1;
                data->origheight = info.srWindow.Bottom - info.srWindow.Top + 1;
                data->origdepth = info.dwSize.Y;
        } else {
                data->origwidth = 80;
                data->origheight = 25;
                data->origdepth = 25;
                }

        data->width = data->origwidth;
        data->height = data->origheight;

        data->attrib = 0x07;
        data->lastmode = C80;
        data->_wscroll = -1;
        SetConsoleTextAttribute(thData.output, ToWinAttribs(thData.attrib));
        GetConsoleMode(data->input, &(data->prevInputMode));
        GetConsoleMode(data->output, &(data->prevOutputMode));
        SetConsoleMode(data->input, ENABLE_PROCESSED_INPUT);
        UpdateWScroll();
        };


static void ExitConio2(Conio2ThreadData *data) {
        ResizeConsole(data->output, data->origwidth, data->origheight, data->origdepth);
        SetConsoleMode(data->input, data->prevInputMode);
        SetConsoleMode(data->output, data->prevOutputMode);
        };


EXTERNC
void gotoxy(int x, int y) {
        COORD pos;
        pos.X = x - 1;
        pos.Y = y - 1;
        SetConsoleCursorPosition(thData.output, pos);
        };


EXTERNC
int wherex() {
        int x;
        GetCP(&x, NULL);
        return x;
        };


EXTERNC
int wherey() {   
        int y;
        GetCP(NULL, &y);
        return y;
        };


EXTERNC
void _setcursortype(int cur_t) {
        CONSOLE_CURSOR_INFO inf;
        GetConsoleCursorInfo(thData.output, &inf);
        if(cur_t == _NOCURSOR) {
                inf.bVisible = FALSE;
        } else if(cur_t == _NORMALCURSOR) {
                inf.bVisible = TRUE;
                inf.dwSize = 13;
        } else if(cur_t == _SOLIDCURSOR) {
                inf.bVisible = TRUE;
                inf.dwSize = 100;
        } else return;
        SetConsoleCursorInfo(thData.output, &inf);
        };


EXTERNC
void textattr(int newattr) {
        thData.attrib = newattr;
        SetConsoleTextAttribute(thData.output, ToWinAttribs(thData.attrib));
        };


EXTERNC
void textbackground(int newcolor) {
        thData.attrib = (thData.attrib & 0x0f) | ((newcolor & 15) << 4);
        SetConsoleTextAttribute(thData.output, ToWinAttribs(thData.attrib));
        };


EXTERNC
void textcolor(int newcolor) {
        thData.attrib = (thData.attrib & 0xf0) | (newcolor & 15);
        SetConsoleTextAttribute(thData.output, ToWinAttribs(thData.attrib));
        };


EXTERNC
void clreol() {
        int cx, cy;
        COORD pos;
        DWORD nwr, len;
        GetCP(&cx, &cy);
        len = thData.width - cx + 1;
        if(len > 0) {
                pos.X = cx - 1;
                pos.Y = cy - 1;
                FillConsoleOutputCharacter(thData.output, ' ', len, pos, &nwr);
                FillConsoleOutputAttribute(thData.output, thData.attrib, len, pos, &nwr);
                gotoxy(cx, cy);
                };
        };


EXTERNC
void clrscr() {
        ReloadConsoleSize();
        DWORD nwr, len = thData.width * thData.height;
        COORD pos;
        pos.X = pos.Y = 0;
        FillConsoleOutputCharacter(thData.output, ' ', len, pos, &nwr);
        FillConsoleOutputAttribute(thData.output, thData.attrib, len, pos, &nwr);
        };


EXTERNC
void delline() {
        int y;
        y = wherey();
        movetext(1, y + 1, thData.width, thData.height, 1, y);
        };


EXTERNC
void insline() {
        int y;
        y = wherey();
        movetext(1, y, thData.width, thData.height - 1, 1, y + 1);
        };


EXTERNC
int getch() {
        BOOL rv;
        DWORD n;
        INPUT_RECORD buf;

        if(thData.ungetCount > 0) {
                thData.ungetCount--;
                return thData.ungetBuf[thData.ungetCount];
                };

        if(thData.charCount > 0) {
                thData.charCount--;
                if((thData.charCount & 1) && thData.charFlag) return 0;
                else return thData.charValue;
                };

        while(1) {
                rv = ReadConsoleInput(thData.input, &buf, 1, &n);
                if(!rv) continue;
                if(buf.EventType != KEY_EVENT) continue;
                if(!buf.Event.KeyEvent.bKeyDown) continue;
                if(HandleKeyEvent(&buf)) break;
                };

        thData.charCount--;
        if((thData.charCount & 1) && thData.charFlag) return 0;
        else return thData.charValue;
        };


EXTERNC
int getche() {
        int ch;
        ch = getch();
        putch(ch);
        return ch;
        };


EXTERNC
int kbhit() {
        BOOL rv;
        DWORD n;
        INPUT_RECORD buf;

        if(thData.ungetCount > 0) return 1;
        if(thData.charCount > 0) return 1;

        rv = PeekConsoleInput(thData.input, &buf, 1, &n);
        if(!rv) return 0;
        if(n == 0) return 0;
        rv = ReadConsoleInput(thData.input, &buf, 1, &n);
        if(!rv) return 0;
        if(buf.EventType != KEY_EVENT) return 0;
        if(!buf.Event.KeyEvent.bKeyDown) return 0;
        return HandleKeyEvent(&buf) ? 1 : 0;
        };


EXTERNC
int ungetch(int ch) {
        if(thData.ungetCount >= 15) return EOF;
        thData.ungetBuf[thData.ungetCount++] = ch;
        return ch;
        };


EXTERNC
int cputs(const char *str) {
        DWORD count;
        if(str == NULL) return EOF;
        UpdateWScroll();
        if(WriteConsoleA(thData.output, str, strlen(str), &count, NULL)) return count;
        else return EOF;
};
EXTERNC
int putch(int c) {
        DWORD count;
        UpdateWScroll();
        if(WriteConsoleA(thData.output, &c, 1, &count, NULL)) return c;
        else return EOF;
};
EXTERNC
int gettext(int left, int top, int right, int bottom, void *dest) {
        int i;
        SMALL_RECT trg;
        COORD pos, size;
        CHAR_INFO *buf;
        buf = (CHAR_INFO *)alloca((right - left + 1) * (bottom - top + 1) * sizeof(CHAR_INFO));

        pos.X = 0; pos.Y = 0;
        size.X = right - left + 1; size.Y = bottom - top + 1;
        trg.Left = left - 1; trg.Top = top - 1;
        trg.Right = right - 1; trg.Bottom = bottom - 1;
        ReadConsoleOutputA(thData.output, buf, size, pos, &trg);
        for(i = 0; i < (right - left + 1) * (bottom - top + 1); i++) {
                ((char *)dest)[i * 2] = buf[i].Char.AsciiChar;
                ((char *)dest)[i * 2 + 1] = FromWinAttribs(buf[i].Attributes);
                };
        return 1;
        };
EXTERNC
int movetext(int left, int top, int right, int bottom, int destleft, int desttop) {
        char *buf;
        buf = (char *)alloca((right - left + 1) * (bottom - top + 1) * 2);
        gettext(left, top, right, bottom, buf);
        puttext(destleft, desttop, destleft + right - left, desttop + bottom - top, buf);
        return 1;
        };
EXTERNC
int puttext(int left, int top, int right, int bottom, void *source) {
        int i;
        SMALL_RECT trg;
        COORD pos, size;
        CHAR_INFO *buf;
        buf = (CHAR_INFO *)alloca((right - left + 1) * (bottom - top + 1) * sizeof(CHAR_INFO));
        for(i = 0; i < (right - left + 1) * (bottom - top + 1); i++) {
                buf[i].Char.AsciiChar = ((char *)source)[i * 2];
                buf[i].Attributes = ToWinAttribs(((char *)source)[i * 2 + 1]);
                };
        pos.X = 0; pos.Y = 0;
        size.X = right - left + 1; size.Y = bottom - top + 1;
        trg.Left = left - 1; trg.Top = top - 1;
        trg.Right = right - 1; trg.Bottom = bottom - 1;
        WriteConsoleOutputA(thData.output, buf, size, pos, &trg);
        return 1;
        };
EXTERNC
void settitle(const char *title) {
        SetConsoleTitleA(title);
        };
int whichplace(char zn, char lettersarray[])
{
        for (int i = 0; i < 25; i++)
        {
                if (lettersarray[i] = zn)
                {
                        return i;
                }
        }
};
void pointscount(int length, int letterpoints[],char lettersarray[])
{
        int p = 1;
        char zn;
        int partsuma=0;
        if (beginx == endx)
        {
                for (int i = 0; i < length; i++)
                {
                        p = 1;
                        while (actualboard[beginx+i][beginy+p] != ' ' && beginy+p<SIZE)
                        {
                                zn = actualboard[beginx+i][beginy +p];
                                int number = whichplace(zn, lettersarray);
                                partsuma += letterpoints[number];
                                p++;
                        }
                        p = 1;
                        while (actualboard[beginx+i][beginy - p] != ' ' && beginy-p>0)
                        {
                                zn = actualboard[beginx+i][beginy-p];
                                int number = whichplace(zn, lettersarray);
                                partsuma += letterpoints[number];
                                p++;
                        }
                        zn = actualboard[beginx + i][beginy];
                        int x = whichplace(zn, lettersarray);
                        if (mnozniki[beginx + i][beginy] != 0)
                        {
                                int m = mnozniki[beginx + i][beginy];
                                if (m > 3)
                                {
                                        m = m / 2;
                                        partsuma += letterpoints[x];
                                        partsuma *= m;
                                        points += partsuma;
                                }
                                else
                                {
                                        partsuma += m*(letterpoints[x]);
                                        points += partsuma;
                                }
                        }
                        else
                        {
                                partsuma += letterpoints[x];
                                points += partsuma;
                        }
                        
                }
                
                partsuma = 0;
                for (int i = 0; i < length; i++)
                {
                        mnoznikliter = 1;
                        if (mnozniki[beginx+1][beginy] != 0)
                        {
                                int g = mnozniki[beginx+1][beginy];
                                if (g > 3)
                                {
                                        g = g / 2;
                                        mnoznikslow += g;
                                }

                        }
                        zn = actualboard[beginx][beginy + i];
                        int number = whichplace(zn, lettersarray);
                        partsuma += (letterpoints[number])*mnoznikliter;
                }
                partsuma *= mnoznikslow;
                p = 1;
                while (beginx - p > 0 && actualboard[beginx - p][beginy] != ' ')
                {
                        zn = actualboard[beginx - p][beginy];
                        int number = whichplace(zn, lettersarray);
                        partsuma += letterpoints[number];
                        p++;
                }
                p = 1;
                while (beginx + p < SIZE && actualboard[beginx + p][beginy])
                {
                        zn = actualboard[beginx + p][beginy];
                        int number = whichplace(zn, lettersarray);
                        partsuma += letterpoints[number];
                        p++;
                }

                points += partsuma;
                partsuma = 0;
        }
        else
        {
                partsuma = 0;
                for (int i = 0; i < length; i++)
                {
                        p = 1;
                        while (actualboard[beginx + p][beginy + i] != ' ' && beginx + p < SIZE)
                        {
                                zn = actualboard[beginx + i][beginy + p];
                                int number = whichplace(zn, lettersarray);
                                partsuma += letterpoints[number];
                                p++;
                        }
                        p = 1;
                        while (actualboard[beginx + p][beginy - i] != ' ' && beginx - p > 0)
                        {
                                zn = actualboard[beginx + i][beginy + p];
                                int number = whichplace(zn, lettersarray);
                                partsuma += letterpoints[number];
                                p++;
                        }
                        zn = actualboard[beginx + i][beginy];
                        int x = whichplace(zn, lettersarray);
                        partsuma += letterpoints[x];
                        points += partsuma;
                }
                partsuma = 0;
                for (int i = 0; i < length; i++)
                {
                        mnoznikliter = 1;
                        if (mnozniki[beginx][beginy + 1] != 0)
                        {
                                int g = mnozniki[beginx][beginy + 1];
                                if (g > 3)
                                {
                                        g = g / 2;
                                        mnoznikslow += g;
                                }

                        }
                        zn = actualboard[beginx][beginy+i];
                        int number = whichplace(zn, lettersarray);
                        partsuma +=( letterpoints[number])*mnoznikliter;
                }
                partsuma *= mnoznikslow;
                p = 1;
                while (beginy - p > 0 && actualboard[beginx][beginy-p] != ' ')
                {
                        zn = actualboard[beginx][beginy-p];
                        int number = whichplace(zn, lettersarray);
                        partsuma += letterpoints[number];
                        p++;
                }
                p = 1;
                while (beginy + p < SIZE && actualboard[beginx][beginy + p])
                {
                        zn = actualboard[beginx][beginy+p];
                        int number = whichplace(zn, lettersarray);
                        partsuma += letterpoints[number];
                        p++;
                }
                points += partsuma;
        }
};
void putpoints(int legendx, int legendy)
{
        gotoxy(legendx, legendy + 11);
        cputs("Points:");
        char hundred = '0';
        char decimal = '0';
        char number = '0';

        number += points % 10;
        int p = points - (points % 10);
        p = p / 10;
        decimal += p % 10;
        p = p - (points % 10);
        hundred += (p / 10);

                gotoxy(legendx, legendy + 12);
                putch(hundred);
                gotoxy(legendx+1, legendy + 12);
                putch(decimal);
                gotoxy(legendx+2, legendy + 12);
                putch(number);

        
};
bool possibilitycheck(int length, char word[])
{
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE - length; j++)
                {
                        for (int w = 0; w < length; w++)
                        {
                                checktable[i][j + w] = word[w];
                        }
                        if (possibilitycheckpart())
                        {
                                return true;
                        }
                        zerocheck();
                }
        }
        for (int i = 0; i < SIZE-length; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        for (int w = 0; w < length; w++)
                        {
                                checktable[j][i + w] = word[w];
                        }
                        if (possibilitycheckpart())
                        {
                                return true;
                        }
                        zerocheck();
                }
        }
        return false;
};
bool possibilitycheckpart()
{
        bool bul = true;
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        if (actualboard[i][j] != checktable[i][j] && checktable[i][j] != ' '&&actualboard[i][j] != ' ')
                        {
                                bul = false;
                        }
                }
        }
        if (bul)
        {
                for (int i = 0; i < SIZE; i++)
                {
                        for (int j = 0; j < SIZE; j++)
                        {
                                if (i != 0 && checktable[i][j] != ' ' && actualboard[i - 1][j] != ' ')
                                {
                                        return true;
                                }
                                if (checktable[i][j] == actualboard[i][j] && checktable[i][j] != ' '&& actualboard[i][j] != ' ')
                                {
                                        return true;
                                }
                                if (j != 0 && checktable[i][j] != ' ' && actualboard[i][j - 1] != ' ')
                                {
                                        return true;
                                }
                                if (j != SIZE - 1 && checktable[i][j] != ' ' && actualboard[i][j + 1] != ' ')
                                {
                                        return true;
                                }
                                if (i != SIZE - 1 && checktable[i][j] != ' ' && actualboard[i + 1][j] != ' ')
                                {
                                        return true;
                                }
                        }
                }
        }       
        return false;
}
bool canputword2()
{
        //char actualboard[SIZE][SIZE];
        //char wordonboard[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        if (i != 0 && wordonboard[i][j]!=' ' && actualboard[i-1][j]!=' ')
                        {
                                return true;
                        }
                        if (wordonboard[i][j] == actualboard[i][j]&&wordonboard[i][j]!=' '&&actualboard[i][j]!=' ')
                        {
                                return true;
                        }
                        if (j != 0 && wordonboard[i][j] != ' ' && actualboard[i][j - 1] != ' ')
                        {
                                return true;
                        }
                        if (j != SIZE - 1 && wordonboard[i][j] != ' ' && actualboard[i][j + 1] != ' ')
                        {
                                return true;
                        }
                        if (i != SIZE - 1 && wordonboard[i][j] != ' ' && actualboard[i + 1][j] != ' ')
                        {
                                return true;
                        }
                }
        }
        return false;
};
bool wordpositionup()
{
        for (int i = 0; i < SIZE; i++)
        {
                if (wordonboard[i][0] != ' ')
                {
                        return false;
                }
        }
        return true;
};
bool wordpositiondown()
{
        for (int i = 0; i < SIZE; i++)
        {
                if (wordonboard[i][SIZE-1] != ' ')
                {
                        return false;
                }
        }
        return true;
};
bool wordpositionleft()
{
        for (int i = 0; i < SIZE; i++)
        {
                if (wordonboard[0][i] != ' ')
                {
                        return false;
                }
        }
        return true;
};
bool wordpositionright()
{
        for (int i = 0; i < SIZE; i++)
        {
                if (wordonboard[SIZE-1][i] != ' ')
                {
                        return false;
                }
        }
        return true;
};
void changeorientation(int *orientation, int length)
{
        
        int check = *orientation;
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        if (check == 0)
                        {
                                pionowa[SIZE - i - 1][j] = wordonboard[j][i];
                        }
                        else
                        {
                                pionowa[j][SIZE - i - 1] = wordonboard[i][j];
                        }
                }
        }

                for (int i = 0; i < SIZE; i++)
                {
                        for (int j = 0; j < SIZE; j++)
                        {

                                wordonboard[j][i] = pionowa[j][i];
                        }
                }

        if (check == 0)
        {
                *orientation = 1;
        }
        else
        {
                *orientation = 0;
        }
};
void gettextinfo(struct text_info *info) {
        info->curx = wherex();
        info->cury = wherey();
        info->attribute = thData.attrib;
        info->normattr = 0x07;
        info->screenwidth = thData.width;
        info->screenheight = thData.height;
        };

void firstwordfunction(char word[], int length,int beginningx,int beginningy,char player1[], int beginningletters,int legendx,int legendy)
{
                int x = beginningx;
                int y = beginningy;
                int p = (SIZE + 1) / 2;
                for (int i = 0; i < length; i++)
                {
                        char zn = word[i];
                        actualboard[p - (length / 2) + i - 1][p - 1] = zn;
                }
                for (int i = 0; i < length; i++)
                {
                        char zn = word[i];
                        for (int j = 0; j < beginningletters; j++)
                        {
                                if (player1[j] == zn)
                                {
                                        player1[j] = ' ';
                                        break;
                                }
                        }
                }
};
void randomaftermove(char player1[], int beginningletters, int* numberofletters, char lettersarray[], int letterscount[])
{
        int z;
        int suma;
        int p = *numberofletters;
        srand(time(NULL));
        for (int i = 0; i < beginningletters; i++)
        {
                if (player1[i] == ' ')
                {
                        z = 0;
                        suma = 0;
                        int ran = rand() % p;
                        while (suma <= ran)
                        {
                                suma += letterscount[z];
                                z++;
                        }
                        p--;
                        z--;
                        letterscount[z]--;
                        player1[i] = lettersarray[z];
                        *numberofletters--;
                }
        }
};
void putword(int beginningx, int beginningy, char word[], int length,int x,int y, int letterpoints[], char lettersarray[], int beginningletters,char player1[])
{
        //orientation 1-pion 0-poziom
//      int firstletterpositionx;
        //int firstletterpositiony;
        int orientation = 0;
        char zn;
        int px = x - beginningx+1;
        int py = y - beginningy+1;
        px = px / 2;
        if (x + length < beginningx +SIZE)
        {        
                for (int i = 0 ;i < length; i++)
                {        
                        wordonboard[px + i][py] = word[i];
                }
        //      firstletterpositionx = px;
        //      firstletterpositiony = py;
        }
        else
        {
                if (x - length  > beginningx)
                {
                        for (int i = 0; i < length; i++)
                        {
                                wordonboard[px - length +1 + i][py] = word[i];
                        }
                //      firstletterpositionx = px-length+1;
                //      firstletterpositiony = py;
                }
                else
                {
                        
                }
        }
        int p = 1;
        bool czyprawda = true;
        while (p)
        {
                textbackground(0);
                clrscr();
                color(beginningx, beginningy);
                board(beginningx, beginningy);
                writeactualboard(beginningx+1, beginningy+1);
                char zn = getch();
                switch (zn)
                {
                        case 0x0d:
                                if (canputword()&&canputword2())
                                {
                                        for (int i = 0; i < SIZE; i++)
                                        {
                                                for (int j = 0; j < SIZE; j++)
                                                {
                                                        if (wordonboard[i][j] != ' ')
                                                        {
                                                                actualboard[i][j]= wordonboard[i][j];
                                                                wordonboard[i][j] = ' ';
                                                                endx = i;
                                                                endy = j;
                                                                if (czyprawda == true)
                                                                {
                                                                        beginx = i;
                                                                        beginy = j;
                                                                        czyprawda = false;
                                                                }
                                                        }
                                                }
                                        }
                                        for (int i = 0; i < length; i++)
                                        {
                                                char zn = word[i];
                                                for (int j = 0; j < beginningletters; j++)
                                                {
                                                        if (player1[j] == zn)
                                                        {
                                                                player1[j] = ' ';
                                                                break;
                                                        }
                                                }
                                        }
                                        //tutaj 
                                        pointscount(length, letterpoints, lettersarray);
                                        p = 0;
                                }
                                else
                                {
                                        gotoxy(beginningx, beginningy + 2 + SIZE);
                                        cputs("Nie mozna umiejscowic wyrazu w tym miejscu...");
                                }
                                break;
                                case 0x48:
                                        //w gore
                                        if (wordpositionup())
                                        {
                                                for (int i = 1; i < SIZE; i++)
                                                {
                                                        for (int j = 0; j < SIZE; j++)
                                                        {
                                                                wordonboard[j][i-1] = wordonboard[j][i];
                                                                wordonboard[j][i] = ' ';
                                                        }
                                                }
                                        }
                                //      firstletterpositiony--;
                                break;
                                case 0x50:
                                        //w dol
                                        if (wordpositiondown())
                                        {
                                                for (int i = SIZE - 1; i>=0; i--)
                                                {
                                                        for (int j = 0; j < SIZE; j++)
                                                        {
                                                                wordonboard[j][i+1] = wordonboard[j][i];
                                                                wordonboard[j][i] = ' ';
                                                        }
                                                }
                                        }
                                //      firstletterpositiony++;
                                        break;
                                case 0x4b:
                                        //w lewo
                                        if (wordpositionleft())
                                        {
                                                for (int i = 0; i < SIZE; i++)
                                                {
                                                        for (int j = 1; j < SIZE; j++)
                                                        {
                                                                wordonboard[j-1][i] = wordonboard[j][i];
                                                                wordonboard[j][i] = ' ';
                                                        }
                                                }
                                        }
                                //      firstletterpositionx--;
                                        break;
                                case 0x4d:
                                        //w prawo
                                        if (wordpositionright())
                                        {
                                                for (int i = 0; i < SIZE; i++)
                                                {
                                                        for (int j = SIZE-2; j >=0; j--)
                                                        {
                                                                wordonboard[j+1][i] = wordonboard[j][i];
                                                                wordonboard[j][i] = ' ';
                                                        }
                                                }
                                        }
                                //      firstletterpositionx++;
                                        break;
                                case 'o':
                                        changeorientation(&orientation,length);
                                        break;
                }
        }
};
bool canputword()
{
//char actualboard[SIZE][SIZE];
//char wordonboard[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        if (actualboard[i][j] != wordonboard[i][j]&&wordonboard[i][j]!=' '&&actualboard[i][j]!=' ')
                        {
                                return false;
                        }
                }
        }
        return true;
};
void board(int x, int y)
{        
        if (SIZE > 10)
        {
                if (SIZE % 2 == 1)
                {
                        if (SIZE < 26)
                        {
                                color(x, y);
                                int px = x;
                                int py = y;
                                x++;
                                for (int i = 1; i < SIZE * 2; i++)
                                {
                                        gotoxy(x, y);
                                        putch('-');
                                        y += SIZE;
                                        y++;
                                        gotoxy(x, y);
                                        putch('-');
                                        y -= SIZE;
                                        y--;
                                        x++;
                                }
                                x -= SIZE * 2;

                                y++;
                                for (int i = 0; i < SIZE; i++)
                                {
                                        gotoxy(x, y);
                                        putch('|');
                                        x += SIZE * 2;
                                        gotoxy(x, y);
                                        putch('|');
                                        x -= SIZE * 2;
                                        y++;
                                }
                                y = py;
                                x = px;
                                x++;
                                y--;
                                char letter = 'a';
                                for (int i = 0; i < SIZE; i++)
                                {
                                        gotoxy(x, y);
                                        putch(letter);
                                        y += (SIZE + 2);
                                        y++;
                                        gotoxy(x, y);
                                        putch(letter);
                                        letter++;
                                        y -= (SIZE + 2);
                                        y--;
                                        x += 2;
                                }
                                x = px;
                                y = py;
                                x--;
                                y++;
                                char number = '0', decimal = '0';
                                for (int i = 0; i < SIZE; i++)
                                {
                                        if (decimal == '0')
                                        {
                                                gotoxy(x, y);
                                                putch(number);
                                                x += ((2 * SIZE) + 2);
                                                gotoxy(x, y);
                                                putch(number);
                                                x -= ((2 * SIZE) + 2);
                                                y++;
                                        }
                                        else
                                        {
                                                gotoxy(x, y);
                                                putch(number);
                                                x--;
                                                gotoxy(x, y);
                                                putch(decimal);
                                                x += ((2 * SIZE) + 3);
                                                gotoxy(x, y);
                                                putch(decimal);
                                                x++;
                                                gotoxy(x, y);
                                                putch(number);
                                                x -= ((2 * SIZE) + 3);
                                                y++;
                                        }
                                        if (number == '9')
                                        {
                                                number = '0';
                                                decimal++;
                                        }
                                        else
                                        {
                                                number++;
                                        }
                                }
                        }
                        else
                        {
                                gotoxy(x, y);
                                cputs("Board size is too big...");
                        }
                }
                else
                {
                        gotoxy(x, y);
                        cputs("Board size cannot be even number...");
                }
        }
        else
                {
                gotoxy(x, y);
                cputs("Board size is too small...");
                }
};
void position(int beginningx, int beginningy, int legendx, int legendy, int x, int y)
{
        gotoxy(legendx, legendy + 9);
        cputs("Actual position of cursor");
        int positiony = 1;
        char letter = 'A';
        char number = '0';
        char decimal = '0';
        beginningx++;
        beginningy++;
        int help = x - beginningx;
        letter += (help /2);
        positiony+= y - beginningy;
        //conversion to char
        number += (positiony % 10);
        positiony -= (positiony % 10);
        decimal += (positiony / 10);
        gotoxy(legendx, legendy + 10);
        putch(letter); 
        if (decimal == '0')
        {
                gotoxy(legendx+1, legendy + 10);
                putch(number);
        }
        else
        {
                gotoxy(legendx+1, legendy + 10);
                putch(decimal);
                gotoxy(legendx+2, legendy + 10);
                putch(number);
        }
};
void putchexchange(int array[], int beginningletters, int legendx, int legendy, char player1[])
{

        int j = 0;
        for (int i = 0; i < beginningletters; i++)
        {
                if (array[i] == 1)
                {
                        gotoxy(legendx + (2*i), legendy + 18);
                        char zn = player1[i];
                        putch(zn);
                        j++;
                }
                else
                {
                        gotoxy(legendx + (2 * i), legendy + 18);
                        putch(' ');
                }
        }
}
void exchangetable( char player1[], int exchange[],int beginningletters, char lettersarray[], int letterscount[],int q, int legendx, int legendy)
{
        int p = 1;
        while (p)
        {
                gotoxy(legendx, legendy + 17);
                cputs("Letters for exchange:");
                char zn = getch();
                switch (zn)
                {
                case '1':
                        if (exchange[0] == 0)
                        {
                                exchange[0] = 1;
                        }
                        else
                        {
                                exchange[0] = 0;
                        }
                        putchexchange(exchange, beginningletters, legendx, legendy, player1);
                        break;
                case '2':
                        if (exchange[1] == 0)
                        {
                                exchange[1] = 1;
                        }
                        else
                        {
                                exchange[1] = 0;
                        }
                        putchexchange(exchange, beginningletters, legendx, legendy, player1);
                        break;
                case '3':
                        if (exchange[2] == 0)
                        {
                                exchange[2] = 1;
                        }
                        else
                        {
                                exchange[2] = 0;
                        }
                        putchexchange(exchange, beginningletters, legendx, legendy, player1);
                        break;
                case '4':
                        if (exchange[3] == 0)
                        {
                                exchange[3] = 1;
                        }
                        else
                        {
                                exchange[3] = 0;
                        }
                        putchexchange(exchange, beginningletters, legendx, legendy, player1);
                        break;
                case '5':
                        if (exchange[4] == 0)
                        {
                                exchange[4] = 1;
                        }
                        else
                        {
                                exchange[4] = 0;
                        }
                        putchexchange(exchange, beginningletters, legendx, legendy, player1);
                        break;
                case '6':
                        if (exchange[5] == 0)
                        {
                                exchange[5] = 1;
                        }
                        else
                        {
                                exchange[5] = 0;
                        }
                        putchexchange(exchange, beginningletters, legendx, legendy, player1);
                        break;
                case '7':
                        if (exchange[6] == 0)
                        {
                                exchange[6] = 1;
                        }
                        else
                        {
                                exchange[6] = 0;
                        }
                        putchexchange(exchange, beginningletters, legendx, legendy, player1);
                        break;
                case 'w':
                        random(exchange, player1, lettersarray, letterscount,beginningletters,q);
                        p = 0;
                        for (int i = 0; i < beginningletters; i++)
                        {
                                exchange[i] = 0;
                        }
                        break;
                case 0x0d:
                        random(exchange, player1, lettersarray, letterscount, beginningletters, q);
                        p = 0;
                        for (int i = 0; i < beginningletters; i++)
                        {
                                exchange[i] = 0;
                        }
                        break;
                }
        }
        
}
void random(int exchange[], char player1[], char lettersarray[], int letterscount[],int beginningletters, int p)
{
        int suma = 0;
        int  z= 0;
        srand(time(NULL));
        for (int i = 0; i < beginningletters; i++)
        {
                if (exchange[i] == 1)
                {
                        char zn = player1[i];
                        for (int j = 0; j < numberofchars; j++)
                        {
                                if (zn == lettersarray[j])
                                {
                                        letterscount[j]++;
                                }
                        }
                        z = 0;
                        suma = 0;
                        int ran = rand() % p;
                        while (suma <= ran)
                        {
                                suma += letterscount[z];
                                z++;
                        }
                        p--;
                        z--;
                        letterscount[z]--;
                        player1[i] = lettersarray[z];
                }
        }
}
void unknown(char word[], int elnumber,int legendx, int legendy)
{
        for (int i = 0; i < elnumber; i++)
        {
                if (word[i] == '?')
                {
                        gotoxy(legendx, legendy + SIZE+4);
                        textbackground(0);
                        cputs("What letter would you like to choose despite '?': ");
                        char zn = getch();
                        while (zn<'a' || zn>'z')
                        {
                                gotoxy(legendx, legendy + SIZE + 4);
                                cputs("You must choose letter not any other character: ");
                                 zn = getch();
                        }
                        word[i] = zn;
                }
        }
};
bool haveallletters(int length, char word[], char player1[], int beginningletters)
{
        bool bul = false;
        for (int i = 0; i < length; i++)
        {
                bul = false;
                char zn = word[i];
                for (int j = 0; j < beginningletters; j++)
                {
                        if (player1[j] == zn||zn==' ')
                        {
                                bul = true;
                        }
                }
                if (bul == false)
                {
                        return false;
                }
        }
        return true;
};
void new_word(char pomocnicza[],char player1[], int beginningletters, int legendx, int legendy, int beginningy, int beginningx, int* firstword, int x, int y, int letterpoint[],char letterarray[])
{
        for (int j = 0; j < beginningletters; j++)
        {
                pomocnicza[j] = player1[j];
        }
        bool bul = true;
        int i = 0;
        int p = 1;
        char zn = '0';
        int py = beginningy + SIZE;
        gotoxy(legendx, py+3);
        cputs("Podaj wyraz do wpisania:");
        char lastletter;
        while (p!=0)
        {
                zn=getch();
                if (i < SIZE)
                {
                        gotoxy(legendx, py + 5);
                        delline();                      
                        switch (zn)
                        {
                        case 0x0d:
                                if (haveallletters(i, word, player1, beginningletters))
                                {
                                        unknown(word, i, legendx, legendy);
                                        if (*firstword == 1)
                                        {
                                                *firstword = 0;
                                                firstwordfunction(word, i, beginningx, beginningy, player1, beginningletters, legendx, legendy);
                                                pointscount(i, letterpoint, letterarray);
                                        }
                                        else
                                        {
                                                if (possibilitycheck(i, word))
                                                {
                                                        putword(beginningx, beginningy, word, i, x, y, letterpoint, letterarray,beginningletters,player1);
                                                }
                                        }
                                }
                                p = 0;
                                break;
                        case 8:
                                if (i != 0)
                                {        
                                        if (bul == true)
                                        {
                                                i--;
                                                word[i - 1] = '/0';
                                                gotoxy(legendx + i, py + 4);
                                                textbackground(0);
                                                char p = ' ';
                                                putch(p);
                                                i--;
                                                for (int j = 0; i < beginningletters; j++)
                                                {
                                                        if (pomocnicza[j] = ' ')
                                                        {
                                                                pomocnicza[j] = lastletter;
                                                                break;
                                                        }
                                                }
                                                bul = false;
                                        }
                                        else
                                        {
                                                gotoxy(legendx, py + 5);
                                                textbackground(0);
                                                textcolor(4);
                                                cputs("You can delete only one letter!");
                                                textcolor(15);
                                                i--;
                                        }
                                }
                                break;
                        case 27:
                                p = 0;
                                break;
                        default:
                                bul = true;
                                word[i] = zn;
                                gotoxy(legendx + i, py + 4);
                                lastletter = zn;
                                for (int j = 0; j < beginningletters; j++)
                                {
                                        if (pomocnicza[j] == zn)
                                        {
                                                pomocnicza[j] = ' ';
                                                textbackground(2);
                                                break;
                                        }
                                        else
                                        {
                                                if (j + 1 == beginningletters)
                                                {
                                                        textbackground(4);
                                                }
                                        }
                                }
                                putch(zn);
                                break;
                        }
                        i++;
                        
                }
                else
                {
                        gotoxy(legendx, py + 5);
                        textbackground(0);
                        textcolor(4);
                        cputs("Too many letters!");
                        textcolor(15);
                        zn = getch();
                        switch (zn)
                        {
                        case 0x0d:
                                unknown(word, i, legendx, legendy);
                                if (*firstword == 1)
                                {
                                        *firstword = 0;
                                        firstwordfunction(word, i, beginningx, beginningy, player1, beginningletters, legendx, legendy);
                                }
                                else
                                {
                                        putword(beginningx, beginningy, word, i, x, y, letterpoint, letterarray,beginningletters,player1);
                                }
                                p = 0;
                                break;
                        case 8:
                                if (i != 0)
                                {
                                        if (bul)
                                        {
                                                i--;
                                                word[i - 1] = '/0';
                                                gotoxy(legendx + i, py + 4);
                                                textbackground(0);
                                                char p = ' ';
                                                putch(p);
                                                for (int j = 0; i < beginningletters; j++)
                                                {
                                                        if (pomocnicza[j] = ' ')
                                                        {
                                                                pomocnicza[j] = lastletter;
                                                                break;
                                                        }
                                                }
                                                bul = false;
                                        }
                                        else
                                        {
                                                gotoxy(legendx, py + 5);
                                                textbackground(0);
                                                textcolor(4);
                                                cputs("You can delete only one letter!");
                                                textcolor(15);
                                                i--;
                                        }
                                }
                                break;
                        case 27:
                                p = 0;
                                break;
                        }
                        textbackground(0);
                }
        }
};
void new_game(int legendx, int legendy,char player1[], int lettercount[],int beginningletters,int* numberofletters,char lettersarray[],int p)
{
        beginning();
        points = 0;
        zerowordonboard();
        int suma = 0;
        int j = 0;
        int z;
        int random;
        *numberofletters = 100;
        clrscr();
        srand(time(NULL));
        for (int i = 0; i < beginningletters; i++)
        {
                z = 0;
                suma = 0;
                int ran = rand() % p;
                while (suma <= ran)
                {
                        suma += lettercount[z];
                        z++;
                }
                p--;
                z--;
                lettercount[z]--;
                player1[i] = lettersarray[z];
                *numberofletters -= 1;
        }
        
};
bool isempty(int x, int y)
{
        if (actualboard[x][y] != ' ')
        {
                return false;
        }
        else
        {
                return true;
        }

}
void colorcross(int i, int px)
{
        if (i == 0)
        {
                textbackground(4);
                putch(' ');
        }
        else
        {
                if (i == (px - 1))
                {
                        textbackground(14);
                        putch(' ');
                }
                else
                {
                        if (i == px)
                        {
                                textbackground(9);
                                putch(' ');
                        }
                        else
                        {
                                textbackground(5);
                                putch(' ');
                        }
                }               
        }
}
void colorputch(char zn, int color)
{
        textbackground(color);
        putch(zn);
}
void colorsmall(int i)
{
        if (i == 0)
        {
                textbackground(14);
                putch(' ');
        }
        else
        {
                textbackground(9);
                putch(' ');
        }       
}
void color(int x, int y)
{
        int i = 0;
        int j = 0;      
        int px, py;
        px = (SIZE + 1) / 2;
        py = (SIZE + 1) / 2;
        
        gotoxy(x + (2*px)-1, y + py);
        colorputch('*', 5);
        
        gotoxy(x + (2 * px) - 9, y + py);
        mnozniki[px - 4][py] = 2;
        colorputch(' ', 9);

        gotoxy(x + (2 * px) + 7, y + py);
        mnozniki[px +3][py] = 2;
        colorputch(' ', 9);

        gotoxy(x + (2 * px) - 1, y + py-4);
        mnozniki[px - 1][py-4] = 2;
        colorputch(' ', 9);

        gotoxy(x + (2 * px) - 1, y + py + 4);
        mnozniki[px - 1][py+4] = 2;
        colorputch(' ', 9);

        gotoxy(x + (2 * px) - 1, ++y);
        mnozniki[px - 1][0] = 6;
        colorputch(' ', 4);

        gotoxy(x + (2 * px) - 1, y + SIZE -1);
        mnozniki[px - 1][SIZE-1] = 6;
        colorputch(' ', 4);

        gotoxy(x + 7, y);
        mnozniki[4][0] = 2;
        colorputch(' ', 9);

        gotoxy(x + (SIZE * 2) - 7, y);
        mnozniki[SIZE-4][y] = 2;
        colorputch(' ', 9);

        gotoxy(x + 7, y+SIZE-1);
        mnozniki[4][SIZE-1] = 2;
        colorputch(' ', 9);

        gotoxy(x +(SIZE*2)-7, y+SIZE-1);
        mnozniki[SIZE-4][SIZE-1] = 2;
        colorputch(' ', 9);

        gotoxy(x+1, y + 3);
        mnozniki[px -2][py-1] = 2;
        colorputch(' ', 9);

        gotoxy(x + 1, y + SIZE-4);
        mnozniki[0][SIZE-4] = 2;
        colorputch(' ', 9);
        px--;

        gotoxy(x + 1+((SIZE-1)*2), y + 3);
        mnozniki[SIZE-2][3] = 2;
        colorputch(' ', 9);

        gotoxy(x +1 +((SIZE-1) * 2), y + SIZE -4);      
        mnozniki[SIZE-2][SIZE-4] = 2;
        colorputch (' ', 9);

        gotoxy(x+1, y -1 + py);
        mnozniki[0][py-1] = 6;
        colorputch(' ', 4);
        
        gotoxy(x + (SIZE*2)-1, y - 1 + py);
        mnozniki[SIZE - 1][py-1] = 6;
        colorputch(' ', 4);
        px--;   
        int w = 0;
        for (int i = 0; i <= px; i++)
        {
                int e;
                if (i == 0)
                {
                        e = 6;
                }
                else
                {
                        if (i == px - 1)
                        {
                                e = 2;
                        }
                        else
                        {
                                if (i == px - 2)
                                {
                                        e = 3;
                                }
                                else
                                {
                                        e = 4;
                                }
                        }
                }
                //left up
                gotoxy(x + (2 * i)+1, y + i);
                mnozniki[i][i]=e;
                colorcross(w, px);
                //left down
                gotoxy(x + 1 + (2 * i), y + SIZE-1 - i);
                mnozniki[i][SIZE - 1 - i]=e;
                colorcross(w, px);

                //right up
                gotoxy(x -1 + 2*SIZE - (i * 2), y + i);
                mnozniki[SIZE - 1 - i][i] = e;
                colorcross(w, px);

                //right down
                gotoxy(x - 1 + 2 * SIZE - (i * 2), y -1 +SIZE - i);
                mnozniki[SIZE - 1 - i][SIZE - 1 - i] = e;
                colorcross(w, px);

                w++;
        }
         i = 0;
        int p = ++x;
        px = (SIZE + 1) / 2;
        while (y + 5 + i != y - 1 + py)
        {
                int d;
                if (i == 0)
                {
                        d = 3;
                }
                else
                {
                        d = 2;
                }
                gotoxy(p+2 + (2*i),y+5+i);
                mnozniki[2 + i][5 + i]=d;
                colorsmall(i);

                gotoxy(x +2 + (2 * i), y + SIZE - 6 - i);
                mnozniki[2 + i][SIZE - 6 - i] = d;
                colorsmall(i);

                gotoxy(x + 10 + (2 * i), y + SIZE - 2 - i);
                mnozniki[5+i][SIZE-2-i] = d;
                colorsmall(i);

                gotoxy(x - 12 + 2 * SIZE - (i * 2), y - 2 + SIZE - i);
                mnozniki[SIZE-6-i][SIZE - 2 - i] = d;
                colorsmall(i);

                gotoxy(x - 4 + 2 * SIZE - (i * 2), y - 6 + SIZE - i);
                mnozniki[SIZE-2-i][SIZE - 6 - i] = d;
                colorsmall(i);

                gotoxy(x - 4 + 2 * SIZE - (i * 2), y+5 + i);
                mnozniki[SIZE-2-i][5+i] = d;
                colorsmall(i);

                gotoxy(x - 12 + 2 * SIZE - (i * 2), y +1+ i);
                mnozniki[SIZE-6-i][i+1] = d;
                colorsmall(i);

                gotoxy(x + (2 * i) + 10, y +1+i);
                mnozniki[5 + i][1+i] = d;
                colorsmall(i);
                i++;
        }
        textbackground(0);
        writeactualboard(x,y);
};
void writeactualboard(int x, int y)
{
        textbackground(0);      
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        gotoxy(x + (2*j), y + i);
                        if (actualboard[j][i] != ' ')
                        {
                                char zn = actualboard[j][i];
                                putch(zn);
                        }
                }
        }
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                        gotoxy(x + (2 * j), y + i);
                        if (wordonboard[j][i] != ' ')
                        {
                                char zn = wordonboard[j][i];
                                if (actualboard[j][i] == ' ')
                                {
                                        textbackground(0);
                                        putch(zn);
                                }
                                else
                                {
                                        if (actualboard[j][i] == zn)
                                        {
                                                textbackground(2);
                                                putch(zn);
                                        }
                                        else
                                        {
                                                textbackground(4);
                                                putch(zn);
                                        }
                                }
                                
                        }
                }
        }
        textbackground(0);
};
void textmode(int mode) {
        if(mode == C80) {
                thData.width = 80;
                thData.height = 25;
                ResizeConsole(thData.output, 80, 25, 25);
        } else if(mode == C4350) {
                thData.width = 80;
                thData.height = 50;
                ResizeConsole(thData.output, 80, 50, 50);
        } else if(mode == LASTMODE) {
                textmode(thData.lastmode);
                };
        };
bool down(int BEGINNINGY, int y)
{
        if (y != BEGINNINGY + 1)
        {
                return true;
        }
        return false;
}
bool left(int BEGINNINGX, int x)
{
        if (x != BEGINNINGX + 1)
        {
                return true;
        }
        return false;
}
bool up(int BEGINNINGY, int y)
{
        if (y != BEGINNINGY + SIZE)
        {
                return true;
        }
        return false;
}
bool right(int BEGINNINGX, int x)
{
        if (x != BEGINNINGX + (SIZE * 2) - 1)
        {
                return true;
        }
        return false;
}
void randaftermove(char player1[], int beginningletters, int letterscount[], char lettersarray[], int* numberofletters )
{
        int suma = 0;
        int z = 0;
        srand(time(NULL));
        int p = *numberofletters;
        int ilosc = 0;
        for (int i = 0; i< beginningletters; i++)
        {
                if (player1[i] == ' ')
                {
                        z = 0;
                        suma = 0;
                        int ran = rand() % p;
                        while (suma <= ran)
                        {
                                suma += letterscount[z];
                                z++;
                        }
                        p--;
                        z--;
                        letterscount[z]--;
                        player1[i] = lettersarray[z];
                        *numberofletters--;
                        ilosc++;
                }
        }
        if (ilosc == beginningletters)
        {
                points += 50;
        }
};

static void Conio2_Exit(void) {
        ExitConio2(&thData);
        };

int Conio2_Init(void) {
        InitConio2(&thData);
        atexit(Conio2_Exit);
        return 0;
        };

#ifdef __cplusplus
static int conio2_init = Conio2_Init();
#endif