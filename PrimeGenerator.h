#ifndef PRIMEGENERATOR_H_
#define PRIMEGENERATOR_H_

#include "BigInt.h"
#include <string>
#include <cstdlib>

BigInt MakeRandom(unsigned long int number_of_digits)
{
	std::string randomNum;
	randomNum.resize(number_of_digits);
	unsigned long int countDigit = 0;

	while (countDigit < number_of_digits)
	{
		unsigned long int newRand = std::rand();

		while (newRand >= 10)
		{
			randomNum[countDigit++] = (newRand % 10) + '0';
			newRand /= 10;
			if (countDigit == number_of_digits)
				break;
		}
	}

	if (randomNum[0] == '0')
		randomNum[0] = (std::rand() % 9) + 1 + '0';
	return randomNum;
}

BigInt generatePrimeCandidate(unsigned long int number_of_digits)
{
	BigInt candidate = MakeRandom(number_of_digits);
	if (!candidate.IsOdd())
		candidate.SetDigit(0, candidate.GetDigit(0) + 1);
	if (candidate.GetDigit(candidate.Length() - 1) == 0)
		candidate.SetDigit(candidate.Length() - 1, (std::rand() % 9) + 1);
	return candidate;
}

BigInt binpow(BigInt a, BigInt b, BigInt m)
{
	a = a % m;
	BigInt res = 1;
	while (b > BigIntZero)
	{
		if ((b % 2).IsOdd())
			res = res * a % m;
		a = a * a % m;
		b = b / 2;
	}
	return res;
}

bool millerTest(BigInt d, BigInt n)
{
	BigInt a;
	do
	{
		a = generatePrimeCandidate(10);
	} while ((a < 2) || (a > (n - 2)));
	BigInt x = binpow(a, d, n);

	if (x == 1 || x == n - 1)
		return true;

	while (d != n - 1)
	{
		x = (x * x) % n;
		d *= 2;

		if (x == 1)
			return false;
		if (x == n - 1)
			return true;
	}

	return false;
}

bool isPrime(BigInt n, BigInt k)
{
	if (n <= 1 || n == 4)
		return false;
	if (n <= 3)
		return true;

	BigInt d = n - 1;
	while (d % 2 == BigIntZero)
		d /= 2;

	for (BigInt i = BigIntZero; i < k; i += 1)
		if (!millerTest(d, n))
			return false;

	return true;
}

BigInt generatePrime(unsigned long int number_of_digits,
					 unsigned long int k)
{
	BigInt primeCandidate;
	primeCandidate = generatePrimeCandidate(number_of_digits);
	while (!isPrime(primeCandidate, k))
	{
		primeCandidate = primeCandidate + 2;
		if (primeCandidate.Length() != number_of_digits)
			primeCandidate = generatePrimeCandidate(number_of_digits);
	}
	return primeCandidate;
}

#endif