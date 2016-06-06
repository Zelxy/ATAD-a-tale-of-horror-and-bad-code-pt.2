#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
extern struct tm today;

#include "shared_adts.h"
#include "io.h"
#include "ui.h"

#define DEFAULT_INPUT_DIR "./input/"


clientlst_t client_list;

int main(int argc, char **argv){
	//It starts at 31/1/2016
	/*last_visit.tm_mday = 30;
	last_visit.tm_mon = 1;
	last_visit.tm_year = 2016;
	last_visit.tm_hour = 0;
	last_visit.tm_min = 0;
	last_visit.tm_sec = 0;*/
	//Hope this works on windows...
	strptime("31 Jan 2016 00:00:00", "%d %b %Y %H:%M:%S", &today);

	client_list.elements = calloc(100, sizeof(client_t));
	client_list.max_size = 100;

	ui_menu();
	free(client_list.elements);
}
