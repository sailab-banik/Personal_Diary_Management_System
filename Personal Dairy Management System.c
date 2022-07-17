#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>


#define ENTER 13
#define TAB 9
#define BKSP 8
#define SPACE 32

int user();
int name();
int password();
int hello();
int enter();
int menu();
int addrecord(); 
int viewrecord();
int editrecord();
int delrecord();

int main()
{
	int u;
	u=user();
	system("cls");
	getch();
}

int user()
{
	int ch;
	printf("\n\n\t\t::Welcome To Your Personal Dairy::\n");
	while(1)
	{
		printf("\n\n\t[1].Register.");
		printf("\n\n\t[2].LogIn Through Password.");
		printf("\n\n\t[3].Exit.");
		printf("\n\n\t\tEnter Your Choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				system("cls");
				name();
			    password();
			    system("cls");
				break;
			case 2:
				system("cls");
				hello();
				break;
			case 3:
				printf("\n\n\tPress Any Key To Exit...\n");
				exit(0);
			default :
			    printf("You Entered Wrong Choice...Try Again");
				break;	
		}
	}
	getch();
}

struct user
{
	char fname[30];
	char lname[30];
};

int name()
{
	printf("\n\n\t\t::Register Your Name And Password::");
	int i;
	FILE *fp;
	struct user u;
	fp=fopen("name.txt","w");
	if(fp==NULL)
	{
		printf("file not found");
		return 0;
	}
	printf("\n\n\t Enter Your First Name: ");
    scanf("%s",u.fname);
    printf("\n\n\t Enter Your Last Name: ");
    scanf("%s",u.lname);
    fwrite(&u,sizeof(u),1,fp);
    fclose(fp);
}

int password()
{
	int i=0;
	FILE *fp;
	char p[5],ch;
	fp=fopen("password.txt","w");
	if(fp==NULL)
	{
		printf("File not Found");
		return 0;
    }
	printf("\n\n\t Set Your Password[No Space/Tab]: ");
	while(p[i]!='\r')
	{
		p[i]=getch();
		if(p[i]==BKSP)
		{
			if(i>0)
			{
				i--;
				printf("\b \b");
			}	
		}
		else if(p[i]==ENTER)
		{
			p[i]='\0';
			break;
		}
		else if(p[i]==TAB||p[i]==SPACE)
		{
			continue;
		}
		else
		{
			printf("*");
			ch=p[i];
			fputc(ch,fp);
			i++;
		}
	}
	fputc(p[i],fp);
	fclose(fp);
	printf("\n\n\nPress Any Key To Go Back....");
	getch();
}

int hello()
{
	printf("\n\n\t\t::LogIn Through Password::");
	int i,j;
	char ch[30];
	struct user u;
	FILE *fp;
	fp=fopen("name.txt","r");
	if(fp==NULL)
	{
		printf("file is not found");
		return 0;
	}
	fread(&u,sizeof(u),1,fp);
	printf("\n\n\t\t\t::Hello! %s %s::",u.fname,u.lname);
	fclose(fp);
	i=enter();
	j=menu();
	system("cls");
}

int enter()
{
	char pass[5],check[5],ch;
	FILE *fp;
	int i=0;
	printf("\n\n\t Enter Your Password: ");
	while(pass[i]!='\r')
	{
		pass[i]=getch();
		if(pass[i]=='\b')
		{
			if(i>0)
			{
				i--;
				printf("\b \b");
			}
		}
		else if(pass[i]==ENTER)
		{
			pass[i]='\0';
			break;
		}
		else if(pass[i]==TAB||pass[i]==SPACE)
		{
			continue;
		}
		else
		{
			printf("*");
			i++;
		}
	}
	pass[i]='\0';
	fp=fopen("password.txt","r");
	if(fp==NULL)
	{
		printf("Error system file\n");
		getch();
		return 1;
	}
	else
	  i=0;
	while(1)
	{
		ch=fgetc(fp);
		if(ch==EOF)
		{
			check[i]='\0';
			break;
		}
		else
		{
		    check[i]=ch;
		    i++;
    	}
	}
	if(strcmp(pass,check)==0)
	{
		printf("\n\n\t Access Granted...\n");
	}
	else
	{
	    printf("\n\n\t Invalid Password...\n");
	    exit(0);
	}
	getch();	  
}

int menu()
{
	system("cls");
	int ch;
	while(1)
	{
		printf("\n\t\t::Main Menu::\n");
	    printf("\n\t[1]Add Record\n");
	    printf("\n\t[2]View Record\n");
	    printf("\n\t[3]Edit Record\n");
	    printf("\n\t[4]Delete Record\n");
	    printf("\n\t[5]Exit\n");
	    printf("\n\tEnter Your choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
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
			    delrecord();
				break;  
			case 5:
				printf("\n\tThank You...Press any key to exit");
				getch();
				exit(0);
			default:
				printf("You Entered A Wrong Choice\n");
				printf("Press Any Key To Go Back\n");
				getch();
				break;
		}
	}
    getch();
}

struct record
{
	char time[10];
	char name[40];
	char date[10];
	char place[40];
	char note[500];
};

int addrecord()
{
	system("cls");
	FILE *fp;
	char another='Y',time[10];
	struct record e;
	char filename[15];
	int choice;
	printf("\n\t\t::Welcome to the Add Menu::\n");
	printf("\n\tEnter The Date of Your Record[dd-mm-yyyy]: ");
	fflush(stdin);
	gets(filename);
	fp=fopen(filename,"a+");
	if(fp==NULL)
	{
		fp=fopen(filename,"w+");
		if(fp==NULL) 
		{
			printf("\nSystem error....Please Enter The Date In The Given Format");
			printf("\nPress any key to exit");
			getch();
			return;
		}
	}
	while(another=='Y'||another=='y')
	{
		choice=0;
		fflush(stdin);
		printf("\n\tEnter Time[hh:mm][24hrs format]: ");
		scanf("%s",time);
		rewind(fp);
		while(fread(&e,sizeof(e),1,fp)==1)
		{
			if(strcmp(e.time,time)==0)
			{
				printf("\tThe record already exits.\n");
				choice=1;
			}
		}
		if(choice==0)
		{
			strcpy(e.time,time);
			printf("\n\tEnter Title: ");
			fflush(stdin);
			gets(e.name);
			printf("\n\tEnter Place: ");
			gets(e.place);
			fflush(stdin);
			printf("\n\tEnter Note: ");
			gets(e.note);
			fwrite(&e,sizeof(e),1,fp);
			printf("\nYour record is Added...\n");
		}
		printf("\n\tAdd Another Record...(Y/N)");
		fflush(stdin);
		another=getchar();
	}
	fclose(fp);
	printf("\n\n\tPress Any Key to exit...");
	getch();
	system("cls");
}

int viewrecord()
{
	system("cls");
	FILE *fp;
    struct record c;
	char time[6],filename[14],name[30];
	int ch,choice;
	choice=enter();
	system("cls");
	printf("\n\n\t\t::Welcome to View Menu::");
	do
	{
		printf("\n\n\tEnter The Date Of Record To Be Viewed[dd-mm-yyyy]: ");
		fflush(stdin);
		gets(filename);
		fp=fopen(filename,"r");
		if(fp==NULL)
		{
			puts("\nThe Record Does Not Exist...\n");
			printf("Press Any Key to Exit...");
			getch();
			return;
		}
		system("cls");
		printf("\n\tHow would you like to view:");
		printf("\n\n\t[1].Whole Record Of The Day.");
		printf("\n\n\t[2].Record Of Fix Time.");
		printf("\n\n\t[3].Record By Title.");
		printf("\n\n\t\tEnter Your Choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("\n\tThe Whole Record for %s is",filename);
				while(fread(&c,sizeof(c),1,fp)==1)
				{
					printf("\n");
					printf("\n\tTime: %s",c.time);
					printf("\n\tTitle: %s",c.name);
					printf("\n\tPlace: %s",c.place);
					printf("\n\tNote: %s",c.note);
					printf("\n");
				}
				break;
			case 2:
				fflush(stdin);
				printf("\n\t\tEnter Time[hh:mm]: ");
				gets(time);
				fp=fopen(filename,"r");
				if(fp==NULL)
	        	{
			        puts("\nThe Record Does Not Exist...\n");
			        printf("Press Any Key to Exit...");
			        getch();
			        return;
		        }
				while(fread(&c,sizeof(c),1,fp)==1)
				{
					if(strcmp(c.time,time)==0)
					{
						printf("\n\n\t\tYour Record is: ");
						printf("\n\n\tTime: %s",c.time);
						printf("\n\tTitle: %s",c.name);
						printf("\n\tPlace: %s",c.place);
						printf("\n\tNote: %s",c.note);
					}
				}
				break;
			case 3:
				fflush(stdin);
				printf("\n\t\tEnter Title: ");
				gets(name);
				fp=fopen(filename,"r");
				if(fp==NULL)
		        {
			        puts("\nThe Record Does Not Exist...\n");
			        printf("Press Any Key to Exit...");
			        getch();
		        	system("cls");
	        	}
				while(fread(&c,sizeof(c),1,fp)==1)
				{
					if(strcmp(c.name,name)==0)
					{
						printf("\n\n\t\tYour Record is:");
						printf("\n\n\tTime: %s",c.time);
						printf("\n\tTitle: %s",c.name);
						printf("\n\tPlace: %s",c.place);
						printf("\n\tNote: %s",c.note);
					}
				}
				break;
			default:
				printf("Wrong Input...\n");
				break;
		}
		printf("\n\nWould You Like To Continue Viewing...(Y/N):");
		fflush(stdin);
		scanf("%c",&choice);
		system("cls");
	}while(choice=='Y'||choice=='y');
	fclose(fp);
	system("cls");
}

int editrecord()
{
	system("cls");
	FILE *fp;
	struct record r;
	char time[6],choice,filename[14],name[30],ch;
	int num,count=0;
	choice=enter();
	system("cls");
	printf("\n\t\t::Welcome to Edit Menu::\n");
	do
	{
		printf("\n\tEnter The Date Of Record To Be Edited[dd-mm-yyyy]: ");
		fflush(stdin);
		gets(filename);
		fp=fopen(filename,"r+");
		if(fp==NULL)
		{
			puts("\nThe record does not exist...\n");
			printf("Press any key to exit...");
			getch();
			return;
		}
		system("cls");
		printf("\n\n\t\tHow Would You Like To Choose Your Record:\n");
		printf("\n\t[1].By Time.\n");
		printf("\n\t[2].By Title.\n");
		printf("\n\t\tEnter Your Choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				fflush(stdin);
				printf("\n\t\tEnter Time[hh:mm]: ");
				gets(time);
				while(fread(&r,sizeof(r),1,fp)==1)
				{
					if(strcmp(r.time,time)==0)
					{
						printf("\n\n\t\tYour Record is: ");
						printf("\n\n\tTime: %s",r.time);
						printf("\n\tTitle: %s",r.name);
						printf("\n\tPlace: %s",r.place);
						printf("\n\tNote: %s",r.note);
						printf("\n\n\t\tWhat Would You Like To Edit:");
						printf("\n\t[1].Time.");
						printf("\n\t[2].Title.");
						printf("\n\t[3].Place");
						printf("\n\t[4].Note");
						printf("\n\t[5].Whole Record.");
						printf("\n\t[6].Go Back To Main Menu");
						do
						{
							printf("\n\tEnter Your Choice: ");
							fflush(stdin);
							scanf("%d",&num);
							fflush(stdin);
							switch(num)
							{
								case 1:
									printf("\n\n\tEnter The New Data:");
									printf("\n\n\tNew Time[hh:mm][24hrs Format]: ");
									gets(r.time);
									break;
								case 2:
								    printf("\n\n\tEnter The New Data:");
									printf("\n\n\tNew Title: ");
									gets(r.name);
									break;
								case 3:
								    printf("\n\n\tEnter The New Data:");
									printf("\n\n\tNew Place: ");
									gets(r.place);
									break;
								case 4:
								    printf("\nEnter The New Data:");
									printf("\nNote: ");
									gets(r.note);
									break;
								case 5:
								    printf("\nEnter The New Data:");
									printf("\nNew Time[hh:mm]: ");
									gets(r.time);
									printf("\nNew Title: ");
									gets(r.name);
									printf("\nNew Place: ");
									gets(r.place);
									printf("\nNote: ");
									gets(r.note);
									break;
								case 6:
								    printf("Press any key to go back....\n");
									getch();
									break;
								default:
								    printf("\nYou Typed Something Else...Try Again");
									break;		
							}
						}while(num<1||num>7);
						fseek(fp,-sizeof(r),SEEK_CUR);
						fwrite(&r,sizeof(r),1,fp);
						fseek(fp,-sizeof(r),SEEK_CUR);
						fread(&r,sizeof(r),1,fp);
						choice=5;
					}
				}
				break;
			    case 2:
				    fflush(stdin);
				    printf("\n\n\t\tEnter Title: ");
				    gets(name);
				    while(fread(&r,sizeof(r),1,fp)==1)
				   {
					if(strcmp(r.name,name)==0)
					{
						printf("\n\n\t\tYour Record is:");
						printf("\n\n\tTime: %s",r.time);
						printf("\n\tTitle: %s",r.name);
						printf("\n\tPlace: %s",r.place);
						printf("\n\tNote: %s",r.note);
						printf("\n\n\t\tWhat Would You Like To Edit: ");
						printf("\n\t[1].Time.");
						printf("\n\t[2].Title.");
						printf("\n\t[3].Place");
						printf("\n\t[4].Note");
						printf("\n\t[5].Whole Record.");
						printf("\n\t[6].Go Back To Main Menu");
						do
						{
							printf("\n\tEnter Your Choice: ");
							fflush(stdin);
							scanf("%d",&num);
							fflush(stdin);
							switch(num)
							{
								case 1:
									printf("\nEnter The New Data:");
									printf("\nNew Time[hh:mm]:");
									gets(r.time);
									break;
								case 2:
								    printf("\nEnter The New Data:");
									printf("\nNew Title: ");	
									gets(r.name);
									break;
								case 3:
								    printf("\nEnter The New Data:");
									printf("\nNew Place: ");
									gets(r.place);
									break;
								case 4:
								    printf("\nEnter The New Data:");
									printf("\nNote: ");
									gets(r.note);
									break;
								case 5:
								    printf("\nEnter The New Data:");
									printf("\nNew Time[hh:mm]: ");
									gets(r.time);
									printf("\nNew Title: ");
									gets(r.name);
									printf("\nNew Place: ");
									gets(r.place);
									printf("\nNote: ");
									gets(r.note);
									break;
								case 6:
								    printf("Press any key to go back....\n");
									getch();
									break;
								default:
								    printf("\nYou Typed Something Else...Try Again");
									break;		
							}		
						}while(num<1||num>7);
						fseek(fp,-sizeof(r),SEEK_CUR);
						fwrite(&r,sizeof(r),1,fp);
						fseek(fp,-sizeof(r),SEEK_CUR);
						fread(&r,sizeof(r),1,fp);
						choice=5;	
					}
				}
			break;
			}
		if(choice==5)
		{
			system("cls");
			printf("\n\t\tEditing Completed...\n");
			fclose(fp);
			printf("\n\n\t\tWould You Like To Edit Another Record(Y/N): ");
			scanf("%c",&choice);
			count++;
			system("cls");
		}
		else
		{
			printf("The Record does not exist...\n");
			printf("\n\tWould You Like To Try Again(Y/N): ");
			scanf("%c",&choice);
			system("cls");
	    }
	}while(choice=='Y'||choice=='y');
	fclose(fp);
	if(count==1)
	{
		printf("\n%d Files Are Edited...\n",count);
	}
	else if(count>1)
	{
		printf("\n%d Files Are Edited...\n",count);
	}
	else
	{
		printf("\nNo Files Are Edited...\n");
	}
	printf("\nPress Any Key To Exit....");
	getch();
	system("cls");
}

int delrecord()
{
	system("cls");
	FILE *fp,*fptr,*ptr;
	struct record d;
	char filename[15],another='Y',time[10],name[30];
	int choice,ch;
	ch=enter();
	system("cls");
	printf("\n\n\t\t::Welcome To Delete Menu::");
	while(another=='Y'||another=='y')
	{
		printf("\n\n\t\tHow Would You Like To Delete.");
		printf("\n\n\t[1].Delete Whole Record of The Day.");
		printf("\n\n\t[2].Delete a Particular Record of The Day by Time.");
		printf("\n\n\t[3].Delete a Particular Record of The Day by Title.");
		do
		{
			printf("\n\n\t\tEnter You Choice: ");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:
					printf("\n\tEnter The Date of Record To be Deleted[dd-mm-yyyy]: ");
					fflush(stdin);
					gets(filename);
					fp=fopen(filename,"r");
					if(fp==NULL)
					{
						printf("\nThe File Does Not Exists");
						printf("\nPress Any Key To Go Back.");
						getch();
						return;
					}
					fclose(fp);
					remove(filename);
					printf("\n\tDeleted Successfully...");
					break;
				case 2:
				    printf("\n\tEnter The Date Of Record[dd-mm-yyyy]: ");
					fflush(stdin);
					gets(filename);
					fp=fopen(filename,"r");
					if(fp==NULL)
					{
						printf("\nThe File Does Not Exists");
						printf("\nPress Any Key To Go Back.");
						getch();
						return;
					}
					printf("\n\tEnter The Time of Record To be Deleted[hh:mm]: ");
					fflush(stdin);
					gets(time);
					fptr=fopen("temp","w");
					if(fptr==NULL)	
					{
						printf("\nThe File Does Not Exists");
						printf("\nPress Any Key To Go Back.");
						getch();
						return;
					}
					while(fread(&d,sizeof(d),1,fp)==1)
					{
						if(strcmp(d.time,time)!=0)
						fwrite(&d,sizeof(d),1,fptr);
					}
					fclose(fp);
					fclose(fptr);
					remove(filename);
					rename("temp",filename);
					remove("temp");
					printf("\n\tDeleted Successfully");
					break;
			    case 3:
				    printf("\n\tEnter The Date Of Record[dd-mm-yyyy]: ");
					fflush(stdin);
					gets(filename);
					fp=fopen(filename,"r");
					if(fp==NULL)
					{
						printf("\nThe File Does Not Exists");
						printf("\nPress Any Key To Go Back.");
						getch();
						return;
					}
					ptr=fopen("temp","w");
					if(ptr==NULL)	
					{
						printf("\nThe File Does Not Exists");
						printf("\nPress Any Key To Go Back.");
						getch();
						return;
					}
					printf("\n\tEnter The Title of Record To be Deleted:");
					fflush(stdin);
					gets(name);
					while(fread(&d,sizeof(d),1,fp)==1)
					{
						if(strcmp(d.name,name)!=0)
						fwrite(&d,sizeof(d),1,ptr);
					}
					fclose(fp);
					fclose(ptr);
					remove(filename);
					rename("temp",filename);
					remove("temp");
					printf("\n\tDeleted Successfully...");
					break;
			default :
			        printf("\n\tYou Entered Wrong Choice");
					break;		
			}
		}while(choice<1||choice>3);
		printf("\n\n\tDo You Like To Delete Another Record(Y/N): ");
		fflush(stdin);
		scanf("%c",&another);
		system("cls");
	}
	printf("\n\n\t Press Any Key To Exit");
	getch();
	system("cls");
}
