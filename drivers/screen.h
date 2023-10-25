#ifndef _SCREEN_H
#define _SCREEN_H

#define VIDEO_ADDRESS (unsigned char *) 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define DEFUALT_COLOR 0x0f

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void clear_screen();
void kprint(char *message);
void kprint_at(char *message, int col, int row);
int print_char(char c, int col, int row, char attr);

#endif