#pragma once

#define NL "\r\n"

enum mode {
	NORMAL, INSERT
};

struct row {
	unsigned int  length;
	char*         chars;
};

struct editor {
	unsigned int  cursor_x;
	unsigned int  cursor_y;
	unsigned int  n_rows;
	struct row    row;
	enum mode     mode;
};
