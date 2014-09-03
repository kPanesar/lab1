#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <String.h>
#include <math.h>

#define MAX_LEN 128

/*int readFile(int fd, char *buffer);*/
int binaryToDecimal(char *data);
int parityOdd(char *data);
void print (char *data, int decimal, int parityOdd);

int main(int argc, char const *argv[])
{
	int fd = 0, bytesRead, decimal, index;
	char buf[8], space[1];

	if(argc > 2){
		printf("Error: Too many arguments!\n");
	}
	else if (argc > 1 && strcmp(argv[1], "-") != 0){ //A file name is provided
		fd = open(argv[1], O_RDONLY) ;

		if(fd == -1){
			printf("There was an error opening the file! Please check the file name.\n");
		}
		else{
			printf("Original\tASCII\tDecimal\tParity\tT.Error\n");
			printf("--------\t-----\t-------\t------\t-------\n");

			while((bytesRead = read(fd, buf, 8)) > 0){ //Until not EOF

				if(bytesRead < 8){ //Insert zeroes in place of missing characters
					for (index = bytesRead; index < 8; index++){
						buf[index] = '0';
					}
				}
				print(buf, binaryToDecimal(buf), parityOdd(buf));

				//Ignore all characters other than '0' and '1' in between character sets
				if(read(fd, space, 1)){
					while(!(space[0] == '0' || space[0] == '1')){
						read(fd, space, 1);
					}
				lseek( fd, -1, SEEK_CUR); //Move offset back to where the space ends
				}
			}
		}
	}
	else{ //No input file provided, use std	in
		//int firstTime = 1;

		//printf("Using Stdin. Please input data and press 'Enter' to submit.\n\nInput: ");
		printf("\nOriginal\tASCII\tDecimal\tParity\tT.Error\n");
		printf("--------\t-----\t-------\t------\t-------\n");

		while((bytesRead = read(0, buf, 8)) > 0 && buf[0] != '\n'){ // '\n' denotes end of input
			if(bytesRead < 8){ //Insert zeroes in place of missing characters
				for (index = bytesRead-1; index < 8; index++){ //The -1 is to replace '\n' character
					buf[index] = '0';
				}
			}
			print(buf, binaryToDecimal(buf), parityOdd(buf));
		}
	}

	return 0;
}


//////////////////////Function Definitions///////////////////////////

int binaryToDecimal(char *data){
	int index, curDigit, sum = 0;

	for(index = 1; index < 8; index++){ //Ignore MSB (Parity Bit)
		curDigit = data[index] - '0'; //Convert character to integer
		sum += curDigit*pow(2,7-index);
	}
	return sum;
}

int parityOdd(char *data){
	int index, curDigit, sum = 0;

	for (index = 0; index < 8; index++){
		curDigit = data[index] - '0'; //Convert character to integer
		sum += curDigit;
		//printf("%d", sum);
	}
	return sum%2; //Return 1 if odd, 0 if even
}

void print (char *data, int decimal, int parityOdd){
	int index;
	const char* asciiMnemonics[] = {"NUL", "SOH", "STX", "ETX", "EOT", "ENQ", 
	"ACK", "BEL", "BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI", "DLE", 
	"DC1", "DC2","DC3","DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", 
	"ESC", "FS", "GS", "RS", "US", "SPACE", "DEL"};

	for (index = 0; index < 8; index++){
		printf("%c", data[index]);
	}

	//Print ASCII and Decimal
	if(decimal < 33 || decimal == 127){
		if(decimal == 127) printf("\t%c\t%d\t", asciiMnemonics[33], decimal);
		else printf("\t%s\t%d\t", asciiMnemonics[decimal], decimal);
	}
	else printf("\t%c\t%d\t", decimal, decimal);

	if (parityOdd == 1)
	{
		printf("ODD\tTRUE\n");
	}
	else printf("EVEN\tFALSE\n");
}