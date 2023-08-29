#include <stdio.h>
// #include <conio.h>

struct Patients
{
    char name[100];
    int id;
    int age;
    char gender;
    int reserve;
};

// Functions ..!
void ask();

void adminMood();
struct Patients Add_Patient();
void print_Srtuct(struct Patients *p);
void print_Arr_Srtuct(struct Patients *p, int s);

void Edit();
int get_index(int id);

void Reserve();
void Cancel();

void userMood();
void clear();

// Global Variables ..!
struct Patients all[100];
int num = 0;
char *Reserves[5] = {"No Reserves", "2pm to 2:30pm", "2:30pm to 3pm", "3pm to 3:30pm", "4pm to 4:30pm", "4:30pm to 5pm"};

int main()
{
    ask();
    // Reserve();
    printf("Adios ..\n");

    return 0;
}

void ask()
{
    clear();

    int ch = 0;
    do
    {
        printf("1: Admin\n");
        printf("2: User\n");
        printf("Your Choice: ");
        scanf("%d", &ch);
    } while (ch != 1 && ch != 2);

    if (ch == 1)
        adminMood();

    else if (ch == 2)
        userMood();
}

void adminMood()
{
    int ps = 0;
    int ch = 0;

    clear();

    printf("Admin ..!\n");

    for (int i = 1; i < 4; i++)
    {
        printf("Enter the Password: ");
        scanf("%d", &ps);

        if(ps == 1234)
        {
            printf("Correct Password .. \nWelcom ..!\n");
            break;
        }

        else
        {
            printf("Wrong Password ..!\n");
            if(i == 3)
            {
                printf("Sorry .. Godbye\n");
                return;
            }
            else
            {
                clear();
                printf("Try Again ..!\n");
            }
        }
    }

    clear();

    printf("0: Show All Patients\n");
    printf("1: Add new patient record\n");
    printf("2: Edit patient record\n");
    printf("3: Reserve a slot with the doctor\n");
    printf("4: Cancel reservation\n");
    printf("Your choice: ");
    scanf("%d", &ch);

    while (ch >4 || ch <0)
    {
        clear();

        printf("Wrong Choice .. Try Again ..!\n");
        printf("0: show\n");
        printf("1: Add new patient record\n");
        printf("2: Edit patient record\n");
        printf("3: Reserve a slot with the doctor\n");
        printf("4: Cancel reservation\n");
        printf("Your choice: ");
        scanf("%d", &ch);
    }

    clear();

    switch (ch)
    {
    case 0:
        print_Arr_Srtuct(all, num);
        break;
    case 1:
        if (num == 100)
            printf("Sorry No space ..!");
        else
            all[num] = Add_Patient();
        break;
    case 2:
        Edit();
        break;
    case 3:
        Reserve();
        break;
    case 4:
        Cancel();
        break;
    }

    do
    {
        printf("Do you want to countinue ?\n");
        printf("0: No\n");
        printf("1: Yes\n");
        printf("Your choice: ");
        scanf("%d", &ch);
        clear();
    } while (ch != 0 && ch != 1);

    if (ch == 1)
        ask();

}

struct Patients Add_Patient()
{
    int ch = 0;
    struct Patients p;

    printf("Patient Name: ");
    scanf("%s", &(p.name));

    do
    {
        printf("Patient ID: ");
        scanf("%d", &(p.id));
        if (check_ID(p.id) == 1)
            clear();
    } while (check_ID(p.id) == 1);
    

    printf("Patient Age: ");
    scanf("%d", &(p.age));

    printf("Patient Gender: \n");
    printf("1:Female \n");
    printf("2:Male \n");
    printf("Your Choice: ");
    scanf("%d", &ch);

    if (ch == 1)
        p.gender = 'F';
    else if (ch == 2)
        p.gender = 'M';

    p.reserve = 0;
    printf("------------------\n");

    num++;
    return p;
}

void print_Srtuct(struct Patients *p)
{
    printf("----------------\n");
    printf("Name: %s\n", (*p).name);
    printf("Age: %d\n", (*p).age);
    printf("ID: %d\n", (*p).id);
    printf("Reserve: %s\n", Reserves[(*p).reserve]);

    if ((*p).gender == 'F')
        printf("Gender: Female\n");
    else if ((*p).gender == 'M')
        printf("Gender: Male\n");

    printf("----------------\n");
}

void print_Arr_Srtuct(struct Patients *p, int s)
{
    if (num == 0)
        printf("No Patients To Show ..!\n");

    else
    {
        printf("ALL ..\n");
        for (int i = 0; i < s; i++)
        {
            printf("Patient No.%d\n", i + 1);
            print_Srtuct(&(p[i]));
        }
        printf("------------------\n");
    }
}

int check_ID(int n)
{
    int found = 0;
    for (int i = 0; i < num; i++)
        if(all[i].id == n)
            found = 1;
        else
            found = 0;
    return found;
}

void Edit()
{
    clear();

    int id = 0;
    int ch = 0;

    printf("Edit ..!\n");

    do
    {
        printf("Enter The Patient ID: ");
        scanf("%d", &id);

        if (check_ID(id) == 0)
            printf("Not Found .. Try Again ..\n");
    } while (check_ID(id) == 0);

    int index = get_index(id);

    clear();
    do
    {
        printf("1: Edit Name \n");
        printf("2: Edit Age \n");
        printf("3: Edit Gender \n");
        printf("4: Edit  Reserve\n");
        printf("Your Choice: ");
        scanf("%d", &ch);

        if (ch > 4 && ch < 1)
            clear();
    } while (ch > 4 && ch<1);
    
    switch (ch)
    {
    case 1:
        printf("New Name: ");
        scanf("%s", &all[index].name);
        break;

    case 2:
        printf("New Age: ");
        scanf("%d", &all[index].age);
        break;

    case 3:
        do
        {
            printf("1: Female\n");
            printf("2: Male\n");
            printf("New Gender: ");
            scanf("%d", &ch);

            if (ch != 1 && ch != 2)
                printf("Wrong choice ..\n");
        } while (ch != 1 && ch !=2);
        
        if (ch == 1)
            all[index].gender = 'F';

        else if (ch == 2)
            all[index].gender = 'M';
        break;

    case 4:
        printf("The Available Slots ..!\n");
        for (int i = 1; i < 5; i++)
            printf("%d: %s\n", i, Reserves[i]);

        do
        {
            printf("Your Choice: ");
            scanf("%d", &ch);

            if (ch > 5 && ch < 1)
                printf("Wrong Choice ..\n");
        } while (ch > 5 && ch < 1);

        all[index].reserve = ch;
        break;
    }
}

int get_index(int id)
{
    for (int i = 0; i < num; i++)
        if (id == all[i].id)
            return i;
    return -1;
}

void Reserve()
{
    clear();
    int id = 0;
    int ch = 0;

    printf("Reserve ..!\n");

    do
    {
        printf("Enter The Patient ID: ");
        scanf("%d", &id);

        if (check_ID(id) == 0)
            printf("Not Found .. Try Again ..\n");
    } while (check_ID(id) == 0);

    int index = get_index(id);

    clear();
    printf("The Available Slots ..!\n");
    for (int i = 1; i < 5; i++)
        printf("%d: %s\n", i, Reserves[i]);

    do
    {
        printf("Your Choice: ");
        scanf("%d", &ch);

        if (ch > 5 && ch < 1)
            printf("Wrong Choice ..\n");
    } while (ch > 5 && ch < 1);

    all[index].reserve = ch;
}

void Cancel()
{
    clear();

    int id = 0;
    printf("Cancel ..!\n");
    do
    {
        printf("Enter ID: ");
        scanf("%d", &id);
        if (check_ID(id) == 0)
            printf("Not Found ..!\n");
    } while (check_ID(id) == 0);

    int index = get_index(id);
    all[index].reserve = 0;
}

void userMood()
{
    int ch;
    int id;

    clear();
    printf("User ..!\n");

    do
    {
        printf("Enter ypur ID: ");
        scanf("%d", &id);

        if (check_ID(id) == 0)
            printf("Not Found ..!\n");
    } while (check_ID(id) == 0);

    do
    {
        printf("1: View patient record\n");
        printf("2: View today’s reservations\n");
        printf("Your choice: ");
        scanf("%d", &ch);

        if(ch != 1 && ch != 2)
            printf("Wrong Choice \n");
    } while (ch != 1 && ch != 2);

    clear();
    int index = get_index(id);

    switch (ch)
    {
    case 1:
        print_Srtuct(&(all[index]));
        break;
    case 2:
        printf("Today's reservations: %s\n", Reserves[all[index].reserve]);
        break;
    }

    do
    {
        printf("Do you want to countinue ?\n");
        printf("0: No\n");
        printf("1: Yes\n");
        printf("Your choice: ");
        scanf("%d", &ch);
        clear();
    } while (ch != 0 && ch != 1);

    if (ch == 1)
        ask();
}

void clear()
{
    system("cls");
}
