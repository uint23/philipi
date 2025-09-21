#pragma once

#include <termios.h>

void disable_raw_mode(struct termios *original_term);
void enable_raw_mode(struct termios *term);
