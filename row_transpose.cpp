#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to encrypt plaintext using Row Transposition Cipher
string encrypt(const string& plaintext, int numCols) {
    int numRows = (plaintext.length() + numCols - 1) / numCols;
    vector<vector<char>> grid(numRows, vector<char>(numCols, ' '));

    // Fill the grid with plaintext characters
    int k = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols && k < plaintext.length(); ++j) {
            grid[i][j] = plaintext[k++];
        }
    }

    // Read the grid column by column to form ciphertext
    string ciphertext;
    for (int j = 0; j < numCols; ++j) {
        for (int i = 0; i < numRows; ++i) {
            if (grid[i][j] != ' ') {
                ciphertext += grid[i][j];
            }
        }
    }
    return ciphertext;
}

// Function to decrypt ciphertext using Row Transposition Cipher
string decrypt(const string& ciphertext, int numCols) {
    int numRows = (ciphertext.length() + numCols - 1) / numCols;
    vector<vector<char>> grid(numRows, vector<char>(numCols, ' '));

    // Fill the grid with ciphertext characters
    int k = 0;
    for (int j = 0; j < numCols; ++j) {
        for (int i = 0; i < numRows && k < ciphertext.length(); ++i) {
            grid[i][j] = ciphertext[k++];
        }
    }

    // Read the grid row by row to form plaintext
    string plaintext;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (grid[i][j] != ' ') {
                plaintext += grid[i][j];
            }
        }
    }
    return plaintext;
}

int main() {
    string plaintext;
    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    int numCols;
    cout << "Enter number of columns: ";
    cin >> numCols;

    string ciphertext = encrypt(plaintext, numCols);
    cout << "Encrypted Text: " << ciphertext << endl;

    string decryptedText = decrypt(ciphertext, numCols);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
