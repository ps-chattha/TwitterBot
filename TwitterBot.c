//Paramjot Singh Chattha
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct Tweet_object
{
    int Id;
    char s[51];
    char txt[141];
    char User[21];

    struct Tweet_object *next;

}Tweet;


void createTweet(Tweet **head,char name[],int *iD)
{
    Tweet *new = (Tweet*)malloc(sizeof(Tweet));
    new->Id = *iD;
    *iD = *iD+1;
    new->next = NULL;
    strcpy(new->User,name);

    printf("\nYour thoughts for a new tweet: ");
    scanf("%[^\n]s",&(new->txt));

    time_t create;
    create=time(NULL);

    strcpy(new->s,strtok(asctime(gmtime(&create)),"\n"));
    if(*head == NULL)
    {
        *head = new;
    }
    else
    {
        new->next = *head;
        *head = new;
    }

}

void searchTweet(Tweet *head,char keyword[21])
{
    Tweet *c=head;
    int count=0;
    while(c!=NULL)
    {
        if(strstr(c->txt,keyword)!=NULL)
        {
            printf("Keyword found \n");
            printf("ID - %d \t\tCreated at - %s \t\tCreated by \"%s\"\n",c->Id,c->s,c->User,c->txt);
            count++;
        }
        c=c->next;
    }
    if(count==0)
        printf("Sorry, there is no such tweet as %s keyword",keyword);
    else
        printf("%dTweets are found with %s keyword",count,keyword);
}

void displayTweet(Tweet *head)
{
    while(head!=NULL)
    {
        printf("ID -  %d \t\tCreated at - %s \t\tCreated by - %s \t\tThoughts are : \"%s\"\n",head->Id,head->s,head->User,head->txt);
        head=head->next;
    }
}

void saveTweet(Tweet *head)
{
    FILE *tweet =NULL;
    char file[21];

    printf("\nEnter the name of file to save your tweets in :");
    scanf("%s",file);

    tweet=fopen(file,"w");

    while(head!=NULL)
    {
        fprintf(tweet,"%d\n%s\n%s\n%s\n",head->Id,head->s,head->User,head->txt);
		head=head->next;
    }
    fclose(tweet);

}

void loadTweet(Tweet *head)
{

    FILE * tweet=NULL;
	char file[21];

	printf("\nEnter the name of file to read tweets from : ");
	scanf("%s",file);

	tweet=fopen(file,"r");

	printf("Tweets are loaded.");
	while(head!=NULL)
	{
		fscanf(tweet,"%d\n%[^\n]s\n%[^\n]s\n%[^\n]s\n",&head->Id,&head->s,&head->User,&head->txt);
		printf("ID - %d \t\t Created at - %s \t\t Created by - %s \n Thoughts : %s \n",head->Id,head->s,head->User,head->txt);
		head=head->next;
	}
	fclose(tweet);
}

int main()
{
    char u_name[10] ;
    int input;
    Tweet *head = NULL;
    int id = 1;
    char keyword[21];

    printf("Enter the username: ");
    scanf("%s",u_name);

    printf("Welcome %s,Begin with your tweeting...", u_name);

    for(int i=0 ; ; i++)
    {

        printf("\nTo display tweets - press 1.\n");
        printf("To search tweets - press 2.\n");
        printf("To create tweets - press 3.\n");
        printf("To Load tweets from file - press 4.\n");
        printf("To save tweets to file - press 5.\n");
        printf("Enter 6 to logout \n");

        scanf(" %d",&input);
        getchar();


        switch(input)
         {
            case 1:
                displayTweet(head);
                break;

			case 2:
               printf("Enter the search keyword: ");
               scanf("%s", keyword);
               searchTweet(head,keyword);
               break;

			case 3:
                createTweet(&head,u_name,&id);
                break;

			case 4:
                loadTweet(head);
               break;

            case 5:
                saveTweet(head);
               break;

            case 6:
				printf("..........Logged out..........");
				break;

           default:
               printf("\nNo Such Function,enter a valid number \n");
               break;
       }
    if(input==6)
        break;

   }

}
