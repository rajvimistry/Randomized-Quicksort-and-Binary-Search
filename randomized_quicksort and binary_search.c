#include<stdio.h>
#include<string.h>
#include <stdbool.h>

int lines = 0;
struct directory{
		char first_name[20];
		char last_name[20];
		char number[15];
	}contacts[1];

int main(int argc, char *argv[])
{
	char filename[200];
    	FILE * userfile;
    	//printf("Please Enter The Name Of The File\n");
   	//scanf("%s", &filename);
	filename[0] = argv[1];
    	userfile = fopen(argv[1], "r");
    	if (userfile)
    	{
      		/*Work on file here*/
		fclose(userfile);
		create(argv[1]);
		int choice = 0;
		char name[30], ch;
		char phone_number[30];
		while(choice != 5)
		{
			printf("\n(1)Sort\n(2)Search\n(3)Delete\n(4)Insert\n(5)Exit\nEnter your choice:\n");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1: sort_contact();
					break;
				case 2: printf("Enter the Name: ");
					fgets(name,30,stdin);
					fgets(name,30,stdin);
					search(&name);
					break;
				case 3: printf("Enter the Name and Phone Number: ");
					fgets(name,200,stdin);
					fgets(name,200,stdin);
					char *b1,name2[30],number2[20];
					b1 = strtok(name,",");
					strcpy(name2,b1);
					b1 = strtok(NULL," ,");
					strcpy(number2,b1);
					delete(&name2,&number2);
					break;
				case 4: printf("Enter the Name and Phone Number: ");
					fgets(name,200,stdin);
					fgets(name,200,stdin);
					char *b,name1[30],number1[20];
					b = strtok(name,",");
					strcpy(name1,b);
					b = strtok(NULL," ,");
					strcpy(number1,b);
					insert(&name1,&number1);
					break;
				case 5: //exit(1);
					break;
			}
		}
    	}
	else
	{
		printf("Unable to open a file\n");
	}

	return 0;
}

//code to create a file

void create(char file[200])
{
	FILE * userfile;
	size_t len = 0;
	ssize_t read;
	char line[128];
	int ch=0;
	//int lines = 0;
	userfile = fopen(file,"r");
	
  	while ((ch = fgetc(userfile)) != EOF)
    	{
      		if (ch == '\n')
    		lines++;
    	}
	fclose(userfile);
	contacts[lines];
	
	//printf("\ntotal number of lines are:%d\n",lines);
	
	
	int i;
	for(i=0;i<lines;i++)
	{
		strcpy(contacts[i].first_name,"NULL");
		strcpy(contacts[i].last_name,"NULL");
		strcpy(contacts[i].number,"");
	}
	
	userfile = fopen(file,"r");
	while ( fgets ( line, sizeof line, userfile ) != NULL ) /* read a line */
	{
		//char str[] = line;
		char *pch;
		pch = strtok(line," ,");
		//while(pch != NULL)
		{
			int j;
			for(j=0;j<lines;j++)
			{	//copy the content of file into data structure
				if(strcmp(contacts[j].first_name,"NULL") == 0)
				{
					strcpy(contacts[j].first_name,pch);
					pch = strtok(NULL," ,");
					strcpy(contacts[j].last_name,pch);
					pch = strtok(NULL," ,");
					strcpy(contacts[j].number,pch);
					break;
				}
			}
			//printf("%s\n",pch);
			//pch = strtok(NULL," ,");
			
		}
	 	 //puts (line); /* write the line */		
      	}
	
        printf("Directory Created !!!");
	fclose(userfile);
}

//Sort Function
void sort_contact()
{
	int i;	
	quicksort(0,lines-1);
	//After sorting to display the result
	for(i=0;i<lines;i++)
	{
		printf("\n%s %s %s",contacts[i].first_name,contacts[i].last_name,contacts[i].number);
	}
}


void quicksort(int p,int q)
{
	
	int j;
	if(p<q)
	{
		j = partition(p,q);
		quicksort(p,j-1);
		quicksort(j+1,q);
	}
}

int partition(int a, int b)
{
	int pivotindex;
	srand(time(NULL));
	pivotindex = a+rand()%(b-a+1);
	int i = a-1;
	int j;
	char pivot_lastname[20];
	char pivot_firstname[20];
	char pivot_number[15];
	strcpy(pivot_lastname,contacts[pivotindex].last_name);
	strcpy(pivot_firstname,contacts[pivotindex].first_name);
	strcpy(pivot_number,contacts[pivotindex].number);

	//swap pivot with last element
	char temp_firstname[20];
	char temp_lastname[20];
	char temp_number[15];
	strcpy(temp_lastname,pivot_lastname);
	strcpy(temp_firstname,pivot_firstname);
	strcpy(temp_number,pivot_number);

	strcpy(contacts[pivotindex].last_name,contacts[b].last_name);
	strcpy(contacts[pivotindex].first_name,contacts[b].first_name);
	strcpy(contacts[pivotindex].number,contacts[b].number);

	strcpy(contacts[b].last_name,temp_lastname);
	strcpy(contacts[b].first_name,temp_firstname);
	strcpy(contacts[b].number,temp_number);


	//compare each element with pivot	
	for(j=a;j<b;j++)
	{	bool same_lname = true;
		bool same_fname = true;

         	if (strcmp(contacts[j].first_name,pivot_firstname) < 0) {
			i++;
			char temp_f_name[20];
			char temp_l_name[20];
			char temp_num[20];
        		strcpy(temp_l_name, contacts[j].last_name);
			strcpy(temp_f_name, contacts[j].first_name);
			strcpy(temp_num,contacts[j].number);
        		strcpy(contacts[j].last_name, contacts[i].last_name);
			strcpy(contacts[j].first_name,contacts[i].first_name);
			strcpy(contacts[j].number,contacts[i].number);
      			strcpy(contacts[i].last_name, temp_l_name);
			strcpy(contacts[i].first_name, temp_f_name);
			strcpy(contacts[i].number, temp_num);
			same_lname = false;
       		}
		if(same_lname == true && (strcmp(contacts[j].first_name,pivot_firstname) == 0))
		{//printf("inside same lname");printf("%d",(strcmp(contacts[j].first_name,pivot_firstname)));printf("i: %d",i);
			if(strcmp(contacts[j].last_name,pivot_lastname) < 0){
				i++;
				char temp_f_name[20];
				char temp_l_name[20];
				char temp_num[20];
        			strcpy(temp_l_name, contacts[j].last_name);
				strcpy(temp_f_name, contacts[j].first_name);
				strcpy(temp_num,contacts[j].number);
	        		strcpy(contacts[j].last_name, contacts[i].last_name);
				strcpy(contacts[j].first_name,contacts[i].first_name);
				strcpy(contacts[j].number,contacts[i].number);
	        		strcpy(contacts[i].last_name, temp_l_name);
				strcpy(contacts[i].first_name, temp_f_name);
				strcpy(contacts[i].number, temp_num);
				same_fname = false;
			}
			else if(same_fname == true && (strcmp(contacts[j].last_name,pivot_lastname) == 0))
			{
				if(strcmp(contacts[j].number,pivot_number) < 0){
					i++;
					char temp_f_name[20];
					char temp_l_name[20];
					char temp_num[20];
        				strcpy(temp_l_name, contacts[j].last_name);
					strcpy(temp_f_name, contacts[j].first_name);
					strcpy(temp_num,contacts[j].number);
	        			strcpy(contacts[j].last_name, contacts[i].last_name);
					strcpy(contacts[j].first_name,contacts[i].first_name);
					strcpy(contacts[j].number,contacts[i].number);
	        			strcpy(contacts[i].last_name, temp_l_name);
					strcpy(contacts[i].first_name, temp_f_name);
					strcpy(contacts[i].number, temp_num);
				}
			}
		}
      	}

	char temp1_lname[20];
	char temp1_fname[20];
	char temp1_number[20];

	strcpy(temp1_lname,contacts[i+1].last_name);
	strcpy(temp1_fname,contacts[i+1].first_name);
	strcpy(temp1_number,contacts[i+1].number);
	strcpy(contacts[i+1].last_name,contacts[b].last_name);
	strcpy(contacts[i+1].first_name,contacts[b].first_name);
	strcpy(contacts[i+1].number,contacts[b].number);
	strcpy(contacts[b].last_name,temp1_lname);
	strcpy(contacts[b].first_name,temp1_fname);
	strcpy(contacts[b].number,temp1_number);
	return i+1;	
}


//Search Function
void search(char *name[30])
{
	
	char *b;
	b = strtok(name," ");
	char first_name[20];
	char last_name[20];
	strcpy(first_name,b);
	b = strtok(NULL," ");
	strcpy(last_name,b);
	int first = 0;
	int last = lines;
	int middle = (first+last)/2;
	bool isFound = false;
	while(first <= last)
	{	//if entered name is after middle element
		if(strcmp(contacts[middle].first_name,first_name) < 0 && strcmp(contacts[middle].first_name,first_name)!= -10)
		{
			first = middle + 1;
			
		}//if entered element is equal to middle element
		else if(strcmp(contacts[middle].first_name,first_name) == 0)
		{
			while((strcmp(contacts[middle].first_name,first_name)+0)==0)
			{	//if element found, print the result
				if((strcmp(contacts[middle].last_name,last_name))== -10)
				{
				isFound=true;
				
				int j = 0;
				while(j<middle)
				{	
					if( (strcmp(contacts[j].first_name,contacts[middle].first_name) == 0 )
						&& (strcmp(contacts[j].last_name,contacts[middle].last_name)== 0))
					{printf("\n%s %s %s",contacts[j].first_name,contacts[j].last_name,contacts[j].number);}
					j++;
				}j++;
				printf("\n%s %s %s",contacts[middle].first_name,contacts[middle].last_name,contacts[middle].number);
				
				while(j<lines)
				{
					if( (strcmp(contacts[j].first_name,contacts[middle].first_name) == 0 )
						&& (strcmp(contacts[j].last_name,contacts[middle].last_name)== 0))
					{printf("\n%s %s %s",contacts[j].first_name,contacts[j].last_name,contacts[j].number);}
					j++;
				}

				first = lines+5000;
				break;}
				else if((strcmp(contacts[middle].last_name,last_name)) > 0){middle--;}
				else
				{middle++;}first++;
			}
		}//if entered number is before pivot element
		else
		{
			last = middle-1;
		}
		//set the middle
		middle = (first+last)/2;
	}

	if(first != lines+5000 && first>last && isFound == false)
	printf("\nName Not Found.");

}


//Delete Function
void delete(char *name[30],char *number1[30])
{
	char *b;
	b = strtok(name," ");
	char first_name[20];
	char last_name[20];
	char number[20];
	strcpy(first_name,b);
	b = strtok(NULL," ");
	strcpy(last_name,b);
	int i;
	bool isFound = false;
	//search the element
	for(i=0;i<lines;i++)
	{
		if((strcmp(contacts[i].first_name,first_name)==0) && (strcmp(contacts[i].last_name,last_name)== 0) && (strcmp(contacts[i].number,number1)==0))
		{
			isFound = true;
			char temp_fname[20],temp_lname[20],temp_number[20];
			
			//swap the user entered name with last element
			strcpy(temp_fname,contacts[i].first_name);
			strcpy(temp_lname,contacts[i].last_name);
			strcpy(temp_number,contacts[i].number);

			strcpy(contacts[i].first_name,contacts[lines-1].first_name);
			strcpy(contacts[i].last_name,contacts[lines-1].last_name);
			strcpy(contacts[i].number,contacts[lines-1].number);

			strcpy(contacts[lines-1].first_name,temp_fname);
			strcpy(contacts[lines-1].last_name,temp_lname);
			strcpy(contacts[lines-1].number,temp_number);
			
			//decrement the index and sort
			lines--;
			sort_contact();
			i = lines + 5;
				
		}
	}
		
	if(isFound == false)
	{printf("Name Not Found.");}
}


//Insert Function
void insert(char *name[30],char *number[30])
{	//break the input string
	char *b;
	b = strtok(name," ");
	char first_name[30];
	char last_name[30];
	strcpy(first_name,b);
	b = strtok(NULL," ");
	strcpy(last_name,b);
	//increment the index and add data to structure and sort
	lines++;
	strcpy(contacts[lines-1].first_name,first_name);
	strcpy(contacts[lines-1].last_name,last_name);
	strcpy(contacts[lines-1].number,number);
	sort_contact();
}

/*void print(char fname[30],char lname[30],char number[30])
{
	int i;
	for(i=0;i<lines;i++)
	{
		if((strcmp(contacts[i].last_name,lname)== -10) && (strcmp(contacts[i].first_name,fname)==0) && (strcmp(contacts[i].number,number) == 0))
		printf("%s %s %s",contacts[i].first_name,contacts[i].last_name,contacts[i].number);
	}
}*/
