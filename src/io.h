#ifndef EXAMPLES_PROJECT_IO_H_
#define EXAMPLES_PROJECT_IO_H_

#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//#include "client.h"
#include <unistd.h>
#include <dirent.h>

int io_print_dir(const char*);
void io_read_purchases(char*);
char* io_filepath_from_stdio(const char*);
int io_file_exists(const char*);

#endif /* EXAMPLES_PROJECT_IO_H_ */

