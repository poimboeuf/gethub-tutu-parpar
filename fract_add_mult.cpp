//
//  fract_add_mult.cpp
//  adding addition and multiplication to fraction class 
//  Fractions class
//
//  Created by Michael Poimboeuf on 10/24/18.
//  Copyright © 2018 Preumbra LLC. All rights reserved.
// ---------------------------------------------------------
/* Known bugs due to overflow in addition and multiplication:
 * Preumbra-MBP:Fractions michaelpoimboeuf$ ./fract_add_mult
 *
 * Enter a numerator between 0 and +/-2147483647:2147483647
 * Enter a denominator between 0 and +/-2147483647:1
 *
 * Reduced rational fraction entered is:  	2147483647/1
 *
 * Enter a numerator between 0 and +/-2147483647:2147483647
 * Enter a denominator between 0 and +/-2147483647:1
 * Reduced rational fraction entered is:  	2147483647/1
 * // addition overflows and sets the sign bit!
 * 2147483647/1	+	2147483647/1 = -2/1
 * // multiplication overflows and also sets the sign bit, but it cancels
 * 2147483647/1	x	2147483647/1 = 1/1
 * // maybe just check for sign bit overflow and report the result as "OVERFLOW"
 * ----------------------------------------------------------
 */

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
    	// set value of Fraction - this is the assignment function for Fractions
        void set(int n, int d) {num = n; den = d; normalize();}
        // get the numerator
        int get_num() {return num;}
        // get the denominator
        int get_den() {return den;}
        
        // Fraction addition 
        Fraction add(Fraction other);
        
        // Fraction multiplication
        Fraction mult(Fraction other);
        
        // Function on Fraction class - set value from console
        Fraction cset(Fraction input);
        
    private:
		// convert to normalized fraction form
        void normalize();
		// greatest common factor
        int gcf(int a, int b);
		// least common multiple
       	int lcm(int a, int b);
};



int main()
{
	// Declarations and initialization to unity
	Fraction finput; 
		finput.set(1,1);
	Fraction fract1;
		fract1.set(1,1);
	Fraction fract2;
		fract2.set(1,1);	
	Fraction fractsum;
		fractsum 	= fract1.add(fract2);
	Fraction fractprod;
		fractprod 	= fract1.mult(fract2);
	
	// Console input of two fractions
	printf("\n");
	fract1 		= fract1.cset(finput);
	printf("\n");
	fract2 		= fract2.cset(finput);
	
	// Sum of fractions
	fractsum 	= fract1.add(fract2);
	printf("\n");
	cout << fract1.get_num() << "/" << fract1.get_den();
	cout << "\t+\t";
	cout << fract2.get_num() << "/" << fract2.get_den();
	cout << " = ";
	cout << fractsum.get_num()<<"/"<<fractsum.get_den()<<"\n";
	
	// Product of fractions
	fractprod 	= fract1.mult(fract2);
	printf("\n");
	cout << fract1.get_num() << "/" << fract1.get_den();
	cout << "\tx\t";
	cout << fract2.get_num() << "/" << fract2.get_den();
	cout << " = ";
	cout << fractprod.get_num()<<"/"<<fractprod.get_den()<<"\n";
	
	printf("\n");
    return 0;
}
//----------------------------------------------------------------------------
// FRACTION CLASS FUNCTIONS

/* Fraction command line entry
 * Derived from console input of fraction.c v0.0 written by Michael Poimboeuf.
 * That console input was in the main() section of fraction. This turns it into
 * a function on the Fraction class objects
 */
Fraction Fraction::cset(Fraction finput)
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
//    string str;
     
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
    finput.set(a,b);
    cout << "\nReduced rational fraction entered is:  \t" << finput.get_num();
    cout << "/" << finput.get_den() << "\n";
    return finput;
}

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
    int n 		= gcf(a, b);
    return a/n*b;
}

// Add fraction function
//
Fraction Fraction::add(Fraction other)
{
	Fraction fract;
	int lcd 	= lcm(den, other.den);
	int quo1 	= lcd/den;
	int quo2	= lcd/other.den;
	fract.set(num*quo1 + other.num * quo2, lcd);
	return fract;
}

// Multiply fraction function
//
Fraction Fraction::mult(Fraction other)
{
	Fraction fract;
	fract.set(num*other.num, den*other.den);
	return fract;
}

