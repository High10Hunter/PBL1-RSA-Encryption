#ifndef ENCRYPT_DECRYPT_H
#define ENCRYPT_DECRYPT_H

#include <string>
#include "Key.h"
#include "keyGenerator.h"
#include "BigInt.h"
#include "PrimeGenerator.h"

string encode(string s, int n)
{
    string encode_string = "";
    for (int i = 0; i < s.length(); i++)
    {
        encode_string += to_string((int)s[i]);
    }
    return encode_string;
}

string decode(string str, int len)
{
    int num = 0;
    string decode_string = "";
    for (int i = 0; i < len; i++)
    {
        num = num * 10 + (str[i] - '0');

        if (num >= 32 && num <= 122)
        {
            char ch = (char)num;
            decode_string += ch;
            num = 0;
        }
    }
    return decode_string;
}

BigInt encryptPiece(string message, key public_key)
{
    BigInt encrypted_mess = encode(message, message.length());
    encrypted_mess = binaryPower(encrypted_mess, public_key.exponent, public_key.modulus);
    return encrypted_mess.ToString();
}

string decryptPiece(BigInt &encrypted_mess, key private_key)
{
    BigInt temp = encrypted_mess;
    temp = binaryPower(temp, private_key.exponent, private_key.modulus);
    return decode(temp, temp.Length());
}

string encryptString(const string message, const key public_key)
{
    const unsigned long int pieceSize(((public_key.modulus.Length() - 2) / 3));
    const unsigned long int pieceCount = message.length() / pieceSize;

    string encrypted_text;
    for (unsigned long int i = 0; i < pieceCount; i++)
    {
        string piece(message.substr(i * pieceSize, pieceSize));
        piece = encryptPiece(piece, public_key);
        encrypted_text.append(piece.append(" "));
    }
    if (pieceSize * pieceCount == message.length())
        return encrypted_text;

    const unsigned long int lastPieceSize = message.length() % pieceSize;
    string lastPiece(message.substr(pieceCount * pieceSize, lastPieceSize));
    lastPiece = encryptPiece(lastPiece, public_key);
    return encrypted_text.append(lastPiece.append(" "));
}

string Encrypt(const string encrypted_mess, const key public_key)
{
    return encryptString(encrypted_mess, public_key);
}

string decryptString(const string encrypted_text, const key private_key)
{
    string original_message;
    long int i = 0, j = 0;
    while ((j = encrypted_text.find(' ', i)) != -1)
    {
        BigInt piece(encrypted_text.substr(i, j - i));
        if (piece >= private_key.modulus)
            throw "Piece too large.";

        string text = decryptPiece(piece, private_key);
        original_message.append(text);
        i = j + 1;
    }
    return original_message;
}

string Decrypt(const string encrypted_text, const key private_key)
{
    return decryptString(encrypted_text, private_key);
}

#endif
