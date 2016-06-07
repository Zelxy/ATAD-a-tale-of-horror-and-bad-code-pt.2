#ifndef EXAMPLES_PROJECT_IO_H_
#define EXAMPLES_PROJECT_IO_H_

#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "shared_adts.h"
#include "client_list.h"

int io_print_dir(const char*);
void io_read_purchases(char*);
char* io_filepath_from_stdio(const char*);
int io_file_exists(const char*);
void io_write_report(const char*);
#endif /* EXAMPLES_PROJECT_IO_H_ */

