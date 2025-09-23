#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "philipi.h"
#include "raw.h"

void exit_cleanup(void);
void run(void);
void setup(void);

struct editor editor;
struct termios original_term;
struct termios raw_mode_term;

void exit_cleanup(void)
{
	/* restore original term */
	disable_raw_mode(&original_term);
	free(editor.row.chars);
	exit(EXIT_SUCCESS);
}

void run(void)
{
	char input;

	while (read(STDIN_FILENO, &input, 1) == 1) {
		if (input == 'q') {
			printf(NL);
			exit_cleanup();
		}
#ifdef a
		else {
			unsigned int *chars_len = &editor.row.length;

			char *new_chars = realloc(editor.row.chars, *chars_len + 2); /* +1 for \0 */
			if (new_chars == NULL) {
				fprintf(stderr, "realloc of editor.row.chars failed...");
				break;
			}

			new_chars[*chars_len] = input;
			(*chars_len)++;
			new_chars[*chars_len] = '\0';

			editor.row.chars = new_chars;

			printf("%c", editor.row.chars[*chars_len-1]);
			fflush(stdout);
		}
#endif
		else if (input == '\r' || input == '\n') {
			printf(NL);
			fflush(stdout);
		}
		else {
			printf("%c", input);
			fflush(stdout);
		}
	}
}

void setup(void)
{
	/* raw mode */
	if (tcgetattr(STDIN_FILENO, &original_term)) {
		fprintf(stderr, "fatal: could not get attributes...\n");
		exit(EXIT_FAILURE);
	}
	raw_mode_term = original_term;
	enable_raw_mode(&raw_mode_term);

	editor.row.chars = malloc(1);
	editor.row.chars[0] = '\0';
	editor.row.length = 0;
	editor.mode = NORMAL;
	editor.cursor_x = 0;
	editor.cursor_y = 0;
	editor.n_rows = 0;
}

int main(void)
{
	setup();
	run();
	return EXIT_SUCCESS;
}
