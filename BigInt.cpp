/*
@Author Gaurav Deshmukh
	    Assignment# 2
		COSC 5340
		Programming Languages , Computer Science , UTTYLER

		Write a program in C++ (using carryover low-level features of C)
		that will partially implement an abstract data type bigInt allowing 
		for unsigned integers of up to 64-bit length. Your program should 
		accept from a file pairs of unsigned hex constants of up to 16 digits each. 
		For each pair print the two constants, their sum, and their product on an 
		output file. Leading zeros are optional.
*/

/*Start Program*/

/* The list of required includes for this program */
#include <iostream>
#include <fstream>
#include <ios>
#include <iomanip>

using namespace std;

/* Class Definition */
class bigInt{
	unsigned long int loworder;
	unsigned long int highorder;
	int overflow;
	public:
		/*Default Constructor */
		bigInt(){};
		/*friend function declaration for respective operator function overloading*/
		friend std::ifstream& operator>>(std::ifstream& in, bigInt&);
		friend std::ofstream& operator<<(std::ofstream& out,bigInt&);
		bigInt operator+(const bigInt&) const;
		bigInt operator*(const bigInt&) const;
	private:
		void shiftLeft(int);
};


/* The main function */
int main()
{
	/*creating objects of ifstream & ofstream for file read and write*/
	ifstream inputfile;
	ofstream outputfile;

	/*objects of class bigInt*/
	bigInt x,y,sum,prod;

	/*open the required files in read and write modes*/
	inputfile.open("lab2.txt",ios::in);
	outputfile.open("output.txt",ios::app|ios::out);

	if(!inputfile)
	{
		cout<<"No file present"<<endl;
		return -1;
	}

	/*The main processing code*/
	while(!inputfile.eof())
	{
		/*Assigning and printing value of X*/
		inputfile >> x;
		outputfile << "\nX:   ";
		outputfile << x;
		outputfile << "\t";
		/*Assigning and printing value of Y*/
		inputfile >> y;
		outputfile << "Y:\t  ";
		outputfile << y;
		outputfile << "\t\n";
		/*Calculating SUM and printining*/
		sum = x + y;
		outputfile <<"SUM: ";
		outputfile << sum;
		/*Calculating PROD and printing it*/
		prod = x * y;
		outputfile <<"\tPROD: ";
		outputfile << prod;
		outputfile << "\n----------------------------------------------------------------------";
	}
		/*closing the respective files*/
		inputfile.close();
		outputfile.close();

	return 0;
}


/* The multiplicaion function with overloaded '*' operator */
bigInt bigInt :: operator*(const bigInt& e) const
{
	/*declaration of the varialbles required*/
	bigInt product,dl,acc,f;
	int bit,sw,n;
	unsigned long int k,m;
	product.loworder = 0;
	acc.loworder = 0;
	product.highorder = 0;
	acc.highorder = 0;
	m = 0x00000001L;
	dl.loworder=loworder;
	dl.highorder=highorder;
	sw=0;

	/*Multiplication algorithm for higher order of given nos*/
	for( n = 31; n >= 0 ; n -=1 )
	{
		 bit = product.highorder >> 31;
		 if (bit!=0)
		 {
			 sw = 1;
		 }
		 product.shiftLeft(1);
		 acc.shiftLeft(1);
		 k = (e.highorder >> n) & m;
		 /*Using Successive addition to get the product of higher order of two nos*/
		 if (k != 0)
		 {
			 product = dl + acc;
			 acc.loworder = product.loworder;
			 acc.highorder = product.highorder;
			 if(product.overflow != 0)
			 {
				 sw = 1;
			 }
		 }
	}

	/*Multiplication algorithm for lower order byte */
	for( n = 31; n >=0; n -= 1 )
	{
		bit = product.highorder >> 31;
		if (bit != 0)
		{
			sw = 1;
		}
		product.shiftLeft(1);
		acc.shiftLeft(1);
		k = (e.loworder >> n) & m;
		/*Using Successive addition to get the product of lower order of two nos*/
		if(k != 0)
		{
			product = dl + acc;
			acc.loworder = product.loworder;
			acc.highorder = product.highorder;
			if( product.overflow != 0)
			{
				sw = 1;
			}
		}
	}

	f.loworder = acc.loworder;
	f.highorder = acc.highorder;
	f.overflow = sw;
	return f;
}


/* The addition function with overloaded '+' operator*/
bigInt bigInt :: operator+(const bigInt& b) const
{
	/*declaration of the varialbles required*/
	bigInt c;
	unsigned long int u,v,w,z;
	int carry;

	u = 0xffffL;
	v = 0xffff0000L;

	/*Addition algorithm for lower order of given nos.*/
	w = (loworder & u) + (b.loworder & u);
	carry = (w & v) >> 16;
	c.loworder= w & u;
	w = loworder & v;
	z = b.loworder & v;
	w = w >> 16;
	z = z >> 16; 
	w = w + z + carry;
	carry = (w & v) >> 16;
	z = (w & u) << 16;
	c.loworder = c.loworder | z;

	/*Addition algorithm for higher order of given nos.*/
	w = (highorder & u) + (b.highorder & u) + carry;
	carry = (w & v) >> 16;
	c.highorder = w & u;

	w = highorder & v;
	z = b.highorder & v;
	w = w >> 16;
	z = z >> 16;

	/*algorithm to adjust the carry*/
	w = w + z + carry;
	carry = (w & v) >> 16;
	z = (w & u) << 16;
	c.highorder = c.highorder | z;
	c.overflow  = carry;
	return c;
}


/* function definition for overloaded '>>' opreator */
ifstream& operator>>(ifstream&in, bigInt& x)
{
	/*declaration of required variables*/
	char digit;
	bigInt acc;
	unsigned long int number;
	acc.highorder = 0;
	acc.loworder  = 0;
	digit = in.get();

	/*algorithm to detect valid digit*/
	while(isxdigit(digit))
	{
		/*if a digit is just a number from 0 to 9*/
		number = digit - '0';
		if((unsigned)number < 10)
		{
			number = digit - '0';
		}

		/*if digit is alphanumeric character */
		else
		{
			/*if a digit is a hexadecimal number in lower case 'a' to 'f'*/
			 number = digit - 'a' ;
			 if((unsigned) number < 6)
			 {
				 number = digit - 'a' + 10;
			 }
			 /*if a digit is a hexadecimal number in upper case 'A' to 'F'*/
			 else
			 {
				 number = digit -'A';
				 if((unsigned) number < 6)
				 {
					number = digit - 'A' + 10;
				 }
			 }
		}

		acc.shiftLeft(4);
		acc.loworder = acc.loworder | number;
		digit = in.get();
	}
		
	x.loworder  = acc.loworder;
	x.highorder = acc.highorder;
	x.overflow = 0;
	return in;	
}


/* the function for bitwise left shift*/
void bigInt :: shiftLeft(int n)
{
	unsigned long int temp;
	/*if given no is less than 32 bit*/
	if ((0 < n) && (n < 32))
	{
		temp = loworder >> (32-n);
		loworder = loworder << n;
		highorder = highorder << n;
		highorder = highorder | temp;

		/*if given no is less than or equal to 32 and 64 bit or greater*/
		if ((32 <= n) && (n < 64))
		{
			highorder = loworder << (n-32);
			loworder = 0;

		}
	}
}


/* function definition for overloaded '<<' opreator*/
ofstream& operator<<(ofstream&out, bigInt& c)
{
	int n;
	unsigned long int t,x,z;
	x = 0x0000000fL;
	
	/*algorithm for printing higher order of the no*/
	for (n = 28; n >= 0; n -= 4)
	{
		t = c.highorder >> n;
		z = t & x;
		out << hex << z;
	}
	
	/*algorithm for printing lower order of the no*/
	for(n = 28; n >= 0; n -= 4)
	{
		t = c.loworder >> n;
		z = t & x;
		out << hex << z;
	}

	/*algorithm for printing carry if any*/
	if(c.overflow)
	{
		out << 'T' ;

	}

	return out;
}
/*End of Program*/
