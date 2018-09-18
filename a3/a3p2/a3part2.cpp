#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <map>

using namespace std;

class Passwd {
private:
	string user;
	string uid;
	string gid;
	string gecos;
	string home;
	string shell;

public:
	Passwd(string user, string uid, string gid, string gecos, string home, string shell){
		this->user = user;
		this->uid = uid;
		this->gid = gid;
		this->gecos = gecos;
		this->home = home;
		this->shell = shell;
	}

	Passwd() {}

	explicit Passwd(string input){
		int n = (int)input.length();
		string strArray[10];

		// split the elements by ":"
		int i = 0;
		char *cstr = new char[n + 1];
		strcpy(cstr, input.c_str());
		char* token = strtok(cstr, ":");

		while (token != NULL){
			strArray[i++] = token;
			token = strtok( NULL, ":" );
		}

		this->user = strArray[0];
		this->uid = strArray[2];
		this->gid = strArray[3];
		this->gecos = strArray[4];
		this->home = strArray[5];
		this->shell = strArray[6];
	}

	const string &getUser() const{
		return user;
	}

	const string &getUid() const{
		return uid;
	}

	const string &getGid() const{
		return gid;
	}

	const string &getGecos() const{
		return gecos;
	}

	const string &getHome() const{
		return home;
	}

	const string &getShell() const{
		return shell;
	}
};

int main()
{
	const int SIZE = 100;
	Passwd PasswdArray[SIZE];
	Passwd PasswdArray2[SIZE];
	int index = 0;

	fstream fileIn;
	fileIn.open("/etc/passwd", ios::in);   // Open the file

	string input = "";

	if (fileIn.is_open()){
		while (true){ // go through the file, get the passed by line
			if (fileIn.eof()){
				break;
			}
			getline(fileIn, input);
			Passwd* newPass = new Passwd(input);
			PasswdArray[index] = *newPass;
			index++;
		}
	}
	fileIn.close();


    // output to text file
	fileIn.open("a3p2task1.txt", ios::out);
	if (fileIn.is_open()){
		for (int i = 0; i < index; i++){
			int record = i + 1;
			fileIn << "Object " << record << endl;
			fileIn << "user: " << PasswdArray[i].getUser() << endl;
			fileIn << "uid: " << PasswdArray[i].getUid() << endl;
			fileIn << "gid: " << PasswdArray[i].getGid()<< endl;
			fileIn << "gecos: " << PasswdArray[i].getGecos() << endl;
			fileIn << "home: " << PasswdArray[i].getHome() << endl;
			fileIn << "shell: " << PasswdArray[i].getShell() << endl << endl;
		}
	}
	fileIn.close();

	// task 2

	// output to the binary file
	fileIn.open("a3p2task2.bin", ios::binary | ios::out);
	if (fileIn.is_open()){
		for (int i = 0; i < index; i++){
			Passwd temp = PasswdArray[i];
			fileIn.write((char *)&temp, sizeof(temp));
		}
	}
	fileIn.close();



	// read from the binary file
	Passwd *p = new Passwd;

	ifstream isFile("a3p2task2.bin", ios::binary | ios::in);

	if (isFile.is_open()){
		for (int i = 0; i < index; i++){
			isFile.read((char*)p, sizeof(Passwd));
			PasswdArray2[i] = *p;
		}
	}
	isFile.seekg(0);
	isFile.close();

	fileIn.open("a3p2task2.txt", ios::out);

	if (fileIn.is_open()){
		// outut to array
		for (int i = 0; i < index; i++){
			int record = i + 1;
			fileIn << "Object " << record << endl;
			fileIn << "user: " << PasswdArray[i].getUser() << endl;
			fileIn << "uid: " << PasswdArray[i].getUid() << endl;
			fileIn << "gid: " << PasswdArray[i].getGid()<< endl;
			fileIn << "gecos: " << PasswdArray[i].getGecos() << endl;
			fileIn << "home: " << PasswdArray[i].getHome() << endl;
			fileIn << "shell: " << PasswdArray[i].getShell() << endl << endl;
		}
	}


    // task 3
    map<int, string> PasswdMap;
	int uid;
	string gid;

	for (int i = 0; i < index; i++)
	{
		gid = PasswdArray[i].getGid();
		uid = atoi(PasswdArray[i].getUid().c_str());
		PasswdMap[uid] = gid;
	}
	// print the map
	for (map<int, string>::iterator i = PasswdMap.begin(); i != PasswdMap.end(); i++)
	{
		cout << i->first << ":";
		cout << i->second << "\n";

	}

	return 0;
}
