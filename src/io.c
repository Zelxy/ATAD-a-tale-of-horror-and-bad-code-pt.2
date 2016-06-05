#include "io.h"

int io_print_dir(const char *path) {
	struct dirent *entry;
	DIR *dir;
	dir = opendir(path);
	if (!dir) {
		perror("Error");
		return -1;
	}
	while ((entry = readdir(dir))) {
#if defined _unix_ || defined linux
		if (entry->d_type != 4) //4 stands for directory it seems, not sure about symlinks
		puts(entry->d_name);
#else//TODO distinguish files from folders on windows
		puts(entry->d_name);
#endif
	}
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
		exit(EXIT_FAILURE);
	}

	char name[100];
	char gender;
	int value;
	int day, month, year;
	int count = 0;

	char line[64];
	while (!fgets(line, sizeof line, file)) {
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

	char *location = malloc(sizeof(char)*256);
	*location = '\0';
	strcat(location, base_folder);
	if (location[strlen(location) - 1] != '/') {
		strcat(location, "/");
	}
	strcat(location, input);
	if (io_file_exists(location)) {
		printf("\"%s\" is not a valid file path!", location);
		free(location);
		return NULL;
	}
	return location;
}

int io_file_exists(const char* path) {
	return (access(path, F_OK) == -1) ? 0 : 1;
}

void io_read_purchases_sample(){
	FILE* ficheiro;
    ficheiro = fopen("f1.txt","r");
    int dia,mes,ano;
    char* nome = malloc(sizeof(char)*100);
    char sexo;
    int gasto;
    while(fscanf(ficheiro,"%100[^,]%*c%c%*c%d\n",nome,&sexo,&gasto) != EOF){
            printf("%s %c %d\n",nome,sexo,gasto);
    }
    fclose(ficheiro);
}
