#include <iostream> 
#include <fstream> 
#include <vector> 
#include <iomanip> 
#include <cstdint> 
#include <string> 

// SHA-256 constants(64 fixed values used in the compression function)

const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// SHA-256 initial hash values(first 32 bits of the fractional parts of square roots of the first 8 primes)
uint32_t H[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

// Rotate right function 
uint32_t rotateRight(uint32_t value, int bits) {
    return (value >> bits) | (value << (32 - bits));
}

// SHA-256 padding function(Function to pad the message so that its length is a multiple of 512 bits)
std::vector<uint8_t> padMessage(const std::string& message) {
    std::vector<uint8_t> data(message.begin(), message.end());
    data.push_back(0x80); 

    // Append 0 ≤ k < 512 bits of '0', so that the resulting message length (in bits) is congruent to 448 (mod 512)
    while ((data.size() * 8 + 64) % 512 != 0) {
        data.push_back(0x00);
    }

    // Append the original length in bits at the end of the message (big-endian)
    uint64_t bitLength = message.size() * 8;
    for (int i = 7; i >= 0; i--) {
        data.push_back((bitLength >> (i * 8)) & 0xFF);
    }

    return data;
}

// main function to compute SHA-256 compression function
void sha256(const std::string& message) {
    std::vector<uint8_t> paddedMessage = padMessage(message); 

   
    for (size_t i = 0; i < paddedMessage.size(); i += 64) {
        uint32_t w[64] = {0};

        
        for (int j = 0; j < 16; j++) {
            w[j] = (paddedMessage[i + j * 4] << 24) |
                   (paddedMessage[i + j * 4 + 1] << 16) |
                   (paddedMessage[i + j * 4 + 2] << 8) |
                   (paddedMessage[i + j * 4 + 3]);
        }

        // Expand 16 words into 64 words
        for (int j = 16; j < 64; j++) {
            uint32_t s0 = rotateRight(w[j - 15], 7) ^ rotateRight(w[j - 15], 18) ^ (w[j - 15] >> 3);
            uint32_t s1 = rotateRight(w[j - 2], 17) ^ rotateRight(w[j - 2], 19) ^ (w[j - 2] >> 10);
            w[j] = w[j - 16] + s0 + w[j - 7] + s1;
        }

        // Initialize working variables with the current hash value
        uint32_t a = H[0], b = H[1], c = H[2], d = H[3];
        uint32_t e = H[4], f = H[5], g = H[6], h = H[7];

        // Main loop of SHA-256 compression function
        for (int j = 0; j < 64; j++) {
            uint32_t S1 = rotateRight(e, 6) ^ rotateRight(e, 11) ^ rotateRight(e, 25);
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = h + S1 + ch + K[j] + w[j];
            uint32_t S0 = rotateRight(a, 2) ^ rotateRight(a, 13) ^ rotateRight(a, 22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;

            //Update working variables
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        // updating hash values 
        H[0] += a;
        H[1] += b;
        H[2] += c;
        H[3] += d;
        H[4] += e;
        H[5] += f;
        H[6] += g;
        H[7] += h;
    }
}

// Print the SHA-256 hash
void printHash() {
    for (int i = 0; i < 8; i++) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << H[i];
    }
    std::cout << std::endl;
}

// Read a file into a string
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
// main function to compute Sha 256 hash
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
        if (input.empty()) return 1;
    } else {
        std::cout << "Invalid choice.\n";
        return 1;
    }

    sha256(input);
    std::cout << "SHA-256 Hash: ";
    printHash();

    return 0;
}
