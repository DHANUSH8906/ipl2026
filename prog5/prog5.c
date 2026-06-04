#include <stdio.h>

union decision
{
    unsigned char flags;

    struct
    {
        unsigned int your_choice : 1;
        unsigned int your_mothers_choice : 1;
        unsigned int your_fathers_choice : 1;
        unsigned int socially_acceptable : 1;
        unsigned int financially_viable : 1;
        unsigned int do_you_have_aptitude : 1;
        unsigned int do_you_like_it : 1;
        unsigned int decision : 1;
    } field;
};

union decision input();
void make_decision(union decision *d);
void print_decision(union decision d);
void print_conclusion_based_on_flags(union decision d);

int main()
{
    union decision d;

    d = input();

    make_decision(&d);

    print_decision(d);

    print_conclusion_based_on_flags(d);

    return 0;
}

union decision input()
{
    union decision d;
    unsigned int temp;

    d.flags = 0;

    printf("Your choice (0/1): ");
    scanf("%u", &temp);
    d.field.your_choice = temp;

    printf("Your mother's choice (0/1): ");
    scanf("%u", &temp);
    d.field.your_mothers_choice = temp;

    printf("Your father's choice (0/1): ");
    scanf("%u", &temp);
    d.field.your_fathers_choice = temp;

    printf("Socially acceptable (0/1): ");
    scanf("%u", &temp);
    d.field.socially_acceptable = temp;

    printf("Financially viable (0/1): ");
    scanf("%u", &temp);
    d.field.financially_viable = temp;

    printf("Do you have aptitude? (0/1): ");
    scanf("%u", &temp);
    d.field.do_you_have_aptitude = temp;

    printf("Do you like it? (0/1): ");
    scanf("%u", &temp);
    d.field.do_you_like_it = temp;

    return d;
}

void make_decision(union decision *d)
{
    d->field.decision =
        d->field.your_choice &&
        d->field.financially_viable &&
        d->field.do_you_have_aptitude &&
        d->field.do_you_like_it;
}

void print_decision(union decision d)
{
    printf("\n----- Decision Report -----\n");

    printf("Your Choice          : %u\n", d.field.your_choice);
    printf("Mother's Choice      : %u\n", d.field.your_mothers_choice);
    printf("Father's Choice      : %u\n", d.field.your_fathers_choice);
    printf("Socially Acceptable  : %u\n", d.field.socially_acceptable);
    printf("Financially Viable   : %u\n", d.field.financially_viable);
    printf("Aptitude             : %u\n", d.field.do_you_have_aptitude);
    printf("You Like It          : %u\n", d.field.do_you_like_it);

    if (d.field.decision)
        printf("\nFinal Decision: GO FOR IT!\n");
    else
        printf("\nFinal Decision: RECONSIDER IT.\n");
}

void print_conclusion_based_on_flags(union decision d)
{
    printf("\nFlags Value = %u\n", d.flags);

    if (d.flags >= 200)
        printf("Conclusion: Excellent overall support.\n");
    else if (d.flags >= 100)
        printf("Conclusion: Moderate support. Think carefully.\n");
    else
        printf("Conclusion: Weak support. Re-evaluate your choice.\n");
}