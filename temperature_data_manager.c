#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0
////  STRUCTURE   ////
typedef struct node
{
    float temperature;
    float averageTemp;
    char day[21];
    struct node *left, *right;
    int save;
    struct node *next;
}node;
////  DECLARATION OF FUNCTIONS   ////
void findTemp(node v[], char s[]);
void findTime(node metrisi[], char input[]);
struct node *newNode(float avtemp, char day[]);
void inorder(struct node *root, node n[]);
struct node *insert(struct node *node, float averageTemp, char day[]);
int search(node n[], char input[], char size);
struct node *minLeaf(struct node *n);
struct node *deleteNode(struct node *root, char day[]);
struct node *modify(struct node *root, char day[], float avtemp);
struct node *insert2(struct node *n, float averageTemp, char day[]);
void minTemp(struct node *root, node n[]);
void maxTemp(struct node *root, node n[]);
void hashFunc(node n[], char s[]);
void insertHash(struct node *c[], float avtemp, char day[], int save);
void printHash(struct node *c[]);
void searchHash(struct node *c[], char day[]);
struct node *modifyHash(struct node *c[], char day[], float avtemp);
struct node *deleteHash(struct node *c[], char day[]);
////  MAIN   ////
int main()
{
    ////   FILE VARIABLES   ////
    FILE *fp,*ft;
    char ch;
    char* path = "C:\\C\\project\\tempm.txt";
    char* path2 = "C:\\C\\project\\test.txt";
    ////   OTHER VARIABLES   ////
    int i, k, choice, menu, mainmenu;
    char str[1000000], answer;
    struct node *root = NULL;
    struct node *chain[116];
    ////   START OF PROGRAM   ////
    printf(" Start program ? (y/n) \n");
    scanf("%c", &answer);
    if(answer == 'y' || answer == 'Y')
    {
        fp = fopen(path, "r");  ////  OPEN STREAM FOR READ   ////
        if (fp == NULL) ////   FILE DOES NOT EXIST   ////
        {
            printf("Could not open file %s",path);
            return 1;
        }
        ft = fopen(path2, "w+");    ////  OPEN STREAM FOR READ AND WRITE   ////
        if (ft == NULL) ////   FILE DOES NOT EXIST   ////
        {
            printf("Could not open file %s",path2);
            return 1;
        }
        while ((ch = fgetc(fp)) != EOF) ////  READ OF FILE   ////
        {
            if(ch=='\n' || ch=='\r')    ////  CHANGING NEWLINE WITH SPACE   ////
                fputc(' ', ft);
            else if(ch == '"')  ////  CHANGING " WITH +   ////
                fputc('+', ft);
            else
                fputc(ch, ft);
        }
        fclose(ft);
    }
    else   exit(1);
    ////  CREATION OF ARRAY OF STRUCTURES   ////
    node metriseis[8222];
    ////   LOADING OF TIMESTAMPS FROM FILE   ////
    ft = fopen(path2, "r");
    fgets(str, 1000000, ft);
    fclose(ft);
    findTime(metriseis, str);
    ////   LOADING OF TEMPERATURES FROM FILE   ////
    ft = fopen(path2, "r");
    fgets(str, 1000000, ft);
    fclose(ft);
    findTemp(metriseis, str);
    ////  CALL OF HASHING FUNCTION   ////
    hashFunc(metriseis, str);
    ////   MENU   ////
    printf("\n\t\t  MAIN MENU\n-------------------------------------------\n1. Load file to BST\n2. Load file to structure: Hashing with chains\n-------------------------------------------\nChoose an option:\n");
    scanf("%d", &mainmenu);
    switch(mainmenu)
    {
        case 1: ////   LOADING FILE TO BST   ////
        {
            printf("\n\t\t  MENU\n-----------------------------------------\n1. Full menu sorted by day\n2. Full menu sorted by average temperature\n-----------------------------------------\nChoose an option:\n");
            scanf("%d", &menu);
            switch(menu)
            {
                case 1: ////   FULL MENU SORTED BY DAY   ////
                {
                    for(i=0; i<116; i++)    ////  SORTING   ////
                    {
                        root = insert(root, metriseis[i].averageTemp, metriseis[i].day);
                    }
                    printf("\nThe BST is sorted by day!\n");
                    while(1)
                    {
                        printf("\n\t\t  MENU\n----------------------------------------\n1-View BST\n2-Search for average temperature\n3-Change average temperature of a record\n4-Delete a record\n5-Exit\n----------------------------------------\nOption:\n");
                        scanf("%d",&choice);
                        switch(choice)
                        {
                            case 1: ////   VIEW BST   ////
                            {
                                printf("\nThe average temperatures are:\n");
                                inorder(root, metriseis);
                                break;
                            }
                            case 2: ////   SEARCH FOR AVERAGE TEMPERATURE   ////
                            {
                                int x;
                                char input[10];
                                printf("\nEnter the day to search:\n");
                                scanf("%s", input);
                                x = search(metriseis, input, 116);
                                printf("The average temperature of day %s is: %1.3f \n", metriseis[x].day, metriseis[x].averageTemp);
                                break;
                            }
                            case 3: ////   CHANGE AVERAGE TEMPERATURE OF A RECORD   ////
                            {
                                char m[10];
                                float t=0;
                                printf("Enter the day for modification:\n");
                                scanf("%s", m);
                                printf("Enter the new average Temperature:\n");
                                scanf("%f", &t);
                                modify(root, m, t);
                                printf("\nThe average temperature updated successfully!\n");
                                break;
                            }
                            case 4: ////   DELETE A RECORD   ////
                            {
                                char mera[10];
                                printf("Give a day to delete:\n");
                                scanf("%s", mera);
                                root = deleteNode(root, mera);
                                printf("\nThe day deleted successfully!\n");
                                break;
                            }
                            case 5: ////   EXIT   ////
                            {
                                fclose(fp);
                                printf("\nEnd of program \n");
                                exit(1);
                            }
                            default:    ////   EXCEPTION   ////
                            {
                                printf("---Warning!---\nInvalid Input!\n");
                                printf("\nEnd of program \n");
                            }
                            exit(1);
                        }
                    }
                }
                case 2: ////   FULL MENU SORTED BY AVERAGE TEMPERATURE   ////
                {
                    for(k=0; k<116; k++)    ////  SORTING   ////
                    {
                        root = insert2(root, metriseis[k].averageTemp, metriseis[k].day);
                    }
                    printf("\nThe BST is sorted by temperature!\n");
                    while(1)
                    {
                        printf("\n\t\t\t  MENU\n----------------------------------------------------------\n1-Display the day/days with the minimum temperature of BST\n2-Display the day/days with the maximum temperature of BST\n3-Exit\n----------------------------------------------------------\nOption:\n");
                        scanf("%d",&choice);
                        switch(choice)
                        {
                            case 1: ////   DISPLAY THE DAY/DAYS WITH THE MINIMUM TEMPERATURE OF BST   ////
                            {
                                minTemp(root, metriseis);
                                break;
                            }
                            case 2: ////   DISPLAY THE DAY/DAYS WITH THE MAXIMUM TEMPERATURE OF BST   ////
                            {
                                maxTemp(root, metriseis);
                                break;
                            }
                            case 3: ////   EXIT   ////
                            {
                                printf("\nEnd of program \n");
                                exit(1);
                            }
                            default:   ////   EXCEPTION   ////
                            {
                                printf("---Warning!---\nInvalid Input!\n");
                                printf("\nEnd of program \n");
                            }
                            exit(1);
                        }
                    }
                }
                default:
                {
                    printf("---Warning!---\nInvalid Input!\n");
                    printf("\nEnd of program \n");
                }
                exit(1);
            }
        }
        case 2: ////   LOADING FILE TO STRACTURE (HASHING WITH CHAINS)   ////
        {
            for(i=0; i<116; i++)    ////  SORTING   ////
            {
                insertHash(chain, metriseis[i].averageTemp, metriseis[i].day, metriseis[i].save);
            }
            while(1)
            {
                printf("\n\t\t  MENU\n----------------------------------------\n1-Search for average temperature\n2-Change average temperature of a record\n3-Delete a record\n4-View the chains of Hashing\n5-Exit\n----------------------------------------\nOption:\n");
                scanf("%d",&choice);
                switch(choice)
                {
                    case 1: ////   SEARCH FOR AVERAGE TEMPERATURE   ////
                    {
                        char d[10];
                        printf("\nEnter the day for search:\n");
                        scanf("%s", d);
                        searchHash(chain, d);
                        break;
                    }
                    case 2: ////   CHANGE AVERAGE TEMPERATURE OF A RECORD   ////
                    {
                        char n[10];
                        float t=0;
                        printf("\nEnter the day for modification:\n");
                        scanf("%s", n);
                        printf("Enter the new average Temperature:\n");
                        scanf("%f", &t);
                        modifyHash(chain, n, t);
                        printf("\nThe average temperature updated successfully!\n");
                        break;
                    }
                    case 3: ////   DELETE A RECORD   ////
                    {
                        char mera[10];
                        printf("Give a day to delete:\n");
                        scanf("%s", mera);
                        deleteHash(chain, mera);
                        printf("\nThe day deleted successfully!\n");
                        break;
                    }
                    case 4: ////   VIEW THE CHAIND OF HASHING   ////
                    {
                        printHash(chain);
                        break;
                    }
                    case 5: ////   EXIT   ////
                    {
                        fclose(fp);
                        printf("\nEnd of program \n");
                        exit(1);
                    }
                    default:    ////   EXCEPTION   ////
                    {
                        printf("---Warning!---\nInvalid Input!\n");
                        printf("\nEnd of program \n");
                    }
                    exit(1);
                }
            }
        }
        default:    ////   EXCEPTION   ////
        {
            printf("---Warning!---\nInvalid Input!\n");
            printf("\nEnd of program \n");
        }
        exit(1);
    }
    return 0;
}
////   FUNCTION FOR CREATION OF NEW NODE (BST)   ////
struct node *newNode(float avtemp, char day[])
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));    ////   DYNAMIC MEMORY MANAGEMENT   ////
    temp->averageTemp = avtemp;     ////   INITIALIZATION   ////
    strcpy(temp->day,day);
    temp->left = temp->right = NULL;
    return temp;
}
////   FUNCTION FOR DISPLAY THE BST IN ORDER   ////
void inorder(struct node *root, node n[])
{
        if (root != NULL)
        {
            inorder(root->left, n);
            printf("Day: %s , Average Temperature: %1.3f \n", root->day, root->averageTemp);
            inorder(root->right, n);
        }
}
////   FUNCTION FOR INSERTION OF NEW NODE (BST) (SORTED BY DAY)   ////
struct node *insert(struct node *n, float averageTemp, char day[])
{
    ////   EMPTY TREE   ////
    if (n == NULL) return newNode(averageTemp, day);
    ////   RECURRING DOWN   ////
    if (strcmp(day, n->day ) < 0)
        n->left  = insert(n->left, averageTemp, day);
    else if (strcmp(day, n->day ) > 0)
        n->right = insert(n->right, averageTemp, day);
    return n;
}
////   FUNCTION FOR FINDING THE MOST LEFT(MINIMUM) LEAF ON A NODE (USAGE: DELETING A NODE)  ////
struct node *minLeaf(struct node *n)
{
    struct node* temp = n;
    ////   LOOP DOWN   ////
    while (temp && temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}
////   FUNCTION FOR DELETING A NODE (BST)   ////
struct node *deleteNode(struct node *root, char day[])
{
    ////   EMPTY TREE   ////
    if (root == NULL) return root;
    ////   GO TO THE LEFT SUBTREE FOR DELETE   ////
    if (strcmp(day, root->day) < 0)
    {
        root->left = deleteNode(root->left, day);
    }
    ////   GO TO THE RIGHT SUBTREE FOR DELETE   ////
    else if (strcmp(day, root->day) > 0)
    {
        root->right = deleteNode(root->right, day);
    }
    ////   ROOT TO BE DELETED   ////
    else
    {
        ////   NODE WITH ONLY ONE CHILD OR NO CHILD   ////
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        ////   NODE WITH TWO OR MORE CHILDREN   ////
        struct node* temp = minLeaf(root->right);
        ////   COPY THE CONTENT OF THE IN ORDER SUCCESSOR TO THE NODE AND DELETE THE IN ORDER SUCCESSOR   ////
        strcpy(root->day, temp->day);
        root->right = deleteNode(root->right, temp->day);
    }
    return root;
}
////   FUNCTION FOR CHANGING THE AVERAGE TEMPERATURE OF A DAY (BST)   ////
struct node *modify(struct node *root, char day[], float avtemp)
{
    if(strcmp(root->day, day) == 0) ////   SEARCH   ////
    {
        root->averageTemp = avtemp;
        return root;
    }
    modify(root->right, day, avtemp);
    return root;
}
////   FUNCTION FOR INSERTION OF NEW NODE (BST) (SORTED BY AVERAGE TEMPERATURE)   ////
struct node *insert2(struct node *n, float averageTemp, char day[])
{
    ////   EMPTY TREE   ////
    if (n == NULL) return newNode(averageTemp, day);
    ////   RECURRING DOWN   ////
    if (averageTemp < n->averageTemp)
        n->left  = insert2(n->left, averageTemp, day);
    else if (averageTemp > n->averageTemp)
        n->right = insert2(n->right, averageTemp, day);
    return n;
}
////   FUNCTION FOR FINDING MINIMUM TEMPERATURE OF BST   ////
void minTemp(struct node *root, node n[])
{
    float min = root->averageTemp;
    int i;
    char mday[11];
    for(i=0; i<116; i++)
    {
        if(min > n[i].averageTemp)
        {
            min = n[i].averageTemp;
            strcpy(mday, n[i].day);
        }
    }
    printf("\nDay: %s, temperature = %1.3f\n", mday, min);
}
////   FUNCTION FOR FINDING MAXIMUM TEMPERATURE OF BST   ////
void maxTemp(struct node *root, node n[])
{
    float max = root->averageTemp;
    int i;
    char mday[11];
    for(i=0; i<116; i++)
    {
        if(max < n[i].averageTemp)
        {
            max = n[i].averageTemp;
            strcpy(mday, n[i].day);
        }
    }
    printf("\nDay: %s, temperature = %1.3f\n", mday, max);
}
////   FUNCTION FOR LOADING OF TIMESTAMPS FROM FILE   ////
void findTime(node metrisi[], char input[])
{
    int k=0, j=0, p=0;
    while (input[p])    ////   READ WHOLE FILE   ////
    {
        if(input[p] == '{') ////   SEPARATE THE DAYS   ////
        {
            p+=2;
            while(input[p] != 'T')  ////   READ ONLY YY/MM/DD   ////
            {
                metrisi[j].day[k] = input[p];
                k++;
                p++;
            }
            k=0;
            j++;
            p++;
        }
        p++;
    }
}
////   FUNCTION FOR LOADING OF TEMPERATURES FROM FILE   ////
void findTemp(node v[], char s[])
{
    int i, j=0, p=1, count=0, k=0, startofday = 0, end_of_day = 0;
    bool issingle = false;
    char *ptr = s;
    float val = 0;
    double divby = 0;
    while (s[p])    ////   READ WHOLE FILE   ////
    {
        if(s[p] == '}') ////   CALCULATE AVERAGE TEMPERATURE AND CHANGE DAY   ////
        {
            for(i=startofday; i<end_of_day; i++)
            {
                v[k].averageTemp = v[k].averageTemp + v[i].temperature;
            }
            divby = end_of_day-startofday;
            v[k].averageTemp = (v[k].averageTemp / divby);
            k++;
            startofday = end_of_day;
        }
        if(s[p] == '+') ////   COUNT THE CROSSES   ////
        {
            count++;
        }
        if(count == 3)
        {
            p++;
            while(s[p] != '+')  ////   READ TEMPERATURE   ////
            {

                if(issingle == true && s[p] == '-')   ////   NEGATIVE TEMPERATURE AND PREVIOUS TEMPERATURE IS SINGLE DIGIT   ////
                {
                    ptr++;
                    p++;
                    val = strtol(ptr, &ptr, 10);
                    v[j].temperature = val;
                    j++;
                    issingle = false;
                    end_of_day++;
                    break;
                }
                if(s[p] == '-') ////   NEGATIVE TEMPERATURE AND DOUBLE DIGIT  ////
                {
                    ptr++;
                    p++;
                    val = strtol(ptr, &ptr, 10);
                    val = val * (-1);
                    v[j].temperature = val;
                    j++;
                    end_of_day++;
                    break;
                }
                else if(isdigit(s[p]))  ////   POSITIVE TEMPERATURE SINGLE OR DOUBLE DIGIT ////
                {
                    val = strtol(ptr, &ptr, 10);
                    v[j].temperature = val;
                    ptr--;
                    j++;
                    end_of_day++;
                    if(val<10)
                        issingle = true;
                    else
                        issingle = false;
                    break;
                }
                ptr++;
                p++;
            }
            count=-1;
        }
        p++;
        ptr++;
    }
}
////   FUNCTION FOR SEARCHING DAY (FROM FILE)   ////
int search(node n[], char input[], char size)
{
    int i;
    for(i=0; i<size; i++)
    {
        if(strcmp(n[i].day, input) == 0)    return i;
    }
    return 0;
}
////   HASHING FUNCTION   ////
void hashFunc(node n[], char s[])
{
    int j=0, p=0, sum=0;
    while (s[p])
    {
        if(s[p] == '{')
        {
            p+=2;
            while(s[p] != 'T')
            {
                sum = sum + (int)s[p];  ////   SUM OF ASCII NUMBERS   ////
                p++;
            }
            n[j].save = sum % 11;   ////   SUM MODULO M=11   ////
            sum = 0;
            j++;
            p++;
        }
        p++;
    }
}
////   FUNCTION FOR CREATION OF NEW RECORD (HASHING)   ////
struct node *newNodeHash(float avtemp, char day[], int save)
{
	struct node *newnode;
	newnode = (struct node *) malloc(sizeof(struct node));  ////   DYNAMIC MEMORY MANAGEMENT   ////
	newnode->averageTemp = avtemp;  ////   INITIALIZATION   ////
	newnode->save = save;
	strcpy(newnode->day, day);
	newnode->next = NULL;
	return newnode;
}
////   FUNCTION FOR INSERTION OF NEW RECORD (HASHING)   ////
void insertHash(struct node *c[], float avtemp, char day[], int save)
{
	struct node *newnode = newNodeHash(avtemp, day, save);
	if (c[save] == NULL)    ////   EMPTY HASH   ////
	{
		c[save] = newnode;
	}
    else
    {
        struct node *temp = c[save];
        while(temp->next)
        {
            temp = temp->next;  ////   NEXT RECORD OF CHAIN   ////
        }
        temp->next = newnode;
    }
}
////   FUNCTION FOR DISPLAY THE RECORDS (HASHING)   ////
void printHash(struct node *c[])
{
    int i;
    for(i=0; i<11; i++) ////   11 CHAINS   ////
    {
        struct node *temp = c[i];
        printf("chain[%d]-->", i);
        while(temp) ////   RUN FOR ALL RECORDS IN THE CHAIN   ////
        {
            printf(" Day:%s,Average Temperature:%1.3f -->", temp->day, temp->averageTemp);
            temp = temp->next;  ////   NEXT RECORD OF CHAIN   ////
        }
        printf("NULL\n");
    }
}
////   FUNCTION FOR SEARCHING THE AVERAGE TEMPERATURE OF A DAY (HASHING)  ////
void searchHash(struct node *c[], char day[])
{
    int i;
    for(i=0; i<11; i++) ////   11 CHAINS   ////
    {
        struct node *temp = c[i];
        while(temp) ////   RUN FOR ALL RECORDS IN THE CHAIN   ////
        {
            if(strcmp(temp->day, day) == 0) ////   SEARCH   ////
            {
                    printf("The average temperature of day: %s is %1.3f\n", day, temp->averageTemp);
            }
            temp = temp->next;  ////   NEXT RECORD OF CHAIN   ////
        }
    }
}
////   FUNCTION FOR CHANGING THE AVERAGE TEMPERATURE OF A DAY (HASHING)   ////
struct node *modifyHash(struct node *c[], char day[], float avtemp)
{
    int i;
    for(i=0; i<11; i++) ////   11 CHAINS   ////
    {
        struct node *temp = c[i];
        while(temp) ////   RUN FOR ALL RECORDS IN THE CHAIN   ////
        {
            if(strcmp(temp->day, day) == 0) ////   SEARCH   ////
            {
                temp->averageTemp = avtemp;
                return c[i];
            }
            temp = temp->next;  ////   NEXT RECORD OF CHAIN   ////
        }
    }
    return 0;
}
////   FUNCTION FOR DELETING A RECORD (HASHING)   ////
struct node *deleteHash(struct node *c[], char day[])
{
    int i;
    for(i=0; i<11; i++) ////   11 CHAINS   ////
    {
        struct node *temp = c[i], *del;
        while(temp) ////   RUN FOR ALL RECORDS IN THE CHAIN   ////
        {
            if(strcmp(temp->day, day) == 0)
            {
                if(strcmp(temp->day, day) == 0) ////   DELETE OF THE RECORD   ////
                {
                    del = temp;
                    temp = temp->next;
                    free(del);
                    return c[i];
                }
                while(temp->next)   ////   MORE THAN ONE RECORDS IN THE CHAIN   ////
                {
                    del = temp->next;
                    temp->next = temp->next->next;
                    free(del);
                }
                return c[i];
            }
            temp = temp->next;  ////   NEXT RECORD OF CHAIN   ////
        }
    }
    return 0;
}   ////   END OF PROGRAM   ////
