#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main(){
	int i;
	string input;
	do {
	cout << "~~>: ";
	getline(cin, input);
	if (input == "exit" || input == "quit" || input == "bye" || input == "done"){
		exit(EXIT_SUCCESS);}
	const char *c = input.c_str();
	i = system(c);
	} while (input != "exit" && input != "quit" && input != "bye" && input != "done");
}
