#include <direct.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;
int main(){
    mkdir("~cs3377\\a1part1");
    mkdir("~cs3377\\a1part1\\dir1");
    chdir("dir1");
    int result;
    result = system("touch dir1file1");
    chdir("..");
    mkdir("~cs3377\\a1part1\\dir2");
    chdir("dir2");
    result = system("touch dir2file2");
    chdir("..");
    result = system("touch file1");
    int symlink(const char *dir2file1, const char *link1);


    return 0;


}
