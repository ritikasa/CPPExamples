#include <iostream>

#include <string>

#include <iomanip>

#include <fstream>

#include <filesystem>

using namespace std;


//Function prototypes
void initialize(int & zeroCount, int & oddCount, int & evenCount, int & counter, int & sum);

void getNumber(int & line, ofstream & outputFile, int & counter);

void classifyNumber(int num, int & zeroCount, int & oddCount, int & evenCount, int& sum);

void printResults(int zeroCount, int oddCount, int evenCount, int sum, float average, ofstream& outputFile);

int main() {
  //Variable declaration
  int counter; //loop control variable
  int number; //variable to store the new number
  int zeros; //variable to store the number of zeros
  int odds; //variable to store the number of odd integers
  int evens; //variable to store the number of even integers
  int sum; //variable to store the sum of all numbers
  float average; //variable to store average of all numbers
  string inputFileName; //variable to store input file's name
  string outputFileName; //variable to store output file's name

  initialize(zeros, odds, evens, counter, sum); //Step 1

  cout << "Please enter input file name: " << flush;

  cin >> inputFileName;

  ifstream inputFile(inputFileName);

  if (!inputFile) {
      cerr << "Error: Could not open file for reading" << endl;
      return 1;
  }

  cout << "Please enter output file name: " << flush;

  cin >> outputFileName;

  cin.ignore();

  if (filesystem::exists(outputFileName)) {
      cerr << "Output file already exists" << endl;
      inputFile.close();
      return 1;
  }

  ofstream outputFile(outputFileName);

  if (!outputFile) {
      cerr << "Error: Could not open file for writing" << endl;
      inputFile.close();
      return 1;
  }
 
  string line;

  while (getline(inputFile, line)) {
    if (line.empty()) {
        continue;
    }
    try {
      number = stoi(line);
    }
    catch (const exception& e) {
      cerr << e.what() << endl;
      inputFile.close();
      outputFile.close();
      return 1;
    }
    getNumber(number, outputFile, counter);
    classifyNumber(number, zeros, odds, evens, sum);
  }

  if (counter % 11 != 0) {
      outputFile << endl;
  }

  average = sum/(1.0*(odds + evens));

  printResults(zeros, odds, evens, sum, average, outputFile); //Step 4

  inputFile.close();
  outputFile.close();

  return 0;
}

void initialize(int & zeroCount, int & oddCount, int & evenCount, int & counter, int & sum) {
  zeroCount = 0;
  oddCount = 0;
  evenCount = 0;
  counter = 1;
  sum = 0;
}

void getNumber(int & line, ofstream & outputFile, int & counter) {
    outputFile << line << " " << flush;
    if (counter % 10 == 0) {
        outputFile << endl;
    }
    counter ++;
}

void classifyNumber(int num, int & zeroCount, int & oddCount, int & evenCount, int& sum) {
  sum += num;
  switch (num % 2) {
  case 0:
    evenCount++;
    if (num == 0)
      zeroCount++;
    break;
  case 1:
  case -1:
    oddCount++;
  } //end switch
} //end classifyNumber

void printResults(int zeroCount, int oddCount, int evenCount, int sum, float average, ofstream& outputFile) {
  outputFile << "\nThere are " << evenCount << " evens, " << "which includes " << zeroCount << " zeros" << endl;
  outputFile << "The number of odd numbers is: " << oddCount << endl;
  outputFile << "The sum of the numbers is: " << sum << endl;
  outputFile << "The average of the numbers is: " << average << endl;
} //end printResults
