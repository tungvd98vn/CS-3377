#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;
	

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
		printf("directory\n");
            listdir(path, indent + 2);
        } else if (entry->d_type == DT_LNK){
            printf("%*s- %s\n", indent, "", entry->d_name);
		printf("symbolic link\n");
        } else{
		printf("%*s- %s\n", indent, "", entry->d_name);
		printf("regular file\n");
		}
    }
    closedir(dir);
}

int main(void) {
	char cwd[1024];
	chdir("a4part1");
	getcwd(cwd, sizeof(cwd));
	printf("workdir: %s\n", cwd);
    listdir(".", 0);
    return 0;
}
