#include <stdio.h>
#include <string.h>
#include "txc_term.h"

static const char* esc = TXC_ESCAPE ;

void 
txc_set_cur_pos(int line, int col)
{
    printf("%s%d;%dH", esc, line, col);
}

void
txc_cur_up(int value)
{
    printf("%s%dA", esc, value);
}

void
txc_cur_down(int value)
{
    printf("%s%dB", esc, value);
}

void
txc_cur_fw(int value)
{
    printf("%s%dC", esc, value);
}


void
txc_cur_bw(int value)
{
    printf("%s%dD", esc, value);
}

void
txc_cur_save(void)
{
    printf("%ss", esc);
}

void
txc_cur_restore(void)
{
    printf("%su", esc);
}

void
txc_clear_screen(void)
{
    printf("%s2J", esc);
}

void 
txc_clear_line(void) 
{
    printf("%sK", esc);
}

void 
txc_gfmode(int attr, int fg, int bg) 
{
    char gfmode[20];
    sprintf(gfmode, "%s", esc);
    int idx = strlen(esc);
    if (attr != -1) {
        sprintf(&gfmode[idx], "%d", attr);
        idx += 1;
    }
    if (fg != -1) {
        if (attr != -1) {
            sprintf(&gfmode[idx], ";");
            idx += 1;
        }
        sprintf(&gfmode[idx], "%d", fg);
        idx += 2;
    }
    if (bg != -1) {
        if (attr != -1 || fg != -1) {
            sprintf(&gfmode[idx], ";");
            idx += 1;
        }
        sprintf(&gfmode[idx], "%d", bg);
        idx += 2;
    }
    printf("%s%sm", esc, gfmode);
}

void 
txc_mode(int value)
{
    printf("%s=%dh", esc, value);
}

void 
txc_reset_mode(int value)
{
    printf("%s=%dl", esc, value);
}

void 
txc_set_kb_str(const char* code, const char* string)
{
    printf("%s%s;%s;p", esc, code, string);
}

static txc_GFMODE last_gfmode = {0,37,-1};

txc_GFMODE
txc_set_gfmode(txc_GFMODE mode) 
{
    txc_gfmode(mode.attr, mode.fg, mode.bg);
    txc_GFMODE tmp = last_gfmode;
    last_gfmode = mode;
    return tmp;
}

void 
txc_clear_gfmode(void)
{
    txc_gfmode(0,37,-1);
}
