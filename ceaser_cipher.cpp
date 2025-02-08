
#include <iostream>
#include <string>

using namespace std;

// Function to encrypt the plaintext using Caesar Cipher
string encrypt(const string& text, int shift) {
    string result = "";

    // Traverse the text
    for (char ch : text) {
        // Encrypt uppercase letters
        if (isupper(ch))
            result += char(int(ch + shift - 65) % 26 + 65);
        // Encrypt lowercase letters
        else if (islower(ch))
            result += char(int(ch + shift - 97) % 26 + 97);
        // Leave non-alphabetic characters unchanged
        else
            result += ch;
    }

    return result;
}

// Function to decrypt the ciphertext using Caesar Cipher
string decrypt(const string& text, int shift) {
    string result = "";

    // Traverse the text
    for (char ch : text) {
        // Decrypt uppercase letters
        if (isupper(ch))
            result += char(int(ch - shift - 65 + 26) % 26 + 65);
        // Decrypt lowercase letters
        else if (islower(ch))
            result += char(int(ch - shift - 97 + 26) % 26 + 97);
        // Leave non-alphabetic characters unchanged
        else
            result += ch;
    }

    return result;
}

int main() {
    string text;
    int shift;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the shift value: ";
    cin >> shift;

    string encryptedText = encrypt(text, shift);
    string decryptedText = decrypt(encryptedText, shift);

    cout << "Encrypted Text: " << encryptedText << endl;
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
