#include <iostream>     
#include <fstream>      
#include <vector>       
#include <iomanip>      
#include <cstdint>      

uint32_t H[8] = { 
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 
};


uint32_t K[8] = { 
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5
};


uint32_t rotateRight(uint32_t value, int bits) {
    return (value >> bits) | (value << (32 - bits));
}


std::vector<uint8_t> padMessage(const std::string& message) {
    std::vector<uint8_t> data(message.begin(), message.end()); 
    data.push_back(0x80);  

    
    while ((data.size() * 8) % 512 != 448) {
        data.push_back(0x00);
    }

    
    uint64_t bitLength = message.size() * 8;
    for (int i = 7; i >= 0; i--) {
        data.push_back((bitLength >> (i * 8)) & 0xFF);
    }

    return data; 
}


void sha256(const std::string& message) {
    std::vector<uint8_t> paddedMessage = padMessage(message); // Get padded message

    
    for (size_t i = 0; i < paddedMessage.size(); i += 64) {
        uint32_t w[64] = {0};  // SHA-256 message schedule

    
        for (int j = 0; j < 16; j++) {
            w[j] = (paddedMessage[i + j * 4] << 24) | 
                   (paddedMessage[i + j * 4 + 1] << 16) | 
                   (paddedMessage[i + j * 4 + 2] << 8) | 
                   (paddedMessage[i + j * 4 + 3]);
        }

       
        uint32_t a = H[0], b = H[1], c = H[2], d = H[3];
        uint32_t e = H[4], f = H[5], g = H[6], h = H[7];

       
        for (int j = 0; j < 64; j++) {
            uint32_t S1 = rotateRight(e, 6) ^ rotateRight(e, 11) ^ rotateRight(e, 25);
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = h + S1 + ch + K[j] + w[j];
            uint32_t S0 = rotateRight(a, 2) ^ rotateRight(a, 13) ^ rotateRight(a, 22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

       
        H[0] += a; H[1] += b; H[2] += c; H[3] += d;
        H[4] += e; H[5] += f; H[6] += g; H[7] += h;
    }
}


void printHash() {
    for (int i = 0; i < 8; i++) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << H[i];
    }
    std::cout << std::endl;
}

std::string readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) { 
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return ""; 
    }

    
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close(); 
    return content;
}


int main() {
    int choice;
    std::cout << "Choose input method:\n";
    std::cout << "1. Enter text manually\n";
    std::cout << "2. Read from file\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;
    std::cin.ignore(); 

    std::string input;
    if (choice == 1) {
        std::cout << "Enter message: ";
        std::getline(std::cin, input);
    } else if (choice == 2) {
        std::string filename;
        std::cout << "Enter file path: ";
        std::getline(std::cin, filename);
        input = readFile(filename);
        if (input.empty()) return 1; // Exit if file reading fails
    } else {
        std::cout << "Invalid choice.\n";
        return 1;
    }

    sha256(input); 
    std::cout << "SHA-256 Hash: ";
    printHash(); // Print hash output

    return 0;
}
