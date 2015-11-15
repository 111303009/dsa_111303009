typedef struct  record{

	char time[6];
	char name[30];
	char place[25];
	char duration[10];
	char note[500];
	
}record ;
int mainmenu();
void addrecord();
void viewrecord();
void editrecord();
void clossingapplication(void);
void deleterecord();
char password[20]={"personal"}; 
