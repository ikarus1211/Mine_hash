/*
 * Simple hash program that was created for a DSA assigment.
 * The Hash is based on Linear probing and its made just for
 * storing numbers. Hash is also resizable. It takes in account
 * number of filled and empty slots. Based on this it makes
 * decision to resize.
 */




#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Basic global variables
 * size_of_array - this variable specifies the size of hash
 * lambda - is the value on which program makes its decision to resize
 * number_of_inserts is just for counting of inserted variables
 */
int size_of_array;
double lambda;
int number_of_inserted = 0;




int Insert_F(int *ptr, int value);


/*
 * Simple hash function that return a key for given value
 * - argument-  is a number which we will be transforming into key
 * - return value- is a key
 */
int Hash_f(int value)
{
    int result;
    result = value % size_of_array;
    return result;

}

/*
 * Function for resizing main array of slots for hash table
 * It creates a new array and then maps every hashed number again onto bigger
 * table
 */

int* Resize_array(int *ptr)
{
    int counter=0,iterator = 0;
    int *new_ptr;

    size_of_array = size_of_array * 2;
    new_ptr = (int*) calloc(size_of_array, sizeof(int));
    while(counter < number_of_inserted && iterator < size_of_array/2)
    {
        if((*(ptr+iterator)) != 0)
        {
            counter++;
           Insert_F(new_ptr,*(ptr+iterator));
        }
        iterator++;
}
    return new_ptr;
}

/*
 * This function inserts number into right place based on key
 * It also solves collisions by linear probing.
 * 
 */
int Insert_F(int *ptr, int value)
{
    int index;
    int n=0;
    index = Hash_f(value);
    while(1)
    {
        if(index >= size_of_array)
            return 1;
        if( *(ptr+index) == 0)
        {
            *(ptr+index)=value;
            break;
        } else {
            index = index + (int)pow(2,n);
            n++;
        }
    }
    return 0;

}
/*
 * Basic driver of the program.
 * Every addition it checks if lambda is not higher than certain number
 *
 */
int main()
{
   int *ptr;
    size_of_array=10;
    int counter = 0, input_Size = 0;
    ptr = (int*) calloc (size_of_array, sizeof(int));
    printf("\nzadaj pocet inputov\n");
    scanf("%d", &input_Size);
    int number;
    while (counter < input_Size) {
        lambda = (double) number_of_inserted / size_of_array;
        if (lambda > 0.5) {
            printf("%p", ptr);
            ptr = Resize_array(ptr);
            printf("%p", ptr);
        }
        counter++;
        scanf("%d", &number);
        number_of_inserted++;
        while (Insert_F(ptr, number)){
            ptr =  Resize_array(ptr);

        }
        for (int i=0;i<20;i++)
            printf("|%d| ",*(ptr+i));
        printf("\n");
    }

    return 0;
}