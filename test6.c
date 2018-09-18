#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "apue.h"
void listdir(const char *name, int indent)
{
	struct stat buf;
char *ptr;

    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
if (lstat(dir, &buf) < 0) {
printf("lstat error");
continue;
}


if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        } else {
            printf("%*s- %s\n", indent, "", entry->d_name);
        }




if (S_ISREG(buf.st_mode))
ptr = "regular";
else if (S_ISDIR(buf.st_mode))
ptr = "directory";
else if (S_ISCHR(buf.st_mode))
ptr = "character special";
else if (S_ISBLK(buf.st_mode))
ptr = "block special";
else if (S_ISFIFO(buf.st_mode))
ptr = "fifo";
else if (S_ISLNK(buf.st_mode))
ptr = "symbolic link";
else if (S_ISSOCK(buf.st_mode))
ptr = "socket";
else
ptr = "** unknown mode **";
printf("%s\n", ptr);

    }
    closedir(dir);
}

int main(void) {
    listdir("a4part1", 0);
    return 0;
}