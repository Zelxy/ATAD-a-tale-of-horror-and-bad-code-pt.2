#include "io.h"
#include "shared_adts.h"
struct tm *last_visit;
clientlst_t client_list;

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
		printf("%s ", entry->d_name);
#else//TODO distinguish files from folders on windows
		puts(entry->d_name);
#endif
	}
	printf("\n");
	closedir(dir);
	return 0;
}

void io_read_purchases(char* path) {
	if (!io_file_exists(path)) {
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
	fscanf(file, "%d/%d/%d",&day,&month,&year);
	last_visit->tm_mday = day;
	last_visit->tm_mon = month;
	last_visit->tm_year = year;
	printf("Data alterada para: %d/%d/%d",day,month,year);
    while(fscanf(file,"%100[^,]%*c%c%*c%d\n",name,&gender,&value) != EOF){
            client_visit_store(&client_list,name,value,gender);
    }
    clientlst_draw(&client_list);
	fclose(file);
}

char* io_filepath_from_stdio(const char* base_folder) {
	char input[256];
	fgets(input, 256, stdin);
	char* line_break = strchr(input, '\n');
	if(line_break){
		*line_break = '\0';
	}

	char *location = malloc(sizeof(char)*256);
	*location = '\0';
	strcat(location, base_folder);
	if (location[strlen(location) - 1] != '/') {
		strcat(location, "/");
	}
	strcat(location, input);
	if (io_file_exists(location))
		return location;
	printf("\"%s\" is not a valid file path!", location);
	free(location);
	return NULL;
}

int io_file_exists(const char* path) {
	return (access(path, F_OK) == -1) ? 0 : 1;
}

