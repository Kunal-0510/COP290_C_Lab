#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include "Sheet.h"
#include "display.h"
#include "parsing.h"

static struct termios orig_termios;
void disableRawMode();
void enableRawMode();
void editActiveCell(Sheet* sheet);
void interactive_mode(Sheet* sheet);
