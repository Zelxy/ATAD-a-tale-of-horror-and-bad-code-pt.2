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
	fscanf(file, "%d/%d/%d", &day, &month, &year);
	today.tm_mday = day;
	today.tm_mon = month;
	today.tm_year = year;
	printf("Data alterada para: %d/%d/%d\n", day, month, year);
	while (fscanf(file, " %100[^,]%*c%c%*c%d\n", name, &gender, &value) != EOF) {
		clientlst_add_store_visit(&client_list, &client_activity_bst, name, value, gender);
	}
	clientlst_draw(&client_list);
	fclose(file);
}

char* io_filepath_from_stdio(const char* base_folder) {
	char input[256];
	fgets(input, 256, stdin);
	char* line_break = strchr(input, '\n');
	if (line_break) {
		*line_break = '\0';
	}

	char *location = malloc(sizeof(char) * 256);
	*location = '\0';
	strcat(location, base_folder);
	if (location[strlen(location) - 1] != '/') {
		strcat(location, "/");
	}
	strcat(location, input);
	if (io_file_exists(location)) return location;
	printf("\"%s\" is not a valid file path!", location);
	free(location);
	return NULL;
}

int io_file_exists(const char* path) {
	return (access(path, F_OK) == -1) ? 0 : 1;
}

void io_write_report(const char* path) {
	FILE *file = fopen(path, "w");
	if (!file) {
		puts("Error opening the file\n");
		exit(EXIT_FAILURE);
	}
	int clients_that_shopped = 0;
	int men = 0;
	int woman = 0;
	for (int i = 0; i < client_list.size; i++) {
		clients_that_shopped += client_list.elements[i].spent == 0 ? 0 : 1;
		if(client_list.elements[i].gender == 'm'){
			men++;
		}else{
			woman++;
		}
	}

	fprintf(stdout, "Número de clientes que visitaram a loja: %d\n", client_list.size);
	fprintf(stdout, "Número de clientes que efetuaram pelo menos uma compra: %d\n", clients_that_shopped);
	fprintf(stdout, "Número de clientes que só visitaram a loja: %d\n", (client_list.size - clients_that_shopped));
	fprintf(stdout, "Valores gastos totais:\n");

	fprintf(stdout, "Valores de consumo médio:\n");


	fprintf(stdout, "Género que mais visita a loja: %s\n", (men > woman) ? "Macho" : "Fémea");
	fprintf(stdout, "Cliente que mais gastou na loja: %s", "");

	//fclose(file);
}

