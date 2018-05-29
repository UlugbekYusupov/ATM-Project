#include<conio.h>
#include<string.h>
#include"atm.h"
int lang = 0;
void mainmenu() {
	printf("            *******************  WELCOME TO ATM SERVICE  ****************\n");
	printf("            *                       1.WITHDRAWAL                        *\n");
	printf("            *                       2.BALANCE INQUIRY                   *\n");
	printf("            *                       3.TRANSFER                          *\n");
	printf("            *                       4.DEPOSIT                           *\n");
	printf("            *                       5.TRANSCTION HISTORY                *\n");
	printf("            *******************     6.EXIT ATM           ****************\n");

}
int main()
{
	system("COLOR 8A");
	printf("%29s -------------------------\n", " ");
	printf("%30s| Choose Your Language: |\n", " ");
	printf("%30s| 1. English            |\n", " ");
	printf("%30s| 2. Korean             |\n", " ");
	printf("%30s| 3. Persian            |\n", " ");
	printf("%29s -------------------------\n", " ");
	printf("%30s| Enter your choice: ", " ");
	scanf("%d", &lang);
	system("cls");
	mainM();
	return 0;
}
int mainM()
{
	ATM* atm;
	atm = Create_Atm();
	int choice;
	bool ex = true;
	while (ex) {
		system("cls");
		mainmenu();
		printf("\n%36sPlease choose\n %41s", " ", " ");

		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			system("cls");
			withdrawal(atm);
			break;
		case 2:
			system("cls");
			balance_check(atm);
			break;
		case 3:
			system("cls");
			transfer(atm);
			break;
		case 4:
			system("cls");
			deposit(atm);
			break;
		case 5:
			system("cls");
			transaction_history();
			break;
		case 6:
			ex = false;
			break;
		}
	}
	put_back(atm);
	return 0;
}