#ifndef KEY_GENERATE_H_
#define KEY_GENERATE_H_

#include <iostream>
#include "BigInt.h"
#include "PrimeGenerator.h"
#include "functions.h"
#include "Key.h"

keyPair generateKeys(unsigned long int key_length, unsigned long int k)
{
    if (key_length < 8)
    {
        throw "Độ dài khoá quá ngắn\n";
    }
    BigInt p = generatePrime(key_length, k);
    BigInt q = generatePrime(key_length, k);

    while (p == q)
        p = generatePrime(key_length, k);

    BigInt n = p * q;
    BigInt phi = (p - BigIntOne) * (q - BigIntOne);

    BigInt e = "65537";
    while (gcd(phi, e) != BigIntOne || e < "65537" || !e.IsOdd())
        e = MakeRandom(5);

    key publicKey;
    publicKey.exponent = e;
    publicKey.modulus = n;

    BigInt d = module_inverse(e, phi);
    key privateKey;
    privateKey.modulus = n;
    privateKey.exponent = d;

    keyPair key_pair;
    key_pair.public_key = publicKey;
    key_pair.private_key = privateKey;
    return key_pair;
}

#endif
