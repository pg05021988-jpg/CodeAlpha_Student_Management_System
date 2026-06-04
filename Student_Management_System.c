#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct Student_Management_System
{
    int id;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void updateStudent();

int main(){
int choise;

while(1){
     printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("enter your choice: ");
        scanf("%d",&choise);

        switch(choise){
            case 1:
                addStudent();
                break;
            
            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("invalid choise!\n");
        }
}
return 0;

}

void addStudent(){
FILE *fp;
struct Student_Management_System s;

fp=fopen("student.dat","ab");

printf("\nEnter Student ID:  ");
scanf("%d",&s.id);

printf("Enter Student Name: ");
scanf(" %[^\n]", s.name);

printf("Enter marks: ");
scanf("%f",&s.marks);

fwrite(&s,sizeof(s),1,fp);
fclose(fp);
printf("Student Record Added Successfully!\n");
}

void displayStudents() {
    FILE *fp;
    struct Student_Management_System s;
    int count = 0;

    fp = fopen("student.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n========================================\n");
    printf("         STUDENT RECORDS\n");
    printf("========================================\n");
    printf("%-6s %-20s %-10s %s\n", "ID", "Name", "Marks", "Grade");
    printf("----------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        char grade;

        // Determine grade based on marks
        if      (s.marks >= 9) grade = 'A';
        else if (s.marks >= 7) grade = 'B';
        else if (s.marks >= 6) grade = 'C';
        else if (s.marks >= 4) grade = 'D';
        else                    grade = 'F';

        printf("%-6d %-20s %-10.2f %c\n", s.id, s.name, s.marks, grade);
        count++;
    }

    fclose(fp);

    if (count == 0) {
        printf("  No student records found.\n");
    }

    printf("----------------------------------------\n");
    printf("Total Students: %d\n", count);
    printf("========================================\n");
}

void searchStudent(){
    FILE *fp;
    struct Student_Management_System s;
    int id,found=0;

    fp=fopen("student.dat","rb");

    if(fp==NULL){
        printf("No record Found!\n");
        return;
    }

    printf("Enter Student ID to Search: ");
    scanf("%d",&id);

    while(fread(&s,sizeof(s),1,fp)==1){

        if(s.id==id){
             printf("\nStudent Found!\n");
            printf("ID: %d\n", s.id);
            printf("Name: %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
            found=1;
            break;
        }
    }
    if(!found){
        printf("Student Not Found!\n");

    }
    fclose(fp);
}

void deleteStudent(){
    FILE *fp,*temp;
    struct Student_Management_System s;
    int id,found=0;

    fp=fopen("student.dat","rb");
    temp=fopen("temp.dat","wb");

    if(fp==NULL){
        
        printf("No records found!\n");
        return;
    }
    if(temp==NULL){
        printf("error creating temporary file!\n");
        fclose(fp);
        return;
    }

    printf("Enter Student ID to Delete: ");
    scanf("%d",&id);

    while(fread(&s,sizeof(s),1,fp)){
        if(s.id==id){
            found=1;
        }else{
            fwrite(&s,sizeof(s),1,temp);
        }
    }
    fclose(fp);
    fclose(temp);

    remove("student.dat");
    rename("temp.dat","student.dat");

    if(found){
        printf("Student Record Delete Succesfully!\n");
    }else{
        printf("Student Not Found!\n");
    }
}

void updateStudent(){
    FILE *fp;
    struct Student_Management_System s;
    int id,found=0;

    fp=fopen("student.dat","rb+");

    if(fp==NULL){
        printf("NO record found!\n");
        return;
    }

    printf("Enter Student ID to Update: ");
    scanf("%d",&id);

    while(fread(&s,sizeof(s),1,fp)){
        if(s.id==id){
            printf("Enter New Name: ");
            scanf(" %[^\n]",s.name);

            printf("Enter New Marks: ");
            scanf("%f",&s.marks);

            fseek(fp,-sizeof(s),SEEK_CUR);

            fwrite(&s,sizeof(s),1,fp);

            found=1;
            break;
        }
    }
    fclose(fp);
    if(found){
        printf("Student Record update Successfully!\n");
    }else{
        printf("Student Not Found!\n");
    }
}
