#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

// Function to convert a character to its corresponding number (A=0, B=1, ..., Z=25)
int charToNum(char c) {
    return toupper(c) - 'A';
}

// Function to convert a number back to its corresponding character
char numToChar(int num) {
    return num + 'A';
}

// Function to perform matrix multiplication modulo 26
vector<int> matrixMultiply(const vector<vector<int>>& matrix, const vector<int>& vec) {
    vector<int> result(matrix.size(), 0);
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            result[i] = (result[i] + matrix[i][j] * vec[j]) % 26;
        }
    }
    return result;
}

// Function to find the modular inverse of a number modulo 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}

// Function to find the determinant of a 2x2 matrix modulo 26
int determinant(const vector<vector<int>>& matrix) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
}

// Function to find the adjugate of a 2x2 matrix modulo 26
vector<vector<int>> adjugate(const vector<vector<int>>& matrix) {
    return {{matrix[1][1], -matrix[0][1]},
            {-matrix[1][0], matrix[0][0]}};
}

// Function to find the inverse of a 2x2 matrix modulo 26
vector<vector<int>> inverseMatrix(const vector<vector<int>>& matrix) {
    int det = determinant(matrix);
    int detInv = modInverse(det, 26);
    if (detInv == -1) {
        throw runtime_error("Matrix is not invertible modulo 26");
    }
    vector<vector<int>> adj = adjugate(matrix);
    for (auto& row : adj) {
        for (auto& elem : row) {
            elem = (elem % 26 + 26) % 26; // Ensure positive values
        }
    }
    for (auto& row : adj) {
        for (auto& elem : row) {
            elem = (elem * detInv) % 26;
        }
    }
    return adj;
}

// Function to encrypt plaintext using the Hill cipher
string encrypt(const string& plaintext, const vector<vector<int>>& keyMatrix) {
    string ciphertext;
    vector<int> vec(2, 0);
    for (size_t i = 0; i < plaintext.length(); i += 2) {
        vec[0] = charToNum(plaintext[i]);
        vec[1] = (i + 1 < plaintext.length()) ? charToNum(plaintext[i + 1]) : 0;
        vector<int> encryptedVec = matrixMultiply(keyMatrix, vec);
        ciphertext += numToChar(encryptedVec[0]);
        ciphertext += numToChar(encryptedVec[1]);
    }
    return ciphertext;
}

// Function to decrypt ciphertext using the Hill cipher
string decrypt(const string& ciphertext, const vector<vector<int>>& keyMatrix) {
    string plaintext;
    vector<int> vec(2, 0);
    vector<vector<int>> invKeyMatrix = inverseMatrix(keyMatrix);
    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        vec[0] = charToNum(ciphertext[i]);
        vec[1] = (i + 1 < ciphertext.length()) ? charToNum(ciphertext[i + 1]) : 0;
        vector<int> decryptedVec = matrixMultiply(invKeyMatrix, vec);
        plaintext += numToChar(decryptedVec[0]);
        plaintext += numToChar(decryptedVec[1]);
    }
    return plaintext;
}

int main() {
    // Define the key matrix (2x2)
    vector<vector<int>> keyMatrix = {{6, 24},
                                     {1, 16}};

    string plaintext;
    cout << "Enter plaintext (uppercase letters only): ";
    getline(cin, plaintext);

    // Ensure the plaintext has an even length
    if (plaintext.length() % 2 != 0) {
        plaintext += 'X'; // Padding character
    }

    string ciphertext = encrypt(plaintext, keyMatrix);
    cout << "Encrypted Text: " << ciphertext << endl;

    string decryptedText = decrypt(ciphertext, keyMatrix);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
