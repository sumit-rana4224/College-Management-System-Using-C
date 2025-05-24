#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct sd
{
    int sreg_no, sl_no, fees;
    float cgpa, p2, boards, attendance;
    char name[50], state[25], district[50], father_name[50];
    char password[20];
} student_data;

typedef struct fd
{
    int freg_no, salary;
    float p2, cgpa;
    char name[50], father_name[50], state[25], district[50];
    char password[20];
} faculty_data;

typedef struct s
{
    student_data *adds;
    struct s *next_stud;
} student;

typedef struct f
{
    faculty_data *addf;
    struct f *next_faculty;
} faculty;
student *top_stud = NULL;
faculty *top_faculty = NULL;
int serial_no = 1;
char admin_p[20];
int att;
int reg_count_stud;
int reg_count_faculty;
int disp = 0;


char *get_password()
{
    char *password = (char *)malloc(20);
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == 13)
            break;
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    return password;
}

void get_valid_name(char *prompt, char *dest, int max_len) {
    char input[100];
    int valid = 0;

    while (!valid) {
        printf("%s", prompt);
        scanf("\n%[^\n]s", input);

        int len = strlen(input);

        if (len < 3) {
            printf("\033[1;91m[!] Name must be at least 3 characters long.\033[0m\n");
            continue;
        }


        valid = 1;
        for (int i = 0; i < len; i++) {
            char ch = input[i];
            if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == ' ')) {
                printf("\033[1;91m[!] Name can contain only letters and spaces.\033[0m\n");
                valid = 0;
                break;
            }
        }

        if (valid) {
            strcpy(dest, input);
        }
    }
}
void admin_notice(char *message,int id)
{
    FILE *notice =fopen("allnotice.txt","w");
    if(notice != NULL)
    {
        fprintf(notice,"%d.%s",id,message);
    }
}
void load_admin_data() 
{
    FILE *fp = fopen("admin.txt", "r");
    if (fp != NULL) 
    {
        fscanf(fp, "%s %d %d %d", admin_p, &att, &reg_count_stud, &reg_count_faculty);
        fclose(fp);
    } 
    else 
    {

        strcpy(admin_p, "admin1234");
        att = 0;
        reg_count_faculty = 27711111; 
        reg_count_stud = 47711111;
    }
}

void save_admin_data() 
{
    FILE *fp = fopen("admin.txt", "w");
    if (fp != NULL) 
    {
        fprintf(fp, "%s %d %d %d", admin_p, att,reg_count_stud,reg_count_faculty);
        fclose(fp);
    }
}

void change_admin_password() {
    char new_pass[20];
    printf("Enter New Admin Password: ");
    strcpy(new_pass, get_password());
    puts("");
    strcpy(admin_p, new_pass);
    save_admin_data();
    printf("\033[1;32mAdmin Password Changed Successfully!\033[0m\n");
}


float getValidSalary() 
{
    float value;
    char ch;

    while (1) 
    {
        printf("Enter a non-negative integer: ");
        if (scanf("%f%c", &value, &ch) == 2 && ch == '\n') 
        {
            if (value >= 20000.00f) 
            {
                return value;
            } 
            else 
            {
                printf("Invalid input! Value must not be negative.\n");
            }
        } 
        else 
        {
            printf("Invalid input! Please enter an integer only.\n");
            while ((ch = getchar()) != '\n' && ch != EOF); 
        }
    }
}
float getValidFloat() 
{
    float value;
    char ch;

    while (1) 
    {
        if (scanf("%f%c", &value, &ch) == 2 && ch == '\n') 
        {
            if (value >= 0.0f && value <= 100.0f) 
            {
                return value;
            } 
            else 
            {
                printf("Invalid input! Value must not be negative.\n");
            }
        }
        else 
        {
            printf("Invalid input! Please enter a float number only.\n");
            while ((ch = getchar()) != '\n' && ch != EOF); 
        }
    }
}

float getValidCgpa() 
{
    float value;
    char ch;

    while (1) 
    {
        if (scanf("%f%c", &value, &ch) == 2 && ch == '\n') 
        {
            if (value >= 0.0f && value <= 10.0f) 
            {
                return value;
            } 
            else 
            {
                printf("Invalid input! Value must not be negative.\n");
            }
        }
        else 
        {
            printf("Invalid input! Please enter a float number only.\n");
            while ((ch = getchar()) != '\n' && ch != EOF); 
        }
    }
}

void add_student(student_data *temp)
{
    student *nws = (student *)malloc(sizeof(student));
    nws->adds = temp;
    nws->next_stud = NULL;

    if (top_stud == NULL)
    {
        top_stud = nws;
    }
    else
    {
        student *t = top_stud;
        while (t->next_stud != NULL)
            t = t->next_stud;
        t->next_stud = nws;
    }
    if(disp)
    {
        puts("\033[1;32mStudent Added Successfully.");
        printf("Student %s's Registration Number is: %d\n\033[0m", temp->name, temp->sreg_no);
    }
}
void add_faculty(faculty_data *temp)
{
    faculty *nwf = (faculty *)malloc(sizeof(faculty));
    nwf->addf = temp;
    nwf->next_faculty = NULL;

    if (top_faculty == NULL)
    {
        top_faculty = nwf;
    }
    else
    {
        faculty *t = top_faculty;
        while (t->next_faculty != NULL)
            t = t->next_faculty;
        t->next_faculty = nwf;
    }
    if(disp)
    {
        puts("\033[1;32mFaculty Added Successfully.");
        printf("Faculty %s's Registration Number is: %d\n\033[0m", temp->name, temp->freg_no);
    }
}

void delete_student()
{
    int reg;
    printf("Enter Registration No to delete: ");
    scanf("%d", &reg);

    student *t = top_stud, *prev = NULL;

    while (t != NULL)
    {
        if (t->adds->sreg_no == reg)
        {
            if (prev == NULL)
                top_stud = t->next_stud;
            else
                prev->next_stud = t->next_stud;

            free(t->adds);
            free(t);
            printf("\033[1;32mStudent Deleted Successfully\033[0m\n");
            
            return;
        }
        prev = t;
        t = t->next_stud;
    }
        printf("\033[1;91m[!] No Student Found\n\033[0m");
}
void delete_faculty()
{
    int reg;
    printf("Enter Registration No to delete: ");
    scanf("%d", &reg);

    faculty *t = top_faculty, *prev = NULL;

    while (t != NULL)
    {
        if (t->addf->freg_no == reg)
        {
            if (prev == NULL)
                top_faculty = t->next_faculty;
            else
                prev->next_faculty = t->next_faculty;

            free(t->addf);
            free(t);
            printf("\033[1;32mFaculty Deleted Successfully\033[0m\n");
            return;
        }
        prev = t;
        t = t->next_faculty;
    }
    printf("\033[1;91m[!] Faculty Not Found\n\033[0m");
}
void see_student_details()
{
    student *t = top_stud;
    if (t == NULL)
    {
        printf("\033[1;91m[!] No Student Data Available\n\033[0m");
        return;
    }

    printf("\n\033[1;94m---- Student Details ----\033[0m\n");

    // Table header
    printf("\033[1;96m%-5s %-20s %-10s %-20s %-12s %-15s %-6s %-8s %-8s %-6s %-10s\n\033[0m",
           "Sl", "Name", "Reg No", "Father's Name", "State", "District", "CGPA", "12th%", "10th%", "Fees", "Attendance");

    // Table rows
    while (t != NULL)
    {
        printf("%-5d %-20s %-10d %-20s %-12s %-15s %-6.2f %-8.2f %-8.2f %-6d %-10.2f\n",
               t->adds->sl_no,
               t->adds->name,
               t->adds->sreg_no,
               t->adds->father_name,
               t->adds->state,
               t->adds->district,
               t->adds->cgpa,
               t->adds->p2,
               t->adds->boards,
               t->adds->fees,
               t->adds->attendance);
        t = t->next_stud;
    }
}

void see_faculty_details()
{
    faculty *t = top_faculty;
    if (t == NULL)
    {
        printf("\033[1;91m[!] No Faculty Data Available\n\033[0m");
        return;
    }

    printf("\n\033[1;94m---- Faculty Details ----\033[0m\n");
    printf("\033[1;96m%-4s %-30s %-15s %-20s %-15s %-15s %-8s %-10s %-10s\n\033[0m",
           "No", "Name", "Reg No", "Father's Name", "State", "District", "CGPA", "12th %%", "Salary");

    int i = 1;
    while (t != NULL)
    {
        printf("%-4d %-30s %-15d %-20s %-15s %-15s %-8.2f %-10.2f %-10d\n",
               i++, t->addf->name, t->addf->freg_no, t->addf->father_name,
               t->addf->state, t->addf->district, t->addf->cgpa,
               t->addf->p2, t->addf->salary);
        t = t->next_faculty;
    }
}

int compare_students(const void *a, const void *b)
{
    student *studA = *(student **)a;
    student *studB = *(student **)b;

    if (studA->adds->cgpa < studB->adds->cgpa) return 1;
    if (studA->adds->cgpa > studB->adds->cgpa) return -1;
    return 0;
}
void print_students_rankwise()
{
    student *t = top_stud;
    if (t == NULL)
    {
        printf("\033[1;91m[!] No Student Data Available\n\033[0m");
        return;
    }
    int count = 0;
    student *temp = t;
    while (temp != NULL)
    {
        count++;
        temp = temp->next_stud;
    }
    student **students = (student **)malloc(count * sizeof(student *));
    temp = t;
    for (int i = 0; i < count; i++)
    {
        students[i] = temp;
        temp = temp->next_stud;
    }
    qsort(students, count, sizeof(student *), compare_students);
    FILE *fp = fopen("ranklist.txt", "w");
    if (fp == NULL)
    {
        printf("\033[1;91m[!] Error: Could not open ranklist.txt for writing.\033[0m\n");
        free(students);
        return;
    }
    printf("\n\033[1;92m=== Student Rankings ===\033[0m\n");
    fprintf(fp, "=== Student Rankings ===\n");
    int rank = 1;
    for (int i = 0; i < count; i++)
    {
        if (i > 0 && students[i]->adds->cgpa < students[i - 1]->adds->cgpa)
        {
            rank = i + 1;
        }
        printf("Rank %d: %s (Reg No: %d) - CGPA: %.2f\n",
               rank,
               students[i]->adds->name,
               students[i]->adds->sreg_no,
               students[i]->adds->cgpa);

        fprintf(fp, "Rank %d: %s Reg No: %d - CGPA: %.2f\n",
                rank,
                students[i]->adds->name,
                students[i]->adds->sreg_no,
                students[i]->adds->cgpa);
    }

    fclose(fp);
    free(students);

    printf("\n\033[1;94m[~] Rank list saved to 'ranklist.txt'\033[0m\n");
}

student_data *fill_stud_detls()
{
    student_data *temp = (student_data *)malloc(sizeof(student_data));


    get_valid_name("Enter Name: ", temp->name, sizeof(temp->name));
    get_valid_name("Enter Father's Name: ", temp->father_name, sizeof(temp->father_name));
    get_valid_name("Enter State: ", temp->state, sizeof(temp->state));
    get_valid_name("Enter District: ", temp->district, sizeof(temp->district));
    printf("Enter CGPA: ");
    temp->cgpa =getValidCgpa();
    printf("Enter 12th Percentage: ");
    temp->p2 = getValidFloat();
    printf("Enter 10th Percentage: ");
    temp->boards = getValidFloat();
    printf("Enter Fees Status (1 for Paid, 0 for Unpaid): \033[0m");
    temp->fees = getValidFloat();
    temp->sreg_no = reg_count_stud++;

    temp->attendance = 0;
    temp->sl_no = serial_no++;

    sprintf(temp->password, "%d", temp->sreg_no);

    return temp;
}
faculty_data *fill_fac_detls()
{
    faculty_data *temp = (faculty_data *)malloc(sizeof(faculty_data));

    get_valid_name("Enter Name: ", temp->name, sizeof(temp->name));
    get_valid_name("Enter Father's Name: ", temp->father_name, sizeof(temp->father_name));
    get_valid_name("Enter State: ", temp->state, sizeof(temp->state));
    get_valid_name("Enter District: ", temp->district, sizeof(temp->district));
    printf("Enter CGPA: ");
    temp->cgpa = getValidCgpa();
    printf("Enter 12th Percentage: ");
    temp->p2 = getValidFloat();
    printf("Enter Salary: \033[0m");
    temp->salary = getValidSalary();
    temp->freg_no = reg_count_faculty++;
    sprintf(temp->password, "%d", temp->freg_no);

    return temp;
}
void change_stud_pass()
{
    int reg_no;
    char new_pass[20];
    printf("Enter Registration No: ");
    scanf("%d", &reg_no);
    printf("Enter New Password: ");
    strcpy(new_pass, get_password());

    student *t = top_stud;
    while (t != NULL)
    {
        if (t->adds->sreg_no == reg_no)
        {
            strcpy(t->adds->password, new_pass);
            printf("\033[1;32mPassword Changed Successfully\033[0m\n");
            return;
        }
        t = t->next_stud;
    }
    printf("\033[1;91m[!] Student Not Found\n\033[0m");
}
void change_fac_pass()
{
    int reg_no;
    char new_pass[20];
    printf("Enter Registration No: ");
    scanf("%d", &reg_no);
    printf("Enter New Password: ");
    scanf("%s", new_pass);

    faculty *t = top_faculty;
    while (t != NULL)
    {
        if (t->addf->freg_no == reg_no)
        {
            strcpy(t->addf->password, new_pass);
            printf("\033[1;32mPassword Changed Successfully\033[0m\n");
            
            return;
        }
        t = t->next_faculty;
    }
    printf("\033[1;91m[!] Faculty Not Found\n\033[0m");

}
int opt_admin()
{
    int res;
    printf("\033[1;96m");
    printf("\n--- Admin Menu ---\n");

    puts("1.  Add Faculty");
    puts("2.  Add Student");
    puts("3.  Check Rankwise Students List");
    puts("4.  See Faculty Details");
    puts("5.  See Students Details");
    puts("6.  Delete Faculty");
    puts("7.  Delete Student");
    puts("8.  Change Student Password");
    puts("9.  Change Faculty Password");
    puts("10. Change Admin Password");
    puts("11. Logout");
    printf("Enter Choice: \033[0m");
    scanf("%d", &res);
    return res;
}
int opt_faculty()
{
    int res;
    printf("\n\033[1;96m--- Faculty Menu ---\n");
    puts("1. See Personal Details");
    puts("2. Upload Marks");
    puts("3. Take Attendance");
    puts("4. Logout");
    printf("Enter Choice: \033[0m");
    scanf("%d", &res);
    return res;
}
int opt_student()
{
    int res;
    printf("\n\033[1;96m--- Student Menu ---\n");
    puts("1. See Personal Details");
    puts("2. See Marks");
    puts("3. See Attendance");
    puts("4. Logout");
    printf("Enter Choice: \033[0m");
    scanf("%d", &res);
    return res;
}
void take_attendance()
{
    int attend;
    printf("\033[1;35m\n---- Take Attendance ----\n\033[0m");
    printf("If Student is present enter 1 else 0: ");
    student *t = top_stud;
    if(t==NULL)
    {
        printf("\033[1;91m[!] Student Not Found\n\033[0m");
        return;
    }
    while (t != NULL)
    {
       printf("%d--> %s's attendance: ", t->adds->sreg_no, t->adds->name);
       scanf("%d",&attend);
       if (attend == 1)
        {
            t->adds->attendance += 1;
            printf("\033[1;32mAttendance Updated Successfully\033[0m\n");
        }
        else if (attend == 0)
        {
                t->adds->attendance += 1;
                printf("\033[1;32mAttendance Updated Successfully\033[0m\n");
        }
        else
        {
            printf("\033[1;91m[!] Invalid Input\n\033[0m");
            return;
        }
        
        t = t->next_stud;
    }
    att++;

}
void see_attendance(int reg_no)
{
    student *t = top_stud;
    while (t != NULL)
    {
        if (t->adds->sreg_no == reg_no)
        {
            printf("Attendance: %.2f %%\n", (t->adds->attendance /att)*100);
            return;
        }
        t = t->next_stud;
    }
    return;
}
void upload_marks()
{
    int reg_no=1;
    float marks;
    printf("\033[1;35m\n---- Upload Marks ----\n\033[0m");
    while(reg_no)
    {
        puts("Enter Registration No:    (Else 0 to exit)");
        scanf("%d", &reg_no);
        student *t = top_stud;
        while (t != NULL)
        {
            if (t->adds->sreg_no == reg_no)
            {
                printf("Enter Mark of '%s' (out of 10): ",t->adds->name);
                scanf("%f", &marks);
                if (marks < 0 || marks > 10)
                {
                    printf("\033[1;91m[!] Invalid Marks Enter mark between 0-10\n\033[0m");
                    return;
                }
                if(t->adds->cgpa == 0)
                {
                    t->adds->cgpa = marks;
                }
                else
                {
                    t->adds->cgpa = (t->adds->cgpa + marks) / 2;
                }

                printf("\033[1;32mMarks Uploaded Successfully\033[0m\n");
                return;
            }
            t = t->next_stud;
        }
    }
}


void see_marks(int reg_no)
{
    printf("\033[1;35m\n---- See Marks ----\n\033[0m");
    student *t = top_stud;
    while (t != NULL)
    {
        if (t->adds->sreg_no == reg_no)
        {
            printf("Marks: %.2f\n", t->adds->cgpa);
            return;
        }
        t = t->next_stud;
    }
    return;
}
void admin_login()
{
    char pass[20];
    printf("Enter Admin Password: ");
    strcpy(pass, get_password());
    puts("");
    if (strcmp(pass, admin_p) == 0)
    {
        printf("\033[1;92mLogin Successful!\033[0m\n");
        printf("\033[1;43m\nWelcome Admin \n\033[0m");
        puts("");
        int choice;
        while (1)
        {
            choice = opt_admin();
            switch (choice)
            {
            case 1:
                add_faculty(fill_fac_detls());
                break;
            case 2:
                add_student(fill_stud_detls());
                break;
            case 3:
                print_students_rankwise();
                break;
            case 4:
                see_faculty_details();
                break;
            case 5:
                see_student_details();
                break;
            case 6:
                delete_faculty();
                break;
            case 7:
                delete_student();
                break;
            case 8:
                change_stud_pass();
                break;
            case 9:
                change_fac_pass();
                break;
            case 10: change_admin_password();
                break;
            case 11: return;
            default:
                printf("\033[1;91m[!] Invalid Choice\n\033[0m");

            }
        }
    }
    else
    {
        printf("\033[1;91m[!] Wrong Password\n\033[0m");

    }
}
void faculty_login()
{
    int reg_no;
    char pass[20];
    printf("Enter Registration No: ");
    scanf("%d", &reg_no);
    printf("Enter Password: ");
    strcpy(pass, get_password());
    puts("");
    faculty *t = top_faculty;
    while (t != NULL)
    {
        if (t->addf->freg_no == reg_no && strcmp(t->addf->password, pass) == 0)
        {
            printf("\033[1;32mLogin Successful!\033[0m\n");
            printf("\033[1;43m\nWelcome Mr.%s \n\033[0m",t->addf->name);
            puts("");
            while(1)
            {
                int choice = opt_faculty();
                switch (choice)
                {
                case 1:
                    printf("Name        : %s\n", t->addf->name);
                    printf("Reg No      : %d\n", t->addf->freg_no);
                    printf("Salary      : %d\n", t->addf->salary);
                    printf("12th Result : %.2f\n", t->addf->p2);
                    printf("CGPA        : %.2f\n", t->addf->cgpa);
                    printf("Father's Name: %s\n", t->addf->father_name);
                    printf("State       : %s\n", t->addf->state);
                    printf("District    : %s\n", t->addf->district);
                    break;
                case 2:
                    upload_marks();
                    break;
                case 3:
                    take_attendance();
                    break;
                case 4:
                    return;
                default:
                    printf("\033[1;91m[!] Invalid Choice\n\033[0m");
                }
            }
            return;
        }
        t = t->next_faculty;
    }
    printf("\033[1;91m[!] Wrong Registration No or Password\n\033[0m");

}
void student_login()
{
    int reg_no;
    char pass[20];
    printf("Enter Registration No: ");
    scanf("%d", &reg_no);
    printf("Enter Password: ");
    strcpy(pass, get_password());
    puts("");
    student *t = top_stud;
    while (t != NULL)
    {
        if (t->adds->sreg_no == reg_no && strcmp(t->adds->password, pass) == 0 )
        {
            printf("\033[1;32mLogin Successful!\033[0m\n");
            printf("\033[1;43m\nWelcome %s \n\033[0m",t->adds->name);
            puts("");
            while(1)
            {
                int choice = opt_student();
                switch (choice)
                {
                case 1:
                    printf("Name       : %s\n", t->adds->name);
                    printf("Reg No     : %d\n", t->adds->sreg_no);
                    printf("Serial No  : %d\n", t->adds->sl_no);
                    printf("CGPA       : %.2f\n", t->adds->cgpa);
                    printf("12th Result: %.2f\n", t->adds->p2);
                    printf("10th Result: %.2f\n", t->adds->boards);
                    printf("Attendance : %.2f%%\n", t->adds->attendance);
                    printf("State      : %s\n", t->adds->state);
                    printf("District   : %s\n", t->adds->district);
                    printf("Father's Name : %s\n", t->adds->father_name);
                    printf("Fees Status   : %d\n", t->adds->fees);
                    break;
                case 2:
                    see_marks(reg_no);
                    break;
                case 3:
                    see_attendance(reg_no);
                    break;
                case 4:
                    return;
                default:
                    printf("\033[1;91m[!] Invalid Choice\n\033[0m");
                }
            }
            int choice = opt_student();
            return;
        }
        t = t->next_stud;
    }
    printf("\033[1;91m[!] Wrong Registration No or Password\n\033[0m");
}

void save_stud()
{
    // Save students
    FILE *fs = fopen("students_data.txt", "w");
    student *ts = top_stud;
    while (ts != NULL)
    {
        fprintf(fs, "%d|%d|%s|%s|%s|%s|%f|%f|%f|%d|%f|%s\n",
                ts->adds->sl_no,
                ts->adds->sreg_no,
                ts->adds->name,
                ts->adds->father_name,
                ts->adds->state,
                ts->adds->district,
                ts->adds->cgpa,
                ts->adds->p2,
                ts->adds->boards,
                ts->adds->fees,
                ts->adds->attendance,
                ts->adds->password);
        ts = ts->next_stud;
    }
    fclose(fs);
}
void save_faculty()
{
    // Save faculty
    FILE *ff = fopen("faculty_data.txt", "w");
    faculty *tf = top_faculty;
    while (tf != NULL)
    {
        fprintf(ff, "%d|%s|%s|%s|%s|%f|%f|%d|%s\n",
                tf->addf->freg_no,
                tf->addf->name,
                tf->addf->father_name,
                tf->addf->state,
                tf->addf->district,
                tf->addf->cgpa,
                tf->addf->p2,
                tf->addf->salary,
                tf->addf->password);
        tf = tf->next_faculty;
    }
    fclose(ff);
}



void load_all_data()
{
    // Load students
    FILE *fs = fopen("students_data.txt", "r");
    if (fs != NULL)
    {
        student_data *temp;
        while (!feof(fs))
        {
            temp = (student_data *)malloc(sizeof(student_data));
            int n = fscanf(fs, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%f|%f|%f|%d|%f|%[^\n]\n",
                           &temp->sl_no,
                           &temp->sreg_no,
                           temp->name,
                           temp->father_name,
                           temp->state,
                           temp->district,
                           &temp->cgpa,
                           &temp->p2,
                           &temp->boards,
                           &temp->fees,
                           &temp->attendance,
                           temp->password);
            if (n == 12)
                add_student(temp);
            else
                free(temp);
        }
        fclose(fs);
    }

    // Load faculty
    FILE *ff = fopen("faculty_data.txt", "r");
    if (ff != NULL)
    {
        faculty_data *temp;
        while (!feof(ff))
        {
            temp = (faculty_data *)malloc(sizeof(faculty_data));
            int n = fscanf(ff, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%f|%f|%d|%[^\n]\n",
                           &temp->freg_no,
                           temp->name,
                           temp->father_name,
                           temp->state,
                           temp->district,
                           &temp->cgpa,
                           &temp->p2,
                           &temp->salary,
                           temp->password);
            if (n == 9)
                add_faculty(temp);
            else
                free(temp);
        }
        fclose(ff);
    }
}


int main()
{

    load_all_data();
    load_admin_data();
    disp=1;
    printf("\033[1;92m\n---- Welcome to College Management System ----\n\033[0m");
    int choice;
    while (1)
    {
        printf("\033[1;93m---- Main Menu ----\n\033[1;96m");
        puts("1. Admin Login");
        puts("2. Faculty Login");
        puts("3. Student Login");
        puts("4. Exit");
        printf("Enter Choice: \033[0m");

        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            admin_login();
            break;
        case 2:
            faculty_login();
            break;
        case 3:
            student_login();
            break;
        case 4:
            save_stud();
            save_faculty();
            save_admin_data();
            exit(0);
        default:
            printf("Invalid Choice\n");
        }
    }
}