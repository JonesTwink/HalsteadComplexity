#pragma once
extern const char* FILE_OF_SOURCE = "Source.swift";
extern char* deletedPartsOfCode = "";
extern const char* UNIQUE_ELEMENTS_QUANTITY = "Уникальных - %d:\n";
extern int totalCounter = 0;
extern int numberOfUniqueVariables = 0;
extern int numberOfUniqueOperators = 0;
extern int numberOfAllVariables = 0;
extern int numberOfAllOperators = 0;
extern int uniqueNamesCounter = 0;
extern const int FIRST = 0;
extern const int SECOND = 1;
extern const int RIGHT_ARRAY_BORDER = 9999;
extern const int NUMBER_OF_STAGES = 2;
extern int Black = 0;
extern int Blue = 1;
extern int Green = 2;
extern int Cyan = 3;
extern int Red = 4;
extern int Magenta = 5;
extern int Brown = 6;
extern int LightGray = 7;
extern int DarkGray = 8;
extern int LightBlue = 9;
extern int LightGreen = 10;
extern int LightCyan = 11;
extern int LightRed = 12;
extern int LightMagenta = 13;
extern int Yellow = 14;
extern int White = 15;
#define SAY_FILENAME_OPENING_FAILED   cout << "Файл " + fileName + " не может быть открыт!" << endl;
#define SAY_FILENAME_OPENING_SUCEEDED cout << "Код успешно считан из файла " + fileName << endl;
#define SAY_COMMENTS_DELETED cout << "Эти участки кода были помечены как комментарии и строковые константы.\n" << endl;
#define SHOW_ELEMENT {\
						cout << i + 1 << ". ";\
						setColor(Cyan, Black);\
						cout << arrayOfPrintingElements[i];\
						setColor(White, Black);\
						cout << endl;\
					 }
#define DETERMINE_SEARCH_OF_OPERATORS printf_s("\nИдёт поиск операторов...");
#define DETERMINE_SEARCH_OF_VARIABLES printf_s("Идёт поиск переменных...\n");
#define DETERMINE_END_OF_OPERATORS_SEARCH printf_s("\nПоиск окончен. Найдено %d операторов, процедур и разделителей.\n", totalCounter);
#define DETERMINE_END_OF_VARIABLES_SEARCH printf_s("Поиск переменных окончен. Всего %d переменных.\n", numberOfAllVariables);
#define DETERMINE_RUSSIAN_CHARSET setlocale(LC_ALL, "rus");
#define IF_VARIABLE_IS_VALID  if (((analyzedStringOfSource.compare(matchPosition + arrayOfElements[i].length(), 1, "]") == 0) |(analyzedStringOfSource.compare(matchPosition + arrayOfElements[i].length(), 1, ")") == 0) |(analyzedStringOfSource.compare(matchPosition + arrayOfElements[i].length(), 1, "--") == 0) |(analyzedStringOfSource.compare(matchPosition + arrayOfElements[i].length(), 1, "++") == 0) |(analyzedStringOfSource.compare(matchPosition + arrayOfElements[i].length(), 1, "-") == 0) |(analyzedStringOfSource.compare(matchPosition + arrayOfElements[i].length(), 1, "+") == 0) |(analyzedStringOfSource.compare(matchPosition + arrayOfElements[i].length(), 1, " ") == 0) | (analyzedStringOfSource.compare(matchPosition + arrayOfElements[i].length(), 1, ":") == 0) | (analyzedStringOfSource.compare(matchPosition + arrayOfElements[i].length(), 1, "\n") == 0)| (analyzedStringOfSource.compare(matchPosition + arrayOfElements[i].length(), 1, "=") == 0))&&((analyzedStringOfSource.compare(matchPosition - 1, 1, " ") == 0) | (analyzedStringOfSource.compare(matchPosition - 1, 1, "\n") == 0) | (analyzedStringOfSource.compare(matchPosition -1, 1, "(") == 0)| (analyzedStringOfSource.compare(matchPosition -1, 1, "++") == 0)| (analyzedStringOfSource.compare(matchPosition -1, 1, "--") == 0)| (analyzedStringOfSource.compare(matchPosition -1, 1, ";") == 0)| (analyzedStringOfSource.compare(matchPosition -1, 1, "\t") == 0)| (analyzedStringOfSource.compare(matchPosition -1, 1, "+") == 0)| (analyzedStringOfSource.compare(matchPosition -1, 1, "-") == 0)| (analyzedStringOfSource.compare(matchPosition -1, 1, "*") == 0)| (analyzedStringOfSource.compare(matchPosition -1, 1, "=") == 0)| (analyzedStringOfSource.compare(matchPosition -1, 1, "[") == 0)))
