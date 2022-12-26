#include <iostream>

#define usage(name) cout << "Usage: " << name << " (-h -r -c -o) <dataset size> (-h for help)" << endl;


using namespace std;

void helpText(string name);
void generateCases(string file, int size, int type);

auto main(int argc, char **argv) -> int
{
	if(argc < 2 ){
		usage(argv[0]);
		return 1;
	}
	uint8_t flags = 0;
	switch(argv[1][1]){
		case 'h':
			helpText(argv[0]);
			break;
		case 'n':
			generateCases("out.txt", atoi(argv[2]), flags);
			break;
		case 'a':
			generateCases("out.txt", atoi(argv[2]), flags);
			break;
		case 'i':
			generateCases("out.txt", atoi(argv[2]), flags);
			break;
		case 'f':
			generateCases("out.txt", atoi(argv[2]), flags);
			break;
		case 'd':
			generateCases("out.txt", atoi(argv[2]), flags);
			break;
		case 'r':
			generateCases("out.txt", atoi(argv[2]), flags);
			break;
		case 'c':
			generateCases("out.txt", atoi(argv[2]), flags);
			break;
		case 'o':
			generateCases(argv[2], atoi(argv[3]), flags);
			break;
		default:
			usage(argv[0]);
			break;
	}

	return 0;
}

void generateCases(string file, int size, uint8_t flags){
	
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