#include <bits/stdc++.h>
// #include "bigInt.h"

int random_Number_Generator_With_Range(int lower, int upper)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(lower, upper);

    return dis(gen);
}

void generateRandomLargeNumber(bigint &a)
{
    int n = random_Number_Generator_With_Range(100, 200);
    vector<int> num(n);
    for (int i = 0; i < n; i++)
        num[i] = random_Number_Generator_With_Range(1, 10);
    string s = "";
    for (int i = 0; i < n; i++)
        s += to_string(num[i]);

    stringstream ss(s);
    ss >> a;
}
