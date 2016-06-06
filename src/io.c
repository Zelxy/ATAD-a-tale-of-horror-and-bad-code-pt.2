#include "io.h"
#include "shared_adts.h"
struct tm today;

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
	struct tm temp_time;
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
	temp_time.tm_mday = day;
	temp_time.tm_mon = month-1;
	temp_time.tm_year = year-1900;
	temp_time.tm_hour = 0;
	temp_time.tm_min = 0;
	temp_time.tm_sec = 0;
	time_t new_time = mktime(&temp_time);
	time_t last_time = mktime(&today);
	if(difftime(new_time,last_time)/ (60 * 60 * 24)<0){
        printf("Ficheiro com data invalida ou anterior ao do ultimo lido!\n");
	} else{
	    today.tm_mday = day;
        today.tm_mon = month-1;
        today.tm_year = year-1900;
	}
	printf("Data alterada para: %d/%d/%d\n",day,month,year);
	clientlst_update_active(&client_list);
    while(fscanf(file," %100[^,]%*c%c%*c%d\n",name,&gender,&value) != EOF){
            clientlst_add_store_visit(&client_list,name,value,gender);
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

