#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
int fd;

fd = mkdir("a4part1", 0777);
fd = mkdir("a4part1/folder1", 0777);
fd = mkdir("a4part1/folder2", 0777);
fd = creat("a4part1/folder1/file1", 0777);
fd = creat("a4part1/folder2/file2", 0777);
fd = creat("a4part1/file3", 0777);
fd = symlink("a4part1/folder2/file2", "a4part1/link4");
}
