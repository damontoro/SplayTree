#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>

#define usage(name) cout << "Usage: " << name << " (-h -r -c -n -a -i -d -f -o) <dataset size> (-h for help)" << endl;

#define nFlag 0x01
#define aFlag 0x02
#define iFlag 0x04
#define fFlag 0x08
#define dFlag 0x10
#define rFlag 0x20
#define cFlag 0x40
#define oFlag 0x80


using namespace std;

void helpText(string name);
void generateCases(string file, int size, uint8_t flags);
vector<int> generateNumbers(int size, bool type);

const string OPERATIONS[3] = {"i", "f", "d"};
default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

auto main(int argc, char **argv) -> int
{
	if(argc < 2 ){
		usage(argv[0]);
		return 1;
	}

	uint8_t flags = 0;
	string out = "out.txt";

	for(int i = 1; i < argc - 1; i++){
		switch(argv[i][1]){
		case 'h':
			helpText(argv[0]);
			return 0;
			break;
		case 'n':
			flags |= nFlag;
			break;
		case 'a':
			flags |= aFlag;
			break;
		case 'i':
			flags |= iFlag;
			break;
		case 'f':
			flags |= fFlag;
			break;
		case 'd':
			flags |= dFlag;
			break;
		case 'r':
			flags |= rFlag;
			break;
		case 'c':
			flags |= cFlag;
			break;
		case 'o':
			out = argv[i + 1]; i++;
			break;
		default:
			usage(argv[0]);
			break;
		}
	}
	int size = atoi(argv[argc - 1]);
	if(size <= 0){
		usage(argv[0]);
		cout << "Invalid size" << endl;
		return 1;
	}
	generateCases(out, size, flags);
	return 0;
}

void generateCases(string file, int size, uint8_t flags){
	vector<int> numbers;
	numbers = generateNumbers(size, flags & cFlag);
	ofstream out(file);
	if(flags & nFlag){
		for(int i = 0; i < size; i++){
			out << numbers[i] << endl;
		}
	}
	else if(flags & aFlag){
		for(int i = 0; i < size; i++){
			out << OPERATIONS[generator()%3] << " " << numbers[i] << endl; 
		}
	}
	else if(flags & iFlag){
		for(int i = 0; i < size; i++){
			out << OPERATIONS[0] << " " << numbers[i] << endl;
		}
	}
	else if(flags & fFlag){
		for(int i = 0; i < size; i++){
			out << OPERATIONS[1] << " " << numbers[i] << endl;
		}
	}
	else if(flags & dFlag){
		for(int i = 0; i < size; i++){
			out << OPERATIONS[2] << " " << numbers[i] << endl;
		}
	}
	else{
		for(int i = 0; i < size; i++){
			out << OPERATIONS[generator()%3] << " " <<numbers[i] << endl; 
		}
	}
}

vector<int> generateNumbers(int size, bool type){
	vector<int> numbers;
	if(type){
		// Small deviation
		cout << "Generating numbers in a normal distribution" << endl;
		cout << "Mean: 0, Deviation: 10" << endl;
		normal_distribution<float> distribution(0, 100);
		for(int i = 0; i < size; i++){
			numbers.push_back(distribution(generator));
		}
	}
	else{
		// Random numbers
		cout << "Generating random numbers" << endl;
		for(int i = 0; i < size; i++){
			numbers.push_back(generator());
		}
	}
	return numbers;
}

void helpText(string name){
	usage(name);
	cout << "Options: (default is a file with random numbers and random operations)" << endl;
	cout << "-h: help" << endl;
	cout << "-n: Generates a file with only numbers" << endl;
	cout << "-a: Generates a file with all operations with random numbers" << endl;
	cout << "-i: Generates a file with insert operations with random numbers" << endl;
	cout << "-f: Generates a file with find operations with random numbers" << endl;
	cout << "-d: Generates a file with remove operations with random numbers" << endl;
	cout << "-r: The numbers are randomly generated" << endl;
	cout << "-c: The numbers are random but the deviation is small" << endl;
	cout << "-o: output file (default is out.txt)" << endl;
}