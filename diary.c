/*****************************************************************************
 * Copyright (C) Nihaal Bharati bharatinihal95@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
#include<stdio.h>                   
#include<stdlib.h>
#include<string.h>                                
#include<termios.h>
#include<time.h>
#include<termios.h>
#include<unistd.h>
 

static struct termios old, new;

void initTermios(int echo){/* Initialize new terminal i/o settings */ 

	tcgetattr(0, &old); /* grab old terminal i/o settings */
	new = old; /* make new settings same as old settings */
 	new.c_lflag &= ~ICANON; /* disable buffered i/o */
 	new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
 	tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}


void resetTermios(void){ /* Restore old terminal i/o settings */

	tcsetattr(0, TCSANOW, &old);

}

/* Read 1 character - echo defines echo mode */
char getch_(int echo){ 
  	char ch;
  	initTermios(echo);
	ch = getchar();
  	resetTermios();
  	return ch;
}

/* Read 1 character without echo */
char getch(void){
  	return getch_(0);
}
/* Read 1 character with echo */
char getche(void) {
  	return getch_(1);
}
int main(){
	Password();
	mainmenu();
	getch();
	return 0;
}
int mainmenu(){
	while(1){
		int ch;
		ch=printmenu();
                switch(ch){
			case 1:
			    addrecord();
			    break;
			case 2:
			    viewrecord();
			    break;
			case 3:
			    editrecord();
			    break;
			case 4:
			    deleterecord();
			    break;
				
			case 5:
			    printf("\n\n\t\t---THANK YOU---\n\n\t\t ");
            	            system("clear");
			    exit(0);
			default:
			    printf("\nYOU ENTERED WRONG CHOICE..");
			    printf("\nPRESS ANY KEY TO TRY AGAIN");
            	            scanf("%d",&ch);
			    break;
		}
		system("clear");
        }       
	
        return 0;
}
int printmenu(){
	int ch;
        printf("\n\n\t||||*******************************************||||\n"); 
        printf("\t\t\t*PERSONAL DIARY*\n");
        printf("\t||||*******************************************||||");
        while(1){
		printf("\n\n\t\t<=MAIN MENU=>");
		printf("\n\n\tADD RECORD\t[1]");
		printf("\n\tVIEW RECORD\t[2]");
		printf("\n\tEDIT RECORD\t[3]");
		printf("\n\tDELETE RECORD\t[4]");
		printf("\n\tCLOSING APPLICATION\t[5]");
		printf("\n\n\tENTER YOUR CHOICE:");
		scanf("%d",&ch);
		return ch;
	}
}
void addrecord(){
	int ch;
  	system("clear");
	FILE *fp ;
	char another = 'Y' ,time[6],date[10];
	record e ;
        char filename[15];
        int choice;
        printf("\n\n\t\t***************************\n");
        printf("\t\t* WELCOME TO THE ADD MENU *");
        printf("\n\t\t***************************\n\n");
        printf("\n\n\tENTER DATE OF YOUR RECORD:[yyyy-mm-dd]:");
        scanf("%s",date);
        fflush(stdin);
        fgets(filename, sizeof(filename), stdin);
        fp = fopen (filename, "ab+" ) ;
        if ( fp == NULL ){
		fp=fopen(filename,"wb+");
        	if(fp==NULL){
            		printf("SYSTEM ERROR...\n");
			printf("PRESS ANY KEY TO EXIT\n");
        	        scanf("%d",&ch);
            	        return ;
                }
        }
        while ( another == 'Y'|| another=='y' ){
        	choice=0;
        	fflush(stdin);
        	printf ( "\n\tENTER TIME:[hh:mm]:");
        	scanf("%s",time);
        	rewind(fp);
        	while(fread(&e,sizeof(e),1,fp)==1){
        		if(strcmp(e.time,time)==0){
                		printf("\n\tTHE RECORD ALREADY EXISTS.\n");
                		choice=1;
			}

        	}
        	if(choice==0){
                	strcpy(e.time,time);
            		printf("\tENTER NAME:");
            		fflush(stdin);
		    	scanf("%s",e.name);
			
		    	printf("\tENTER PLACE:");
			fflush(stdin);
		        scanf("%s",e.place);
		    	
		    	printf("\tENTER DURATION:");
			fflush(stdin);
		    	scanf("%s",e.duration);
		    
		    	printf("\tNOTE:");
			fflush(stdin);
		    	scanf("%s",e.note);
		
		    	fwrite ( &e, sizeof ( e ), 1, fp ) ;
		    	printf("\nYOUR RECORD IS ADDED...\n");
		}
		printf ( "\n " ) ;
		fflush ( stdin ) ;
		scanf("%c",&another);
	}
    	fclose ( fp ) ;
    	printf("PRESS ONLY INTEGERS KEY TO EXIT ADD MENU..\n");
    	scanf("%d",&ch);
    	return;
}
void viewrecord(){
	FILE *fpte ;
        system("clear");
    	struct record customer ;
    	char time[6],choice,filename[14],date[10];
    	int ch;
    	printf("\n\n\t\t*******************************\n");
    	printf("\t\t* HERE IS THE VIEWING MENU *");
    	printf("\n\t\t*******************************\n\n");
    	
    	do{
        	printf("\n\tENTER THE DATE OF RECORD TO BE VIEWED:[yyyy-mm-dd]:");
		scanf("%s",date);
        	fflush(stdin);
        	fgets(filename,sizeof(filename),stdin);
        	fpte = fopen ( filename, "rb" ) ;
        	if ( fpte == NULL ){
            		puts ( "\nTHE RECORD DOES NOT EXIST...\n" ) ;
            		printf("PRESS ANY KEY TO EXIT...");
			scanf("%d",&ch);
            		return ;
        	}
        	system("clear");
		printf("\n\tHoW WOULD YOU LIKE TO VIEW:\n");
		printf("\n\t1.WHOLE RECORD OF THE DAY.");
		printf("\n\t2.RECORD OF FIX TIME.");
		printf("\n\t\tENTER YOUR CHOICE:");
		scanf("%d",&ch);
		switch(ch){
        		case 1:
			printf("\nTHE WHOLE RECORD FOR %s IS:",filename);
            		while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 ){
                		printf("\n");
				printf("\nTIME: %s",customer.time);
				printf("\nMEETING WITH: %s",customer.name);
				printf("\nMEETING AT: %s",customer.place);
				printf("\nDURATION: %s",customer.duration);
				printf("\nNOTE: %s",customer.note);
				printf("\n");
			}
            		break;
        		case 2:
            		fflush(stdin);
            		printf("\nENTER TIME:[hh:mm]:\n");
        		scanf("%s",time);
            		while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 ){
                		if(strcmp(customer.time,time)==0){
		            		printf("YOUR RECORD IS:\n");
		            		printf("TIME: %s\n",customer.time);
		            		printf("MEETING WITH: %s\n",customer.name);
		           		printf("MEETING AT: %s\n",customer.place);
		           	 	printf("DUARATION: %s\n",customer.duration);
		            		printf("NOTE: %s\n",customer.note);
                		}
            		}
            		break;
        		default:
            			printf("\nYOU TYPED SOMETHING ELSE...");
            		break;
		}
                printf ( "\n " ) ;
		fflush ( stdin ) ;
		scanf("%c",&choice);
	}
    	while(choice=='Y'||choice=='y');
    	fclose ( fpte ) ;
    	printf("PRESS ONLY INTEGERS KEY TO EXIT VIEW MENU..\n");
    	scanf("%d",&ch);
    	return ;
}

void editrecord(){
	int ch,i;
 
    	system("clear");
    	FILE *fpte ;
	struct record customer ;
    	char time[6],choice,filename[14];
    	char date[10];
   	int num,count=0;
    	printf("\n\n\t\t*******************************\n");
    	printf("\t\t* WELCOME TO THE EDITING MENU *");
    	printf("\n\t\t*******************************\n\n");
    
    	do{
   
		system("clear");
        	printf("\n\tENTER THE DATE OF RECORD TO BE EDITED:[yyyy-mm-dd]:");
		scanf("%s",date);
		fflush(stdin);
		fgets(filename,sizeof(filename),stdin);
		printf("\n\tENTER TIME:[hh:mm]:");
		scanf("%s",time);
		fpte = fopen ( filename, "rb+" ) ;
		if ( fpte == NULL ){
            		printf( "\nRECORD DOES NOT EXISTS:" ) ;
            		printf("\nPRESS ANY KEY TO GO BACK");
			scanf("%d",&ch);
            		return;
        	}
        	while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 ){
            		if(strcmp(customer.time,time)==0){
                		printf("\nYOUR OLD RECORD WAS AS:");
                		printf("\nTIME: %s",customer.time);
                		printf("\nMEETING WITH: %s",customer.name);
                		printf("\nMEETING AT: %s",customer.place);
                		printf("\nDURATION: %s",customer.duration);
                		printf("\nNOTE: %s",customer.note);
                		printf("\n\n\t\tWHAT WOULD YOU LIKE TO EDIT..");
                		printf("\n1.TIME.");
                		printf("\n2.MEETING PERSON.");
                		printf("\n3.MEETING PLACE.");
                		printf("\n4.DURATION.");
                		printf("\n5.NOTE.");
                		printf("\n6.WHOLE RECORD.");
                		printf("\n7.GO BACK TO MAIN MENU.");
                		do{
                    			printf("\n\tENTER YOUR CHOICE:");
                    			fflush(stdin);
                    			scanf("%d",&num);
                   			fflush(stdin);
					switch(num){
                    				case 1:
							printf("\nENTER THE NEW DATA:");
							printf("\nNEW TIME:[hh:mm]:");
							fflush(stdin);
					    		scanf("%s",customer.time);
                        				break;
                    				case 2:
                        				printf("\nENTER THE NEW DATA:");
                        				printf("\nNEW MEETING PERSON:");
                   					fflush(stdin);
		    					scanf("%s",customer.name);
			                        
							break;
                    				case 3:
                        				printf("\nENTER THE NEW DATA:");
							printf("\nNEW MEETING PLACE:");
				   			fflush(stdin);
						    	scanf("%s",customer.place);
							break;
                    				case 4:
							printf("\nENTER THE NEW DATA:");
							printf("\nDURATION:");
							fflush(stdin);
						    	scanf("%s",customer.duration);
		
							break;
                    				case 5: 
							printf("ENTER THE NEW DATA:");
							printf("\nNOTE:");
							fflush(stdin);
						    	scanf("%s",customer.note);
							break;
                    				case 6:
							printf("\nENTER THE NEW DATA:");

							printf("\nNEW TIME:[hh:mm]:");
							fflush(stdin);
						    	scanf("%s",customer.time); 
			
							printf("\nNEW MEETING PERSON:");
							fflush(stdin);
						    	scanf("%s",customer.name);
			
							printf("\nNEW MEETING PLACE:");
							fflush(stdin);
						    	scanf("%s",customer.place);
			
							printf("\nDURATION:");
							fflush(stdin);
						    	scanf("%s",customer.duration);

							printf("\nNOTE:");
							fflush(stdin);
						    	scanf("%s",customer.note);
							break;
                    				case 7:
                        				printf("\nPRESS ANY KEY TO GO BACK...\n");
							scanf("%d",&ch);
							return ;
							break;
                    				default:
							printf("\nYOU TYPED SOMETHING WRONG TRY AGAIN\n");
							break;
					}
		    
				}
				while(num<1||num>8);
				fseek(fpte,-sizeof(customer),SEEK_CUR);
				fwrite(&customer,sizeof(customer),1,fpte);
				fseek(fpte,-sizeof(customer),SEEK_CUR);
				fread(&customer,sizeof(customer),1,fpte);
				choice=5;
				break;
			}
		}
        	if(choice==5){
            	system("clear");
            	printf("\n\t\tEDITING COMPLETED...\n");
            	printf("--------------------\n");
            	printf("THE NEW RECORD IS:\n");
            	printf("--------------------\n");
            	printf("\nTIME: %s",customer.time);
            	printf("\nMEETING WITH: %s",customer.name);
            	printf("\nMEETING AT: %s",customer.place);
            	printf("\nDURATION: %s",customer.duration);
            	printf("\nNOTE: %s",customer.note);
          
            	printf("\n");
            	scanf("%c",&choice);
            	count++;
	}
        else{
		printf("\nTHE RECORD DOES NOT EXIST::\n");
           
            	scanf("%c",&choice);
        }
	fclose(fpte);
	printf("\n\n\tWOULD YOU LIKE TO EDIT ANOTHER RECORD.(Y/N)");
        scanf("%c",&choice);
        count++;
        }while(choice=='Y'||choice=='y');
    	
    
    	if(count==1)
        	printf("\n%d FILE IS EDITED...\n",count);
    	else if(count>1)
        	printf("\n%d FILES ARE EDITED..\n",count);
    	else
		printf("\nNO FILES EDITED...\n");
	    	printf("\tPRESS ANY KEY TO EXIT EDITING MENU.");
		scanf("%d",&ch);

}
int Password(){
	system("clear");
	char d[25]="Password Protected";
	char ch,pass[10];
	int i=0,j; 
	printf("\n");
	printf("\n");printf("\n");
	printf("Enter Password:");
	while(ch!=10){
		ch=getch();

		if(ch!=10 && ch!=8){
			printf("*");
			pass[i] = ch;
			i++;
		}
	}
	   
	pass[i] = '\0';
	if(strcmp(pass,password)==0){

		printf("\n");
		printf("Password granted\n");
	
		return ;
		
	}
	else{
		printf("\n");
		printf("\aWarning!! Incorrect Password");
		Password();
	}
	return 1;
}
void deleterecord(){
	int ch;
    	system("clear");
    	FILE *fp,*fptr ;
    	record file ;
    	char filename[15],another = 'Y' ,time[10];;
    	int choice;
    	printf("\n\n\t\t*************************\n");
    	printf("\t\t* WELCOME TO DELETE MENU*");
    	printf("\n\t\t*************************\n\n");
    
    	while ( another == 'Y' ){
		printf("\n\n\tHOW WOULD YOU LIKE TO DELETE.");
		printf("\n\n\t#DELETE WHOLE RECORD\t\t\t[1]");
		printf("\n\t#DELETE A PARTICULAR RECORD BY TIME\t[2]");
        	do{
            		printf("\n\t\tENTER YOU CHOICE:");
            		scanf("%d",&choice);
            		switch(choice){
            			case 1:
                			printf("\n\tENTER THE DATE OF RECORD TO BE DELETED:[yyyy-mm-dd]:");
                			fflush(stdin);
					fgets(filename, sizeof(filename), stdin);
					fp = fopen (filename, "wb" ) ;
					if ( fp == NULL ){
				    		printf("\nTHE FILE DOES NOT EXISTS");
				    		printf("\nPRESS ANY KEY TO GO BACK.");
						scanf("%d",&ch);
                    				return ;
                			}
                			fclose(fp);
                			remove(filename);
                			printf("\nDELETED SUCCESFULLY...");
                			break;
            			case 2:
                			printf("\n\tENTER THE DATE OF RECORD:[yyyy-mm-dd]:");
                			fflush(stdin);
					fgets(filename, sizeof(filename), stdin);
					fp = fopen (filename, "rb" ) ;
					if ( fp == NULL ){
				    		printf("\nTHE FILE DOES NOT EXISTS");
				    		printf("\nPRESS ANY KEY TO GO BACK.");
						scanf("%d",&ch);
                    				return ;
                			}
					fptr=fopen("temp","wb");
					if(fptr==NULL){
				    		printf("\nSYSTEM ERROR");
				    		printf("\nPRESS ANY KEY TO GO BACK");
						scanf("%d",&ch);
                    				return ;
                			}
					printf("\n\tENTER THE TIME OF RECORD TO BE DELETED:[hh:mm]:");
					fflush(stdin);
				   	fgets(time, sizeof(time), stdin);
					while(fread(&file,sizeof(file),1,fp)==1){
				    		if(strcmp(file.time,time)!=0)
				        		fwrite(&file,sizeof(file),1,fptr);
					}
					fclose(fp);
					fclose(fptr);
					remove(filename);
					rename("temp",filename);
					printf("\nDELETED SUCCESFULLY...");
					break;
			    		default:
						printf("\n\tYOU ENTERED WRONG CHOICE");
					break;
				}
			}
			while(choice<1||choice>2);
			printf("\n\tDO YOU LIKE TO DELETE ANOTHER RECORD.(Y/N):");
			fflush(stdin);
			scanf("%c",&another);
    		}
		printf("\n\n\tPRESS ANY KEY TO EXIT...");
		scanf("%d",&ch);


}


    
    




