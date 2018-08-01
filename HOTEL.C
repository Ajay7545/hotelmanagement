#include<stdio.h>
#include<string.h>
using namespace std;
int scount=0;
int dcount=0;
int decount=0;
int bill;
int single[10]={100,101,102,103,104,105,106,106,108,109};
int doubl[10]={200,201,202,203,204,205,206,207,208,209};
int deluxe[10]={300,301,302,303,304,305,306,307,308,309};
int member=0;
int food[100][2];
int top=-1;
int n;
struct details
{
	int roomno;
	char first[20];
	char last[20];
	char phone[11];
	struct date
	{
		int day;
		int month;
		int year;
	}d;
	struct time
	{
		int hour;
		int minute;
	}t;
	char idtype[100];
	char id[40];
}d1;
struct checkindate
	{
		int day;
		int month;
		int year;
		int hour;
		int minute;
	};
struct list
{
	char first[20];
	char last[20];
	int roomno;
	struct checkindate *d;
	int bill;
	char type[20];
	struct list *next;
}*start=NULL;
FILE *f1,*l,*r;
void detail(int ,int ,char []);
void create(char [],char [],int ,int ,int ,int ,int ,int ,int ,char []);
int compute(char []);
void print();
void scan();
int main()
{
	int m,a,b,room;
	startmenu:
	printf("1.Administrator\n2.Customer\n3.exit\nEnter choice");
	up:
	scanf("%d",&m);
	switch(m)
	{
		case 1:
		printf("\t\t\t1.modify customer details\n");
		printf("\t\t\t2.bill\n\t\t\t3.Add or delete from food menu\n\t\t\t4.modify features of room");
		printf("\n\t\t\t5.exit to main menu");
		up1:
		printf("\nenter choice");
		scanf("%d",&a);
		switch(a)
		{
			case 1:scan();
			break;
			case 2:
			break;
			case 3:
			break;
			case 4:
			break;
			case 5:
			goto startmenu;
			default:
			printf("wrong choice");
			goto up1;
		}
		break;
		case 2:
		up4:
		printf("\t\t\t1.book a room\n\t\t\t2.food menu\n\t\t\t3.check out");
		printf("\n\t\t\t4.exit to main menu");
		up2:
		printf("\nenter choice");
		scanf("%d",&b);
		switch(b)
		{
			case 1:
			printf("Types of room       fixed charges    charges per day   availability\n");
			printf("1.single room     | 1000           | 3000             | %d\n",10-scount);
			printf("2.double room     | 1000           | 4000             | %d\n",10-dcount);
			printf("3.deluxe room     | 1000           | 5000             | %d\n",10-decount);
			up3:
			printf("enter choice");
			scanf("%d",&room);
			switch(room)
			{
				case 1:n=compute("single");
				detail(n,3000,"single");
				printf("\n");
				goto up4;
				case 2:
				n=compute("double");
				printf("Member 1 details\n");
				detail(n,4000,"double");
				member++;
				printf("Member 2 details\n");
				detail(n,4000,"double");
				member=0;
				printf("\n");
				goto up4;
				case 3:
				break;
				default:
				printf("wrong choice");
				goto up3;
			}
			break;
			case 2:
			break;
			case 3:
			break;
			case 4:
			goto startmenu;
			default:
			printf("wrong choice");
			goto up2;
		}
		break;
		case 3:
		print();
		//exit(0);
		default:
		printf("wrong choice");
		goto up;
	}
	//getch();
	return 0;
}
void foodmenu()
{

}
void create(char first[],char last[],int roomno,int day,int month,int year,int hour,int minute,int bill,char type[])
{
	struct list *p,*tmp;
    tmp=(struct list *)malloc(sizeof(struct list));
	strcpy(tmp->first,first);
	strcpy(tmp->last,last);
	tmp->roomno=roomno;
	tmp->d.day=day;
	tmp->d.month=month;
	tmp->d.year=year;
	tmp->d.hour=hour;
	tmp->d.minute=minute;
	tmp->bill=1000+bill;
	strcpy(tmp->type,type);
	tmp->next=NULL;
	if(start==NULL)
		start=tmp;
	else
	{
		p=start;
		while(p->next!=NULL)
			p=p->next;
		p->next=tmp;
	}
}
void detail(int room,int bill,char type[])
{
	printf("Enter following details:\n");
	printf("First name:");
	f1=fopen("customer.txt","a+");
	fflush(stdin);
	scanf("%s",&d1.first);
	printf("Last name:");
	fflush(stdin);
	scanf("%s",&d1.last);
	fprintf(f1,"%d\n",room);
	fprintf(f1,"%s %s\n",d1.first,d1.last);
	fflush(stdout);
	printf("Phone no.:");
	fflush(stdin);
	scanf("%s",&d1.phone);
	fprintf(f1,"%s\n",d1.phone);
	if(member==0)
	{
	    printf("Date(dd-mm-yyyy):");
		fflush(stdin);
	    scanf("%d-%d-%d",&d1.d.day,&d1.d.month,&d1.d.year);
	    fprintf(f1,"%d-%d-%d\n",d1.d.day,d1.d.month,d1.d.year);
		fflush(stdout);
	    printf("Time:");
		fflush(stdin);
	    scanf("%d:%d",&d1.t.hour,&d1.t.minute);
		fflush(stdin);
	    fprintf(f1,"%d:%d\n",d1.t.hour,d1.t.minute);
		fflush(stdout);
	}
	printf("Id type:");
	fflush(stdin);
	scanf("%s",d1.idtype);
	fprintf(f1,"%s\n",d1.idtype);
	fflush(stdin);
	printf("Id number:");
	fflush(stdin);
	scanf("%s",d1.id);
	fflush(stdin);
	fprintf(f1,"%s\n\n",d1.id);
	if(member==0)
	{
		create(d1.first,d1.last,room,d1.d.day,d1.d.month,d1.d.year,d1.t.hour,d1.t.minute,bill,type);
	}
	printf("You have been alloted room number:%d",room);
	if(member==0)
	{
		if(strcmp(type,"single")==0)
		    scount++;
	    else if(strcmp(type,"double")==0)
		    dcount++;
	    else if(type=="deluxe")
	        decount++;
	}
	close(f1);
}
int compute(char type[])
{
	int i,f=0;
	struct list *a;
	if(strcmp(type,"single")==0)
	{	for(i=0;i<10;i++)
	    {
			a=start;
		    while(a!=NULL)
			{
				if(single[i]==a->roomno)
				{
					f=1;
					break;
				}
		    a=a->next;
			}
			if(f!=1)
				break;
			f=0;
	    }
		return single[i];
	}
	else if(strcmp(type,"double")==0)
	{
		for(i=0;i<10;i++)
	    {
			a=start;
		    while(a!=NULL)
			{
				if(doubl[i]==a->roomno)
				{
					f=1;
					break;
				}
		    a=a->next;
			}
			if(f!=1)
				break;
			f=0;
	    }
		return doubl[i];
	}
	else if(strcmp(type,"deluxe")==0)
	{
		for(i=0;i<10;i++)
	    {
			a=start;
		    while(a!=NULL)
			{
				if(deluxe[i]==a->roomno)
				{
					f=1;
					break;
				}
		    a=a->next;
			}
			if(f!=1)
				break;
			f=0;
	    }
		return deluxe[i];
	}
}
void print()
{
	struct list *a;
	a=start;
	l=fopen("list.txt","w");
	while(a!=NULL)
	{
		fprintf(l,"%d\n",a->roomno);
		fflush(stdout);
	    fprintf(l,"%s ",a->first);
		fflush(stdout);
		fprintf(l,"%s\n",a->last);
		fflush(stdout);
		fprintf(l,"%d-%d-%d\n",a->d->day,a->d->month,a->d->year);
		fflush(stdout);
		fprintf(l,"%d:%d\n",a->d->hour,a->d->minute);
		fflush(stdout);
		fprintf(l,"%d\n",a->bill);
		fprintf(l,"%s\n",a->type);
		a=a->next;
	}
	fclose(l);
}
void scan()
{
	struct details s;
	char strf[20];
	char strl[20];
	r=fopen("customer.txt","r");
	printf("enter name of customer");
	fflush(stdin);
	scanf("%s %s",strf,strl);
	fflush(stdin);
	while(1)
	{
		if(feof(r)==0)
		{
			fscanf(r,"%d\n",&s.roomno);
			fscanf(r,"%s %s",s.first,s.last);
			fscanf(r,"%s",s.phone);
		    fscanf(r,"%d-%d-%d\n",&s.d.day,&s.d.month,&s.d.year);
		    fscanf(r,"%d:%d\n",&s.t.hour,&s.t.minute);
			fscanf(r,"%s\n",s.idtype);
			fscanf(r,"%s\n",s.id);
			if(strcmp(strf,s.first)==0 && strcmp(strl,s.last)==0)
			{
				printf("Room no.:%d\n",s.roomno);
				printf("Name:%s %s\n",s.first,s.last);
				printf("Phone no.:%s\n",s.phone);
			    printf("Check in date:%d-%d-%d\n",s.d.day,s.d.month,s.d.year);
			    printf("Check in time:%d:%d\n",s.t.hour,s.t.minute);
				printf("Id type:%s\n",s.idtype);
				printf("Id no.:%s\n",s.id);
			}
		}
		else
		break;
	}

	close(r);
}
