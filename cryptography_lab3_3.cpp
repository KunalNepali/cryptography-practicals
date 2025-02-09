#include <iostream>
using namespace std;

int ExtendedEuclidean(int a, int b, int *x, int *y) // mistake 1
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;  // Mistake 2
    }

    int x1, y1;  // Mistake 3
    int gcd = ExtendedEuclidean(b % a, a, &x1, &y1);

    // Update x and y using the results of the recursive call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

int main()
{
    int x, y, a, b;
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;

    int e_gcd = ExtendedEuclidean(a, b, &x, &y);
    cout << "GCD(" << a << ", " << b << ") = " << e_gcd << endl;

    return 0;
}

