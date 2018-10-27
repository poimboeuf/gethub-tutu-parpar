//
//  fractions.cpp
//  Fractions class
//
//  Created by Michael Poimboeuf on 10/23/18.
//  Copyright © 2018 Preumbra LLC. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

class Fraction
{
    private:
// numerator
        int num;
// denominator
        int den;
    public:
        void set(int n, int d) {num = n; den = d; normalize();}
        int get_num() {return num;}
        int get_den() {return den;}
    private:
// convert to normalized fraction form
        void normalize();
// greatest common factor
        int gcf(int a, int b);
// least common multiple
       int lcm(int a, int b);
};

// Define member function set()
//

int main()
{
    // Initializations
    //
    // a the integer for the numerator
    int a = 0;
    // alpha is the double precision input read from console for conversion
    // we use double for this so that the mantissa is larger than 32 bits
    double alpha = 0;
    // b is the integer for the denominator
    // as alpha above, beta is the double precision console value
    int b = 0;
    double beta = 0;
    // str initializes to default "", but be careful to assign correctly later
    string str;
    // fraction is unintialized, be careful to set correction later
    Fraction fract;
   
    // Banner
    cout << "\n-------------------------------------------------------\n";
    cout << "Program to reduce a rational fraction of two integers.\n";
    cout << "Leaving the result in fractional form, e.g. 3/2 not 1 1/2\n\n";
    // forever loop waiting for numbers to factor until terminated with
    // !Y or !y
    while (true)
    {
        cout << "Enter a numerator between 0 and +/-" << INT_MAX <<":";
        // read in the value alpha as a double for casting to a later checking
        // that alpha is in range for Max/Min INT on this computer
        cin >> alpha;
        while (alpha>INT_MAX || alpha<INT_MIN)
        {
            cout << "The magnitude of the number you entered is too large,\n";
            cout << "please re-enter a numerator between 0 and ";
            cout << INT_MAX <<":";
            cin >> alpha;
        }
        // cast alpha double to int a
        a   =   int(alpha);
        cout << "Enter a denominator between 0 and +/-" << INT_MAX <<":";
        
        // read in the value beta as a double for casting to a later checking
        // that beta is in range for Max/Min INT on this computer
        cin >>  beta;
        while (beta>INT_MAX || beta<INT_MIN)
        {
            cout << "The magnitude of the number you entered is too large,\n";
            cout << "please re-enter a denominator between 0 and ";
            cout << INT_MAX <<":";
            cin >> beta;
        }
        // cast beta double to int b
        b   =   int(beta);
        
        // set the fraction to the calculated a and b
        fract.set(a,b);
        cout << "\nReduced rational fraction is:  \t" << fract.get_num();
        cout << "/" << fract.get_den() << "\n";
        // continue loop if Y or y, break loop if anything else
        cout << "\nReduce another fraction? (Y/N) ";
        cin >> str;
        if (!(str[0] == 'Y' || str[0] == 'y')) break;
    }
    cout << "Exiting program ---->\n";
    return 0;
}
//----------------------------------------------------------------------------
// FRACTION CLASS FUNCTIONS

// Normailize: put fraction into standard form
//
void Fraction::normalize()
{
    // cases involving 0
    if (den == 0 || num == 0)
    {
        num =   0;
        den =   1;
    }
    
    // put negative sign on numerator only, flipping the sign of the
    // numerator if negative, to make positive so we don't have -n/-d
    // or n/-d
    if (den<0)
    {
        num *= 	-1;
        den *= 	-1;
    }
    
    // factor out Greatest Common Factor from numerator & denominator
    //
    int n   = gcf(num, den);
    num /= 		n;
    den /= 		n;
}

// Greatest Common Factor function
//
int Fraction::gcf(int a, int b)
    {
        if (b==0)
        {
            return abs(a);
        }
        else
        {
            return gcf(b, a%b);
        }
    }
// Least Common Multiple
//
int Fraction::lcm(int a, int b)
{
    int n 	= gcf(a, b);
    return a/n*b;
}

//Original test code for member functions commented out below
//There is a bug in this code, probably in set(), which defaults den to 1
//Define member function get_num()
//void Fraction::set(int n, int d)
//{
//    num = n;
//    den = d;
//}
//
//int Fraction::get_num()
//{
//    int n;
//    return n;
//}
//
// Define member function get_den()
//
//int Fraction::get_den()
//{
//    int d;
//    return d;
//}
//
