#include <gba.h>
#include <stdio.h>

static void wait_release(void) {
    while (1) {
        scanKeys();
        if (!keysHeld()) break;
        VBlankIntrWait();
    }
}

int main(void) {
    irqInit();
    irqEnable(IRQ_VBLANK);
    consoleDemoInit();

    iprintf("\x1b[2J");
    iprintf("\n\n       NUTTNMON\n");
    iprintf("     KRISTALLPFAD\n\n");
    iprintf(" Ein neues GBA Abenteuer\n\n");
    iprintf("     START druecken\n");

    while (1) {
        VBlankIntrWait();
        scanKeys();
        if (keysDown() & KEY_START) break;
    }
    wait_release();

    int selected = 0;
    const char* starters[3] = { "FROSNIX", "LUMIRAN", "AQUALISSE" };
    while (1) {
        iprintf("\x1b[2J");
        iprintf("\n  PROFESSOR: Willkommen!\n\n");
        iprintf("  Waehle dein erstes\n  NUTTNMON:\n\n");
        for (int i = 0; i < 3; ++i) {
            iprintf("  %c %s\n", i == selected ? '>' : ' ', starters[i]);
        }
        iprintf("\n  Steuerkreuz + A\n");

        VBlankIntrWait();
        scanKeys();
        u16 down = keysDown();
        if (down & KEY_UP) selected = (selected + 2) % 3;
        if (down & KEY_DOWN) selected = (selected + 1) % 3;
        if (down & KEY_A) break;
    }
    wait_release();

    iprintf("\x1b[2J");
    iprintf("\n\n  Du hast %s\n  gewaehlt!\n\n", starters[selected]);
    iprintf("  Willkommen in der Welt\n  von NUTTNMON!\n\n");
    iprintf("  Prototyp 0.1\n");

    while (1) VBlankIntrWait();
    return 0;
}
