#define VIDEO_ADDRESS (char *) 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define COLOR 0x0f

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void clear_screen();
void set_cursor_offset(int offset);
int get_cursor_offset();