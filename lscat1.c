#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CHUNK 1024 /* read 1024 bytes at a time */

// return 0 if not a .c file
// otherwise return 1



int main(int argc, char **argv) {
	char filename[80];
	int  name_length;
	DIR *dp;
	struct dirent *dirp;
	bool cFile;

	if (argc != 2)
	{
		fprintf(stderr, "usage: %s dir_name\n", argv[0]);
		exit(1);
	}

	if ((dp = opendir(argv[1])) == NULL )
	{
		fprintf(stderr, "can't open '%s'\n", argv[1]);
		exit(1);
	}

	while ((dirp = readdir(dp)) != NULL )
	{
		printf("%s\n", dirp->d_name);

		memset(filename, '\0', sizeof(filename));
		strcpy(filename, dirp->d_name);
		printf(" ** %s ", filename);
		name_length = strlen(filename);
		printf(" name_length=%d \n", name_length);

			if (strncmp(&filename[name_length - 1], "c", 1) == 0 && strncmp(&filename[name_length - 2], ".", 1) == 0){
                cFile = true;
            }
            else
                cFile = false;


		// if the file is a .c file
		if (cFile)
		{
			// then output the file content
			char buf[CHUNK];
			FILE *file;
			size_t nread;

			file = fopen(filename, "r");
			if (file) {
				while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
					fwrite(buf, 1, nread, stdout);
				fclose(file);
			}
		}

	}

	closedir(dp);
	return(0);
}