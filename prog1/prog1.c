#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char name[30];
    float marks;
} Student;

/* Function Prototypes */
void addRecords(char *filename, int n);
void displayRecord(char *filename, int m);
void deleteRecord(char *filename, int del_id);

int main()
{
    int n, m, choice, del_id;
    char filename[] = "students.dat";

    printf("Enter number of records: ");
    scanf("%d", &n);

    addRecords(filename, n);

    printf("\nEnter record number to display: ");
    scanf("%d", &m);

    displayRecord(filename, m);

    printf("\nEnter ID of record to delete: ");
    scanf("%d", &del_id);

    deleteRecord(filename, del_id);

    printf("\nRecords after deletion:\n");

    /* Display all remaining records */
    FILE *fp = fopen(filename, "rb");
    Student s;

    while (fread(&s, sizeof(Student), 1, fp))
    {
        printf("ID: %d\n", s.id);
        printf("Name: %s\n", s.name);
        printf("Marks: %.2f\n\n", s.marks);
    }

    fclose(fp);

    return 0;
}

/* Function to add records into binary file */
void addRecords(char *filename, int n)
{
    FILE *fp;
    Student s;

    fp = fopen(filename, "wb");

    if (fp == NULL)
    {
        printf("File cannot be opened\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Enter ID: ");
        scanf("%d", &s.id);

        printf("Enter Name: ");
        scanf("%s", s.name);

        printf("Enter Marks: ");
        scanf("%f", &s.marks);

        fwrite(&s, sizeof(Student), 1, fp);
    }

    fclose(fp);
}

/* Function to get mth record using fseek */
void displayRecord(char *filename, int m)
{
    FILE *fp;
    Student s;

    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }

    /* Move file pointer to mth record */
    fseek(fp, (m - 1) * sizeof(Student), SEEK_SET);

    if (fread(&s, sizeof(Student), 1, fp))
    {
        printf("\nMth Record Details:\n");
        printf("ID: %d\n", s.id);
        printf("Name: %s\n", s.name);
        printf("Marks: %.2f\n", s.marks);
    }
    else
    {
        printf("Record not found\n");
    }

    fclose(fp);
}

/* Function to delete a record */
void deleteRecord(char *filename, int del_id)
{
    FILE *fp, *temp;
    Student s;
    int found = 0;

    fp = fopen(filename, "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    /* Copy all records except deleted one */
    while (fread(&s, sizeof(Student), 1, fp))
    {
        if (s.id != del_id)
        {
            fwrite(&s, sizeof(Student), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    /* Replace original file with temp file */
    remove(filename);
    rename("temp.dat", filename);

    if (found)
        printf("Record deleted successfully\n");
    else
        printf("Record not found\n");
}