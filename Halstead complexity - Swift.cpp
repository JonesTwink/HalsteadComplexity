// Halstead complexity - Swift.cpp: определяет точку входа для консольного приложения.
//
//TO DO: ПОИСК ПЕРЕМЕННЫХ ПАРАМЕТРОВ
//TO DO: ПОИСК ПЕРЕМЕННЫХ В СТРОКОВЫХ КОНСТАНТАХ
#include "stdafx.h"
#include "optional.h"
#include <windows.h>
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;
void deleteComments();
void findUniqueOperators();
void setColor(int text, int background);
void readFromFile(string *destinationString, string fileName);
void findVariables(string inputString, string *ArrayOfMatches);
void findOperators(string inputString, string *ArrayOfMatches);
void printUnique(string arrayOfPrintingElements[RIGHT_ARRAY_BORDER], int printingElementsCounter);
int findAllExistingVariables(string inputString);
string analyzedSourceCode;
string foundVariables[RIGHT_ARRAY_BORDER];
string foundOperators[RIGHT_ARRAY_BORDER];
string uniqueOperators[RIGHT_ARRAY_BORDER];

int main()
{
	setlocale(LC_ALL, "rus");
	readFromFile(&analyzedSourceCode, FILE_OF_SOURCE);
	deleteComments();
	//cout << analyzedSourceCode << endl;
	findVariables(analyzedSourceCode, foundVariables);
	findOperators(analyzedSourceCode, foundOperators);
	findUniqueOperators();
};

void readFromFile (string *destinationString, string fileName)
{
	ifstream fileOfCode(fileName);
	if ( !fileOfCode.is_open() )
		cout << "Файл " + fileName + " не может быть открыт!" << endl;
	else
	{
		cout << "Код успешно считан из файла ";
		cout << fileName << endl;
		while (fileOfCode)
		{
			fileOfCode.unsetf(std::ios_base::skipws);
			std::copy(istream_iterator< char >(fileOfCode), istream_iterator< char >(), std::back_inserter(*destinationString));
		}
		fileOfCode.close();
	}
}

void deleteComments()
{
	regex commentPattern("[\/][\/].*|[\#].*|[\/][\*][^]*?[\*][\/]|[\'][^]*?[\']");
	smatch searchResults;
	string deletedComments = analyzedSourceCode;
	cout << " Удалены:  \n\n";

	while (regex_search(deletedComments, searchResults, commentPattern))
	{
		for (auto output : searchResults) cout << output << "\n\n";
		deletedComments = searchResults.suffix().str();
	}
	cout << endl;
	analyzedSourceCode = regex_replace(analyzedSourceCode, commentPattern, "");
}

void findVariables(string inputString, string *ArrayOfMatches)
{
	string analyzedStringOfSource = inputString;
	regex variablePattern("(var[ ]+|let[ ]+)([_A-Za-z][_A-Za-z\d]*)");
	smatch searchResults;
	int i = 0;
	while (regex_search(analyzedStringOfSource, searchResults, variablePattern))
	{
		i++;
		for (auto output : searchResults) ArrayOfMatches[i - 1] = output;
		analyzedStringOfSource = searchResults.suffix().str();
	}
	totalCounter = i;
	numberOfUniqueVariables = totalCounter;
	printf_s("Идёт поиск переменных...\n");
	int numberOfAllVariables = findAllExistingVariables(inputString);
	printf_s("Поиск переменных окончен. Всего %d переменных.\n", numberOfAllVariables);
	printUnique(foundVariables,totalCounter);
}

int findAllExistingVariables(string inputString)
{
	int matchPosition, numberOfMatches = 0;
	string analyzedStringOfSource;
	for (int i = 0; i < numberOfUniqueVariables;i++)
	{
		analyzedStringOfSource = inputString;
		do
		{
			matchPosition = analyzedStringOfSource.find(foundVariables[i]);
			if (matchPosition != std::string::npos)
			{
				numberOfMatches++;
				analyzedStringOfSource.replace(matchPosition, foundVariables[i].length()," ");
			}
		} while (matchPosition != std::string::npos);
	}
	return numberOfMatches;
}

void findOperators(string inputString, string *ArrayOfMatches)
{
	totalCounter = 0;
	int i, foundFunctions;
	for (int currentStage = 0; currentStage < NUMBER_OF_STAGES; currentStage++)
	{
		switch (currentStage)
		{
			case FIRST:
			{
				string analyzedStringOfSource = inputString;
				regex operatorPattern("(func[ ]+)([_A-Za-z][_A-Za-z\d]*)");
				smatch searchResults;
				i = 0;
				while (regex_search(analyzedStringOfSource, searchResults, operatorPattern))
				{
					i++;
					for (auto output : searchResults) ArrayOfMatches[i - 1] = output;
					analyzedStringOfSource = searchResults.suffix().str();
				}
				foundFunctions = i;
			}
				break;
			case SECOND:
			{
				printf_s("\nИдёт поиск операторов...");
				string analyzedStringOfSource = inputString;
				regex operatorPattern("[.][.][.]|[.][.][<]|[+][+]|[-][-]|[&][&]|[<][<]|[>][>]|[=][=]|[+][=]|[-][=]|[!][=]|[>][=]|[<][=]|[|][|]|[+]|[-]|[%]|[^/][/][^/]|[>]|[*]|[<]|[!]|[=]|[,]|[~]|print|return |[?][a-zA-z0-9 _.!]*[:][a-zA-z0-9 _.!]*");
				smatch searchResults;
				i = 0;
				while (regex_search(analyzedStringOfSource, searchResults, operatorPattern))
				{
					i++;
					for (auto output : searchResults) ArrayOfMatches[foundFunctions + i - 1] = output;
					analyzedStringOfSource = searchResults.suffix().str();
				}
			}
				break;
		}
		totalCounter += i;
	}
	printf_s("\nПоиск окончен. Найдено %d операторов, процедур и разделителей.\n", totalCounter);
}

void findUniqueOperators()
{
	int uniqueOperatorsCounter = 0;
	for (int i = 0; i < totalCounter;i++)
	{
		bool unique = true;
		int j = 0;
		while (j < uniqueOperatorsCounter)
		{
			if (foundOperators[i] == uniqueOperators[j])
				unique = false;
			j++;
		}
		if (unique)
		{
			uniqueOperators[uniqueOperatorsCounter] = foundOperators[i];
			uniqueOperatorsCounter++;
		}
	}
	printUnique(uniqueOperators, uniqueOperatorsCounter);
}

void printUnique(string arrayOfPrintingElements[RIGHT_ARRAY_BORDER], int printingElementsCounter)
{
	printf_s("Уникальных - %d:\n", printingElementsCounter);
	for (int i = 0; i < printingElementsCounter;i++)
	{
		cout << i + 1 <<". ";
		setColor(Cyan, Black);
		cout << arrayOfPrintingElements[i];
		setColor(White, Black);
		cout << " \n";
	}
}

void setColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}