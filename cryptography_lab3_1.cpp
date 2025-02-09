#include<iostream>
using namespace std;

int findGCD(int a, int b)
{
    if (a == 0)
        return b;  // Return 'b' instead of 0 when 'a' is 0

    return findGCD(b % a, a); // Proper recursive call
}

int main()
{
    int a, b;
    cout << "Enter the value of a:\n";
    cin >> a;
    cout << "Enter the value of b:\n";
    cin >> b;

    cout << "GCD( " << a << " , " << b << " ) = " << findGCD(a, b) << endl;
    return 0;
}
