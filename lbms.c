#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
void createPassword(int);
void createUserAccount();
void createAdminAccount();
int rePassword(int,int);
void opac();
void returnBook(int);
void takeBook(int);
void bookCount();
void addNewBook();
void removeBook();
void increaseBookCount();
void decreaseBookCount();
void userStatus();
void userLogin();
void adminLogin();
int userId = 1;
int adminId = 1;
int bookId = 1;
struct user
{
    char name[100];
    char sex[10];
    char mobileNumber[15];
    char collegeId[15];
    char password[50];
    int bookStatus;
    int userBookId;
    int userStatus;
}userList[10000];
struct admin
{
    char name[100];
    char sex[10];
    char mobileNumber[15];
    char collegeId[15];
    char password[50];
    int adminStatus;
}adminList[10000];
struct availableBooks
{
    char bookName[100];
    int bookCount;
    int booksStatus;
}books[10000];
void createPassword(int choice)
{
    int len,index,digit = 0,alpha = 0,spclChar = 0;
    char tempPassword[50];
    printf("The password must contain minimum of 8 characters  with atleast 1 Uppercase 1 LowerCase 1 Symbol and 1 Number\n");
    if(choice==1)
    {
        scanf(" %s",userList[userId-1].password);
        strcpy(tempPassword,userList[userId-1].password);
    }
    else if(choice == 2)
    {
        scanf(" %s",adminList[adminId-1].password);
        strcpy(tempPassword,adminList[adminId-1].password);

    }
    len = strlen(tempPassword);
    printf("%d %d %d %d\n",alpha,spclChar,digit,(alpha+spclChar+digit));
    for(index = 0;index < len;index++)
    {
        if(isdigit(tempPassword[index]) != 0)
        {
            digit++;
        }
        else if(isalpha(tempPassword[index]) != 0)
        {
            if(isupper(tempPassword[index]) != 0)
            {
                alpha++;
            }
        }
        else
        {
            spclChar++;
        }
    }
    printf("%d %d %d %d\n",alpha,spclChar,digit,(alpha+spclChar+digit));
    if(alpha < 1 || spclChar < 1 || digit < 1 || (alpha + spclChar + digit) < 6)
    {
        printf("Your password doesn't satisfy the above condition\nPlease re-enter the password\n");
        createPassword(choice);
    }
}
void createUserAccount()
{
    printf("\nEnter your name : \n");
    scanf(" %[^\n]s",userList[userId-1].name);
    printf("\nEnter your sex : \nMale \nFemale\n");
    scanf(" %s",userList[userId-1].sex);
    printf("\nEnter your Mobile Number : \n");
    scanf(" %s",userList[userId-1].mobileNumber);
    printf("\nEnter the college Id card Number : \n");
    scanf(" %s",userList[userId-1].collegeId);
    printf("\nEnter your password : \n");
    createPassword(1);
    printf("\nYour account is successfully created\n");
    printf("\nYour user Id is %d\n",userId);
    printf("\nYour Password is %s\n",userList[userId-1].password);
    userList[userId-1].userStatus = 1;
    userId++;
}
void createAdminAccount()
{
    printf("\nEnter your name : \n");
    scanf(" %[^\n]s",adminList[adminId-1].name);
    printf("\nEnter your sex : \nMale \nFemale\n");
    scanf(" %s",adminList[adminId-1].sex);
    printf("\nEnter your Mobile Number : \n");
    scanf(" %s",adminList[adminId-1].mobileNumber);
    printf("\nEnter the college staff Id card Number : \n");
    scanf(" %s",adminList[adminId-1].collegeId);
    printf("\nEnter your password : \n");
    createPassword(2);
    printf("\nYour account is successfully created\n");
    printf("\nYour Admin Id is %d\n",adminId);
    printf("\nYour Password is %s\n",adminList[adminId-1].password);
    adminList[adminId-1].adminStatus = 1;
    adminId++;
}
int rePassword(int loginId,int choice)
{
    int reEnter;
    char loginPassword[50],passwordChoice[50];
    printf("Enter your password : \n");
    scanf("%s",loginPassword);
    if(choice==1)
    {
        strcpy(passwordChoice,userList[loginId-1].password);
    }
    else
    {
        strcpy(passwordChoice,adminList[loginId-1].password);
    }
    if(strcmp(loginPassword,passwordChoice)!=0)
    {
        printf("Your userId doesn't match with your passwword\nPress 1 to re-type password or Press 0 to abord\n");
        scanf("%d",&reEnter);
        if(reEnter)
        {
            rePassword(loginId,choice);
        }
        else
        {
            return 0;
        }
    }
    return 1;
}
void opac()
{
    int index;
    printf("The available books are \n");
    printf("Book Name Book Id Book Count\n");
    for(index =0;index<bookId-1;index++)
    {
        printf("%s        %d      %d\n",books[index].bookName,index+1,books[index].bookCount);
    }
}
void returnBook(int loginId)
{
    if(userList[loginId-1].bookStatus == 0)
    {
        printf("You currently don't have any book to return\n");
        return;
    }
    else
    {
        userList[loginId-1].bookStatus = 0;
        books[userList[loginId-1].userBookId - 1].bookCount++;
    }
}
void takeBook(int loginId)
{
    int bookIdTemp;
    if(userList[loginId-1].bookStatus == 1)
    {
        printf("You already took 1 book\tPlease return it to take another book\n");
        return;
    }
    else
    {
        printf("Enter book id to take \n");
        scanf("%d",&bookIdTemp);
        if(books[bookIdTemp - 1].bookCount == 0)
        {
           printf("The particular book is currently out of stock\nPlease come again later\n");
           return;
        }
        userList[loginId-1].bookStatus = 1;
        printf("The book is %s\n",books[bookIdTemp - 1].bookName);
        books[bookIdTemp - 1].bookCount--;
    }
}
void bookCount()
{
    int bookIdTemp,reType;
    printf("Enter the book Id to find count\n");
    scanf("%d",&bookIdTemp);
    if(bookIdTemp < 1 || bookIdTemp > bookId || books[bookIdTemp-1].booksStatus != 1)
    {
        printf("You don't have book with this Book Id\nPress 1 to re-enter BookId or Press 0 to abord\n");
        scanf("%d",&reType);
        if(reType)
        {
            bookCount();
        }
        else
        {
            return;
        }
    }
    else
    {
        printf("The book Name is %s\n",books[bookIdTemp - 1].bookName);
        printf("The Book Count is %d\n",books[bookIdTemp - 1].bookCount);
    }
}
void addNewBook()
{
    printf("Enter the name of the book\n");
    scanf(" %[^\n]s",books[bookId - 1].bookName);
    printf("Enter the count of the book\n");
    scanf("%d",&books[bookId - 1].bookCount);
    printf("\nYou added a book named %s\nCount of this book is %d\n",books[bookId - 1].bookName,books[bookId - 1].bookCount);
    printf("Book id is %d\n",bookId);
    books[bookId - 1].booksStatus = 1;
    bookId++;
}
void removeBook()
{
    int bookIdTemp,reType;
    printf("Enter the book Id to removeBook\n");
    scanf("%d",&bookIdTemp);
    if(bookIdTemp < 1 || bookIdTemp > bookId || books[bookIdTemp-1].booksStatus != 1)
    {
        printf("You don't have book with this Book Id\nPress 1 to re-enter BookId or Press 0 to abord\n");
        scanf("%d",&reType);
        if(reType)
        {
            bookCount();
        }3
        else
        {
            return;
        }
    }
}
void increaseBookCount()
{
    int bookIdTemp,reType,bookCountTemp;
    printf("Enter the book Id to Increase count\n");
    scanf("%d",&bookIdTemp);
    if(bookIdTemp < 1 || bookIdTemp > bookId || books[bookIdTemp-1].booksStatus != 1)
    {
        printf("You don't have book with this Book Id\nPress 1 to re-enter BookId or Press 0 to abord\n");
        scanf("%d",&reType);
        if(reType)
        {
            bookCount();
        }
        else
        {
            return;
        }
    }
    else
    {
        printf("The book Name is %s\n",books[bookIdTemp - 1].bookName);
        printf("The Book Count is %d\n",books[bookIdTemp - 1].bookCount);
        printf("\nEnter the count to increase\n");
        scanf("%d",&bookCountTemp);
        books[bookIdTemp - 1].bookCount = books[bookIdTemp - 1].bookCount + bookCountTemp;
        printf("The Current Book Count is %d\n",books[bookIdTemp - 1].bookCount);
    }
}
void decreaseBookCount()
{
    int bookIdTemp,reType,bookCountTemp;
    printf("Enter the book Id to find count\n");
    scanf("%d",&bookIdTemp);
    if(bookIdTemp < 1 || bookIdTemp > bookId || books[bookIdTemp-1].booksStatus != 1)
    {
        printf("You don't have book with this Book Id\nPress 1 to re-enter BookId or Press 0 to abord\n");
        scanf("%d",&reType);
        if(reType)
        {
            bookCount();
        }
        else
        {
            return;
        }
    }
    else
    {
        printf("The book Name is %s\n",books[bookIdTemp - 1].bookName);
        printf("The Book Count is %d\n",books[bookIdTemp - 1].bookCount);
        printf("\nEnter the count to decrease\n");
        scanf("%d",&bookCountTemp);
        if(bookCountTemp > books[bookIdTemp - 1].bookCount)
        {
            printf("Your Decrease book count is greater than available book count\n");
            return;
        }
        books[bookIdTemp - 1].bookCount = books[bookIdTemp - 1].bookCount - bookCountTemp;
        printf("The Current Book Count is %d\n",books[bookIdTemp - 1].bookCount);
    }
}
void userStatus()
{
    int userIdTemp,reType;
    printf("Enter the User Id\n");
    scanf("%d",&userIdTemp);
    if(userIdTemp < 1 || userIdTemp > userId || userList[userIdTemp - 1].userStatus != 1)
    {
        printf("User Id entered is wrong\nPress 1 to re-Enter\nPress 0 to abord\n");
        scanf("%d",&reType);
        if(reType)
        {
            userStatus();
        }
        else
        {
            return;
        }
    }
    else
    {
        printf("Name is %s\n",userList[userIdTemp - 1].name);
        if(userList[userIdTemp - 1].bookStatus ==1)
        {
            printf("User book Id is %d\n",userList[userIdTemp - 1].userBookId);
            printf("The Book Name is %s\n",books[userList[userIdTemp - 1].userBookId -1].bookName);
        }
        else
        {
            printf("The user currently dont have any book\n");
        }
    }
}
void userLogin()
{
    int loginUserId,choice;
    int reType;
    printf("Enter your user id : \n");
    scanf("%d",&loginUserId);
    if(loginUserId < 1 || loginUserId > userId || userList[loginUserId-1].userStatus != 1)
    {
        printf("You don't have user account \nPress 1 to re-enter your user Id or Press 0 to abord\n");
        scanf("%d",&reType);
        if(reType)
        {
            userLogin();
        }
        else
        {
            return;
        }
    }
    if(rePassword(loginUserId,1))
    {
        int choice;
        printf("\n-----------User Login Successfully----------\n");
        printf("Name : %s\n",userList[loginUserId-1].name);
        if(userList[loginUserId-1].bookStatus == 1)
        {
            printf("You had already took book named \nPlease return it to take another book\n");
        }
        do
        {
            printf("Enter your choice\n1.OPAC\n2.Return a Book\n3.Take a Book\n4.Logout\n");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                    opac();
                    break;
                case 2:
                    returnBook(loginUserId);
                    break;
                case 3:
                    takeBook(loginUserId);
                    break;
                case 4:
                    printf("Your logout made succesfully\n");
                    return;
                default:
                    printf("Please enter a valid choice\n");
            }
            printf("Press 1 to go Home Screen or 0 to logout\n");
            scanf("%d",&choice);
        }while(choice != 0);
    }
}
void adminLogin()
{
    int loginAdminId,choice;
    int reType;
    printf("Enter your admin id : \n");
    scanf("%d",&loginAdminId);
    if(loginAdminId < 1 || loginAdminId > adminId || adminList[loginAdminId-1].adminStatus != 1)
    {
        printf("You don't have admin account \nPress 1 to re-enter your user Id or Press 0 to abord\n");
        scanf("%d",&reType);
        if(reType)
        {
            adminLogin();
        }
        else
        {
            return;
        }
    }
    if(rePassword(loginAdminId,0))
    {
        printf("\n-----------Admin Login Successfully----------\n");
        printf("Name :%s\n",adminList[loginAdminId-1].name);

        do
        {
            printf("Enter your choice\n1.OPAC\n2.Count of a Book\n3.Add a new book\n4.Remove a book\n");
            printf("5.Increase a book count\n6.Decrease a book count\n7.User status\n8.Logout\n");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                    opac();
                    break;
                case 2:
                    bookCount();
                    break;
                case 3:
                    addNewBook();
                    break;
                case 4:
                    removeBook();
                    break;
                case 5:
                    increaseBookCount();
                    break;
                case 6:
                    decreaseBookCount();
                    break;
                case 7:
                    userStatus();
                    break;
                case 8:
                    printf("Logout made successfully\n");
                    return;
                default:
                    printf("Enter a valid choice\n");
            }
            printf("Press 1 to go Home Screen or 0 to logout\n");
            scanf("%d",&choice);
        }while(choice!=0);
    }
}
int main()
{
    int choice,ans;
    printf("\nHai there!!\n");
    do
    {
        printf("\nEnter your choice\n1.Create User Account\n2.Create Admin Account\n3.User Login\n4.Admin Login\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                createUserAccount();
                break;
            case 2:
                createAdminAccount();
                break;
            case 3:
                userLogin();
                break;
            case 4:
                adminLogin();
                break;
            default:
                printf("Enter the valid choice\n");
        }
        printf("\nPress 1 to go Dashboard \nPress 0 to out\n");
        scanf("%d",&ans);
    }while(ans);
}
