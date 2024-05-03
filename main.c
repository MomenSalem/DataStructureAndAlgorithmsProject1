

//Student name : Momen Musa Fuad Salem
//ID : 1200034
//Section : 2
//Doctor : Ahmad Abu Snaina
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Passenger
{
    int passenger_id;
    int traveling_date;
    char traveling_time[6];
    char from_des[20];//des -> mean destination
    char to_des[20];
    struct Passenger *next;
};
struct Bus
{
    int bus_num;
    int leaving_date;
    char departure_time[6];
    char from_station[20];
    char to_station[20];
    int ticket_price;//**maybe float
    int capacity;
    struct Bus *next;
    struct Passenger *passlinkedlist;//pointer to the passenger linked list inside the bus
};
typedef struct Passenger Passenger;
typedef struct Bus Bus;
int busisEmpty(Bus *buslinkedlist)
{
    if(buslinkedlist->next != NULL)//there is no node in the linked list
        return 0;
    else
        return 1;
}
int passengerIsEmpty(Passenger *passengerlinkedlist)
{
    if(passengerlinkedlist->next != NULL)
        return 0;
    else
        return 1;
}
void insertBus(Bus *buslinkedlist, Bus *busnode)//insert bus function (busses can have common number)
{
    if(buslinkedlist != NULL && busnode != NULL)
    {
        Bus *tempbus;
        tempbus = buslinkedlist;
        while(tempbus->next != NULL)
        {
            tempbus = tempbus->next;
        }
        tempbus->next = busnode;
    }
    else if(buslinkedlist == NULL)
    {
        printf("Sorry, The bus linked list didn't exist");
        return ;
    }
    else if(busnode == NULL)
    {
        printf("Sorry, The new bus node didn't exist");
        return ;
    }
}
int checkPassengerExist(Passenger *passengerlinkedlist, int passengerid)//function to check if the id for passenger exist(the id must be unique)
{
    if(passengerlinkedlist != NULL)
    {
        if(!passengerIsEmpty(passengerlinkedlist))//check if the passenger linked list is empty
        {
            Passenger *temppass;
            temppass = passengerlinkedlist->next;
            while(temppass != NULL)
            {
                if(temppass->passenger_id == passengerid)
                    return 1;
                temppass = temppass->next;
            }
            return 0;
        }
    }
    else
    {
        printf("Sorry, The passenger linked list didn't exist");
        exit(0);
    }
    return 0;
}
void insertPassenger(Passenger *passlinkedlist, Passenger *passnode)//insert passenger to the linked list and check if the id exist
{
    if(passlinkedlist != NULL && passnode != NULL)
    {
        if(!checkPassengerExist(passlinkedlist, passnode->passenger_id))
        {
            Passenger *temppass;
            temppass = passlinkedlist;
            while(temppass->next != NULL)
            {
                temppass = temppass->next;
            }
            temppass->next = passnode;
        }
        else
            printf("Sorry, The passenger ID %d is exist we can't repeat it\n",passnode->passenger_id);
    }
    else if(passlinkedlist == NULL)
    {
        printf("Sorry, The passenger linked list didn't exist");
        return ;
    }
    else if(passnode == NULL)
    {
        printf("Sorry, The new passenger node didn't exist");
        return ;
    }
}
Passenger *findPreviousPass(Passenger *passlinkedlist, Passenger *passenger)//the wanted passenger
{
    if(passlinkedlist != NULL && passenger != NULL)
    {
        Passenger *prevpassenger;
        prevpassenger = passlinkedlist->next;//prevpassenger point to the first passenger in the linked list
        if(prevpassenger == passenger)//if the wanted passenger is the first then there's no previous for his/her
            return passlinkedlist;//so return the linked list(The header of the linked list)
        while(prevpassenger != NULL)//loop to find the previous passenger if the passenger is not at first
        {
            if(prevpassenger->next == passenger)
                return prevpassenger;//return the previous passenger
            prevpassenger = prevpassenger->next;
        }
    }
    else if(passlinkedlist == NULL)
    {
        printf("Sorry, The passenger linked list didn't exist so there's no previous");
        exit(0);
    }
    else if(passenger == NULL)
    {
        printf("Sorry, The passenger node didn't exist");
        exit(0);
    }
    return NULL;
}
Passenger *returnDeletePassenger(Passenger *passengerlinkedlist, Passenger *wpassenger)//w : means wanted passenger
{
    if(passengerlinkedlist != NULL && wpassenger != NULL)
    {
        Passenger *passenger;
        passenger = findPreviousPass(passengerlinkedlist, wpassenger);//passenger point to the previous
        if(passenger != NULL)//if there is previous
        {
            passenger->next = wpassenger->next;//the wanted passenger is deleted but without use NULL (later in the assign function
            return passenger;//return the passenger linked list without the passenger who i want to delete it
        }
    }
    else if(passengerlinkedlist == NULL)//check if the linked lists are not exist
    {
        printf("Sorry, The passenger linked list didn't exist");
        exit(0);
    }
    else if(wpassenger == NULL)
    {
        printf("Sorry, The passenger node didn't exist");
        exit(0);
    }
    return NULL;
}
void assigningPassengers(Bus *buslinkedlist, Passenger *passengerlinkedlist)
{
    if(buslinkedlist != NULL && passengerlinkedlist != NULL)
    {
        if(!passengerIsEmpty(passengerlinkedlist))
        {
            Bus *bustemp;//pointer to the first bus
            bustemp = buslinkedlist->next;
            while(bustemp != NULL)
            {
                Passenger *passtemp;//pointer to the passenger linked list inside the bus
                passtemp = passengerlinkedlist->next;
                while(passtemp != NULL)
                {
                    if(passtemp->traveling_date == bustemp->leaving_date)//condition to check if the passenger is proper to the bus info
                    {
                        if(strcmp(passtemp->from_des,bustemp->from_station) == 0 && strcmp(passtemp->to_des,bustemp->to_station) == 0)
                        {
                            if(strcmp(passtemp->traveling_time,bustemp->departure_time) == 0)
                            {
                                if(bustemp->capacity > 0)//if the bus has empty chairs so the passenger can't set
                                {
                                    Passenger *temp;//temporarily pointer to the passenger who can go with bus
                                    temp = passtemp;
                                    passtemp = returnDeletePassenger(passengerlinkedlist,passtemp);//function call to return passenger linked list without the passenger how go to the bus
                                    temp->next = NULL;//the next will be NULL to insert the passenger correctly
                                    insertPassenger(bustemp->passlinkedlist,temp);//insert the passenger to his proper bus
                                    bustemp->capacity--;//decrement the bus capacity
                                }
                                else//if the bus don't have capacity
                                {
                                    printf("Sorry, The bus number %d is full (there's no capacity)\n",bustemp->bus_num);
                                    break;//to exit from the whole bus if it is full
                                }
                            }
                        }
                    }
                    passtemp = passtemp->next;//check next passenger until NULL
                }
                bustemp = bustemp->next;//check next bus until NULL
            }
        }
        else
            printf("Sorry, The passenger linked list is empty(There's no passengers at station)\n");
    }
    else if(buslinkedlist == NULL)
    {
        printf("Sorry, The bus linked list didn't exist");
        return ;
    }
    else if(passengerlinkedlist == NULL)
    {
        printf("Sorry, The passenger linked list didn't exist");
        return ;
    }
}
void printBusesInformations(Bus *buslinkedlist)
{
    if(buslinkedlist != NULL)
    {
        Bus *tempbus;
        tempbus = buslinkedlist->next;
        if(tempbus == NULL)//if the bus linked list is empty
        {
            printf("Sorry, There's no buses in the station\n");
            return ;
        }
        printf("The informations for all buses are :-\n");
        printf("-----------------------------------------------------------------------------------------------------------------------");
        while(tempbus != NULL)
        {
            printf("\nBus number : %d | Leaving date : %d | At : %s | From : %s | To : %s | Price : %d | Capacity : %d \n",tempbus->bus_num,tempbus->leaving_date,tempbus->departure_time,tempbus->from_station,tempbus->to_station,tempbus->ticket_price,tempbus->capacity);
            printf("-----------------------------------------------------------------------------------------------------------------------");
            tempbus = tempbus->next;
        }
        printf("\n");
    }
    else if(buslinkedlist == NULL)
    {
        printf("Sorry, The bus linked list didn't exist");
        return ;
    }
}
void printSpecificBus(Bus *buslinkedlist, int busnumber)
{
    int thebusexist = 0;//check int if i print the bus and if the bus is exist(because the bus number can be used more than once)
    if(buslinkedlist != NULL)
    {
        Bus *tempbus;
        tempbus = buslinkedlist->next;
        while(tempbus != NULL)
        {
            if(tempbus->bus_num == busnumber)
            {
                thebusexist++;//change the value to avoid the print (bus doesn't exist)
                printf("The informations for bus number %d are : \n",tempbus->bus_num);
                printf("Leaving date : %d | Departure time : %s | From station : %s | To station : %s | Ticket price : %d | Capacity : %d\n",tempbus->leaving_date,tempbus->departure_time,tempbus->from_station,tempbus->to_station,tempbus->ticket_price,tempbus->capacity);
                Passenger *temppass;
                temppass = tempbus->passlinkedlist->next;
                if(temppass == NULL)
                {
                    printf("The bus number %d doesn't have any passengers\n",tempbus->bus_num);
                }
                else
                {
                    printf("The passengers IDs for bus number %d are : \n",tempbus->bus_num);
                    while(temppass != NULL)
                    {
                        printf("%d \t",temppass->passenger_id);
                        temppass = temppass->next;
                    }
                    printf("\n");
                }
            }
            tempbus = tempbus->next;
        }
        if(thebusexist == 0)
            printf("Sorry, The bus number %d does not exist\n",busnumber);
    }
    else if(buslinkedlist == NULL)
    {
        printf("Sorry, The bus linked list didn't exist");
        return ;
    }
}
void printUnMatchedPass(Passenger *passengerlinkedlist)
{
    if(passengerlinkedlist != NULL)
    {
        Passenger *temppass;
        temppass = passengerlinkedlist->next;
        if(temppass == NULL)
        {
            printf("Sorry, There's no unmatched passengers\n");//if the unmatched linked list is empty
            return ;
        }
        printf("The Unmatched passengers are : \n");
        while(temppass != NULL)
        {
            printf("Passenger id : %d \t Traveling date : %d \t At : %s \t From : %s \t To : %s \n",temppass->passenger_id,temppass->traveling_date,temppass->traveling_time,temppass->from_des,temppass->to_des);
            temppass = temppass->next;
        }
    }
    else if(passengerlinkedlist == NULL)
    {
        printf("Sorry, The passenger linked list didn't exist");
        return ;
    }
}
void deletePassenger(Bus *buslinkedlist, Passenger *passengerlinkedlist, int passengerid)//function to delete passenger first i search in busses then in the unmatched linked list
{
    if(buslinkedlist != NULL)
    {
        if(!busisEmpty(buslinkedlist))//if there is no busses check the unmatched passenger linked list
        {
            Bus *tempbus;
            tempbus = buslinkedlist->next;
            while(tempbus != NULL)
            {
                Passenger *temppass;
                temppass = tempbus->passlinkedlist->next;
                while(temppass != NULL)
                {
                    if(temppass->passenger_id == passengerid)
                    {
                        Passenger *prevpass;
                        prevpass = findPreviousPass(tempbus->passlinkedlist,temppass);
                        if(prevpass != NULL)
                        {
                            prevpass->next = temppass->next;
                            temppass->next = NULL;
                            printf("The passenger ID = %d is deleted properly from bus number %d \n", temppass->passenger_id,tempbus->bus_num);
                            tempbus->capacity++;//increment the bus capacity
                            return ;
                        }
                    }
                    temppass = temppass->next;
                }
                tempbus = tempbus->next;
            }
            printf("The passenger ID = %d didn't ride any bus\n",passengerid);
        }//if the passenger didn't ride any bus may be in the unmatched passenger
        if(passengerlinkedlist != NULL)
        {
            Passenger *passenger;
            passenger = passengerlinkedlist->next;
            while (passenger != NULL)
            {
                if(passenger->passenger_id == passengerid)
                {
                    Passenger *prevpass;//find previous passenger and let the next for previous be the next to the wanted passenger and so delete it
                    prevpass = findPreviousPass(passengerlinkedlist,passenger);
                    if(prevpass != NULL)//if there is previous without problem enter the loop
                    {
                        prevpass->next = passenger->next;
                        passenger->next = NULL;
                        printf("The passenger ID = %d is deleted properly from un matched Passengers\n", passenger->passenger_id);
                        return ;
                    }
                }
                passenger = passenger->next;
            }
            printf("The passenger ID = %d doesn't exist!!!\n",passengerid);
        }
        else if(passengerlinkedlist == NULL)
        {
            printf("Sorry, The passenger linked list didn't exist");
            return ;
        }
    }
    else if(buslinkedlist == NULL)
    {
        printf("Sorry, The bus linked list didn't exist");
        return ;
    }
}
Bus *previousBus(Bus *buslinkedlist, Bus *bus)//(bus mean)the wanted bus and it return pointer to the previous bus
{
    if(buslinkedlist != NULL && bus != NULL)
    {
        Bus *prevbus;//pointer to the first bus node in the linked list
        prevbus = buslinkedlist->next;//function like find previous passenger exactly *
        if(prevbus == bus)
            return buslinkedlist;
        while(prevbus != NULL)
        {
            if(prevbus->next == bus)
                return prevbus;
            prevbus = prevbus->next;
        }
    }
    else if(buslinkedlist == NULL)
    {
        printf("Sorry, The bus linked list didn't exist");
        exit(0);
    }
    else if(bus == NULL)
    {
        printf("Sorry, The bus node didn't exist");
        exit(0);
    }
    return NULL;
}
void deleteBus(Bus *buslinkedlist, int busnumber, Passenger *passengerlinkedlist)//un matched passenger linked list to add the passengers inside the bus after delete the bus
{
    if(buslinkedlist != NULL)
    {
        Bus *tempbus;
        tempbus = buslinkedlist->next;
        while(tempbus != NULL)
        {
            if(tempbus->bus_num == busnumber)
            {
                Bus *prevbus;
                prevbus = previousBus(buslinkedlist,tempbus);
                if(prevbus != NULL)//delete the bus and print a message
                {
                    prevbus->next = tempbus->next;
                    tempbus->next = NULL;
                    printf("The bus number %d is deleted correctly \n",tempbus->bus_num);
                    Passenger *temppass;
                    temppass = tempbus->passlinkedlist->next;
                    while(temppass != NULL)//move the passengers inside the bus to the unmatched linked list(to the station)
                    {
                        Passenger *deletedpass;
                        deletedpass = temppass;
                        temppass = returnDeletePassenger(tempbus->passlinkedlist,temppass);//function i use it above
                        deletedpass->next = NULL;
                        insertPassenger(passengerlinkedlist,deletedpass);//insert the passenger to unmatched linked list
                        temppass = temppass->next;
                    }
                    return ;
                }
            }
            tempbus = tempbus->next;
        }
        printf("Sorry, The bus number %d doesn't exist\n",busnumber);//if the bus not in the linked list print a massege
    }
    else if(buslinkedlist == NULL)
    {
        printf("Sorry, The bus linked list didn't exist");
        return ;
    }
}
int checkIfDigit(char theword[20])//function to check if the word is digit or no
{
    for(int i = 0 ; i < strlen(theword) ; i++)
    {
        if(!isdigit(theword[i]))
        {
            printf("You Must enter a digit only!\n");
            return 1;
        }
    }
    return 0;
}
int main()
{
    int choice1;
    printf("Please Enter 1 to load the bus information file or anything else to exit\n");
    scanf("%d", &choice1);
    if(choice1 == 1)
    {
        Bus *buslinkedlist;//create a header for bus linked list and save it to the memory
        buslinkedlist = (Bus *)malloc(sizeof(Bus));
        buslinkedlist->next = NULL;
        FILE *openbusfile;//open the bus line and read the informations
        openbusfile = fopen("busses.txt", "r");
        if(openbusfile == NULL)//if the file name is false exit the system and print message
        {
            printf("Sorry, The bus file doesn't exist(must be busses.txt)");
            return 0;
        }
        char line[200];
        char *token = NULL;//pointer to split the word initially point to NULL(nothing)
        while(fgets(line, 200, openbusfile) != NULL)//loop to read all information until the last line in the file
        {
            //if(line[strlen(line) - 1] == 10)
            //line[strlen(line) - 1] = '\0';//Delete it if i dont use for capacity************
            Bus *busnode;//create bus node
            busnode = (Bus *)malloc(sizeof(Bus));
            Passenger *pass;//create a header for passenger linked list inside every bus
            pass = (Passenger *)malloc(sizeof(Passenger));
            pass->next = NULL;
            token = strtok(line, "#");//split every line depending on # sign
            busnode->bus_num = atoi(token);//convert string to integer by atoi funcion
            token = strtok(NULL, "#");
            busnode->leaving_date = atoi(token);
            token = strtok(NULL, "#");
            strcpy(busnode->departure_time, token);
            token = strtok(NULL, "#");
            strcpy(busnode->from_station, token);
            token = strtok(NULL, "#");
            strcpy(busnode->to_station, token);
            token = strtok(NULL, "#");
            busnode->ticket_price = atoi(token);
            token = strtok(NULL, "#");
            busnode->capacity = atoi(token);
            busnode->next = NULL;//the next bus is always null to insert it properly
            busnode->passlinkedlist = pass;//the passenger inside bus point to the header for passenger linked list
            insertBus(buslinkedlist, busnode);//function call for adding busses to the system
        }
        fclose(openbusfile);//close the buses file
        int choice2;
        printf("Please Enter 1 to load the passenger information file or anything else to ignore\n");
        scanf("%d", &choice2);
        if(choice2 == 1)
        {
            Passenger *passengerlinkedlist;//create a header for passenger linked list and save it to the memory
            passengerlinkedlist = (Passenger *)malloc(sizeof(Passenger));
            passengerlinkedlist->next = NULL;//the next node for header is always NULL before add any node
            FILE *openpassfile;//open the passenger file and read the information
            openpassfile = fopen("passengers.txt", "r");
            if(openpassfile == NULL)
            {
                printf("Sorry, The passenger file doesn't exist(must be passengers.txt)");
                return 0;
            }
            char linepass[200];
            char *tokenpass = NULL;
            while(fgets(linepass, 200, openpassfile) != NULL)//loop to read all information until the last line in the file
            {
                if(linepass[strlen(linepass) - 1] == 10)//condition important for comparing in functions (The last thing in the passenger file line is to destination it is String so if i don't clear the new line character the compare operation well be false)
                    linepass[strlen(linepass) - 1] = '\0';//delete the new line character by make the character before it be NULL
                Passenger *passenger;//create passenger node
                passenger = (Passenger *)malloc(sizeof(Passenger));
                tokenpass = strtok(linepass, "#");//split the line in the file depending on # sign
                passenger->passenger_id = atoi(tokenpass);//assign the proper data
                tokenpass = strtok(NULL, "#");
                passenger->traveling_date = atoi(tokenpass);
                tokenpass = strtok(NULL, "#");
                strcpy(passenger->traveling_time,tokenpass);
                tokenpass = strtok(NULL, "#");
                strcpy(passenger->from_des,tokenpass);
                tokenpass = strtok(NULL, "#");
                strcpy(passenger->to_des,tokenpass);
                passenger->next = NULL;//the next for the passenger node is always null to insert it properly
                insertPassenger(passengerlinkedlist, passenger);//function call to add passengers to the system
            }
            fclose(openpassfile);//close the passengers file
            int menuchoice = 0;
            while(menuchoice != 7)
            {
                printf("Please choose one number of the following list below :\n");//my menu
                printf("1. Assign passengers and print assignment information of all busses\n2. Print a specific bus information along with its passengers information(IDs)\n");
                printf("3. Print unmatched passengers\n4. Add new passenger\n5. Delete passenger\n6. Delete bus number\n7. Exit\n");
                scanf("%d", &menuchoice);//the choice for menu

                if(menuchoice == 1)
                {
                    assigningPassengers(buslinkedlist,passengerlinkedlist);//assign passenger function
                    printBusesInformations(buslinkedlist);//print assignment info for busses function
                    menuchoice = 0;//if the user enter a character after this code to avoid infinite loop
                }
                else if(menuchoice == 2)
                {
                    if(!busisEmpty(buslinkedlist))
                    {
                        printf("Please Enter the number of bus : \n");
                        char checkbusnumber[20];
                        scanf("%s",checkbusnumber);
                        if(!checkIfDigit(checkbusnumber))//check if the user enter a number or not
                        {
                            int busnumber;
                            busnumber = atoi(checkbusnumber);
                            printSpecificBus(buslinkedlist,busnumber);//function to print a specific bus info with passengers ID's
                        }
                    }
                    else
                        printf("Sorry, The bus linked list is empty(There's no buses in the station)\n");
                    menuchoice = 0;
                }
                else if(menuchoice == 3)
                {
                    printUnMatchedPass(passengerlinkedlist);//print the unmatched passengers
                    menuchoice = 0;
                }
                else if(menuchoice == 4)
                {
                    Passenger *newpassenger;
                    newpassenger = (Passenger *)malloc(sizeof(Passenger));//add new passenger node to the passenger linked list
                    newpassenger->next = NULL;
                    printf("Please Enter the passenger ID : \n");
                    char checkpassengerid[20];
                    scanf("%s",checkpassengerid);
                    if(!checkIfDigit(checkpassengerid))
                    {
                        newpassenger->passenger_id = atoi(checkpassengerid);
                        printf("Please Enter the passenger traveling date : \n");
                        char checkpassengertravelingdate[20];
                        scanf("%s",checkpassengertravelingdate);
                        if(!checkIfDigit(checkpassengertravelingdate))
                        {
                            newpassenger->traveling_date = atoi(checkpassengertravelingdate);
                            printf("Please Enter the passenger traveling time : \n");
                            scanf("%s",newpassenger->traveling_time);
                            printf("Please Enter the passenger destination traveling from : \n");
                            getchar();//to remove the new line character
                            fgets(newpassenger->from_des,20,stdin);//fgets to read the whole line
                            newpassenger->from_des[strlen(newpassenger->from_des) - 1] = '\0';
                            printf("Please Enter the passenger destination traveling to : \n");
                            fgets(newpassenger->to_des,20,stdin);
                            newpassenger->to_des[strlen(newpassenger->to_des) - 1] = '\0';
                            insertPassenger(passengerlinkedlist,newpassenger);//add the passenger node to the linked list
                        }

                    }

                    menuchoice = 0;
                }
                else if(menuchoice == 5)
                {
                    if(!passengerIsEmpty(passengerlinkedlist))
                    {
                        printf("Please Enter the passenger ID to delete it : \n");
                        char checkpassengerid[20];
                        scanf("%s",checkpassengerid);
                        if(!checkIfDigit(checkpassengerid))
                        {
                            int passengerid;
                            passengerid = atoi(checkpassengerid);
                            deletePassenger(buslinkedlist,passengerlinkedlist,passengerid);
                        }
                        else
                            printf("Sorry, The passenger linked list is empty(There's no passengers at the station)\n");
                        menuchoice = 0;
                    }
                }
                else if(menuchoice == 6)
                {
                    if(!busisEmpty(buslinkedlist))
                    {
                        printf("Please Enter the bus number to delete it : \n");
                        char checkbusnumber[20];
                        scanf("%s",checkbusnumber);
                        if(!checkIfDigit(checkbusnumber))
                        {
                            int busnumber;
                            busnumber = atoi(checkbusnumber);
                            deleteBus(buslinkedlist,busnumber,passengerlinkedlist);
                        }
                    }
                    else
                        printf("Sorry, The bus linked list is empty(There's no buses in the station)\n");
                    menuchoice = 0;
                }
                else if(menuchoice == 7)
                {
                    printf("Thank You and Welcome to my system");
                }
                else
                {
                    printf("Please You must choose a number from 1 - 7 !\n");
                    fflush(stdin);
                }
            }
        }
        else
        {
            printf("Thank You (The passenger file doesn't load correctly you must enter number 1)");
            return 0;
        }
    }
    else
    {
        printf("Thank You (The bus file doesn't load correctly you must enter number 1)");
        return 0;
    }
    return 0;
}
