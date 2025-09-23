#pragma once

#include <stddef.h>
#include <termios.h>

void disable_raw_mode(struct termios* original_term);
void enable_raw_mode(struct termios* term);
void raw_write_buff(const char* buff, size_t buff_len);
void raw_write_char(const char* c);
