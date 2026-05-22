#include <stdio.h>

// Function to print the bits of a standard 32-bit integer
void printBits(int n) {
    // Loop from the most significant bit (31) down to the least significant (0)
    for (int i = 31; i >= 0; i--) {
        int bit = (n >> i) & 1;
        printf("%d", bit);
        
        // Add a space every 4 bits for easier reading
        if (i % 4 == 0) printf(" ");
    }
    printf("\n");
}

// Function to count the number of 1 bits (Brian Kernighan's Algorithm)
int countOneBits(int n) {
    int count = 0;
    while (n != 0) {
        n = n & (n - 1); // Clears the lowest set bit
        count++;
    }
    return count;
}

int main() {
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
    printf("Bits of %d: ", num);
    printBits(num);
    
    printf("Number of 1 bits: %d\n", countOneBits(num));
    return 0;
}