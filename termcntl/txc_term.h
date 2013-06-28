/*
Cursor Position:
Moves the cursor to the specified position (coordinates).
If you do not specify a position, the cursor moves to the home position at the upper-left corner of the screen (line 0, column 0). This escape sequence works the same way as the following Cursor Position escape sequence.
*/
void txc_set_pos(int line, int column);

/*
Cursor Up:
Moves the cursor up by the specified number of lines without changing columns. If the cursor is already on the top line, ANSI.SYS ignores this sequence.
*/
void txc_cur_up(int value);

/*
Cursor Down:
Moves the cursor down by the specified number of lines without changing columns. If the cursor is already on the bottom line, ANSI.SYS ignores this sequence.
*/
void txc_cur_down(int value);

/*
Cursor Forward:
Moves the cursor forward by the specified number of columns without changing lines. If the cursor is already in the rightmost column, ANSI.SYS ignores this sequence.
*/
void txc_cur_fw(int value);

/*
Cursor Backward:
Moves the cursor back by the specified number of columns without changing lines. If the cursor is already in the leftmost column, ANSI.SYS ignores this sequence.
*/
void txc_cur_bw(int value);

/*
Save Cursor Position:
Saves the current cursor position. You can move the cursor to the saved cursor position by using the Restore Cursor Position sequence.
*/
void txc_cur_save(void);

/*
Restore Cursor Position:
Returns the cursor to the position stored by the Save Cursor Position sequence.
*/
void txc_cur_restore(void);

/*
Erase Display:
Clears the screen and moves the cursor to the home position (line 0, column 0).
*/
void txc_clear_screen(void);

/*
Erase Line:
Clears all characters from the cursor position to the end of the line (including the character at the cursor position).
*/
void txc_clear_line(void);

/*
Set Graphics Mode:
Calls the graphics functions specified by the following values. These specified functions remain active until the next occurrence of this escape sequence. Graphics mode changes the colors and attributes of text (such as bold and underline) displayed on the screen.
 
Text attributes
0	All attributes off
1	Bold on
4	Underscore (on monochrome display adapter only)
5	Blink on
7	Reverse video on
8	Concealed on
 
Foreground colors
30	Black
31	Red
32	Green
33	Yellow
34	Blue
35	Magenta
36	Cyan
37	White
 
Background colors
40	Black
41	Red
42	Green
43	Yellow
44	Blue
45	Magenta
46	Cyan
47	White
 
Parameters 30 through 47 meet the ISO 6429 standard.
*/
void txc_gfmode(int attr, int fg, int bg);

/*
Set Mode:
Changes the screen width or type to the mode specified by one of the following values:
 
Screen resolution
0	 40 x 25 monochrome (text)
1	 40 x 25 color (text)
2	 80 x 25 monochrome (text)
3	 80 x 25 color (text)
4	320 x 200 4-color (graphics)
5	320 x 200 monochrome (graphics)
6	640 x 200 monochrome (graphics)
7	Enables line wrapping
13	320 x 200 color (graphics)
14	640 x 200 color (16-color graphics)
15	640 x 350 monochrome (2-color graphics)
16	640 x 350 color (16-color graphics)
17	640 x 480 monochrome (2-color graphics)
18	640 x 480 color (16-color graphics)
19	320 x 200 color (256-color graphics)
*/ 
void txc_mode(int value);

/*
Reset Mode:
Resets the mode by using the same values that Set Mode uses, except for 7, which disables line wrapping
(the last character in this escape sequence is a lowercase L).
*/
void txc_reset_mode(int value);

/*
http://ascii-table.com/ansi-escape-sequences.php
*/
void txc_set_kb_str(const char* code, const char* string);

typedef struct txc_GFMODE_
{
    int attr;
    int fg;
    int bg;
} txc_GFMODE;

/*
 * set gfmode using struct instead of native
 */
txc_GFMODE txc_set_gfmode(txc_GFMODE mode);

/*
 * set to no attr, white fg and black bg
 */
void txc_clear_gfmode(void);

#define TXC_OUTPUT(gfmode,print) \
    txc_GFMODE lm = txc_set_gfmode( gfmode );\
    print \
    txc_set_gfmode( lm );

#define TXC_ESCAPE "\x1B\x5B"
#define TXC_END_FORMAT TXC_ESCAPE "0;37m"

#define TXC_A(attr,string) \
    TXC_ESCAPE #attr "m" string TXC_END_FORMAT
#define TXC_F(fg,string) \
    TXC_ESCAPE #fg "m" string TXC_END_FORMAT
#define TXC_AF(attr,fg,string) \
    TXC_ESCAPE #attr ";" #fg "m"  string TXC_END_FORMAT
#define TXC_AFB(attr,fg,bg,string) \
    TXC_ESCAPE #attr ";" #fg ";" #bg "m" string TXC_END_FORMAT
    
#define TXC_ERROR(string) TXC_AF(1,31,string)
#define TXC_WARN(string) TXC_AF(1,33,string)
#define TXC_GREEN(string) TXC_AF(1,32,string)
#define TXC_BLUE(string) TXC_AF(1,34,string)
#define TXC_NOTICE(string) TXC_AF(5,31,string)

