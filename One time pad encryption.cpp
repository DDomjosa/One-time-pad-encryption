#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
#include <windows.h>
bool inputFromFile(std::string fileName, std::vector<unsigned char>& chars)
{
    char input;
    std::ifstream read(fileName);
    while (read.get(input))
        chars.push_back(input);
    if (!chars.size())
    {
        std::cout << std::endl << "'" << fileName << "' doesn't exist or is empty!";
        return false;
    }
    else
        return true;
}
int getInt(int minimum, int maximum)
{
    std::string line;
	int number;
	while (std::getline(std::cin, line))
	{
		std::istringstream is(line);
		if ((is >> number) && !(is >> line) && (number >= minimum) && (number <= maximum))
            return number;
        else
            std::cout << std::endl << "Error! Try again: ";
	}
}
unsigned char keyChar(std::mt19937& randomGenerator, std::uniform_int_distribution<int>& randomNumber)
{
    return (unsigned char)randomNumber(randomGenerator);
}
void ignore()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void xorVectors(std::vector<unsigned char>& input1, std::vector<unsigned char>& input2, std::vector<unsigned char>& output)
{
    int vecSize;
    if (input1.size() == input2.size())
        vecSize = input1.size();
    else
    {
        std::cout << std::endl << "Input lengths do not match! Using the lower one.";
        if (input1.size() < input2.size())
            vecSize = input1.size();
        else
            vecSize = input2.size();
    }
    for (int i=0;i<vecSize;i++)
        output.push_back(input1[i] ^ input2[i]);
}
void createFiles()
{
    CreateDirectory("Input", NULL);
    std::ofstream temp;
    temp.open("Input\\(D)Ciphertext.ddkey", std::ios::app);
    temp.close();
    temp.open("Input\\(D)Key.ddkey", std::ios::app);
    temp.close();
    temp.open("Input\\(E)Key.ddkey", std::ios::app);
    temp.close();
    temp.open("Input\\(E)Plain text.txt", std::ios::app);
    temp.close();
    CreateDirectory("Output", NULL);
    temp.open("Output\\(D)Plain text.txt", std::ios::app);
    temp.close();
    temp.open("Output\\(E)Ciphertext.ddkey", std::ios::app);
    temp.close();
    temp.open("Output\\(E)Key.ddkey", std::ios::app);
    temp.close();
}
int main()
{
    std::mt19937 randomGenerator(time(NULL));
    std::uniform_int_distribution<int> randomNumber(0, 255);
    std::vector<unsigned char> plainTextChars, keyChars, ciphertextChars;
    createFiles();
    std::cout << "(1)Encryption;" << std::endl << "(2)Decryption: ";
    int choice1 = getInt(1, 2);
    switch (choice1)
    {
    case 1:
        {
            std::cout << std::endl << "Plain text: 'Input\\(E)Plain text.txt'" << std::endl << "(1)Random key;" << std::endl << "(2)Key: 'Input\\(E)Key.ddkey': ";
            int choice2 = getInt(1, 2);
            std::cout << std::endl << "Press ENTER after the files are ready! ";
            ignore();
            switch (choice2)
            {
            case 1:
                {
                    if (inputFromFile("Input\\(E)Plain text.txt", plainTextChars))
                    {
                        for (int i=0;i<plainTextChars.size();i++)
                            keyChars.push_back(keyChar(randomGenerator, randomNumber));
                        xorVectors(plainTextChars, keyChars, ciphertextChars);
                    }
                    else
                        plainTextChars.clear();
                    break;
                }
            case 2:
                {
                    if ((inputFromFile("Input\\(E)Plain text.txt", plainTextChars)) && (inputFromFile("Input\\(E)Key.ddkey", keyChars)))
                        xorVectors(plainTextChars, keyChars, ciphertextChars);
                    else
                    {
                        plainTextChars.clear();
                        keyChars.clear();
                    }
                    break;
                }
            }
            if (plainTextChars.size())
            {
                std::cout << std::endl << "Key:\t\t'Output\\(E)Key.ddkey'" << std::endl << "Ciphertext:\t'Output\\(E)Ciphertext.ddkey'";
                std::ofstream keyPrint("Output\\(E)Key.ddkey"), ciphertextPrint("Output\\(E)Ciphertext.ddkey");
                for (int i=0;i<keyChars.size();i++)
                    keyPrint << keyChars[i];
                for (int i=0;i<ciphertextChars.size();i++)
                    ciphertextPrint << ciphertextChars[i];
            }
            break;
        }
    case 2:
        {
            std::cout << std::endl << "Key: 'Input\\(D)Key.ddkey';" << std::endl << "Ciphertext: 'Input\\(D)Ciphertext.ddkey'.";
            std::cout << std::endl << "Press ENTER after the files are ready! ";
            ignore();
            if ((inputFromFile("Input\\(D)Key.ddkey", keyChars)) && (inputFromFile("Input\\(D)Ciphertext.ddkey", ciphertextChars)))
                xorVectors(keyChars, ciphertextChars, plainTextChars);
            else
            {
                keyChars.clear();
                ciphertextChars.clear();
            }
            if (keyChars.size())
            {
                std::cout << std::endl << "Plain text:\t'Output\\(D)Plain text.txt'";
                std::ofstream plainTextPrint("Output\\(D)Plain text.txt");
                for (int i=0;i<plainTextChars.size();i++)
                    plainTextPrint << plainTextChars[i];
            }
        }
    }
    std::cout << std::endl << std::endl << "Press ENTER to exit! ";
    ignore();
}
