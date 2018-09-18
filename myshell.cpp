
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

int main(){

    string input;
    do{
        cout << "enter command: " << endl;
        getline(cin, input);
        if (input == "exit") break;
        istringstream iss(input);
        int k = 0;
        do {
            string subs;
            iss >> subs;
            if (k == 0){ // Check for command
                cout << "Command: " + subs << endl;
                k++;
            }

            if (subs.find(".") != string::npos) cout << "Argument: " + subs << endl; // Check for argument
            if (subs.find("$") != string::npos) cout << "Argument: " + subs << endl;

            int n = subs.length(); // Check for option
            if (subs[0] == '-'){
                for (int i = 1; i < n; i++){
                    cout << "Option: " <<subs[i] << endl;
                }
            }

            if (subs == "<" || subs == ">" || subs == ">>") cout << "File Redirection: " + subs << endl; // Check for redirection

            if (subs == "|"){ // Check for pipe
                cout << "Pipe" << endl;
                k = 0;
            }
        } while (iss);
    } while (input != "exit");
}
