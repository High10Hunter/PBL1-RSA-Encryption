#include <bits/stdc++.h>
// #include "bigInt.h"
#include "generateRandomNumber.h"
using namespace std;

bigint binpow(bigint a, bigint b, bigint m)
{
    a = a % m;
    bigint res = 1;
    while (b > 0)
    {
        if (b % 2)
            res = res * a % m;
        a = a * a % m;
        b = b / 2;
    }
    return res;
}

bool millerTest(bigint d, bigint n)
{
    bigint a;
    do
    {
        generateRandomLargeNumber(a);
    } while ((a < 2) || (a > (n - 2)));
    bigint x = binpow(a, d, n);

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

bool isPrime(bigint n, bigint k)
{
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;

    bigint d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    for (bigint i = 0; i < k; i += 1)
        if (!millerTest(d, n))
            return false;

    return true;
}
