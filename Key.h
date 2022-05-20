#ifndef KEY_H_
#define KEY_H_

#include "BigInt.h"
#include <iostream>

struct key
{
	BigInt modulus;
	BigInt exponent;
};

struct keyPair
{
	key private_key;
	key public_key;
};

#endif /*KEY_H_*/
