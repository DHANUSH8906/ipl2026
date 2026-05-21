#include <stdio.h>

#define MAX 5

struct Student
{
    int roll;
    char name[30];
    float marks;
};

int createIndex(FILE *fp, long pos[])
{
    int count = 0;
    struct Student s;

    rewind(fp);

    while (1)
    {
        pos[count] = ftell(fp);

        if (fscanf(fp, "%d %s %f",
                   &s.roll,
                   s.name,
                   &s.marks) != 3)
        {
            break;
        }

        count++;
    }

    return count;
}

void displayRecord(FILE *fp, long position)
{
    struct Student s;

    fseek(fp, position, SEEK_SET);

    fscanf(fp, "%d %s %f",
           &s.roll,
           s.name,
           &s.marks);

    printf("\nRecord Found:\n");
    printf("Roll  : %d\n", s.roll);
    printf("Name  : %s\n", s.name);
    printf("Marks : %.2f\n", s.marks);
}

int main()
{
    struct Student s[MAX] =
    {
        {1, "Amit", 85.5},
        {2, "Ravi", 90.0},
        {3, "Neha", 78.5},
        {4, "Sita", 88.0},
        {5, "Kiran", 92.5}
    };

    FILE *fp;
    long positions[MAX];
    int i, total;

    fp = fopen("students.txt", "w");

    if (fp == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    for (i = 0; i < MAX; i++)
    {
        fprintf(fp, "%d %s %.2f\n",
                s[i].roll,
                s[i].name,
                s[i].marks);
    }

    fclose(fp);

    fp = fopen("students.txt", "r");

    if (fp == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    total = createIndex(fp, positions);

    printf("Seek Positions:\n");

    for (i = 0; i < total; i++)
    {
        printf("Record %d starts at %ld\n",
               i + 1,
               positions[i]);
    }

    displayRecord(fp, positions[2]);

    fclose(fp);

    return 0;
}