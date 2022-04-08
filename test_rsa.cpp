#include <bits/stdc++.h>
#include "bigInt.h"
// #include "process_bigInt.h"

typedef long long ll;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    bigint a, b;
    cin >> a >> b;
    bigint c = a % b;
    cout << c;
    return 0;
}
