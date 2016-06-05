#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "ui.h"

#define DEFAULT_INPUT_DIR "./input/"

int main(int argc, char **argv){
	io_print_dir(DEFAULT_INPUT_DIR);
	ui_menu();
}
