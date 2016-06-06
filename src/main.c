#include <stdio.h>
#include <stdlib.h>
#include <time.h>
extern struct tm *last_visit;

#include "shared_adts.h"
#include "io.h"
#include "ui.h"

#define DEFAULT_INPUT_DIR "./input/"


int main(int argc, char **argv){
	//It starts at 31/1/2016
	last_visit = calloc(1, sizeof(struct tm));
	last_visit->tm_mday = 30;
	last_visit->tm_mon = 1;
	last_visit->tm_year = 2016;
	last_visit->tm_hour = 0;
	last_visit->tm_min = 0;
	last_visit->tm_sec = 0;

	ui_menu();
}
