#include<stdio.h>
#include<string.h>
#define MAX1_NAME 50 //MAXIMUM SIZE OF NAME FIELD
#define MAX2_BRANCH 25//MAXIMUM SIZE OF BRANCH FIELD
#define MAX_MEMBERS 100//MAXIMUM NUMBER OF STUDENTS THAT CAN JOIN CLUBS
//Structure to store the details of a student registered in a club
FILE*fp;

typedef struct student{
      int id;
      char name[MAX1_NAME];
      char branchName[MAX2_BRANCH];
      int semester;
      int clubChoice;
}student;
student s[MAX_MEMBERS];//Array to store the records of registered students
int memberCount=0;//counts or Tracks the total number of successfully registered students
void pauseScreen()
{
    printf("                     >>> PRESS ENTER TO CONTINUE <<<\n");
    getchar();
}
void registration();//Registers a student for a selected club
void viewMembership(int id);//it searches for a student's membership using their ID
void displayAllMembers();//it displays the records of all registered students
void displayClubInformation();//displays information about a selected club by you .
void removeMembership();
void clubWiseList();
void displayClub(int clubChoice);//displays the club name corresponding to its numeric choice choosed in registration section

void saveMembers();
void loadMembers();
int main()
{
    loadMembers();
    int n,no;
    char password[50],pw[50]="BVM_IS_BEST";// PASSWORD ARRANGEMENT......
    //WELCOME SCREEN >>>
    printf("=============================================================================== \n");
    printf("                       COLLEGE CLUB MEMBERSHIP PORTAL  \n");
    printf("=============================================================================== \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
    pauseScreen();
    //This loo[p will Repeat the main menu until the user chooses to exit
    do{
    //MAIN MENUU ::
    printf("\n");
    printf("**************************************************** \n");
    printf("*                  MAIN MENU                       * \n");
    printf("**************************************************** \n");
    printf ("1. Registration For Club\n");// OPTION TO GET REGISTERED IN CLUBS
    printf ("2. View My Membership \n");//OPTION TO SEE YOUR MEMBERSHP
    printf ("3. Display All Member \n");//THIS OPTION DISPLAYS ALL MEMBERSHIPS REGISTERED
    printf ("4. Display Club Informations\n");//THIS GIVES YOU INFORMATION ABOUT CLUBS YOU SELECT
    printf ("5. Remove my membership \n");//it removes your membership
    printf ("6. Clubwise Membership list \n");// club wise membership list
    printf ("7. EXIT Portal \n");// THIS OPTION MAKE YOU TO EXIT PORTAL
    printf ("\n")  ;
    printf ("\n")  ;
    printf ("Enter your choice: \n");
    scanf("%d",&n);
    switch(n){
        case 1 :
            registration();
            break ;

        case 2 :
            printf("ENTER ID NO.");
            scanf("%d",&no);
            viewMembership(no);
            break ;

        case 3 :
             printf("ENTER PASSWORD TO ACCESS MEMBERSHIP DETAILS OF  ALL STUDENTS \n \n");
             scanf("%49s",password);
             if(strcmp(password,pw)==0)
             {
                 if(memberCount!=0)
                 {
                     displayAllMembers();
                 }
                 else
                 {
                     printf("NO STUDENTS HAVE YET REGISTERED in any of the clubs \n ");
                     getchar();
                     pauseScreen();
                 }
             }else
             {
                 printf("INCORRECT PASSWORD !!!! \n");
                 getchar();
                 pauseScreen();
             }
             break ;
        case 4 :
             displayClubInformation();
             break ;

        case 5 :
             removeMembership();
             break ;

        case 6 :
            clubWiseList();
            break ;

        case 7 :
            printf("THANK YOU FOR USING PORTAL  !!!!\n VISIT AGAIN !!!!!");
            break ;

        default:
        printf("Wrong choice !!!!! \n Try Again...\n");
        getchar();
        pauseScreen();
        }
        }while(n!=7);
    return 0;
}
void registration(){
    //This below if condition Prevent registration when the maximum member limit is reached
    if(memberCount>=MAX_MEMBERS)
    {
        printf("Registration is full! The maximum member limit has been reached.\n");
        return;
    }
    printf("Enter id no. :");
    scanf("%d",&s[memberCount].id);
    int flag=0;
    //Check if the entered student ID is already registered
    for(int i=0;i<memberCount;i++)
    {
         if(s[i].id==s[memberCount].id)
         {
             flag=1;
             printf("STUDENT WITH THIS ID no. HAVE ALREADY REGISTERED \n");
             printf("Anything else ,\n");
             break;
         }
    }
        if(flag==0)
        {
             printf("ENTER STUDENT NAME            :  ");
             getchar();
             fgets(s[memberCount].name,MAX1_NAME,stdin);// fgets records the "Enter" key press as '\n'.
             s[memberCount].name[strcspn(s[memberCount].name, "\n")] = '\0';// This line finds that '\n' and replaces it with '\0' (null terminator) to clean the string.
             printf("ENTER ENGINEERING BRANCH NAME : ");
             fgets(s[memberCount].branchName,MAX2_BRANCH,stdin);// fgets records the "Enter" key press as '\n'.
             s[memberCount].branchName[strcspn(s[memberCount].branchName, "\n")] = '\0';// This line finds that '\n' and replaces it with '\0' (null terminator) to clean the string.

             printf("Enter your semester           : ");
             scanf("%d",&s[memberCount].semester);
             //Keep asking until the student enters a valid club number from 1 to 5 given choices
             do{
             printf("\n \n");
             printf("CHOOSE YOUR CLUB \nAMONG THIS GIVEN CHOICE ONLY \n");
             printf("AVAILABLE CLUBS ARE :\n");
             printf("1. CODING CLUB\n");
             printf("2. ROBOTICS CLUB\n");
             printf("3. ELECTRONIC CIRCUIT\n");
             printf("4. CULTURAL CLUB\n");
             printf("5. SPORTS CLUB \n");
             scanf("%d",&s[memberCount].clubChoice);
             }while(!(s[memberCount].clubChoice>0) || !(s[memberCount].clubChoice<=5));
             printf("CONGRATULATIONS!\n YOUR CLUB MEMBERSHIP HAS BEEN SUCCESSFULLY COMPLETED!!!! \n");//registration gets successful
             getchar();
             pauseScreen();
             memberCount++;   // it increments the count only after successful registration
             saveMembers();
             printf("Anything else ,\n");
             }
        return;
}
void viewMembership(int id)
{
    int i, flag = -1;//initialization of flag as -1 indicates that student has not ben found

    for(i = 0; i < memberCount; i++)
    {
        if(id == s[i].id)
        {
            flag = i;//replaces flag as -1  with i when matching ID is found
            break;
        }
    }
    //displays details if matching ID is found
    if(flag != -1)
    {
        printf("\nSTUDENT FOUND,Here is his details, \n \n");
        printf("STUDENT NAME.            : %s \n", s[flag].name);
        printf("ID NO.                   : %d \n", s[flag].id);
        printf("ENGINERRING BRANCH NAME  : %s \n", s[flag].branchName);
        printf("SEMESTER                 : %d \n", s[flag].semester);

        printf("CLUB JOINED              : ");
        displayClub(s[flag].clubChoice);
        printf("\n");
    }
    else
    {
        printf("\nStudent with this ID is not registered.\n");
    }
    getchar();
    pauseScreen();
    printf("Anything else ,\n");
}
void displayAllMembers()//this function displays the details of every registered dtudent
{
    for(int i=0;i<memberCount;i++)
    {
        printf("STUDENT NAME : %s \n", s[i].name);
        printf("ID NO.       : %d \n", s[i].id);
        printf("BRANCH NAME  : %s \n", s[i].branchName);
        printf("SEMESTER     : %d \n", s[i].semester);
        printf("CLUB JOINED  : ");
        displayClub(s[i].clubChoice);
        printf("\n");
        printf("\n");
    }
    getchar();
    printf("Press enter to continue.....\n") ;
    getchar();
    printf("Anything else ,\n");
}

void displayClubInformation(void)// it displays information about club based on selected club
{
    int choice;

    printf("\n========== CLUB INFORMATION ==========\n");
    printf("1. Coding Club\n");
    printf("2. Robotics Club\n");
    printf("3. Electronics Club\n");
    printf("4. Cultural Club\n");
    printf("5. Sports Club\n");

    printf("\nEnter the club number to view its information: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            printf("\n==========> CODING CLUB <==========\n");
            printf("The Coding Club focuses on programming and problem-solving.\n");
            printf("Students can practise coding and participate in coding competitions.\n");
            break;

        case 2:
            printf("\n==========> ROBOTICS CLUB <==========\n");
            printf("The Robotics Club focuses on designing and building robots.\n");
            printf("Students can explore sensors, motors, and robotics projects.\n");
            break;

        case 3:
            printf("\n==========> ELECTRONICS CLUB <==========\n");
            printf("The Electronics Club focuses on electronic components and circuits.\n");
            printf("Students can learn circuit design and work on electronics projects.\n");
            break;

        case 4:
            printf("\n==========> CULTURAL CLUB <==========\n");
            printf("The Cultural Club promotes art, music, dance, and creativity.\n");
            printf("Students can participate in cultural events and competitions.\n");
            break;

        case 5:
            printf("\n==========> SPORTS CLUB <==========\n");
            printf("The Sports Club promotes physical fitness and teamwork.\n");
            printf("Students can participate in sports activities and competitions.\n");
            break;

        default:
            printf("\nInvalid choice! Please select a number from 1 to 5.\n");
    }
    getchar();
    printf("Press enter to continue.....\n") ;
    getchar();
    printf("Anything else ,\n");
}
void removeMembership()//removes the student membership ONLY if the student is registered
{
    int rollNo,flag=0,removeChoice;
    printf("Enter your ID no.  : ");
    scanf("%d",&rollNo);
    //below loop checks whether student is registered
    for(int i=0;i<memberCount;i++)
    {
        if(rollNo==s[i].id)
        {
            flag=1;
            rollNo=i;
            break;
        }
    }
    if(flag==0)
    {
        printf("MEMBER WITH THIS ID IS NOT YET REGISTERED \n");//displays this if member is not registered
        getchar();
        pauseScreen();
        return;
    }
    printf("STUDENT FOUND !!!!!\n \n \n");
    do{
            //asking for confirmation to remove the membership
            printf("CONFIRM \n 1. I want to remove\n 2. I don't want to remove  \n");

            scanf("%d",&removeChoice);
    switch(removeChoice)
    {
        case 1:
            //process to remove membership
            for(int i=rollNo;i<memberCount-1;i++)
            {
                s[i].id=s[i+1].id;
                strcpy(s[i].name,s[i+1].name);
                strcpy(s[i].branchName,s[i+1].branchName);
                s[i].semester=s[i+1].semester;
                s[i].clubChoice=s[i+1].clubChoice;
            }
            printf("MEMBERSHIP REMOVED SUCCESSFULLY!!!!\n");
            getchar();
            pauseScreen();
            memberCount--;
            saveMembers();
            break;

        case 2:
            //wishing for choosing, not to remove membership option
            printf("\n GOOD DECISION \n");
            getchar();
            pauseScreen();
            break;

        default:
            printf("\n Wrong choice \n Try again.... \n");
    }
    }while(removeChoice!=1 && removeChoice!=2);

}
void clubWiseList()// Displays the list of students registered in a selected club
{
    // Check whether any student has registered in the portal
    if(memberCount==0)
    {
        printf("NO STUDENT HAVE YET REGISTERED \n");
        getchar();
        pauseScreen();
        return;//Exit the function if no student is registered yet...
    }
    int wish,flag=0;
    printf("ENTER YOUR INTENDED CLUB CHOICE TO LOOK its FOR MEMBERSHIP LIST \n") ;
    do{
    printf("1. Coding Club\n");
    printf("2. Robotics Club\n");
    printf("3. Electronics Club\n");
    printf("4. Cultural Club\n");
    printf("5. Sports Club\n");
    scanf("%d",&wish);
    switch(wish)
    {
        case 1:
            flag=0;// Reset the flag before searching the Club members
            printf("STUDENTS WHO JOINT CODING CLUB ARE :\n \n");
            for(int i = 0; i < memberCount; i++)
            {
                if(wish==s[i].clubChoice)
                {
                    flag=1;
                    printf("ID No.          :%d \n",s[i].id);
                    printf("NAME OF STUDENT :%s \n",s[i].name);
                }
            }
            // Display a message if no members were found in this club
            if(flag==0)
            {
                printf("Actually no student have yet registered in this club ...\n");
            }
            getchar();
            pauseScreen();
            break;
        case 2:
            flag=0;// Reset the flag before searching the Club members
            printf("STUDENTS WHO JOINT ROBOTICS CLUB ARE :\n \n");
            for(int i = 0; i < memberCount; i++)
            {
                if(wish==s[i].clubChoice)
                {
                    flag=1;
                    printf("ID No.          :%d \n",s[i].id);
                    printf("NAME OF STUDENT :%s \n",s[i].name);
                }
            }
             // Display a message if no members were found in this club
            if(flag==0)
            {
                printf("Actually no student have yet registered in this club ...\n");
            }
            getchar();
            pauseScreen();
            break;
        case 3:// Reset the flag before searching the Club members
            flag=0;
            printf("STUDENTS WHO JOINT ELECTRPNICS CIRCUIT CLUB ARE :\n \n");
            for(int i = 0; i < memberCount; i++)
            {
                if(wish==s[i].clubChoice)
                {
                    flag=1;
                    printf("ID No.          :%d \n",s[i].id);
                    printf("NAME OF STUDENT :%s \n",s[i].name);

                }
            }
             // Display a message if no members were found in this club
            if(flag==0)
            {
                printf("Actually no student have yet registered in this club ...\n");
            }
            getchar();
            pauseScreen();
            break;
        case 4:// Reset the flag before searching the Club members
            flag=0;
            printf("STUDENTS WHO JOINT CULTURAL CLUB ARE :\n \n");
            for(int i = 0; i < memberCount; i++)
            {
                if(wish==s[i].clubChoice)
                {
                    flag=1;
                    printf("ID No.          :%d \n",s[i].id);
                    printf("NAME OF STUDENT :%s \n",s[i].name);
                }
            }
             // Display a message if no members were found in this club
            if(flag==0)
            {
                printf("Actually no student have yet registered in this club ...\n");
            }

            getchar();
            pauseScreen();
            break;
        case 5:// Reset the flag before searching the Club members
            flag=0;
            printf("STUDENTS WHO JOINT SPORTS CLUB ARE :\n \n");
            for(int i = 0; i < memberCount; i++)
            {
                if(wish==s[i].clubChoice)
                {
                    flag=1;
                    printf("ID No.          :%d \n",s[i].id);
                    printf("NAME OF STUDENT :%s \n",s[i].name);
                }
            }
             // Display a message if no members were found in this club
            if(flag==0)
            {
                printf("Actually no student have yet registered in this club ...\n");
            }
            getchar();
            pauseScreen();
            break;

        default:
            printf("wrong choice !!!!\n try again \n");

    }
    }while(wish<1 || wish>5);


}
void displayClub(int clubChoice)//Display the club name corresponding to the given club number(basically useful for functoin viewMembership)
{
    switch(clubChoice)
    {
        case 1:
            printf("Coding Club");
            break ;
        case 2:
            printf("ROBOTICS CLUB" );
            break ;
        case 3:
            printf("ELECTRONICS CLUB");
            break ;
        case 4:
           printf("CULTURAL CLUB");
           break ;
        case 5:
           printf("SPORTS CLUB ");
           break ;
        default :
           printf("INVALID CLUB CHOICE.");
    }
    return;
}

void saveMembers()
{
    fp=fopen("student.txt","w");
    if(fp==NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i<memberCount; i++)
    {
        fprintf(fp, "%d|%s|%s|%d|%d\n",s[i].id,s[i].name,s[i].branchName,s[i].semester,s[i].clubChoice);
    }

    fclose(fp);
    printf("Membership records saved with updation.\n");
}
void loadMembers()
{
    fp = fopen("student.txt", "r");

    if (fp == NULL)
    {
        printf("No existing membership file found.\n");
        return;
    }

    for (int i = 0;(i < MAX_MEMBERS) && (fscanf(fp, "%d|%49[^|]|%24[^|]|%d|%d",&s[i].id,s[i].name,s[i].branchName,&s[i].semester,&s[i].clubChoice) == 5);i++)
        {
            memberCount++;
        }

    fclose(fp);

    printf("%d STUDENT REGISTERED.\n", memberCount);
}
