#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "BigInt.h"
#include "PrimeGenerator.h"
#include "keyGenerator.h"
#include "encrypt_decrypt.h"
using namespace std;

typedef long long ll;

int main()
{
    std::srand(time(NULL));

    cout << "---------------RSA ENCRYPTION---------------\n";
    cout << "1.Generate keys" << endl;
    cout << "2.Encrypt Message" << endl;
    cout << "3.Decrypt Message" << endl;
    cout << "a.Input from keyboard" << endl;
    cout << "b.Input from files" << endl;
    cout << "Choose option: ";
    char option;
    cin >> option;
    if (option == 'a')
    {
        while (1)
        {
            cout << "---------------RSA ENCRYPTION---------------\n";
            cout << "1.Generate keys" << endl;
            cout << "2.Encrypt Message" << endl;
            cout << "3.Decrypt Message" << endl;
            cout << "4.Quit" << endl;
            cout << "Choose option: ";
            int option;
            cin >> option;

            if (option == 1)
            {
                int key_length, iteration;
                cout << "Enter key length: ";
                cin >> key_length;
                cout << "Enter number of iterations in Miller-Rabin test: ";
                cin >> iteration;
                keyPair key_pair = generateKeys(key_length, iteration);
                cout << "Public key" << endl;
                cout << "{" << endl;
                cout << "e = " << key_pair.public_key.exponent << endl;
                cout << "n = " << key_pair.public_key.modulus << endl;
                cout << "}" << endl;
                cout << "Private key" << endl;
                cout << "{" << endl;
                cout << "d = " << key_pair.private_key.exponent << endl;
                cout << "n = " << key_pair.private_key.modulus << endl;
                cout << "}" << endl;
            }
            else if (option == 2)
            {
                string message;
                cout << "Enter secret message: ";
                cin.ignore();
                getline(cin, message);
                key public_key;
                cout << "Enter your public key:" << endl;
                cout << "e = ";
                cin >> public_key.exponent;
                cout << "n = ";
                cin >> public_key.modulus;
                string encrypted_message = Encrypt(message, public_key);
                cout << "Encrypted message: ";
                cout << encrypted_message << endl;
            }
            else if (option == 3)
            {
                string encrypted_message;
                cout << "Enter encrypted message: ";
                cin.ignore();
                getline(cin, encrypted_message);
                encrypted_message += " ";
                key private_key;
                cout << "Enter your private key:" << endl;
                cout << "d = ";
                cin >> private_key.exponent;
                cout << "n = ";
                cin >> private_key.modulus;
                string original_message = Decrypt(encrypted_message, private_key);
                cout << "Secret message: ";
                cout << original_message << endl;
            }
            else if (option == 4)
            {
                cout << "Goodbye!!" << endl;
                break;
            }
            else
                cout << "Please enter the correct option number!!" << endl;
        }
    }
    else if (option == 'b')
    {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);

        while (1)
        {
            int option;
            cin >> option;

            if (option == 1)
            {
                int key_length, iteration;
                cin >> key_length;
                cin >> iteration;
                keyPair key_pair = generateKeys(key_length, iteration);
                cout << "Public key" << endl;
                cout << "{" << endl;
                cout << "e = " << key_pair.public_key.exponent << endl;
                cout << "n = " << key_pair.public_key.modulus << endl;
                cout << "}" << endl;
                cout << "Private key" << endl;
                cout << "{" << endl;
                cout << "d = " << key_pair.private_key.exponent << endl;
                cout << "n = " << key_pair.private_key.modulus << endl;
                cout << "}" << endl;
            }
            else if (option == 2)
            {
                string message;
                cin.ignore();
                getline(cin, message);
                key public_key;
                cin >> public_key.exponent;
                cin >> public_key.modulus;
                string encrypted_message = Encrypt(message, public_key);
                cout << "Encrypted message: ";
                cout << encrypted_message << endl;
            }
            else if (option == 3)
            {
                string encrypted_message;
                cin.ignore();
                getline(cin, encrypted_message);
                encrypted_message += " ";
                key private_key;
                cin >> private_key.exponent;
                cin >> private_key.modulus;
                string original_message = Decrypt(encrypted_message, private_key);
                cout << "Secret message: ";
                cout << original_message << endl;
            }
            else if (option == 4)
            {
                break;
            }
            else
                cout << "Please enter the correct option number!!" << endl;
        }
    }

    return 0;
}
