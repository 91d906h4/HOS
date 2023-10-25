#include "screen.h"
#include "port.h"
#include "../lib/util.h"

// Declaration of private functions.
int print_char(char c, int col, int row, char attr);
int get_cursor_offset();
void set_cursor_offset(int offset);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

void kprint(char *message) {
    kprint_at(message, -1, -1);
}

void kprint_at(char *message, int col, int row) {
    int offset, i = 0;

    if (col >= 0 && row >= 0) {
        offset = get_offset(col, row);
    }
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    while (*(message + i) != 0) {
        offset = print_char(*(message + i++), col, row, DEFUALT_COLOR);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

int print_char(char c, int col, int row, char attr) {
    int offset;

    if (!attr) attr = DEFUALT_COLOR;

    if (col >= MAX_COLS || row >= MAX_ROWS) {
        *(VIDEO_ADDRESS + 2 * MAX_COLS * MAX_ROWS - 2) = 'E';
        *(VIDEO_ADDRESS + 2 * MAX_COLS * MAX_ROWS - 1) = DEFUALT_COLOR;

        return get_offset(col, row);
    }

    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1);
    }
    else if (c == '\t') {
        for (int i = 0; i < 4; i++) {
            *(VIDEO_ADDRESS + offset++) = ' ';
            *(VIDEO_ADDRESS + offset++) = attr;
        }
    }
    else {
        *(VIDEO_ADDRESS + offset++) = c;
        *(VIDEO_ADDRESS + offset++) = attr;
    }

    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        for (int i = 1; i < MAX_ROWS; i++) {
            mem_copy(get_offset(0, i) + VIDEO_ADDRESS, get_offset(0, i - 1) + VIDEO_ADDRESS, MAX_COLS * 2);
        }

        char *last_line = get_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
        for (int i = 0; i < MAX_COLS * 2; i++) *(last_line + i) = 0;

        offset -= 2 * MAX_COLS;
    }

    set_cursor_offset(offset);

    return offset;
}

void clear_screen() {
    for (int i = 0; i < MAX_COLS * MAX_ROWS; i++) {
        *(VIDEO_ADDRESS + i * 2) = ' ';
        *(VIDEO_ADDRESS + i * 2 + 1) = DEFUALT_COLOR;
    }

    set_cursor_offset(get_offset(0, 0));
}

int get_cursor_offset() {
    int offset;

    port_byte_out(REG_SCREEN_CTRL, 14);
    offset = port_byte_in(REG_SCREEN_DATA) << 8; // Height byte << 8.

    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);

    return offset * 2;
}

void set_cursor_offset(int offset) {
    offset /= 2;

    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));

    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}


int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset) {
    return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset) {
    return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}