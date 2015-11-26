#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
#include <windows.h>
#define alphabetSize 94
bool inputFromFile(std::string, bool, std::vector<int>&, std::vector<char>&, std::map<int, char>&, std::map<char, int>&);
void decryptText(std::vector<int>&, std::vector<int>&, std::vector<int>&, std::vector<char>&, std::map<int, char>&, std::map<char, int>&);
void encryptText(std::vector<int>&, std::vector<int>&, std::vector<int>&, std::vector<char>&, std::map<int, char>&, std::map<char, int>&);
void generateKey(std::mt19937&, std::uniform_int_distribution<int>&, std::vector<int>&, std::vector<char>&, std::vector<int>&, std::map<int, char>&, std::map<char, int>&);
bool decryption(std::vector<char>& plainTextChars, std::vector<char>& keyChars, std::vector<char>& encryptedTextChars, std::map<int, char>& alphabetChars, std::map<char, int>& alphabetValues)
{
    std::vector<int> plainTextValues, keyValues, encryptedTextValues;
    bool goodKey = inputFromFile("Input\\Key input decryption.txt", true, keyValues, keyChars, alphabetChars, alphabetValues);
    bool goodEncryptedText = inputFromFile("Input\\Encrypted text input decryption.txt", true, encryptedTextValues, encryptedTextChars, alphabetChars, alphabetValues);
    if (keyValues.size() != encryptedTextValues.size())
    {
        std::cout << "Key's length doesn't match encrypted text's length!" << std::endl;
        return false;
    }
    else if (goodKey && goodEncryptedText)
        decryptText(keyValues, encryptedTextValues, plainTextValues, plainTextChars, alphabetChars, alphabetValues);
    else
    {
        if (!goodKey)
            std::cout << "'Input\\Key input decryption.txt' is empty!" << std::endl;
        if (!goodEncryptedText)
            std::cout << "'Input\\Encrypted text input decryption.txt' is empty!" << std::endl;
    }
    return goodKey && goodEncryptedText;
}
bool encryption(std::mt19937& randomGenerator, std::uniform_int_distribution<int>& randomNumber, std::vector<char>& plainTextChars, std::vector<char>& keyChars, std::vector<char>& encryptedTextChars, std::map<int, char>& alphabetChars, std::map<char, int>& alphabetValues, bool fromFile)
{
    std::vector<int> plainTextValues, keyValues, encryptedTextValues;
    bool goodText = inputFromFile("Input\\Text input encryption.txt", false, plainTextValues, plainTextChars, alphabetChars, alphabetValues), goodKey;
    if (fromFile)
        goodKey = inputFromFile("Input\\Key input encryption.txt", true, keyValues, keyChars, alphabetChars, alphabetValues);
    else
    {
        generateKey(randomGenerator, randomNumber, plainTextValues, keyChars, keyValues, alphabetChars, alphabetValues);
        goodKey = true;
    }
    if (plainTextValues.size() != keyValues.size())
    {
        std::cout << "Key's length doesn't match text's length!" << std::endl;
        return false;
    }
    else if (goodText && goodKey)
        encryptText(plainTextValues, keyValues, encryptedTextValues, encryptedTextChars, alphabetChars, alphabetValues);
    else
    {
        if (!goodText)
            std::cout << "'Input\\Text input encryption.txt' is empty!" << std::endl;
        if (!goodKey)
            std::cout << "'Input\\Key input encryption.txt' is empty!" << std::endl;
    }
    return goodText && goodKey;
}
bool inputFromFile(std::string fileName, bool key, std::vector<int>& values, std::vector<char>& chars, std::map<int, char>& alphabetChars, std::map<char, int>& alphabetValues)
{
    char input;
    int character = 0;
    std::vector<int> illegalCharacters;
    std::ifstream read(fileName);
    while (read.get(input))
    {
        character++;
        if (input == '|' || input == ' ' || input == '\t')
        {
            if (key)
                chars.push_back('|');
            else
                chars.push_back(' ');
            values.push_back(alphabetValues[' ']);
            continue;
        }
        else if (input == '\\' || input == '\n')
        {
            if (key)
                chars.push_back('\\');
            else
                chars.push_back('\n');
            values.push_back(alphabetValues['\n']);
            continue;
        }
        else if (alphabetValues.count(input))
        {
            chars.push_back(input);
            values.push_back(alphabetValues[input]);
            continue;
        }
        else
            illegalCharacters.push_back(character);
    }
    if (illegalCharacters.size() < 623 && illegalCharacters.size())
    {
        if (illegalCharacters.size() == 1)
        {
            std::cout << illegalCharacters.size() << " illegal character has been found in '" << fileName;
            fileName.erase(0, 6);
            fileName.erase(fileName.end()-4, fileName.end());
            std::cout << "' and has been ignored, it will be put into 'Output\\Illegal characters '" << fileName << "' output.txt' as well. Number of that character in the file is: ";
        }
        else
        {
            std::cout << illegalCharacters.size() << " illegal characters have been found in '" << fileName;
            fileName.erase(0, 6);
            fileName.erase(fileName.end()-4, fileName.end());
            std::cout << "' and have been ignored, they will be put into 'Output\\Illegal characters '" << fileName << "' output.txt' as well. Numbers of those characters in the file are: ";
        }
        std::ofstream illegalCharactersPrint("Output\\Illegal characters '" + fileName + "' output.txt");
        for (int i=0;i<illegalCharacters.size();i++)
        {
            std::cout << illegalCharacters[i] << " ";
            illegalCharactersPrint << illegalCharacters[i] << " ";
        }
        std::cout << std::endl;
    }
    else if (illegalCharacters.size())
    {
        std::cout << illegalCharacters.size() << " illegal characters have been found in '" << fileName;
        fileName.erase(0, 6);
        fileName.erase(fileName.end()-4, fileName.end());
        std::cout << "' and have been ignored, there are too many to display on screen, so they will be put into 'Output\\Illegal characters '" << fileName << "' output.txt'" << std::endl;
        std::ofstream illegalCharactersPrint("Output\\Illegal characters '" + fileName + "' output.txt");
        for (int i=0;i<illegalCharacters.size();i++)
            illegalCharactersPrint << illegalCharacters[i] << " ";
    }
    if (!values.size())
        return false;
    return true;
}
char keyChar(std::mt19937& randomGenerator, std::uniform_int_distribution<int>& randomNumber, std::map<int, char>& alphabetChars, std::map<char, int>& alphabetValues)
{
    int generatedNumber = randomNumber(randomGenerator);
    if (generatedNumber != alphabetValues[' '] && generatedNumber != alphabetValues['\n'])
        return alphabetChars[generatedNumber];
    else if (generatedNumber == alphabetValues[' '])
        return '|';
    else if (generatedNumber == alphabetValues['\n'])
        return '\\';
}
int getInt(std::string question, int minimum, int maximum)
{
    std::string line;
	int x;
	while((std::cout << question) && std::getline(std::cin, line))
	{
		std::istringstream is(line);
		if((is >> x) && !(is >> line) && (x >= minimum) && (x <= maximum))
            return x;
        else
            std::cerr << "Error! ";
	}
}
void createFiles()
{
    CreateDirectory("Input", NULL);
    std::ofstream temp;
    temp.open("Input\\Encrypted text input decryption.txt", std::ios::app);
    temp.close();
    temp.open("Input\\Key input decryption.txt", std::ios::app);
    temp.close();
    temp.open("Input\\Key input encryption.txt", std::ios::app);
    temp.close();
    temp.open("Input\\Text input encryption.txt", std::ios::app);
    temp.close();
    CreateDirectory("Output", NULL);
    temp.open("Output\\Encrypted text output.txt", std::ios::app);
    temp.close();
    temp.open("Output\\Key output.txt", std::ios::app);
    temp.close();
    temp.open("Output\\Plain text output.txt", std::ios::app);
    temp.close();
    temp.open("Output\\Illegal characters 'Encrypted text input decryption' output.txt", std::ios::app);
    temp.close();
    temp.open("Output\\Illegal characters 'Key input decryption' output.txt", std::ios::app);
    temp.close();
    temp.open("Output\\Illegal characters 'Key input encryption' output.txt", std::ios::app);
    temp.close();
    temp.open("Output\\Illegal characters 'Text input encryption' output.txt", std::ios::app);
    temp.close();
}
void decryptText(std::vector<int>& keyValues, std::vector<int>& encryptedTextValues, std::vector<int>& plainTextValues, std::vector<char>& plainTextChars, std::map<int, char>& alphabetChars, std::map<char, int>& alphabetValues)
{
    for (int i=0;i<encryptedTextValues.size();i++)
    {
        int valueDifference = encryptedTextValues[i] - keyValues[i];
        while (valueDifference < 0)
            valueDifference += alphabetSize;
        int tempValue = valueDifference % alphabetSize;
        plainTextValues.push_back(tempValue);
        plainTextChars.push_back(alphabetChars[tempValue]);
    }
}
void encryptText(std::vector<int>& plainTextValues, std::vector<int>& keyValues, std::vector<int>& encryptedTextValues, std::vector<char>& encryptedTextChars, std::map<int, char>& alphabetChars, std::map<char, int>& alphabetValues)
{
    for (int i=0;i<plainTextValues.size();i++)
    {
        int tempValue = (plainTextValues[i] + keyValues[i]) % alphabetSize;
        encryptedTextValues.push_back(tempValue);
        if (tempValue != alphabetValues[' '] && tempValue != alphabetValues['\n'])
        {
            encryptedTextChars.push_back(alphabetChars[tempValue]);
            continue;
        }
        else if (tempValue == alphabetValues[' '])
        {
            encryptedTextChars.push_back('|');
            continue;
        }
        else if (tempValue == alphabetValues['\n'])
        {
            encryptedTextChars.push_back('\\');
            continue;
        }
    }
}
void fillMaps(std::map<int, char>& alphabetChars, std::map<char, int>& alphabetValues)
{
    char tempAlphabetChars[] = " \nABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890/*-+=!?,.:;\"'`~@#$%^&_(){}<>[]";
    for (int i=0;i<alphabetSize;i++)
        alphabetValues[tempAlphabetChars[i]] = i;
    for (int i=0;i<alphabetSize;i++)
        alphabetChars[i] = tempAlphabetChars[i];
}
void generateKey(std::mt19937& randomGenerator, std::uniform_int_distribution<int>& randomNumber, std::vector<int>& plainTextValues, std::vector<char>& keyChars, std::vector<int>& keyValues, std::map<int, char>& alphabetChars, std::map<char, int>& alphabetValues)
{
    for (int i=0;i<plainTextValues.size();i++)
    {
        char tempChar = keyChar(randomGenerator, randomNumber, alphabetChars, alphabetValues);
        keyChars.push_back(tempChar);
        if (tempChar != '|' && tempChar != '\\')
        {
            keyValues.push_back(alphabetValues[tempChar]);
            continue;
        }
        else if (tempChar == '|')
        {
            keyValues.push_back(alphabetValues[' ']);
            continue;
        }
        else if (tempChar == '\\')
        {
            keyValues.push_back(alphabetValues['\n']);
            continue;
        }
    }
}
int main()
{
    std::cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << std::endl;
    std::cout << "|DDomjosa's one time pad encryption/decryption program|" << std::endl;
    std::cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << std::endl;
    std::cout << "Characters you can use with this program include the whole english alphabet in both upper and lower case letters, all arabic numerals, simple mathematical operations signs, most brackets, spaces ('|' will be converted into a space), tabs (will be converted into a space or a '|'), new lines (\"\\\" will be converted into a new line) and some more miscellaneous symbols. Any illegal characters this program encounters will be ignored." << std::endl << std::endl;
    std::map<int, char> alphabetChars;
    std::map<char, int> alphabetValues;
    fillMaps(alphabetChars, alphabetValues);
    std::mt19937 randomGenerator(time(NULL));
    std::uniform_int_distribution<int> randomNumber(0, alphabetSize-1);
    createFiles();
    int choice = getInt("To encrypt enter 1, to decrypt enter 2: ", 1, 2);
    switch (choice)
    {
    case 1:
    {
        std::cout << "The text you want to encrypt will be read from 'Input\\Text input encryption.txt' The results will be put in a folder named 'Output'" << std::endl;
        int case1choice = getInt("To use a randomly generated key enter 1, to read a key from 'Input\\Key input encryption.txt' enter 2: ", 1, 2);
        std::vector<char> plainTextChars, keyChars, encryptedTextChars;
        bool goodEncryption;
        switch (case1choice)
        {
        case 1:
        {
            std::cout << "Press ENTER after the file is ready! ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goodEncryption = encryption(randomGenerator, randomNumber, plainTextChars, keyChars, encryptedTextChars, alphabetChars, alphabetValues, false);
            break;
        }
        case 2:
        {
            std::cout << "Press ENTER after the files are ready! ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goodEncryption = encryption(randomGenerator, randomNumber, plainTextChars, keyChars, encryptedTextChars, alphabetChars, alphabetValues, true);
            break;
        }
        }
        if (goodEncryption)
        {
            bool print = true;
            if (plainTextChars.size() > 623)
                print = false;
            std::ofstream keyPrint("Output\\Key output.txt"), encryptedTextPrint("Output\\Encrypted text output.txt");
            std::cout << "Plain text:\t";
            if (!print)
                std::cout << "too long to display on screen!";
            for (int i=0;i<plainTextChars.size();i++)
            {
                if (print)
                    std::cout << plainTextChars[i];
            }
            std::cout << std::endl << "Key:\t\t";
            if (!print)
                std::cout << "too long to display on screen!";
            for (int i=0;i<keyChars.size();i++)
            {
                if (print)
                    std::cout << keyChars[i];
                keyPrint << keyChars[i];
            }
            std::cout << std::endl << "Encrypted text:\t";
            if (!print)
                std::cout << "too long to display on screen!";
            for (int i=0;i<encryptedTextChars.size();i++)
            {
                if (print)
                    std::cout << encryptedTextChars[i];
                encryptedTextPrint << encryptedTextChars[i];
            }
            std::cout << std::endl;
        }
        break;
    }
    case 2:
    {
        std::cout << "The text you want to decrypt will be read from 'Input\\Encrypted text input decryption.txt' and the key will be read from 'Input\\Key input decryption.txt'" << std::endl;
        std::cout << "The results will be put in a folder named 'Output'" << std::endl;
        std::vector<char> plainTextChars, keyChars, encryptedTextChars;
        std::cout << "Press ENTER after the files are ready! ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        bool goodDecryption = decryption(plainTextChars, keyChars, encryptedTextChars, alphabetChars, alphabetValues);
        if (goodDecryption)
        {
            bool print = true;
            if (plainTextChars.size() > 623)
                print = false;
            std::ofstream plainTextPrint("Output\\Plain text output.txt");
            std::cout << "Plain text:\t";
            if (!print)
                std::cout << "too long to display on screen!";
            for (int i=0;i<plainTextChars.size();i++)
            {
                if (print)
                    std::cout << plainTextChars[i];
                plainTextPrint << plainTextChars[i];
            }
            std::cout << std::endl << "Key:\t\t";
            if (!print)
                std::cout << "too long to display on screen!";
            for (int i=0;i<keyChars.size();i++)
            {
                if (print)
                    std::cout << keyChars[i];
            }
            std::cout << std::endl << "Encrypted text:\t";
            if (!print)
                std::cout << "too long to display on screen!";
            for (int i=0;i<encryptedTextChars.size();i++)
            {
                if (print)
                    std::cout << encryptedTextChars[i];
            }
            std::cout << std::endl;
        }
        break;
    }
    }
    std::cout << "Press ENTER to exit! ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
