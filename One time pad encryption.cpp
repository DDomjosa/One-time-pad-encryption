#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
#include <windows.h>
std::string base64_decode(std::string const&);
static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
bool inputFromFile(std::string fileName, std::vector<unsigned char>& chars, bool plainText)
{
    char input;
    std::ifstream read(fileName);
    while (read.get(input))
        chars.push_back(input);
    if (!plainText)
    {
        std::string base64String(chars.begin(), chars.end());
        chars.clear();
        std::string rawString = base64_decode(base64String);
        base64String.clear();
        std::copy(rawString.begin(), rawString.end(), std::back_inserter(chars));
    }
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
static inline bool is_base64(unsigned char c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
}
std::string base64_decode(std::string const& encoded_string)
{
    size_t in_len = encoded_string.size(), i = 0, j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;
    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
    {
        char_array_4[i++] = encoded_string[in_];
        in_++;
        if (i == 4)
        {
            for (i=0;i<4;i++)
                char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            for (i=0;i<3;i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    if (i)
    {
        for (j=i;j<4;j++)
            char_array_4[j] = 0;
        for (j=0;j<4;j++)
            char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        for (j=0;j<i-1;j++)
            ret += char_array_3[j];
    }
    return ret;
}
std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len)
{
    std::string ret;
    int i = 0, j = 0;
    unsigned char char_array_3[3], char_array_4[4];
    while (in_len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for (i=0;i<4;i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    if (i)
    {
        for(j=i;j<3;j++)
            char_array_3[j] = '\0';
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        for (j=0;j<i+1;j++)
            ret += base64_chars[char_array_4[j]];
        while (i++<3)
            ret += '=';
    }
    return ret;
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
    temp.open("Output\\(R)Key.ddkey", std::ios::app);
    temp.close();
}
int main()
{
    std::mt19937 randomGenerator(time(NULL));
    std::uniform_int_distribution<int> randomNumber(0, 255);
    std::vector<unsigned char> plainTextChars, keyChars, ciphertextChars;
    bool go;
    do
    {
        plainTextChars.clear();
        keyChars.clear();
        ciphertextChars.clear();
        createFiles();
        std::cout << "(1)Encryption;" << std::endl << "(2)Decryption;" << std::endl << "(3)Key generation: ";
        int choice1 = getInt(1, 3);
        switch (choice1)
        {
        case 1:
            {
                std::cout << std::endl << "Plain text: 'Input\\(E)Plain text.txt'" << std::endl << "(1)Random key;" << std::endl << "(2)Key: 'Input\\(E)Key.ddkey': ";
                int choice2 = getInt(1, 2);
                std::cout << std::endl << "Press ENTER after the files are ready! ";
                ignore();
                bool printKey;
                switch (choice2)
                {
                case 1:
                    {
                        if (inputFromFile("Input\\(E)Plain text.txt", plainTextChars, true))
                        {
                            for (int i=0;i<plainTextChars.size();i++)
                                keyChars.push_back(keyChar(randomGenerator, randomNumber));
                            xorVectors(plainTextChars, keyChars, ciphertextChars);
                            printKey = true;
                        }
                        else
                            plainTextChars.clear();
                        break;
                    }
                case 2:
                    {
                        if ((inputFromFile("Input\\(E)Plain text.txt", plainTextChars, true)) && (inputFromFile("Input\\(E)Key.ddkey", keyChars, false)))
                        {
                            xorVectors(plainTextChars, keyChars, ciphertextChars);
                            printKey = false;
                        }
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
                    if (printKey)
                    {
                        std::cout << std::endl << "Key:\t\t'Output\\(E)Key.ddkey'" << std::endl << "Ciphertext:\t'Output\\(E)Ciphertext.ddkey'";
                        std::ofstream keyPrint("Output\\(E)Key.ddkey"), ciphertextPrint("Output\\(E)Ciphertext.ddkey");
                        std::string rawKey(keyChars.begin(), keyChars.end());
                        keyChars.clear();
                        std::string base64Key = base64_encode(reinterpret_cast<const unsigned char*>(rawKey.c_str()), rawKey.length());
                        rawKey.clear();
                        keyPrint << base64Key;
                        std::string rawCiphertext(ciphertextChars.begin(), ciphertextChars.end());
                        ciphertextChars.clear();
                        std::string base64Ciphertext = base64_encode(reinterpret_cast<const unsigned char*>(rawCiphertext.c_str()), rawCiphertext.length());
                        rawCiphertext.clear();
                        ciphertextPrint << base64Ciphertext;
                    }
                    else
                    {
                        std::cout << std::endl << "Ciphertext:\t'Output\\(E)Ciphertext.ddkey'";
                        std::ofstream ciphertextPrint("Output\\(E)Ciphertext.ddkey");
                        std::string rawCiphertext(ciphertextChars.begin(), ciphertextChars.end());
                        ciphertextChars.clear();
                        std::string base64Ciphertext = base64_encode(reinterpret_cast<const unsigned char*>(rawCiphertext.c_str()), rawCiphertext.length());
                        rawCiphertext.clear();
                        ciphertextPrint << base64Ciphertext;
                    }
                }
                break;
            }
        case 2:
            {
                std::cout << std::endl << "Key: 'Input\\(D)Key.ddkey';" << std::endl << "Ciphertext: 'Input\\(D)Ciphertext.ddkey'.";
                std::cout << std::endl << "Press ENTER after the files are ready! ";
                ignore();
                if ((inputFromFile("Input\\(D)Key.ddkey", keyChars, false)) && (inputFromFile("Input\\(D)Ciphertext.ddkey", ciphertextChars, false)))
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
                break;
            }
        case 3:
            {
                std::cout << std::endl << "(1 - 100000000)Key's effective characters: ";
                int choice3 = getInt(1, 100000000);
                std::cout << std::endl << "Key:\t\t'Output\\(R)Key.ddkey'";
                for (int i=0;i<choice3;i++)
                    keyChars.push_back(keyChar(randomGenerator, randomNumber));
                std::ofstream keyPrint("Output\\(R)Key.ddkey");
                std::string rawKey(keyChars.begin(), keyChars.end());
                keyChars.clear();
                std::string base64Key = base64_encode(reinterpret_cast<const unsigned char*>(rawKey.c_str()), rawKey.length());
                rawKey.clear();
                keyPrint << base64Key;
                break;
            }
        }
        std::cout << std::endl << std::endl << "(1)Continue;" << std::endl << "(2)Exit: ";
        go = getInt(1, 2) == 1 ? true : false;
        std::cout << std::endl;
    }
    while (go);
    std::cout << "Press ENTER to exit! ";
    ignore();
}
