#include <iostream>
#include "BigInt.h"

BigInt x, y, g;

BigInt gcd(BigInt a, BigInt b)
{
    if (b.EqualsZero())
        return a;
    else
        return gcd(b, a % b);
}

void extended_gcd(BigInt a, BigInt b)
{
    if (b.EqualsZero())
    {
        x = BigIntOne;
        y = BigIntZero;
        g = a;
    }
    else
    {
        extended_gcd(b, a % b);
        BigInt temp = x;
        x = y;
        y = temp - a / b * y;
    }
}

BigInt module_inverse(BigInt a, BigInt m)
{
    BigInt res;
    extended_gcd(a, m);
    if (g != BigIntOne)
    {
        cout << "Module Inverse does not exist!" << endl;
        return -1;
    }
    else
    {
        x = (x % m + m) % m;
        res = x;
    }
    return res;
}

BigInt binaryPower(BigInt a, BigInt b, BigInt m)
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
