#include "io.h"

int io_print_dir(const char *path) {
	struct dirent *entry;
	DIR *dir;
	dir = opendir(path);
	if (!dir) {
		perror("Error");
		return -1;
	}
	while ((entry = readdir(dir)))
		if (entry->d_type != 4) //4 stands for directory it seems
			puts(entry->d_name);
	closedir(dir);
	return 0;
}

void io_read_purchases(char* path) {
	if (io_file_exists(path)) {
		printf("\"%s\" is not there!", path);
		return;
	}
	FILE *file = fopen(path, "r");
	if (!file) {
		puts("Error opening the file\n");
		exit(-1);
	}
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	char name[100];
	char gender;
	int value;
	int day, month, year;

	int count = 0;
	while ((read = getline(&line, &len, file)) != -1) {
		printf("I've read: 	%s\n", line);

		if (!count) { //First line is the date
			sscanf(line, "%2d/%d/%4d", &day, &month, &year);
		} else if (count > 1000) {
			printf("Over 1k lines read, likely an infinite loop\n");
			break;
		} else {
			//Replace commas with spaces
			char *comma = strchr(line, ',');
			if (!comma) { //Discard empty lines despite carriage return and line feed
				break;
			}
			while (comma) {
				*comma = ' ';
				comma = strchr(++comma, ',');
			}

			sscanf(line, "%50s %c %d", name, &gender, &value);
			//Add the purchase somewhere
			//client_add_purchase(name, gender, value, day, month, year);
		}
		count++;
	}
	fclose(file);
}

char* io_filepath_from_stdio(const char* base_folder) {
	char input[256];
	fgets(input, 256, stdin);

	char location[256] = "\0";
	strcat(location, base_folder);
	if (location[strlen(location) - 1] != '/') {
		strcat(location, "/");
	}
	strcat(location, input);
	if (io_file_exists(location)) {
		printf("\"%s\" is not a valid file path!", location);
		return NULL;
	}
	return location;
}

int io_file_exists(const char* path) {
	return (access(path, F_OK) == -1) ? 0 : 1;
}