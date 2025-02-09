#include <iostream>
using namespace std;

int gcd(int x, int y)
{
    if (x == 0)
        return y;

    return gcd(y % x, x); // maile gareko mistake 1
}

int main()
{
    int x, y;
    cout << "Enter the number x: ";
    cin >> x;
    cout << "Enter the number y: ";
    cin >> y;

    int gcd_value = gcd(x, y);  //mistake 2

    cout << "Since, the gcd of " << x << " and " << y << " is: " << gcd_value; //mistake 3

    if (gcd_value == 1) //mistake 4
        cout << ", these numbers are relatively prime." << endl;
    else
        cout << ", these numbers are NOT relatively prime." << endl;

    return 0;
}

