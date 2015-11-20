// Halstead complexity - Swift.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "optional.h"
#include <windows.h>
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;
void deleteComments();
void findUniqueOperators();
void determineDictionaties();
void findUniqueNamesOfVariables();
void setColor(int text, int background);
void readFromFile(string *destinationString, string fileName);
void findVariables(string inputString, string *ArrayOfMatches);
void findOperators(string inputString, string *ArrayOfMatches);
void parseFunctionParameters(string inputString, string *ArrayOfMatches);
void printUnique(string arrayOfPrintingElements[RIGHT_ARRAY_BORDER], int printingElementsCounter);
int findAllExistingVariables(string inputString, string arrayOfElements[RIGHT_ARRAY_BORDER]);
string analyzedSourceCode;
string foundVariables[RIGHT_ARRAY_BORDER];
string foundOperators[RIGHT_ARRAY_BORDER];
string uniqueOperators[RIGHT_ARRAY_BORDER];
string uniqueVariableNames[RIGHT_ARRAY_BORDER];

int main()

{
	DETERMINE_RUSSIAN_CHARSET
	readFromFile(&analyzedSourceCode, FILE_OF_SOURCE);
	deleteComments();
	findVariables(analyzedSourceCode, foundVariables);
	findOperators(analyzedSourceCode, foundOperators);
	findUniqueOperators();
	determineDictionaties();
};

void readFromFile (string *destinationString, string fileName)
{
	ifstream fileOfCode(fileName);
	if (!fileOfCode.is_open())
		SAY_FILENAME_OPENING_FAILED
	else
	{
		SAY_FILENAME_OPENING_SUCEEDED
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
	regex commentPattern("[\/][\/].*|[\#].*|[\/][\*][^]*?[\*][\/]|[\"][^]*?[\"]");
	smatch searchResults;
	string deletedComments = analyzedSourceCode;
	while (regex_search(deletedComments, searchResults, commentPattern))
	{
		setColor(Green, Black);
		for (auto output : searchResults) cout << output<< endl;
		deletedComments = searchResults.suffix().str();
	}
	setColor(White, Black);
	SAY_COMMENTS_DELETED
	analyzedSourceCode = regex_replace(analyzedSourceCode, commentPattern, "");
}

void findVariables(string inputString, string *ArrayOfMatches)
{
	string analyzedStringOfSource = inputString;
	regex variablePattern("(var[ ]+|let[ ]+)([_A-Za-z][_A-Za-z0-9]*[ ]{0,3}[:=])");
	smatch searchResults;
	int i = 0;
	while (regex_search(analyzedStringOfSource, searchResults, variablePattern))
	{
		i++;
		for (auto output : searchResults) ArrayOfMatches[i - 1] = output;
		analyzedStringOfSource = searchResults.suffix().str();
	}
	totalCounter = i;
	parseFunctionParameters(analyzedSourceCode,foundVariables);
	numberOfUniqueVariables = totalCounter;
	DETERMINE_SEARCH_OF_VARIABLES
	for (int j = 0; j < numberOfUniqueVariables; j++)
	{
		ArrayOfMatches[j][ArrayOfMatches[j].length() - 1] = ' ';
		ArrayOfMatches[j].erase(ArrayOfMatches[j].find_last_not_of(" \n\r\t") + 1);
	}
	findUniqueNamesOfVariables();
	numberOfAllVariables = findAllExistingVariables(inputString,uniqueVariableNames);
	DETERMINE_END_OF_VARIABLES_SEARCH
	printUnique(foundVariables, numberOfUniqueVariables);
}

void parseFunctionParameters(string inputString, string *ArrayOfMatches)
{
	int numberOfFoundParameters = 0;
	int foundHeaderPosition = 0;
	string listOfParameters;
	string analyzedStringOfSource = inputString;
	regex funcHeaderPattern("func [_A-Za-z\d ]*[(]");
	regex parameterPattern("[_A-Za-z][_A-Za-z0-9]*[ ]*[:=]");
	smatch parseHeadersResults;
	smatch searchParametersResults;
	while (regex_search(analyzedStringOfSource, parseHeadersResults, funcHeaderPattern))
	{
		for (auto output : parseHeadersResults)
		{
			foundHeaderPosition = inputString.find(output);
			int parameterPosition = 0;
			int globalSourcePosition = foundHeaderPosition + output.length();
			listOfParameters = " ";
			while (inputString[globalSourcePosition]!=')')
			{
				listOfParameters += inputString[globalSourcePosition];
				parameterPosition++;
				globalSourcePosition++;
			}
			int i = 0;
			while (regex_search(listOfParameters, searchParametersResults, parameterPattern))
			{
				i++;
				for (auto output : searchParametersResults) ArrayOfMatches[totalCounter + numberOfFoundParameters + i - 1] = output;
				listOfParameters = searchParametersResults.suffix().str();
			}
			numberOfFoundParameters += i;
		}
		analyzedStringOfSource = parseHeadersResults.suffix().str();

	}
	totalCounter += numberOfFoundParameters;

}

int findAllExistingVariables(string inputString, string arrayOfElements[RIGHT_ARRAY_BORDER])
{
	int matchPosition, numberOfMatches = 0;
	string analyzedStringOfSource = inputString;
	for (int i = 0; i < uniqueNamesCounter;i++)
	{
		analyzedStringOfSource = inputString;
		do
		{
			matchPosition = analyzedStringOfSource.find(arrayOfElements[i]);
			if (matchPosition != std::string::npos)
			{
				IF_VARIABLE_IS_VALID
					numberOfMatches++;
				analyzedStringOfSource.replace(matchPosition, arrayOfElements[i].length(), "");
			}
		} while (matchPosition != std::string::npos);
	}
	return numberOfMatches;
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
	numberOfUniqueOperators = uniqueOperatorsCounter;
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
				DETERMINE_SEARCH_OF_OPERATORS
				string analyzedStringOfSource = inputString;
				regex operatorPattern("[.][.][.]|[.][.][<]|[+][+]|[-][-]|[&][&]|[<][<]|[>][>]|[=][=]|[+][=]|[-][=]|[!][=]|[>][=]|[<][=]|[|][|]|[+]|[-]|[%]|[^/][/][^/]|[>]|[*]|[<]|[!]|[=]|[,]|[;]|[~]|if|else|print|return|switch|[|]|for|while|[?][a-zA-z0-9 _.!]*[:][a-zA-z0-9 _.!]*");
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
	DETERMINE_END_OF_OPERATORS_SEARCH
		numberOfAllOperators = totalCounter;
}

void findUniqueNamesOfVariables()
{
	for (int i = 0; i < numberOfUniqueVariables;i++)
	{
		bool unique = true;
		int j = 0;
		while (j < uniqueNamesCounter)
		{
			if (foundVariables[i] == uniqueVariableNames[j])
				unique = false;
			j++;
		}
		if (unique)
		{
			uniqueVariableNames[uniqueNamesCounter] = foundVariables[i];
			uniqueNamesCounter++;
		}
	}
}

void determineDictionaties()
{
	int programmDictionary = numberOfUniqueVariables + numberOfUniqueOperators;
	int programmLength = numberOfAllVariables + numberOfAllOperators;
	double volumeOfProgramm = (double)programmLength * log2((double)programmDictionary);
	double theoreticalLength = numberOfUniqueOperators*log2(numberOfUniqueOperators) + numberOfUniqueVariables*log2(numberOfUniqueVariables);
	int theoreticalDictionary = numberOfUniqueOperators + 1;
	double theoreticalVolumeOfProgramm = (double)theoreticalLength * log2((double)theoreticalDictionary);
	printf_s("\nn1 = %d, n2 = %d, n = %d\n", numberOfUniqueOperators, numberOfUniqueVariables, programmDictionary);
	printf_s("\nN1 = %d, N2 = %d, N = %d\n", numberOfAllOperators, numberOfAllVariables, programmLength);
	printf_s("\nV = %f\n", volumeOfProgramm);
	printf_s("\nN* = %f\n", theoreticalLength);
	printf_s("\nV* = %f\n", theoreticalVolumeOfProgramm);
	printf_s("\nV*/V = %f\n", theoreticalVolumeOfProgramm / volumeOfProgramm);
}
void printUnique(string arrayOfPrintingElements[RIGHT_ARRAY_BORDER], int printingElementsCounter)
{
	printf_s(UNIQUE_ELEMENTS_QUANTITY, printingElementsCounter);
	for (int i = 0; i < printingElementsCounter; i++)
		SHOW_ELEMENT
}

void setColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}