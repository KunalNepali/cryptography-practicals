#include <iostream>
#include <string>

using namespace std;

// Function to generate the key in a cyclic manner equal to the length of the original text
string generateKey(const string& text, const string& keyword) {
    string key = keyword;
    while (key.size() < text.size()) {
        key += keyword;
    }
    return key.substr(0, text.size());
}

// Function to encrypt the plaintext using the Vigenère cipher
string encrypt(const string& plaintext, const string& key) {
    string ciphertext;
    for (size_t i = 0; i < plaintext.size(); ++i) {
        char p = plaintext[i];
        char k = key[i];
        if (isupper(p)) {
            ciphertext += char(((p - 'A') + (toupper(k) - 'A')) % 26 + 'A');
        } else if (islower(p)) {
            ciphertext += char(((p - 'a') + (tolower(k) - 'a')) % 26 + 'a');
        } else {
            ciphertext += p; // Non-alphabetic characters are added unchanged
        }
    }
    return ciphertext;
}

// Function to decrypt the ciphertext using the Vigenère cipher
string decrypt(const string& ciphertext, const string& key) {
    string plaintext;
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        char c = ciphertext[i];
        char k = key[i];
        if (isupper(c)) {
            plaintext += char(((c - 'A') - (toupper(k) - 'A') + 26) % 26 + 'A');
        } else if (islower(c)) {
            plaintext += char(((c - 'a') - (tolower(k) - 'a') + 26) % 26 + 'a');
        } else {
            plaintext += c; // Non-alphabetic characters are added unchanged
        }
    }
    return plaintext;
}

int main() {
    string text, keyword;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the keyword: ";
    getline(cin, keyword);

    string key = generateKey(text, keyword);
    string encryptedText = encrypt(text, key);
    string decryptedText = decrypt(encryptedText, key);

    cout << "Original Text: " << text << endl;
    cout << "Keyword: " << keyword << endl;
    cout << "Generated Key: " << key << endl;
    cout << "Encrypted Text: " << encryptedText << endl;
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
