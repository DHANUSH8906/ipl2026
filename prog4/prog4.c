#include <stdio.h>

// Structure with bit-fields
struct BitField {
    unsigned int firstbit : 1;   // Uses only 1 bit
    unsigned int secondbit : 2;  // Uses 2 bits
    unsigned int thirdbit : 3;   // Uses 3 bits
};

int main() {
    struct BitField a;

    // Assign values
    a.firstbit = 1;
    a.secondbit = 3;
    a.thirdbit = 5;

    // Display values
    printf("firstbit  = %u\n", a.firstbit);
    printf("secondbit = %u\n", a.secondbit);
    printf("thirdbit  = %u\n", a.thirdbit);

    printf("Size of structure = %zu bytes\n", sizeof(a));

    return 0;
}