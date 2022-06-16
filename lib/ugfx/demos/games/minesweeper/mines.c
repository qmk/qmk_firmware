#include <stdlib.h>
#include "gfx.h"
#include "mines.h"

typedef struct {            // Node properties
      gU8 num;          // Node number, how many mines around
      gBool open;          // Node shown or hidden
      gBool check;         // Node needs to be checked or not, used for opening up empty nodes
      gBool flag;          // Node is marked with flag by player
      gU16 fieldNum;    // Node number, used to randomize gamestart "animation"
} nodeProps;

static GEventMouse ev;
static nodeProps minesField[MINES_FIELD_WIDTH][MINES_FIELD_HEIGHT];   // Mines field array
static gBool minesGameOver = gFalse;
static gBool minesGameWinner = gFalse;
static gI16 minesEmptyNodes;                        // Empty node counter
static gI16 minesFlags;                             // Flag counter
static gI16 minesTime;                              // Time counter
static GTimer minesTimeCounterTimer;
static const char* minesGraph[] = {"1.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp","7.bmp","8.bmp", "closed.bmp", "empty.bmp", "explode.bmp", "flag.bmp", "mine.bmp", "wrong.bmp"}; // 14 elements (0-13)
static gImage minesImage;
static gU8 minesStatusIconWidth = 0;
static gU8 minesStatusIconHeight = 0;
static gBool minesFirstGame = gTrue;                  // Just don't clear field for the first time, as we have black screen already... :/
static gBool minesSplashTxtVisible = gFalse;
#if MINES_SHOW_SPLASH
    static GTimer minesSplashBlink;
#endif

static int uitoa(unsigned int value, char* buf, int max)
{
    int n = 0;
    int i = 0;
    int tmp = 0;

    if (!buf)
        return -3;
    if (2 > max)
        return -4;

    i=1;
    tmp = value;
    if (0 > tmp) {
        tmp *= -1;
        i++;
    }

    for (;;) {
        tmp /= 10;
        if (0 >= tmp)
            break;
        i++;
    }
    if (i >= max) {
        buf[0] = '?';
        buf[1] = 0x0;
        return 2;
    }

    n = i;
    tmp = value;
    if (0 > tmp) {
        tmp *= -1;
    }

    buf[i--] = 0x0;
    for (;;) {
        buf[i--] = (tmp % 10) + '0';
        tmp /= 10;
        if (0 >= tmp)
            break;
    }

    if (-1 != i) {
        buf[i--] = '-';
    }

    return n;
}

static void initRng(void)
{
    srand(gfxSystemTicks());
}

static gU32 randomInt(gU32 max)
{
    return rand() % max;
}

static void printStats(void)
{
    char pps_str[12];

    gFont font = gdispOpenFont("fixed_5x8");
    uitoa(MINES_MINE_COUNT, pps_str, sizeof(pps_str));
    gdispFillString(minesStatusIconWidth+8, gdispGetHeight()-11, "    ", font, GFX_BLACK, GFX_BLACK);
    gdispDrawString(minesStatusIconWidth+8, gdispGetHeight()-11, pps_str, font, GFX_WHITE);
    uitoa(minesFlags, pps_str, sizeof(pps_str));
    gdispFillString(8+(minesStatusIconWidth*2)+gdispGetStringWidth("99999", font), gdispGetHeight()-11, "    ", font, GFX_BLACK, GFX_BLACK);
    gdispDrawString(8+(minesStatusIconWidth*2)+gdispGetStringWidth("99999", font), gdispGetHeight()-11, pps_str, font, GFX_WHITE);
    gdispCloseFont(font);
}

static void minesUpdateTime(void)
{
    char pps_str[12];

    if (minesTime > 9999)
        minesTime = 9999;

    gFont font = gdispOpenFont("digital_7__mono_20");
    uitoa(minesTime, pps_str, sizeof(pps_str));
    gdispFillArea((MINES_FIELD_WIDTH*MINES_CELL_WIDTH)-gdispGetStringWidth("9999", font), gdispGetHeight()-15, gdispGetWidth(), 15, GFX_BLACK);
    gdispDrawString((MINES_FIELD_WIDTH*MINES_CELL_WIDTH)-gdispGetStringWidth(pps_str, font), gdispGetHeight()-15, pps_str, font, GFX_LIME);
    gdispCloseFont(font);
}

static void minesTimeCounter(void* arg)
{
    (void)arg;

    minesTime++;
    minesUpdateTime();
}

static gBool inRange(gI16 x, gI16 y)
{
    if ((x >= 0) && (x < MINES_FIELD_WIDTH) && (y >= 0) && (y < MINES_FIELD_HEIGHT))
        return gTrue;
    else
        return gFalse;
}

static void showOne(gI16 x, gI16 y)
{
    minesField[x][y].open = gTrue;
    if (minesField[x][y].flag) {
        minesField[x][y].flag = gFalse;
        minesFlags--;
    }

    gdispFillArea((x*MINES_CELL_WIDTH)+1, (y*MINES_CELL_HEIGHT)+1, MINES_CELL_WIDTH-1, MINES_CELL_HEIGHT-1, GFX_BLACK);

    if ((minesField[x][y].num > 0) && (minesField[x][y].num < 9)) {
        gdispImageOpenFile(&minesImage, minesGraph[minesField[x][y].num-1]);
        gdispImageDraw(&minesImage, (x*MINES_CELL_HEIGHT)+1, (y*MINES_CELL_WIDTH)+1, MINES_CELL_WIDTH, MINES_CELL_HEIGHT, 0, 0);
        gdispImageClose(&minesImage);
        minesEmptyNodes--;
    } else if (minesField[x][y].num == 9) {
        minesGameOver = gTrue;
        minesGameWinner = gFalse;
        gdispImageOpenFile(&minesImage, minesGraph[10]);
        gdispImageDraw(&minesImage, (x*MINES_CELL_HEIGHT)+1, (y*MINES_CELL_WIDTH)+1, MINES_CELL_WIDTH, MINES_CELL_HEIGHT, 0, 0);
        gdispImageClose(&minesImage);
        // Dirty HACK to not draw mine icon on GameOver event :D
        minesField[x][y].num = 0;
    } else if (minesField[x][y].num == 0) {
        gdispImageOpenFile(&minesImage, minesGraph[9]);
        gdispImageDraw(&minesImage, (x*MINES_CELL_HEIGHT)+1, (y*MINES_CELL_WIDTH)+1, MINES_CELL_WIDTH, MINES_CELL_HEIGHT, 0, 0);
        gdispImageClose(&minesImage);
        minesField[x][y].check = gTrue;
        minesEmptyNodes--;
    }
}

static void openEmptyNodes(void)
{
    gI16 x, y, i, j;
    gBool needToCheck = gTrue;

    while (needToCheck) {
        needToCheck = gFalse;
        for (x = 0; x < MINES_FIELD_WIDTH; x++) {
            for (y = 0; y < MINES_FIELD_HEIGHT; y++) {
                if (minesField[x][y].check) {
                    for (i = -1; i <= 1; i++) {
                        for (j = -1; j <= 1; j++) {
                            if ((i != 0) || (j != 0)) {                 // We don't need to check middle node as it is the one we are checking right now! :D
                                if (inRange(x+i,y+j)) {
                                    if (!minesField[x+i][y+j].open) showOne(x+i,y+j);
                                    if (minesField[x+i][y+j].check) needToCheck = gTrue;
                                }
                            }
                        }
                    }
                    minesField[x][y].check = gFalse;
                }
            }
        }
    }
}

static GFX_THREAD_FUNCTION(thdMines, msg)
{
    (void)msg;
    gU16 x,y, delay;
    gBool delayed = gFalse;
    while (!minesGameOver) {
        if (minesEmptyNodes == 0) {
            minesGameOver = gTrue;
            minesGameWinner = gTrue;
        }
        initRng();
        ginputGetMouseStatus(0, &ev);
        delayed = gFalse;
        if (ev.buttons & GINPUT_MOUSE_BTN_LEFT) {
            x = ev.x/MINES_CELL_WIDTH;
            y = ev.y/MINES_CELL_WIDTH;
            delay = 0;
            while (ev.buttons & GINPUT_MOUSE_BTN_LEFT) { // Wait until release
                ginputGetMouseStatus(0, &ev);
                gfxSleepMilliseconds(1);
                delay++;
                if (delay >= MINES_FLAG_DELAY) {
                    delay = MINES_FLAG_DELAY;
                    if (!delayed && inRange(x, y) && !minesField[x][y].open) {
                        if (minesField[x][y].flag) {
                            gdispImageOpenFile(&minesImage, minesGraph[8]);
                            gdispImageDraw(&minesImage, (x*MINES_CELL_HEIGHT)+1, (y*MINES_CELL_WIDTH)+1, MINES_CELL_WIDTH-1, MINES_CELL_HEIGHT-1, 0, 0);
                            gdispImageClose(&minesImage);
                            minesField[x][y].flag = gFalse;
                            minesFlags--;
                            printStats();
                        } else {
                            gdispImageOpenFile(&minesImage, minesGraph[11]);
                            gdispImageDraw(&minesImage, (x*MINES_CELL_HEIGHT)+1, (y*MINES_CELL_WIDTH)+1, MINES_CELL_WIDTH, MINES_CELL_HEIGHT, 0, 0);
                            gdispImageClose(&minesImage);
                            minesField[x][y].flag = gTrue;
                            minesFlags++;
                            printStats();
                        }
                        delayed = gTrue;
                    }
                }
            }
            // Check time, if longer than MINES_FLAG_DELAY then add flag...
            if (delay < MINES_FLAG_DELAY) {
                if ((x < MINES_FIELD_WIDTH) && (y < MINES_FIELD_HEIGHT) && !minesField[x][y].open && !minesField[x][y].flag) {
                    showOne(x, y);
                    openEmptyNodes();
                    printStats();
                }
            }
        }
    }
    gfxThreadReturn(0);
}

static void printGameOver(void)
{
    if (minesGameOver) {
        gFont font = gdispOpenFont("DejaVuSans16");
        if (minesGameWinner) {
            gdispDrawString((gdispGetWidth()-gdispGetStringWidth("You LIVE!", font))/2, gdispGetHeight()-15, "You LIVE!", font, GFX_WHITE);
        } else {
            gdispDrawString((gdispGetWidth()-gdispGetStringWidth("You DIED!", font))/2, gdispGetHeight()-15, "You DIED!", font, GFX_WHITE);
        }
        gdispCloseFont(font);
    } else {
        gdispFillArea(0, gdispGetHeight()-25, gdispGetWidth(), 25, GFX_BLACK);
    }
}

static void initField(void)
{
    gI16 x, y, mines, i, j;

    minesFlags = 0;
    minesGameOver = gFalse;
    printGameOver();

    gFont font = gdispOpenFont("fixed_5x8");
    gdispImageOpenFile(&minesImage, "plainmine.bmp");
    // Saving status icons width/height for later use
    minesStatusIconWidth = minesImage.width;
    minesStatusIconHeight = minesImage.height;
    gdispImageDraw(&minesImage, 4, gdispGetHeight()-minesImage.height, minesImage.width, minesImage.height, 0, 0);
    gdispImageClose(&minesImage);
    gdispImageOpenFile(&minesImage, "plainflag.bmp");
    gdispImageDraw(&minesImage, 4+minesImage.width+gdispGetStringWidth("99999", font), gdispGetHeight()-minesImage.height, minesImage.width, minesImage.height, 0, 0);
    gdispImageClose(&minesImage);
    gdispCloseFont(font);
    printStats();

    initRng();

    // Clearing/resetting field here...
    i = 0;
    for (x = 0; x < MINES_FIELD_WIDTH; x++) {
        for (y = 0; y < MINES_FIELD_HEIGHT; y++) {
            minesField[x][y].num = 0;
            minesField[x][y].open = gFalse;
            minesField[x][y].check = gFalse;
            minesField[x][y].flag = gFalse;
            minesField[x][y].fieldNum = i;
            i++;
        }
    }

    // Randomizing closed field drawing...
    for (x = 0; x < MINES_FIELD_WIDTH; x++) {
        for (y = 0; y < MINES_FIELD_HEIGHT; y++) {
            // Getting random node and swapping it with current
            i = randomInt(MINES_FIELD_WIDTH);
            j = randomInt(MINES_FIELD_HEIGHT);
            mines = minesField[x][y].fieldNum;
            minesField[x][y].fieldNum = minesField[i][j].fieldNum;
            minesField[i][j].fieldNum = mines;
        }
    }

    // Clearing nodes randomly
    if (!minesFirstGame) {
        for (x = 0; x < MINES_FIELD_WIDTH; x++) {
            for (y = 0; y < MINES_FIELD_HEIGHT; y++) {
                i = minesField[x][y].fieldNum/MINES_FIELD_HEIGHT;
                j = minesField[x][y].fieldNum-(i*MINES_FIELD_HEIGHT);
                gdispFillArea((i*MINES_CELL_WIDTH)+1, (j*MINES_CELL_HEIGHT)+1, MINES_CELL_WIDTH, MINES_CELL_HEIGHT, GFX_BLACK);
                gfxSleepMilliseconds(2);
            }
        }
    } else {
        minesFirstGame = gFalse;
    }

    // Drawing closed nodes randomly
    gdispImageOpenFile(&minesImage, minesGraph[8]);
    for (x = 0; x < MINES_FIELD_WIDTH; x++) {
        for (y = 0; y < MINES_FIELD_HEIGHT; y++) {
            i = minesField[x][y].fieldNum/MINES_FIELD_HEIGHT;
            j = minesField[x][y].fieldNum-(i*MINES_FIELD_HEIGHT);
            gdispImageDraw(&minesImage, (i*MINES_CELL_HEIGHT)+1, (j*MINES_CELL_WIDTH)+1, MINES_CELL_WIDTH, MINES_CELL_HEIGHT, 0, 0);
            gfxSleepMilliseconds(2);
        }
    }
    gdispImageClose(&minesImage);
    minesEmptyNodes = MINES_FIELD_WIDTH*MINES_FIELD_HEIGHT;

    // Placing mines in random nodes :D
    mines = 0;
    while (mines != MINES_MINE_COUNT) {
        x = randomInt(MINES_FIELD_WIDTH);
        y = randomInt(MINES_FIELD_HEIGHT);
        if (minesField[x][y].num != 9) {
        mines++;
        minesEmptyNodes--;
        minesField[x][y].num = 9;
        }
    }

    // Calculating numbers for nearby mine nodes
    for (x = 0; x < MINES_FIELD_WIDTH; x++) {
        for (y = 0; y < MINES_FIELD_HEIGHT; y++) {
            if (minesField[x][y].num != 9) {
                for (i = -1; i <= 1; i++) {
                    for (j = -1; j <= 1; j++) {
                        if ((i != 0) || (j != 0)) {                                   // We don't need to check middle node as we already know it is not a mine! :D
                            if (inRange(x+i,y+j) && (minesField[x+i][y+j].num == 9)) {
                                minesField[x][y].num++;
                            }
                        }
                    }
                }
            }
        }
    }

    minesTime = 0;
    minesUpdateTime();
    gtimerStart(&minesTimeCounterTimer, minesTimeCounter, 0, gTrue, 1000);
}

void minesStart(void)
{
    gI16 x, y;

#if MINES_SHOW_SPLASH
    gtimerStop(&minesSplashBlink);
    gdispClear(GFX_BLACK);
#endif

    initField();
    gfxThreadCreate(0, 1024, gThreadpriorityNormal, thdMines, 0); 
    while (!minesGameOver) {
        gfxSleepMilliseconds(100);
    }
    printGameOver();
    gtimerStop(&minesTimeCounterTimer);

    if (!minesGameWinner) {
        // Print generated mines for player to see
        gFont font = gdispOpenFont("fixed_10x20");
        for (x = 0; x < MINES_FIELD_WIDTH; x++) {
            for (y = 0; y < MINES_FIELD_HEIGHT; y++) {
                if (minesField[x][y].num == 9 && !minesField[x][y].flag) {
                    gdispImageOpenFile(&minesImage, minesGraph[12]);
                    gdispImageDraw(&minesImage, (x*MINES_CELL_HEIGHT)+1, (y*MINES_CELL_WIDTH)+1, MINES_CELL_WIDTH, MINES_CELL_HEIGHT, 0, 0);
                    gdispImageClose(&minesImage);
                }
                if (minesField[x][y].flag && (minesField[x][y].num != 9)) {
                    gdispImageOpenFile(&minesImage, minesGraph[13]);
                    gdispImageDraw(&minesImage, (x*MINES_CELL_HEIGHT)+1, (y*MINES_CELL_WIDTH)+1, MINES_CELL_WIDTH, MINES_CELL_HEIGHT, 0, 0);
                    gdispImageClose(&minesImage);
                }
            }
        }
        gdispCloseFont(font);
    }
}

#if MINES_SHOW_SPLASH
    static void minesSplashBlinker(void* arg)
    {
        (void)arg;

        minesSplashTxtVisible = !minesSplashTxtVisible;

        if (minesSplashTxtVisible) {
            gdispImageOpenFile(&minesImage, "splashtxt.bmp");
        } else {
            gdispImageOpenFile(&minesImage, "splashclr.bmp");
        }

        gdispImageDraw(&minesImage, (gdispGetWidth()/2)-150+93, (gdispGetHeight()/2)-100+161, 112, 10, 0, 0);

        gdispImageClose(&minesImage);
    }
    
    void minesShowSplash(void)
    {
        gdispImageOpenFile(&minesImage, "splash.bmp");
        gdispImageDraw(&minesImage, (gdispGetWidth()/2)-150, (gdispGetHeight()/2)-100, 300, 200, 0, 0);
        gdispImageClose(&minesImage);
    
        gtimerStart(&minesSplashBlink, minesSplashBlinker, 0, gTrue, 400);
    }
#endif

void minesInit(void)
{
    initRng();

    gdispClear(GFX_BLACK);
}
