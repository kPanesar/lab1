Lab 1, Making Sense of Zeroes and Ones
======================================
by Karanvir Panesar

Summary: This program reads zeroes and ones from either a text file or stdin. It then reads 8
		 characters at a time and then converts the 8 character binary string to decimal, calculates
		 the parity and determines the ASCII character associated with the decimal value. Any 
		 non-printable character is identified by its mnemonic in accordance with man ASCII. 

		 Currently, all required features function properly. The program ignores all characters 
		 other than '0' and '1' in between sets of 8 characters for text file input. Stdin does 
		 NOT support any spaces. 


Work Log 
---------

###September 2, 2014
	- Added functionality to print mnemonics for non-printable ASCII characters

###September 1, 2014
	- Properly read input via stdin
	- Added functionality to ignore all characters other than '0' and '1' for input via text
	- Defined the print function to print the final output

###August 31, 2014
	- Properly read the input file 8 bytes at a time and stored them into a buffer
	- Defined binaryToDecimal and parityOdd() functions

###August 30, 2014
	- Opened a text file with the open() function
	- Tested the read() funtion to read a text file and print its contents
	- Laid out conditional statements to check the number of arguments and choose between text file or stdin

###August 29, 2014
	- Created skeleton Code
	- Defined function prototypes
