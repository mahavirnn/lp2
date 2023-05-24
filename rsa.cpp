// rsa
#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
    if (n <= 1)
        return false;

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }

    return true;
}

int findGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void generateKeys(int p, int q, int& n, int& e, int& d) {
    n = p * q;
    int phi = (p - 1) * (q - 1);
    for (e = 2; e < phi; e++) {
        if (findGCD(e, phi) == 1)
            break;
    }
    for (d = 2; d < phi; d++) {
        if ((d * e) % phi == 1)
            break;
    }
}

int encrypt(int message, int e, int n) {
    int encryptedMessage = pow(message, e);
    encryptedMessage = fmod(encryptedMessage, n);
    return encryptedMessage;
}

int decrypt(int encryptedMessage, int d, int n) {
    int decryptedMessage = pow(encryptedMessage, d);
    decryptedMessage = fmod(decryptedMessage, n);
    return decryptedMessage;
}

int main() {
    int p, q;
    cout << "Enter two prime numbers: ";
    cin >> p >> q;

    if (!isPrime(p) || !isPrime(q)) {
        cout << "Both numbers must be prime." << endl;
        return 0;
    }

    int n, e, d;
    generateKeys(p, q, n, e, d);

    cout << "Public Key: (e = " << e << ", n = " << n << ")" << endl;
    cout << "Private Key: (d = " << d << ", n = " << n << ")" << endl;

    // Encryption
    int message;
    cout << "Enter a message to encrypt: ";
    cin >> message;
    int encryptedMessage = encrypt(message, e, n);
    cout << "Encrypted message: " << encryptedMessage << endl;

    // Decryption
    int decryptedMessage = decrypt(encryptedMessage, d, n);
    cout << "Decrypted message: " << decryptedMessage << endl;

    return 0;
}
