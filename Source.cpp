#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

using namespace std;

unsigned int c = 1;

void CheckPrime(unsigned int n, bool usefile, bool useexfile, string filename);
bool CheckForFile();
string CreateNewFile();
unsigned int GetLastNumber();
void SendToFile(string msg, bool useexfile, string filename);

void main() {
	unsigned int n = 1;
	
	bool useexfile = false;

	if (CheckForFile()) {
		cout << "File detected, would you like to continue using it?(Y/N)" << endl;
		string inp;
		while (true) {
			cin >> inp;
			for (int i = 0; i < inp.length(); i++) {
				inp[i] = tolower(inp[i]);
			}
			if (inp != "y" && inp != "yes" && inp != "n" && inp != "no") {
				cout << "Answer must be yes/no/y/n." << endl;
			}
			else {
				if (inp == "y" || inp == "yes") {
					useexfile = true;
					
				}
				else {
					useexfile = false;
				}
				break;
			}
		}
	}
	string filename;
	bool usefile;
	if (useexfile == false) {
		if (CheckForFile()) {
			cout << "Would you like to create a new output file?(Y/N)" << endl;
		}
		else {
			cout << "Would you like to create a output file?(Y/N)" << endl;
		}
		string inp2;
		while (true) {
			cin >> inp2;
			for (int i = 0; i < inp2.length(); i++) {
				inp2[i] = tolower(inp2[i]);
			}
			if (inp2 != "y" && inp2 != "yes" && inp2 != "n" && inp2 != "no") {
				cout << "Answer must be yes/no/y/n." << endl;
			}
			else {
				if (inp2 == "y" || inp2 == "yes") {
					usefile = true;
					filename = CreateNewFile();
				}
				else {
					usefile = false;
				}
				break;
			}
		}
	}
	else {
		n = GetLastNumber();
	}

	int tt = thread::hardware_concurrency();
	cout << "total threads: " << tt << endl;
	
	cout << "Select how many threads you would like to use (1-" << tt << ")." << endl;
	int t;
	while (true) {
		cin >> t;
		if ((t > 0) && (t <= t)) {
			break;
		}
		else {
			cout << "Please select a number between 1 and " << tt << endl;
		}
	}

	vector<thread> threads (tt);
	while (true) {
		for (int i = 0; i < t; i++) {
			threads.at(i) = thread(CheckPrime,n,usefile,useexfile,filename);
			n++;
		}
		for (int i = 0; i < t; i++) {
			threads.at(i).join();
		}
	}

}

void CheckPrime(unsigned int n, bool usefile, bool useexfile, string filename) {
	int h = (n / 2) + 1;
	stringstream ss;
	for (int i = 1; i < h; i++) {
		if (n == 1) {
			ss << "prime " << c << ": " << n << endl;
			cout << "prime " << c << ": " << n << endl;
			c++;
		}
		if (n % i == 0 && i != 1) {
			return;
		}
	}
	cout << "prime " << c << ": " << n << endl;
	ss << "prime " << c << ": " << n << endl;
	c++;
	if (usefile || useexfile) {
		SendToFile(ss.str(), useexfile, filename);
	}
}

bool CheckForFile(){
	ifstream FILE("PrimeNumbers.txt");
	return FILE.good();
}

string CreateNewFile(){
	ifstream FILE("PrimeNumbers.txt");
	if(FILE.good()){
		int i=1;
		while(true){
			stringstream ss;
			ss << "PrimeNumbers" << i << ".txt";
			ifstream NEWFILE(ss.str());
			if(NEWFILE.good()){
				i++;
			}else{
				return ss.str();
			}
		}
	}else{
		return "PrimeNumbers.txt";
	}
}

unsigned int GetLastNumber() {
	fstream FILE("PrimeNumbers.txt", ios::in);
	FILE.seekg(-1, ios::end);
	string line;
	while (true) {
	//	cout << "looking for last number" << endl;

		char ch2;
		ch2 = FILE.get();
		//cout << "ch2 = " << c << endl;
		if(ch2 == '\n'){
			FILE.seekg(-2, ios::cur);
			while(true) {
				FILE.seekg(-2, ios::cur);
				char ch = FILE.get();
		//		cout << "ch = " << ch << endl;
				if (ch == '\n') {
					break;
				}
			}
			break;
		}
		else {
			FILE.seekg(-2, ios::cur);
		}
	}
	getline(FILE, line);
	//cout << "line = " << line << endl;
	
	size_t found = line.rfind(":");
	if (found != string::npos) {
		string line2 = line;
		line2.erase(found, (line2.length() - found));
		line2.erase(0, 5);
	//	cout << "line 2 = " << line2 << endl;
		c = stoi(line2);

		line.erase(0, found+1);
	//	cout << "line = " << line << endl;
		unsigned int n = stoi(line);

		return n;
	}
}

void SendToFile(string msg, bool useexfile, string filename) {
	if (useexfile) {
		fstream FILE("PrimeNumbers.txt", ios::app);
		FILE << msg;
		FILE.close();
	}
	else {
		fstream FILE(filename, ios::app);
		FILE << msg;
		FILE.close();
	}
}