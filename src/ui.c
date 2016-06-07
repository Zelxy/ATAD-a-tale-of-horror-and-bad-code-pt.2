#include "ui.h"

void ui_menu() {
	while (1) {
		char option;
		do {
			printf("A - Load input file\n"
					"B - Generate report\n"
					"C - Print records tree\n"
					"D - Print clients list\n"
					"E - Exit\n");
			scanf("%c", &option);
			getchar(); //Discard line feed
		} while (tolower(option) < 'a' || tolower(option) > 'e');
		switch (option) {
		case 'A':
			ui_input_menu();
			break;
		case 'B':
			ui_generate_report();
			break;
		case 'C':
			//TODO
			break;
		case 'D':
			//TODO
			break;
		case 'E':
			exit(0);
		}
	}
}

void ui_input_menu() {
	char* file_name;
	puts("Here are the available files\n");
	io_print_dir(DEFAULT_INPUT_DIR);
	puts("Type the name of a file\n");

	do {
		file_name = io_filepath_from_stdio(DEFAULT_INPUT_DIR);
	} while (!file_name);
	io_read_purchases(file_name);
	getchar();
}

void ui_generate_report() {
	char file_name[64];
	char path[128] = DEFAULT_INPUT_DIR;
	puts("Pick a file name:\n");
	fgets(file_name, 64, stdin);
	char* line_break = strchr(file_name, '\n');
	if (line_break) {
		*line_break = '\0';
	}
	strcat(path, file_name);
	io_write_report(path);
}
