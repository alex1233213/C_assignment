/**
Assignment 2

Security authorisation program.

Program which allows user to input a password which then gets stored into
an array of characters. This password can be encrypted, if it hasn't been already
encrypted. The password can also be decrypted, if it hasn't been decrypted already.
If the user enters a invalid password, i.e. not 4 digits long or non-numerical values,
the option to encrypt the password will not be available for the user to use.

The default access code for this program is 4523. This is an encrypted code for the
password 1234.

Program is menu driven. Menu will be continually be displayed unless user chooses to
exit the program.

The following are the options given in the menu:

1. Allows user to input a code.
2. Encrypts the code and compares it with the access code to indicate if it's correct.
3. Decrypts the code.
4. Displays the amount of times the user has entered the code correctly/ incorrectly.
5. Exits the program.

Alexandru Bulgari

C18342126
*/

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Symbolic names
#define SIZE 10
#define FIRST 0
#define SECOND 1
#define THIRD 2
#define FOURTH 3
#define PINLEN 4
#define NINE 9
#define TEN 10
#define MIN -1

//Function prototypes
void printStars(void);//Prints stars
char* enterCode(bool*, int*);//allows user to enter code
void crptAndVerify(char*, char*, int*, int*);//encrypts password and verifies if it's right/wrong
void decrypt(char*);//decrypts password
void displayAttempts(int*, int*);//Displays how many times password has been entered correctly/incorrectly


int main()
{
    //declaring variables
    int choice;
    char *access_code = "4523";
    char *user_code;
    int sAttempts = 0;
    int uAttempts = 0;
    bool code_entered = false;
    bool restricted = false;
    bool encrypted = false;
    bool decrypted = false;


    //Run program on a continual basis unless user chooses to end program
    while(choice != 5)
    {
        //Print menu
        printStars();
        printf("Security authorisation program\n\n");
        printf("Choose one of the following options\n\n");
        printf("Enter 1 to enter your access code\n\n");
        printf("Enter 2 to encrypt your access code and verify if it's correct\n\n");
        printf("Enter 3 to decrypt your access code\n\n");
        printf("Enter 4 to display the amount of times the code has been entered successfuly/ unsuccessfully\n\n");
        printf("Enter 5 to exit program\n\n");
        printStars();

        //Take user's input
        scanf("%d", &choice);

        switch(choice)//start switch statement
        {
            case 1://allows user to enter code
                //call enterCode()
                user_code = enterCode(&restricted, &uAttempts);
                encrypted = false;
                decrypted = false;
                code_entered = true;
                break;


            case 2://encrypt the users code and verify if its correct
                //check if code has been already encrypted
                if(encrypted == true)//check if code has already been encrypted
                {
                    printf("Your code has already been encrypted\n");
                }
                else//call crptAndVerify()
                {
                    if(restricted == true)//restricted is true when user enters an invalid code
                    {
                        printf("You must enter a valid code before encrypting it\n");
                    }
                    else if(code_entered == false)//if user hasn't entered a code
                    {
                        printf("Error: no code has been entered\n");
                    }
                    else//call crptAndVerify()
                    {
                        crptAndVerify(user_code, access_code, &sAttempts, &uAttempts);
                        //After function call, the code is encrypted
                        encrypted = true;
                    }
                }
                break;


            case 3://decrypt the users code
                if(decrypted == false)//check if code has not been decrypted
                {
                    if(encrypted == true)//check if code has already been encrypted
                    {
                        //call decrypt()
                        decrypt(user_code);
                        //code becomes decrypted
                        decrypted = true;
                    }
                    else//code has not been encrypted
                    {
                        printf("You must encrypt your code in order to be able to decrypt it\n");
                    }
                }
                else//code already decrypted
                {
                    printf("You code has already been decrypted\n");
                }

                break;

            case 4: //display the users correct/ incorrect attempts of entering the code
                //call displayAttempts
                displayAttempts(&sAttempts, &uAttempts);
                break;

            case 5:
                //exit program
                printf("Program has ended\n\n");
                free(user_code);//free memory
                return 0;
                break;

            //Any other option
            default:
                printf("You have not entered a valid option\n\n");
        }//end switch
    }//end while
    //free memory
    free(user_code);
}//end main

//Implement enterCode()
char* enterCode(bool *rstrct, int *failure_attempt)
{
    //Declaring variables
    char *code;
    int len;
    int i;
    int digitVerify = 0;

    //Allocate memory
    code = calloc(SIZE, sizeof(char));

    //Check if memory has been allocated
    if(code == NULL)
    {
        printf("Error: Could not allocate memory\n\n");//Inform user
    }
    else
    {
        //Get input from user
        printf("Enter your 4 digit code. Choose from numbers 0 - 9 \n\n");

        scanf("%s", &*code);
    }


    //length variable
    len = strlen(code);

    //start a loop to go through all the digits of the code
    for (i = 0; i < len; i++)
    {
        //check for code if it contains the correct digits
        if (*(code + i) == '1' || *(code + i) == '2'
            || *(code + i) == '3' || *(code + i) == '4'
            || *(code + i) == '5' || *(code + i) == '6'
            || *(code + i) == '7' || *(code + i) == '8'
            || *(code + i) == '9')
            {
                digitVerify++;
            }//end if
    }//end for

    if(digitVerify == PINLEN && len == PINLEN)
    {
        *rstrct = false;
        return code;
    }
    else
    {
        printf("Error: invalid input\n");
        *failure_attempt = *failure_attempt + SECOND;
        *rstrct = true;
        return NULL;
    }

}//end enterCode()

//Implement printStars()
void printStars(void)
{
    printf("*************************************************************************************************\n");
}

//Implement crptAndVerify
void crptAndVerify(char *code_encrypt, char *axes_code, int *sATT, int *uATT)
{
    //declaring variables
    int i;
    int nums[SIZE];
    int tmp;
    int tmp2;
    int len;
    int *ptr;

    //length of code
    len = strlen(code_encrypt);


    //pointing to the integer array
    ptr = nums;

    //Allocate memory for nums
    ptr = calloc(SIZE, sizeof(int));

    //Check if memory is allocated
    if(ptr == NULL)
    {
        printf("Error: could not allocate memory\n");
    }
    else
    {
        //converting string to integers
        for(i = 0; i < len; i++)
        {
            *(nums + i) = (int)( *(code_encrypt + i) - '0');
        }
    }//end else

    //Encrypting the code
    for(i = 0; i < len; i++)
    {
        if(i == FIRST)
        {
            //swapping first and third element
            tmp = *(nums + i);
            *(nums + i) = *(nums + THIRD);
            *(nums + THIRD) = tmp;

            //adding 1 to both elements
            *(nums + i) = *(nums + i) + SECOND;
            if( *(nums + i) == TEN)//check if the number has a value of 10
            {
                *(nums + i) = FIRST;//10 = 0
            }

            *(nums + THIRD) = *(nums + THIRD) + SECOND;
            if( *(nums + THIRD) == TEN)//check if third number is 10
            {
                *(nums + THIRD) = FIRST;//10 = 0
            }
        }//end if

        if(i == SECOND)
        {
            //swapping the second and fourth element
            tmp2 = *(nums + i);
            *(nums + i) = *(nums + FOURTH);
            *(nums + FOURTH) = tmp2;

            //adding 1 to both elements
            *(nums + i) = *(nums + i) + SECOND;
            if( *(nums + i) == TEN)//check if the digit is 10
            {
                *(nums + i) = FIRST;//10 = 0
            }

            *(nums + FOURTH) = *(nums + FOURTH) + SECOND;
            if( *(nums + FOURTH) == TEN)
            {
                *(nums + FOURTH) = FIRST;
            }
        }//end if

        //assigning encrypted digits back into the string code
        *(code_encrypt + i) = (char)( *(nums + i) + '0');
    }//end for

    if(strcmp(code_encrypt, axes_code) == 0 )//check if encrypted code matches the access code
    {
        printf("Correct Code entered\n");
        *sATT = *sATT + SECOND;//increment successful attempts
    }
    else
    {
        printf("Wrong Code entered\n");
        *uATT = *uATT + SECOND;//increment unsuccessful attempts
    }

    free(ptr);//free allocated memory
}//end crptAndVerify

//Implement decrypt
void decrypt(char *u_code)
{
    //declaring variables
    int i;
    int num_values[SIZE];
    int *point;
    int leng;
    int temp;
    int temp2;

    //length of array
    leng = strlen(u_code);

    //set pointer to adress of first element in num_values
    point = num_values;

    //Allocate memory for num_values
    point = calloc(SIZE, sizeof(int));

    //Check if memory has been allocated
    if(point == NULL)
    {
        printf("Error: could not allocate memory\n");
    }
    else//convert string to integers
    {
        for(i = 0; i < leng; i++)
        {
            *(num_values + i) = (int)( *(u_code + i) - '0');
        }
    }//end else


    //decrypt the digits

    //subtract 1 from each value
    for(i = 0; i < leng; i++)
    {
        *(num_values + i) = *(num_values + i) - SECOND;
        if( *(num_values + i) == MIN)//check if digit is -1
        {
            *(num_values + i) = NINE;//-1 = 9
        }
    }//end for

    //change positions in the array
    for(i = 0; i < leng; i++)
    {
        //checks if its the first number
        if(i == FIRST)
        {
            //swap first number with third number
            temp = *(num_values + i);
            *(num_values + i) = *(num_values + THIRD);
            *(num_values + THIRD) = temp;
        }//end if
        //check if its the second number
        if(i == SECOND)
        {
            //swap the second number with fourth number
            temp2 = *(num_values + i);
            *(num_values + i) = *(num_values + FOURTH);
            *(num_values + FOURTH) = temp2;
        }//end if
    }//end for

    //return the decrypted digits back into the original string array
    for(i = 0; i < leng; i++)
    {
        *(u_code + i) = (char)( *(num_values + i) + '0' );
    }//end for

    //free allocated memory
    free(point);

}//end decrypt

//Implement displayAttempts()
void displayAttempts(int *s_a, int *u_a)
{
    printf("You entered your code %d times successfully\n", *s_a);
    printf("You entered your code %d times incorrectly\n", *u_a);
}
