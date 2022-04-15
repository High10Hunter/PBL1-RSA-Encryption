#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

typedef vector<ll> bigNum;
// input and output bigNum
void standardize(bigNum &number)
{
    number.push_back(0);
    for (int i = 0; i < number.size() - 1; i++)
    {
        number[i + 1] += (number[i] / 10);
        number[i] %= 10;
        if (number[i] < 0)
        {
            number[i] += 10;
            --number[i - 1];
        }
    }

    while (number.size() > 1 && number.back() == 0)
        number.pop_back();
}

istream &operator>>(istream &cin, bigNum &number)
{
    string s;
    cin >> s;

    number.clear();
    for (int i = s.size() - 1; i >= 0; --i)
        number.push_back(s[i] - '0');

    return number, cin;
}

ostream &operator<<(ostream &cout, bigNum &number)
{
    cout << number.back();
    for (int i = number.size() - 2; i >= 0; --i)
        cout << number[i];

    return cout;
}

// compare operator > < ==
bool operator<(const bigNum &a, const bigNum &b)
{
    if (a.size() != b.size())
        return a.size() < b.size();

    for (int i = a.size() - 1; i >= 0; --i)
        if (a[i] != b[i])
            return a[i] < b[i];

    return false;
}

bool operator>(const bigNum &a, const bigNum &b)
{
    if (a.size() != b.size())
        return a.size() > b.size();

    for (int i = a.size() - 1; i >= 0; --i)
        if (a[i] != b[i])
            return a[i] > b[i];

    return false;
}

bool operator==(const bigNum &a, const bigNum &b)
{
    if (a.size() != b.size())
        return false;

    for (int i = a.size() - 1; i >= 0; --i)
        if (a[i] != b[i])
            return false;

    return true;
}

//+ - * / % operator
bigNum operator+(bigNum a, bigNum b)
{
    a.resize(max(a.size(), b.size()), 0);

    for (int i = 0; i < b.size(); ++i)
        a[i] += b[i];

    standardize(a);

    return a;
}

bigNum operator-(bigNum a, bigNum b)
{
    for (int i = 0; i < b.size(); ++i)
        a[i] -= b[i];

    standardize(a);

    return a;
}

bigNum operator*(bigNum a, bigNum b)
{
    bigNum product(a.size() + b.size() + 1, 0);

    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < b.size(); ++j)
        {
            product[i + j] += (a[i] * b[j]);
            product[i + j + 1] += (product[i + j] / 10);
            product[i + j] %= 10;
        }

    standardize(product);

    return product;
}

bigNum operator/(bigNum a, bigNum b)
{
    bigNum quotient;
    quotient.clear();
    bigNum carry;

    while (a.size() > 0)
    {
        int finish = a.size() - 1;
        int start = finish - b.size() + 1;
        if (start < 0)
            start = 0;
        int count = start;

        if (carry.size() == 0)
        {
            while (count <= finish)
            {
                carry.push_back(a[start]);
                a.pop_back();
                ++count;
            }
        }
        else
        {
            while (count <= finish)
            {
                carry.insert(carry.begin(), a[start]);
                a.pop_back();
                ++count;
            }
        }

        if ((carry < b) || (carry == b) && a.size() > 0)
        {
            carry.insert(carry.begin(), a[start - 1]);
            a.pop_back();
        }

        standardize(carry);

        count = 0;
        while (carry < b || carry == b)
        {
            ++count;
            carry = carry - b;
        }

        if (count >= 10)
        {
            int x = count % 10;
            count /= 10;
            int y = count % 10;
            count /= 10;
            quotient.insert(quotient.begin(), y);
            quotient.insert(quotient.begin(), x);
        }
        else
        {
            quotient.insert(quotient.begin(), count);
        }
    }
}