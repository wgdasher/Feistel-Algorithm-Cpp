#include <iostream>
#include <fstream>
#include "poly.h"

const int m = 0x11B;
long size(std::ifstream &file);

int main(int argc, char *argv[]) {

    if (argc != 4) {
        perror("Incorrect input: required 3 arguments\n");
        return 1;
    }

    std::string fileName = argv[1];
    std::string key = argv[2];
    std::string mode = argv[3];

    int keyLength = key.length();
    bool padded = false;
    
    std::ifstream inputFile;
    std::ofstream outputFile;

    inputFile.open(fileName);

    //pad size if odd
    long fileSize = size(inputFile);
    if ((fileSize % 2) != 0) {
        outputFile.open(fileName, std::ios::app);
        outputFile << "#";
        outputFile.close();
        fileSize = size(inputFile);
        padded = true;
    }

    //create character buffer
    //iterate through
    char charBuff[2];
    for (std::streamsize i = 0; i < fileSize; i+=2) {
        if (!inputFile.is_open()) {
            std::cerr << "File failed to open\n";
        }

        inputFile.read(charBuff, 2);
        char LH = charBuff[0];
        char RH = charBuff[1];
        int round;
        for (round = 0; round < 16; ++round) {
            int copyRH = RH;
            int roundKey = (int)key[round % key.size()];
            RH = poly::multiply_galois(RH, roundKey, m);
            RH ^= LH;
            LH = copyRH;
        }
        //swap at end
        //append to textfile 
        int temp = LH;
        LH = RH;
        RH = temp;
        outputFile.open(fileName, std::ios::app);
        std::string newString;
        newString += static_cast<char>(LH);
        newString += static_cast<char>(RH);
        outputFile << newString;
        outputFile.close();
    }


}

long size(std::ifstream &file) {
    if (!file.is_open()) {
        std::cerr <<" Could not open file\n";
        return -1;
    }

    long count = 0;
    char ch;

    while (file.get(ch))
        count++;
    
    file.clear();
    file.seekg(0, std::ios::beg);
    return count;
}