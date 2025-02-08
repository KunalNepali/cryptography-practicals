#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to prepare the key table (5x5 matrix)
void generateKeyTable(const string& key, char keyTable[5][5]) {
    string processedKey;
    vector<bool> alphabetUsed(26, false);

    // Process the key: remove duplicates and handle 'J'
    for (char ch : key) {
        ch = toupper(ch);
        if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
        if (!alphabetUsed[ch - 'A']) {
            processedKey += ch;
            alphabetUsed[ch - 'A'] = true;
        }
    }

    // Fill the key table with the processed key
    int idx = 0;
    for (char ch : processedKey) {
        keyTable[idx / 5][idx % 5] = ch;
        idx++;
    }

    // Fill the remaining spaces with other letters
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; // Skip 'J'
        if (!alphabetUsed[ch - 'A']) {
            keyTable[idx / 5][idx % 5] = ch;
            idx++;
        }
    }
}

// Function to preprocess the plaintext: handle 'J', insert 'X' between duplicate letters, and make even length
string preprocessPlaintext(const string& plaintext) {
    string processedText;
    for (char ch : plaintext) {
        if (ch == ' ') continue; // Remove spaces
        ch = toupper(ch);
        if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
        processedText += ch;
    }

    // Insert 'X' between duplicate letters in pairs
    for (size_t i = 0; i < processedText.length(); i += 2) {
        if (i + 1 < processedText.length() && processedText[i] == processedText[i + 1]) {
            processedText.insert(i + 1, "X");
        }
    }

    // If the length is odd, append 'X' at the end
    if (processedText.length() % 2 != 0) {
        processedText += 'X';
    }

    return processedText;
}

// Function to find the position of a character in the key table
void findPosition(char keyTable[5][5], char ch, int& row, int& col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyTable[i][j] == ch) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

// Function to encrypt a pair of characters
string encryptPair(char keyTable[5][5], char a, char b) {
    int row1, col1, row2, col2;
    findPosition(keyTable, a, row1, col1);
    findPosition(keyTable, b, row2, col2);

    if (row1 == row2) {
        // Same row: move right
        return string(1, keyTable[row1][(col1 + 1) % 5]) + keyTable[row2][(col2 + 1) % 5];
    } else if (col1 == col2) {
        // Same column: move down
        return string(1, keyTable[(row1 + 1) % 5][col1]) + keyTable[(row2 + 1) % 5][col2];
    } else {
        // Rectangle: swap columns
        return string(1, keyTable[row1][col2]) + keyTable[row2][col1];
    }
}

// Function to decrypt a pair of characters
string decryptPair(char keyTable[5][5], char a, char b) {
    int row1, col1, row2, col2;
    findPosition(keyTable, a, row1, col1);
    findPosition(keyTable, b, row2, col2);

    if (row1 == row2) {
        // Same row: move left
        return string(1, keyTable[row1][(col1 + 4) % 5]) + keyTable[row2][(col2 + 4) % 5];
    } else if (col1 == col2) {
        // Same column: move up
        return string(1, keyTable[(row1 + 4) % 5][col1]) + keyTable[(row2 + 4) % 5][col2];
    } else {
        // Rectangle: swap columns
        return string(1, keyTable[row1][col2]) + keyTable[row2][col1];
    }
}

// Function to encrypt the plaintext using the Playfair cipher
string encrypt(const string& plaintext, const string& key) {
    char keyTable[5][5];
    generateKeyTable(key, keyTable);
    string processedText = preprocessPlaintext(plaintext);
    string ciphertext;

    for (size_t i = 0; i < processedText.length(); i += 2) {
        ciphertext += encryptPair(keyTable, processedText[i], processedText[i + 1]);
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using the Playfair cipher
string decrypt(const string& ciphertext, const string& key) {
    char keyTable[5][5];
    generateKeyTable(key, keyTable);
    string plaintext;

    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        plaintext += decryptPair(keyTable, ciphertext[i], ciphertext[i + 1]);
    }

    return plaintext;
}

int main() {
    string key, text;
    int choice;

    cout << "Enter the key: ";
    getline(cin, key);

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Choose an option:\n1. Encrypt\n2. Decrypt\n";
    cin >> choice;

    if (choice == 1) {
        string encryptedText = encrypt(text, key);
        cout << "Encrypted Text: " << encryptedText << endl;
    } else if (choice == 2) {
        string decryptedText = decrypt(text, key);
        cout << "Decrypted Text: " << decryptedText << endl;
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
