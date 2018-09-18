
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>

using namespace std;
int main() {

    pid_t pid, pid2;

    int n;

    cout << "Select a number [1-5]: ";

    cin >> n;

    cout << endl;

    switch(n) {

        case 1:

        fork();

        cout << "This is process " + getpid() << endl;

        break;



        case 2:

        fork(); fork();

        cout << "This is process " + getpid() << endl;

        break;



        case 3:

        fork(); fork(); fork();

        cout << "This is process " + getpid() << endl;

        break;



        case 4:

        if((pid=fork()) && (pid2 = fork())) {fork();}

        if((pid=fork()) && (pid2 = fork())) {fork();}

        if ((pid=fork()) && (pid2 = fork())) {fork();}

        cout << "This is process " + getpid() << endl;

        break;

        case 5:

        for (int i=1; i<=5; i++){

        fork();

        }

        cout << "This is process " + getpid() << endl;

        break;

        default:

        cout << "Number not in range [1-5] !" << endl;

    }

}
