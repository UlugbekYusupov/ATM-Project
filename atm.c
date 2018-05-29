#include "atm.h"
void with_menu() {
	printf("\n");
	printf("            *******************  WELCOME TO WITHDRAWAL SECTION  *********\n");
	printf("            *                    1.WITHDRAWAL                           *\n");
	printf("            *                    2.CHECK BALANCE                        *\n");
	printf("            *************************************************************\n");
	printf("\n%33sEnter Your choice\n %41s", " ", " ");
}
void deposit_menu() {
	printf("\n");
	printf("            *******************  WELCOME TO Deposit SECTION  *********\n");
	printf("            *                    1.DEPOSIT                              *\n");
	printf("            *                    2.CHECK BALANCE                        *\n");
	printf("            *************************************************************\n");
	printf("\n%33sEnter Your choice\n %41s", " ", " ");
}
void balance_menu() {
	printf("\n");
	printf("            *******************  WELCOME TO BALANCE SECTION  *********\n");
	printf("            *                    1.CHECK BALANCE                        *\n");
	printf("            *                    2.WITHDRAWAL                           *\n");
	printf("            *************************************************************\n");
	printf("\n%33sEnter Your choice\n %41s", " ", " ");
}
void transfer_menu() {
	printf("\n");
	printf("            *******************  WELCOME TO TRANSFER SECTION  *********\n");
	printf("            *                    1.TRANSFER                             *\n");
	printf("            *                    2.WITHDRAWAL                           *\n");
	printf("            *************************************************************\n");
	printf("\n%33sEnter Your choice\n %41s", " ", " ");
}
/*Reading data from file and keep in the head so that we can use in any function*/
ATM* Create_Atm()
{
	ATM* atm;                                                            // pointer to ATM
	FILE* file;                                                          // pointer to file
	file = fopen("data.txt", "r");                                      // reading data from file
	if (file == NULL) {                                                 //cheking if its null then it is not exist;
		printf("File not open\n");
		exit(EXIT_FAILURE);
	}
	atm = (ATM*)malloc(sizeof(ATM));                                    // initializing atm and creating in the heap
	if (atm) {                                                         // checking whether it is NULL or not if it is not do
		atm->buffer = (Account*)malloc(sizeof(Account)*(30));         // allocating space for 30 structures
		atm->count = 0;                                               //initializing the index to 0
		while (fscanf(file, "%s %s %s %s %d %d %d", atm->buffer[atm->count].fist_name,
			atm->buffer[atm->count].last_name, atm->buffer[atm->count].id,
			atm->buffer[atm->count].bank_name, &(atm->buffer[atm->count].account_number),
			&(atm->buffer[atm->count].balance), &(atm->buffer[atm->count].password)) != EOF) {
			// reading all data from file and store them in the structure by increamenting
			//count we are building array of structures

			/*printf("%s %s %s %s %d %d %d\n", atm->buffer[atm->count].fist_name,
			atm->buffer[atm->count].last_name, atm->buffer[atm->count].id,
			atm->buffer[atm->count].bank_name, atm->buffer[atm->count].account_number,
			atm->buffer[atm->count].balance, atm->buffer[atm->count].password);*/

			(atm->count)++;              // count how many accounts exist in the heap
		}
	}
	return atm;                        //  returning the address of array
}
/*receive the adress of the data in the head that is the address of arrays of structures*/
void withdrawal(ATM* atm) {            // receiving the address of array
	with_menu();
	char id[MAX];                    // id to read from a user
	int position;                   // to keep position of the id in the array
	int password, amount;          // for user's password and to withdraw amount
	int choice;
	bool success;                 // just bool variable
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("\n%33sEnter Your Id\n %41s", " ", " ");
		scanf("%s", id);
		success = search_ID(atm, id, &position);                                 // search_id returns true if it finds id, else false
																				 // and if its true it will keep the address of that position, where it found ID in the heap
		if (success) {                                                         // if success=true then do following statement
			printf("\n%33sEnter Your Password(4 digits)\n %41s", " ", " "); scanf("%d", &password);
			if (atm->buffer[position].password == password) {                 // checking wheather it is same as in the
																			  // heap at that location that search id returned
				printf("\n%33sEnter Amount to withdraw\n %41s", " ", " "); scanf("%d", &amount); // ask for amount
				if (amount >= 1000) {                                       // if amount is more than or equal 1000 then do following statement
					if (atm->buffer[position].balance >= amount) {         //  if amount that user input is lessen than or equal to in the buffer in that location's balance
						atm->buffer[position].balance -= amount;          //subtract the value of amount from the balance amount then again initialize it on it is own location
						printf("\n%35sSuccessfully Done!\n %33sPlease Take Your Cash", " ", " ");
						getch();
					}
					else {
						printf("\n%33sInsufficient balance\n %41s", " ", " ");
					}
				}
				else {
					printf("\n%33sInsufficient amount(more than 1000)\n %41s", " ", " ");
				}
			}
			else {
				printf("\n%33sPassword Incorrect! Try again...\n %41s", " ", " ");
			}
		}
		else {
			printf("\n%33sNot Found\n %41s", " ", " ");
		}
		break;
	case 2:
		balance_check(atm);
		break;
	}
	FILE* history;
	char dir[MAX] = "History\\";
	char filename[MAX];
	char txt[MAX] = ".txt";
	strcpy(filename, atm->buffer[position].id);             // copying users id to the free array
	strcat(filename, txt);
	strcat(dir, filename);															// making txt file format to read if it exists or will create if it is not
	history = fopen(dir, "a+");
	if (history == NULL) {                                                 //cheking if its null then it is not exist;
		printf("File not open\n");
		exit(EXIT_FAILURE);
	}
	else {
		fprintf(history, "Account number:%d, Amount withdrawed:%d\n",    // writing account number and amount in each users trans
			atm->buffer[position].account_number, amount);               // history list
	}
}
/*receive the adress of the data in the head that is the address of arrays of structures*/
void deposit(ATM* atm) {
	deposit_menu();
	int choice;
	char id[MAX];
	int position;
	int password, amount;
	bool success;
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("\n%33sEnter Your ID\n %41s", " ", " ");
		scanf("%s", id);
		success = search_ID(atm, id, &position);                                //searching id form the heap search_ID returns true if
		if (success) {                                                         // finds asked id otherwise false;
			printf("\n%33sEnter Your Password(4 digits)\n %41s", " ", " "); scanf("%d", &password); // if it is true it does following statements
			if (atm->buffer[position].password == password) {                 // checking if password is equal with the password in
				printf("\n%33sEnter Amount To Deposit\n %41s", " ", " "); scanf("%d", &amount);    // heap and asking to enter amount to deposit
				if (amount >= 1000) {                                   // it will add to the user's balance that amount if it is over
					atm->buffer[position].balance += amount;            // 1000
					printf("\n%33sSuccessful\n %41s", " ", " ");
					getch();
				}
				else {
					printf("\n%33sInsufficient balance\n %41s", " ", " ");
					getch();
				}
			}
			else {
				printf("\n%33sPassword Incorrect! Try again...\n %41s", " ", " ");
				getch();
			}
		}
		else {
			printf("\n%33sNot found\n %41s", " ", " ");
			getch();
		}
		break;
	case 2:
		balance_check(atm);
		break;
	}
	FILE* history;
	char dir[MAX] = "History\\";
	char filename[MAX];
	char txt[MAX] = ".txt";
	strcpy(filename, atm->buffer[position].id);                    // copying user's id in the free array and
	strcat(filename, txt);
	strcat(dir, filename);											//making txt file format with txt array then opening that file
	history = fopen(dir, "a+");                                    // if it exists it will append contents if isn't create new file named with id
	if (history == NULL) {                                                 //cheking if its null then it is not exist;
		printf("\n%33sFile Not Open\n %41s", " ", " ");
		exit(EXIT_FAILURE);
	}
	else {
		fprintf(history, "Account number:%d, Amount deposited:%d\n",
			atm->buffer[position].account_number, amount);
	}
}
/*receive the adress of the data in the head that is the address of arrays of structures*/
void balance_check(ATM* atm) {
	balance_menu();
	int choice;
	char id[MAX];
	char ch;
	int password, position;
	bool success;
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("\n%33sEnter Your ID\n %41s", " ", " "); scanf("%s", id);
		success = search_ID(atm, id, &position);
		if (success) {
			printf("\n%33sEnter Password (4 digits)\n %41s", " ", " "); scanf("%d", &password);
			if (atm->buffer[position].password == password) {
				printf("\n%33sYour balance: %d\n", " ", atm->buffer[position].balance);
				getchar();
				printf("%33sDo you wish receipt? (Y/N): ", " "); scanf("%c", &ch);
				printf("\n");
				if (ch == 'Y' || ch == 'y') {
					balance_receipt(atm, &position);
				}
				else {
					printf("\n%33sThank You!\n %41s", " ", " ");
				}
			}
			else {
				printf("\n%33sPassword Incorrect! Try again...\n %41s", " ", " ");
			}
		}
		else {
			printf("\n%33sNot Found\n %41s", " ", " ");
		}
		break;
	case 2:
		withdrawal(atm);
		break;
	}
}
/*receive the adress of the data in the head that is the address of arrays of structures*/
void transfer(ATM* atm) {
	transfer_menu();
	int choice;
	char id[MAX], *bankname[] = { "HANA_BANK","KB_BANK","WOORI_BANK","SHINHAN_BANK" };
	int bank_num;
	char ch;
	int i = 0, password, position, position2, myaccount, transaccount, amount;
	bool success, success1;
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("\n%33sEnter Your ID\n %41s", " ", " "); scanf("%s", id);
		success = search_ID(atm, id, &position);
		if (success) {
			printf("\n%33sEnter Your Password\n %41s", " ", " "); scanf("%d", &password);
			if (atm->buffer[position].password == password) {
				printf("\n%33sEnter Your Account number\n %41s", " ", " "); scanf("%d", &myaccount);
				if (atm->buffer[position].account_number == myaccount) {
					while (i < 4) {
						printf("%33s%d: %s\n", i + 1, " ", bankname[i]);
						i++;
					}
					printf("\n%33sChoose Transfer Bank\n %41s", " ", " ");
					scanf("%d", &bank_num);
					printf("\n%33sEnter Account number\n %41s", " ", " "); scanf("%d", &transaccount);
					success1 = search_Bank(atm, &transaccount, &position2);
					if (success1) {
						printf("%33sHolder full name: %s %s\n", " ", atm->buffer[position2].fist_name, atm->buffer[position2].last_name);
						printf("\n%33sEnter Amount\n %41s", " ", " "); scanf("%d", &amount);
						if (atm->buffer[position].balance >= amount) {
							atm->buffer[position].balance -= amount;
							atm->buffer[position2].balance += amount;
							printf("%33sSuccessfully transferred....\n", " ");
							getchar();
							printf("%33sDo you wish receipt (Y/N): ", " "); scanf("%c", &ch);
							printf("\n");
							if (ch == 'Y' || ch == 'y') {
								transfer_receipt(atm, &position, &position2, &amount);
							}
							else {
								printf("%33sThank you for your transaction....", " ");
							}
						}
						else {
							printf("%33sInsufficient amount...", " ");
						}
					}
					else {
						printf("%33sIncorrecr account number...Try again...Thank You.\n", " ");
					}
				}
				else {
					printf("%33sBank you entered is not supported...\n", " ");
				}
			}
			else {
				printf("%33sAccount number is incorrect...Try again...Thank You.\n", " ");
			}
		}
		else {
			printf("%33sNot found....", " ");
		}
		break;
	case 2:
		balance_check(atm);
		break;
	}
	FILE* history;
	char dir[MAX] = "History\\";
	char filename[MAX];
	char txt[MAX] = ".txt";
	strcpy(filename, atm->buffer[position].id);
	strcat(filename, txt);
	strcat(dir, filename);
	history = fopen(dir, "a+");

	if (history == NULL) {                                                 //cheking if its null then it is not exist;
		printf("File not open\n");
		exit(EXIT_FAILURE);
	}
	else {
		fprintf(history, "Account number:%d, Amount transferred:%d, Receiver's Full name: %s %s, Transferred Account:%d\n",
			atm->buffer[position].account_number, amount, atm->buffer[position2].fist_name,
			atm->buffer[position2].last_name,
			atm->buffer[position2].account_number);
	}
}
void transaction_history() {
	FILE* history;
	char id[MAX], filename[MAX], txt[MAX] = ".txt";
	char dir[MAX] = "History\\";
	printf("\n%33sEnter Your ID\n %41s", " ", " "); scanf("%s", id);
	strcpy(filename, id);
	strcat(filename, txt);
	strcat(dir, filename);
	history = fopen(dir, "r");
	if (history == NULL) {
		printf("%33sID is not exist or transaction never occured...\n", " ");
		exit(EXIT_FAILURE);
	}
	else {
		printf("%20s", " ");
		while (1) {
			char ch;
			ch = getc(history);
			printf("%c", ch);
			if (ch == EOF)
				break;
		}
	}
	getch();
}
/*true if bank name is exist in the array's structure's memebers else false */
bool search_Bank(ATM* atm, int* account_num, int* x) {
	bool success = false;
	int i = 0;
	if (atm->buffer == NULL) {
		printf("%33sThere are no data in the heap\n", " ");
		success = false;
	}
	else {
		while (i <= atm->count) {
			if (atm->buffer[i].account_number == *account_num) {
				*x = i;
				success = true;
				break;
			}
			i++;
		}
	}
	return success;
}
bool search_ID(ATM* atm, char* id, int* x) {
	bool success = false;
	int i = 0;
	if (atm->buffer == NULL) {
		printf("%33sThere are no data in the heap\n", " ");
		success = false;
	}
	else {
		while (i <= atm->count) {
			if (strcmp(id, atm->buffer[i].id) == 0) {
				*x = i;
				success = true;
				break;
			}
			i++;
		}
		return success;
	}
}
void balance_receipt(ATM* atm, int* x) {
	if (atm->buffer == NULL) {
		printf("There are no data in the head..\n");
	}
	else {
		printf("%27s******************RECEIPT****************\n", " ");
		printf("%27s  Full Name: %s %s \n", " ", atm->buffer[*x].fist_name, atm->buffer[*x].last_name);
		printf("%27s  Bank Name: %s \n", " ", atm->buffer[*x].bank_name);
		printf("%27s  Account Num: %d \n", " ", atm->buffer[*x].account_number);
		printf("%27s  Balance: %d \n", " ", atm->buffer[*x].balance);
		printf("%27s*****************************************\n", " ");
		getch();
	}
}
void transfer_receipt(ATM* atm, int* position1, int* position2, int* amount) {
	if (atm->buffer == NULL) {
		printf("%27sThere are no data in the head..\n", " ");
	}
	else {
		printf("%27s**************TRANSFER RECEIPT************\n", " ");
		printf("%27s  Sender Full Name: %s %s \n", " ", atm->buffer[*position1].fist_name, atm->buffer[*position1].last_name);
		printf("%27s  Sender Bank Name: %s \n", " ", atm->buffer[*position1].bank_name);
		printf("%27s  Receiver Account Num: %d \n", " ", atm->buffer[*position2].account_number);
		printf("%27s  Amount Transferred: %d \n", " ", *amount);
		printf("%27s******************************************\n", " ");
	}
}
void put_back(ATM* atm) {
	FILE* back;
	int i = 0;
	back = fopen("data.txt", "w");
	if (back == NULL) {
		printf("Failed while opening file\n");
	}
	else {
		while (i < atm->count) {
			fprintf(back, "%s %s %s %s %d %d %d\n", atm->buffer[i].fist_name, atm->buffer[i].last_name,
				atm->buffer[i].id, atm->buffer[i].bank_name, atm->buffer[i].account_number,
				atm->buffer[i].balance, atm->buffer[i].password);
			i++;
		}
		printf("\n");
	}
}