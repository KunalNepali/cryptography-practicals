#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to encrypt plaintext using Rail Fence Cipher
string encrypt(const string& plaintext, int numRails) {
    if (numRails == 1) return plaintext;

    vector<string> rails(numRails);
    int rail = 0;
    bool down = false;

    for (char c : plaintext) {
        rails[rail] += c;
        if (rail == 0 || rail == numRails - 1) down = !down;
        rail += down ? 1 : -1;
    }

    string ciphertext;
    for (const string& railStr : rails) {
        ciphertext += railStr;
    }
    return ciphertext;
}

// Function to decrypt ciphertext using Rail Fence Cipher
string decrypt(const string& ciphertext, int numRails) {
    if (numRails == 1) return ciphertext;

    vector<string> rails(numRails);
    int rail = 0;
    bool down = false;
    vector<int> railLengths(numRails, 0);

    // Calculate the length of each rail
    for (int i = 0; i < ciphertext.length(); ++i) {
        railLengths[rail]++;
        if (rail == 0 || rail == numRails - 1) down = !down;
        rail += down ? 1 : -1;
    }

    // Fill the rails with ciphertext characters
    int index = 0;
    for (int i = 0; i < numRails; ++i) {
        for (int j = 0; j < railLengths[i]; ++j) {
            rails[i] += ciphertext[index++];
        }
    }

    // Read the rails in a zigzag pattern to form plaintext
    string plaintext;
    rail = 0;
    down = false;
    for (int i = 0; i < ciphertext.length(); ++i) {
        plaintext += rails[rail][0];
        rails[rail].erase(rails[rail].begin());
        if (rail == 0 || rail == numRails - 1) down = !down;
        rail += down ? 1 : -1;
    }
    return plaintext;
}

int main() {
    string plaintext;
    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    int numRails;
    cout << "Enter number of rails: ";
    cin >> numRails;

    string ciphertext = encrypt(plaintext, numRails);
    cout << "Encrypted Text: " << ciphertext << endl;

    string decryptedText = decrypt(ciphertext, numRails);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
