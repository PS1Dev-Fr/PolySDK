// Draw a textured sprt primitive
//
// based on Lameguy64's tutorial : http://lameguy64.net/svn/pstutorials/chapter1/3-textures.html
// Schnappy 2020
// OlivierP-To8 2024
#include <sys/types.h>
#include <stdio.h>
#include <libgte.h>
#include <libetc.h>
#include <libgpu.h>

#define VMODE 1 // Video Mode : 0 : NTSC, 1: PAL
#define SCREENXRES 320
#define SCREENYRES 240
#define OTLEN 8 // Ordering Table Length

DISPENV disp[2]; // Double buffered DISPENV and DRAWENV
DRAWENV draw[2];
u_long ot[2][OTLEN];         // double ordering table of length 8 * 32 = 256 bits / 32 bytes
char primbuff[2][32768];     // double primitive buffer of length 32768 * 8 =  262.144 bits / 32,768 Kbytes
char *nextpri = primbuff[0]; // pointer to the next primitive in primbuff. Initially, points to the first bit of primbuff[0]
short db = 0;                // index of which buffer is used, values 0, 1

#include "../../core/include/texture.h"

#include "minou4.h"
#include "minou8.h"
#include "minou16.h"

void init(void)
{
    ResetGraph(0);
    SetDefDispEnv(&disp[0], 0, 0, SCREENXRES, SCREENYRES);
    SetDefDispEnv(&disp[1], 0, SCREENYRES, SCREENXRES, SCREENYRES);
    SetDefDrawEnv(&draw[0], 0, SCREENYRES, SCREENXRES, SCREENYRES);
    SetDefDrawEnv(&draw[1], 0, 0, SCREENXRES, SCREENYRES);
    if (VMODE)
    {
        SetVideoMode(MODE_PAL);
        disp[0].screen.y += 8;
        disp[1].screen.y += 8;
    }
    SetDispMask(1); // Display on screen
    setRGB0(&draw[0], 50, 50, 50);
    setRGB0(&draw[1], 50, 50, 50);
    draw[0].isbg = 1;
    draw[1].isbg = 1;
    PutDispEnv(&disp[db]);
    PutDrawEnv(&draw[db]);
}

unsigned char loadTIG(unsigned char *tex, RECT *rtex, RECT *rpal)
{
    TEXTURE_HEADER *th = (TEXTURE_HEADER *)tex;
    if ((th->signature[0] == 'T') && (th->signature[1] == 'I') && (th->signature[2] == 'G'))
    {
        unsigned int offset = sizeof(TEXTURE_HEADER);
        rtex->w = th->wVram;
        rtex->h = th->height;

        // Transfer the data from memory to VRAM at position rtex.x, rtex.y
        LoadImage(rtex, (u_long *)(tex + offset));
        DrawSync(0); // Wait for the drawing to end

        rtex->w = th->width;

        switch (th->mode)
        {
        case TEXTURE_PAL8:
            offset += th->width * th->height;
            LoadImage(rpal, (u_long *)(tex + offset));
            DrawSync(0);
            break;
        case TEXTURE_PAL4:
            offset += (th->width * th->height) / 2;
            LoadImage(rpal, (u_long *)(tex + offset));
            DrawSync(0);
            break;
        }

        return th->mode;
    }

    return 0xff;
}

void displayTIG(SPRT *sprt, DR_TPAGE *tpage, RECT *rtex, RECT *rpal,
                unsigned char mode, short x, short y)
{
    setSprt(sprt);
    // Set RGB color. 128,128,128 is neutral. You can color the image by adjusting these values
    setRGB0(sprt, 128, 128, 128);
    // Set sprite position
    setXY0(sprt, x, y);
    // Set sprite width and height
    setWH(sprt, rtex->w, rtex->h);
    if (rpal != 0)
    {
        setClut(sprt, rpal->x, rpal->y);
    }
    // add the sprite primitive to the ordering table
    addPrim(ot[db], sprt);

    // Set Texture page for the texture
    setDrawTPage(tpage, 0, 1, getTPage(mode, 0, rtex->x, rtex->y));
    // add the sprite primitive to the ordering table
    addPrim(ot[db], tpage);
}

void display(void)
{
    DrawSync(0);
    VSync(0);
    PutDispEnv(&disp[db]);
    PutDrawEnv(&draw[db]);
    DrawOTag(&ot[db][OTLEN - 1]);
    db = !db;
    nextpri = primbuff[db];
}

int main(void)
{
    RECT rtex16 = {640, 0, 64, 128};
    RECT rtex8 = {704, 0, 64, 128};
    RECT rpal8 = {0, 480, 256, 1};
    RECT rtex4 = {768, 0, 64, 128};
    RECT rpal4 = {0, 481, 16, 1};

    // Define 3 pointers to DR_TPAGE struct. We need three because our images are on three different texture pages.
    init();
    unsigned char mode16 = loadTIG(minou16_array, &rtex16, 0);   // Load everything to vram
    unsigned char mode8 = loadTIG(minou8_array, &rtex8, &rpal8); // Load everything to vram
    unsigned char mode4 = loadTIG(minou4_array, &rtex4, &rpal4); // Load everything to vram

    while (1)
    {
        ClearOTagR(ot[db], OTLEN);

        SPRT *sprt_16b = (SPRT *)nextpri;
        nextpri += sizeof(SPRT);
        DR_TPAGE *tpage_16b = (DR_TPAGE *)nextpri;
        nextpri += sizeof(DR_TPAGE);
        displayTIG(sprt_16b, tpage_16b, &rtex16, 0, mode16, 32, 56);

        SPRT *sprt_8b = (SPRT *)nextpri;
        nextpri += sizeof(SPRT);
        DR_TPAGE *tpage_8b = (DR_TPAGE *)nextpri;
        nextpri += sizeof(DR_TPAGE);
        displayTIG(sprt_8b, tpage_8b, &rtex8, &rpal8, mode8, 128, 56);

        SPRT *sprt_4b = (SPRT *)nextpri;
        nextpri += sizeof(SPRT);
        DR_TPAGE *tpage_4b = (DR_TPAGE *)nextpri;
        nextpri += sizeof(DR_TPAGE);
        displayTIG(sprt_4b, tpage_4b, &rtex4, &rpal4, mode4, 224, 56);

        display();
    }

    return 0;
}
