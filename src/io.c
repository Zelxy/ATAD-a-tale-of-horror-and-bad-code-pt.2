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
//		if (entry->d_type != 4) //4 stands for directory it seems
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
	char name[100];
	char gender;
	int value;
	int day, month, year;
	fscanf("%d/%d/%d",&day,&month,&year);
	printf("%d/%d/%d",day,month,year);
    while(fscanf(file,"%100[^,]%*c%c%*c%d\n",&name,&gender,&value) != EOF){
            printf("%s %c %d\n",name,gender,value);
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

