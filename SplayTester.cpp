#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <chrono>

#include "Splaytree.cpp"

using namespace std;

#define usage(name) cout << "Usage: " << name << " (-h -i -c -r -A -I -F -D) <number of operations> (-h for help)" << endl;

#define AFlag 0x01
#define IFlag 0x02
#define FFlag 0x04
#define DFlag 0x08
#define rFlag 0x10
#define cFlag 0x20
#define iFlag 0x40

struct operation{
	string op;
	int value;
};

void helpText(string name);
vector<operation> parseOperations(string file);
void test(string file, uint8_t flags);

int main(int argc, char *argv[]){
	
	if(argc < 2){
		usage(argv[0]);
		return 1;
	}

	uint8_t flags = 0;
	string file = "out.txt";
	int size = 1000;
	char *args[20];
	int argCount = 1;
	args[0] = strdup("./CaseGenerator");
	

	for(int i = 1; i < argc; i++){
		switch(argv[i][1]){
		case 'h':
			helpText(argv[0]);
			return 0;
			break;
		case 'i':
			file = argv[++i];
			flags |= iFlag;
			break;
		case 'c':
			flags |= cFlag;
			args[argCount++] = strdup("-c");
			break;
		case 'r':
			args[argCount++] = strdup("-r");
			flags |= rFlag;
			break;
		case 'A':
			args[argCount++] = strdup("-a");
			flags |= AFlag;
			break;
		case 'I':
			args[argCount++] = strdup("-i");
			flags |= IFlag;
			break;
		case 'F':
			args[argCount++] = strdup("-f");
			flags |= FFlag;
			break;
		case 'D':
			args[argCount++] = strdup("-d");
			flags |= DFlag;
			break;
		}
	}
	args[argCount++] = strdup(argv[argc-1]);
	args[argCount++] = NULL;
	if(file == "out.txt"){
		pid_t pid = fork();
		if(pid == 0){
			cout << "Generating Cases..." << endl;
			execvp("./CaseGenerator", args);
		}
		else{
			waitpid(-1, NULL, 0);
		}
	}
	cout << "Finished creating cases" << endl;
	test(file, flags);
	


	return 0;
	
}

void test(string file, uint8_t flags){
	vector<operation> operations = parseOperations(file);
	Splaytree<int> tree;
	chrono::microseconds time(0);
	for(int i = 0; i < operations.size(); i++){
		if(operations[i].op == "i"){
			auto ini = chrono::high_resolution_clock::now();
			tree.insert(operations[i].value);
			auto fin = chrono::high_resolution_clock::now();
			time +=  chrono::duration_cast<chrono::microseconds>(fin - ini);;
		}
		else if(operations[i].op == "f"){
			auto ini = chrono::high_resolution_clock::now();
			tree.find(operations[i].value);
			auto fin = chrono::high_resolution_clock::now();
			time +=  chrono::duration_cast<chrono::microseconds>(fin - ini);;
		}
		else if(operations[i].op == "d"){
			auto ini = chrono::high_resolution_clock::now();
			tree.remove(operations[i].value);
			auto fin = chrono::high_resolution_clock::now();
			time +=  chrono::duration_cast<chrono::microseconds>(fin - ini);;
		}
	}
	cout << "Time(microseconds): " << time.count() << endl;
	cout << "Operations: " << operations.size() << endl;
	cout << "Average time: " << float(time.count()/operations.size()) << endl;
	if(flags & cFlag)
		cout << "Type: Normal distribution" << endl;
	else if(flags & rFlag)
		cout << "Type: Random distribution" << endl;
	if(flags & AFlag)
		cout << "Operations: Random" << endl;
	else if(flags & IFlag)
		cout << "Operations: Insert" << endl;
	else if(flags & FFlag)
		cout << "Operations: Find" << endl;
	else if(flags & DFlag)
		cout << "Operations: Remove" << endl;
}

vector<operation> parseOperations(string file){
	vector<operation> operations;
	ifstream read(file);
	if(!read.is_open()){
		cout << "Error opening file" << endl;
		exit(1);
	}
	string line;
	while(getline(read, line)){
		operation op;
		op.op = line[0];
		op.value = stoi(line.substr(2));
		operations.push_back(op);
	}
	read.close();
	return operations;
}

void helpText(string name){
	usage(name);
	cout << "Options: (default is a test with 1000 random operations and random numbers)" << endl;
	cout << "-h: help" << endl;
	cout << "-i <file>: select input file" << endl;
	cout << "-c runs the tests with numbers following a normal distribution" << endl;
	cout << "-r runs the tests with random numbers" << endl;
	cout << "-A runs the tests with random operations" << endl;
	cout << "-I runs the tests with insert operations" << endl;
	cout << "-F runs the tests with find operations" << endl;
	cout << "-D runs the tests with remove operations" << endl;
}