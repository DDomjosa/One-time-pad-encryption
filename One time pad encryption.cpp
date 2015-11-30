#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <time.h>
#include <windows.h>
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
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
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
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
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
std::string inputFromFile(std::string fileName, bool plainText)
{
    std::ifstream read(fileName);
    std::stringstream buffer;
    buffer << read.rdbuf();
    std::string fileContents = buffer.str();
    if (!fileContents.length())
        std::cout << std::endl << "'" << fileName << "' doesn't exist or is empty!";
    if (!plainText)
        fileContents = base64_decode(fileContents);
    return fileContents;
}
std::string xorStrings(std::string& input1, std::string& input2)
{
    int strLength = input1.length() < input2.length() ? input1.length() : input2.length();
    std::string output;
    for (int i=0;i<strLength;i++)
        output += (input1[i] ^ input2[i]);
    return output;
}
unsigned char keyChar(std::mt19937& randomGenerator, std::uniform_int_distribution<int>& randomNumber)
{
    return (unsigned char)randomNumber(randomGenerator);
}
void ignore()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    std::string plaintext, key, ciphertext;
    bool repeat;
    std::cout << "DDomjosa's one time pad encryption/decryption program" << std::endl;
    do
    {
        plaintext.clear();
        key.clear();
        ciphertext.clear();
        createFiles();
        std::cout << std::endl << "(1)Encryption;" << std::endl << "(2)Decryption;" << std::endl << "(3)Key generation: ";
        int choice1 = getInt(1, 3);
        switch (choice1)
        {
        case 1:
            {
                std::cout << std::endl << "Plain text:\t'Input\\(E)Plain text.txt'" << std::endl << "(1)Random key;" << std::endl << "(2)Key:\t'Input\\(E)Key.ddkey': ";
                int choice2 = getInt(1, 2);
                std::cout << std::endl << "Press ENTER after the files are ready! ";
                ignore();
                bool printKey;
                switch (choice2)
                {
                case 1:
                    {
                        plaintext = inputFromFile("Input\\(E)Plain text.txt", true);
                        if (plaintext.length())
                        {
                            for (int i=0;i<plaintext.length();i++)
                                key += keyChar(randomGenerator, randomNumber);
                            ciphertext = xorStrings(plaintext, key);
                        }
                        printKey = true;
                        break;
                    }
                case 2:
                    {
                        plaintext = inputFromFile("Input\\(E)Plain text.txt", true);
                        key = inputFromFile("Input\\(E)Key.ddkey", false);
                        if (plaintext.length() && key.length())
                            ciphertext = xorStrings(plaintext, key);
                        else
                        {
                            plaintext.clear();
                            key.clear();
                        }
                        printKey = false;
                        break;
                    }
                }
                if (plaintext.length())
                {
                    if (printKey)
                    {
                        std::cout << std::endl << "Key:\t\t'Output\\(E)Key.ddkey'" << std::endl << "Ciphertext:\t'Output\\(E)Ciphertext.ddkey' ";
                        key = base64_encode(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
                        std::ofstream keyOutput("Output\\(E)Key.ddkey");
                        keyOutput << key;
                        ciphertext = base64_encode(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.length());
                        std::ofstream ciphertextOutput("Output\\(E)Ciphertext.ddkey");
                        ciphertextOutput << ciphertext;
                    }
                    else
                    {
                        std::cout << std::endl << "Ciphertext:\t'Output\\(E)Ciphertext.ddkey' ";
                        ciphertext = base64_encode(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.length());
                        std::ofstream ciphertextOutput("Output\\(E)Ciphertext.ddkey");
                        ciphertextOutput << ciphertext;
                    }
                }
                break;
            }
        case 2:
            {
                std::cout << std::endl << "Key:\t\t'Input\\(D)Key.ddkey'" << std::endl << "Ciphertext:\t'Input\\(D)Ciphertext.ddkey' ";
                std::cout << std::endl << "Press ENTER after the files are ready! ";
                ignore();
                key = inputFromFile("Input\\(D)Key.ddkey", false);
                ciphertext = inputFromFile("Input\\(D)Ciphertext.ddkey", false);
                if (key.length() && ciphertext.length())
                    plaintext = xorStrings(key, ciphertext);
                else
                {
                    key.clear();
                    ciphertext.clear();
                }
                if (key.length())
                {
                    std::cout << std::endl << "Plain text:\t'Output\\(D)Plain text.txt' ";
                    std::ofstream plaintextOutput("Output\\(D)Plain text.txt");
                    plaintextOutput << plaintext;
                }
                break;
            }
        case 3:
            {
                std::cout << std::endl << "(1 - 128000000)Key's effective bytes: ";
                int choice3 = getInt(1, 128000000);
                std::cout << std::endl << "Key:\t\t'Output\\(R)Key.ddkey' ";
                for (int i=0;i<choice3;i++)
                    key += keyChar(randomGenerator, randomNumber);
                key = base64_encode(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
                std::ofstream keyOutput("Output\\(R)Key.ddkey");
                keyOutput << key;
                break;
            }
        }
        std::cout << std::endl << std::endl << "(1)Continue;" << std::endl << "(2)Exit: ";
        repeat = getInt(1, 2) == 1 ? true : false;
    }
    while (repeat);
    std::cout << std::endl << "Press ENTER to exit! ";
    ignore();
}
