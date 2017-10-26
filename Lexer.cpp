//Name: Royce Nguyen
//E-mail: roycenguyen@csu.fullerton.edu
//Course: CPSC 323
//Assignment: Assignment 1

//This program is a lexical analyzer that parses a file written in the programming language RAT17F and outputs its tokens and token types
//Language MUST be inputted into the file "RAT17F.txt" in order for program to parse the file.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char c, word[15];
ifstream myFile("RAT17F.txt");

char parseChar()	// Parses the file one character every time it is called
{
	c = myFile.get();
	return c;
} // End of parseChar

bool isOperator()	// Checks if character qualifies as an operator
{
	char operators[] = { '<=', '>=', '+', '-', '==', '=', '/', '*', '<', '>', '%', ':' };
	for (int i = 0; i <= 12; i++)
	{
		if (c == operators[i])
		{
			return true;
		}
	}
	return false;
} // End of isOperator

bool isSeparator() // Checks if character qualifies as a separator
{
	char separators[] = { '{', '}', '(', ')', ',', ';' };
	for (int i = 0; i <= 5; i++)
	{		
		if (c == separators[i])
		{
			return true;
		}
	}
	return false;
} // End of isSeparator

bool isKeyword(char word[])		// Checks if character is in a keyword
{
	char keywords[6][10] = { "int", "if", "fi", "while", "read", "write" };
	for (int i = 0; i <= 32; i++)
	{
		if (strcmp(keywords[i], word) == 0)
		{
			return true;
			break;
		}
	}

	return false;
} // End of isKeyword

bool isNum(char c)		// Checks if character is part of a number
{
	if (((c - '0') <= 9) && ((c - '0') >= 0))
	{
		return true;
	}
	return false;
} // End of isNum

void lexer()		//Returns tokens and their values (lexeme)
{
	int counter = 0;
	if (!myFile.is_open())
	{
		cout << "File 'RAT17F.txt' could not be opened." << endl;
	}

	cout << "Token\t\tLexeme" << endl;
	cout << "------------------------------" << endl;

	while (!myFile.eof())
	{
		parseChar();
		if (isOperator())				// Operators
		{
			cout << "Operator\t";
			if (c == '<' || '>' || '=' || ':')		// Checks two-character operators
			{
				cout << c;
				c = parseChar();
				if (c == '=')
				{
					cout << c;
					c = parseChar();
				}
			}
			cout << endl;

		}
		else if (isSeparator())					// Separators
		{
			cout << "Separator\t" << c << endl;
			if (c == '%')
			{
				cout << c << c << endl;
				parseChar();
				parseChar();
			}
			else if (c == '@')
			{
				cout << "Separator\t" << c << endl;
				parseChar();
			}
		}
		else if (isNum(c))				// Numbers
		{
			cout << "Number\t\t";
			while (((c - '0') <= 9) && ((c - '0') >= 0))
			{
				cout << c - '0';
				c = parseChar();
				if (c == '.')
				{
					cout << c;
					c = parseChar();
				}
			}
			cout << endl;
		}
		else if (isalnum(c) || c == '#')		// Checks string
		{
			word[counter++] = c;	// Moves character into string array
		}
		else if ((c == ' ' || c == '\n') && (counter != 0))	// Keywords and Identifiers
		{
			word[counter] = '\0';
			counter = 0;

			if (isKeyword(word))
			{
				cout << "Keyword\t\t" << word << endl;
			}
			else
			{
				cout << "Identifier\t" << word << endl;
			}
		}
	}
} // End of lexer

int main()
{
	
	lexer();

	getchar();
	system("pause");
	return 0;
}  // End of main