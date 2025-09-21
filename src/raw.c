#include <unistd.h>

#include "raw.h"

void enable_raw_mode(struct termios *term)
{
	term->c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	term->c_oflag &= ~(OPOST);
	term->c_cflag |= (CS8);
	term->c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, term);
}

void disable_raw_mode(struct termios *original_term)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, original_term);
}
