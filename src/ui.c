#include "ui.h"

void ui_menu() {
	char option;
	do {
		printf("A - Load input file\n"
				"B - Generate report\n"
				"C - Print records tree\n"
				"D - Print clients list\n"
				"E - Exit");
		scanf("%c", &option);
		getchar();//Discard line feed
	} while (tolower(option) < 'a' || tolower(option) > 'e');
	switch (option) {
	case 'A':
		ui_input_menu();
		break;
	case 'B':
		//TODO
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

void ui_input_menu() {
	char* file_name;
	puts("Here are the available files\n");
	io_print_dir(DEFAULT_INPUT_DIR);
	puts("Type the name of a file\n");

	do {
		file_name = io_filepath_from_stdio(DEFAULT_INPUT_DIR);
	} while (!file_name);
	io_read_purchases(file_name);
}
