include <windows.h>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <dir.h>
#include <unistd.h>
using namespace std;


std::string current_working_directory()
{
    char working_directory[MAX_PATH+1] ;
    GetCurrentDirectoryA( sizeof(working_directory), working_directory ) ;
    return working_directory ;
}
int main(void)
{
int i,j;
   for(i=1;i<=2;i++)
   {  
    if (mkdir("working_directory\diri",0777)==-1);
       {
       cerr<<"Error : "<<strerror(errno)<<endl;
       exit(1);
       }
   else
       {
       cout << "Please enter j value: ";
       cin >> j;

        ofstream write ("working_directory\diri\filej.txt");
       if (write.is_open())
           {
           write << "This is a new file."<<endl;
           write.close();
           }
       else
           cout << "Unable to open file";
       }
       if (j==20)
       int symlink(const char *filej, const char *link1)
  
   }
   ofstream write ("working_directory\file1.txt");
       if (write.is_open())
       {
           write << "This is the first file."<<endl;
           write.close();
       }
       else
           cout << "Unable to open file";
return 0;
}