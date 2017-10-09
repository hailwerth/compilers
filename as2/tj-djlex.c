/*  I pledge my Honor that I have not cheated, and will not cheat, on this assignment  */
/*  Tanmay J. Kotha  */
/*  EXTRA CREDIT: LEXER for DJ written by hand in C */
#include <stdio.h>
#include <stdlib.h>
//note: these should only be used inside of the while loop!
#define GETCHAR(c) c = getc(fptr);
#define CARRYON(c) c = getc(fptr);continue;

//helper functions
int stringcompare(char* c1, char* c2)
{
    int i=0,flag = 0;
    while(c1[i]!='\0' && c2[i]!='\0')
    {
        if(c1[i]!=c2[i]){
            flag=1;     
        } 
        ++i;
    }
    if(flag == 0 && c1[i]=='\0' && c2[i]=='\0')
        return 1;
    else {
        return 0;
    }
}

void printError(int linenumber, char c)
{
    printf("\nLex error on line %d: Illegal Character: %c\n", linenumber,c);
    exit(-1);
}

//linked list structure for identifier/number matching
typedef struct linkedlist{
    char c;
    struct linkedlist* nextNode;
} linkedlist;

char* makestring(linkedlist* list, int size)
{
    char* str = malloc(sizeof(char)*size);
    linkedlist* current = list;
    int i = 0;
    while(i < size)
    {
        str[i] = current->c;
        current= current->nextNode;
        i++;
    }
    return str;
}


int main(int argc, char** argv)
{
    char c = 0;
    int linenumber = 1;

    FILE *fptr;
    fptr = fopen(argv[1],"r");
    if(fptr == NULL)
    {
        printf("Cannot open file, please make sure you have the correct path relative to the executable\n");
        exit(0);
    }

    GETCHAR(c);
    while(c!=EOF){
        //printf("%c",c);
        //get rid of comments
        if(c == '/'){
            GETCHAR(c);
            
            if(c=='/'){
                while(c!='\n') GETCHAR(c);
            }
            else if(c=='*'){
                int flag = 0;
                while(!flag)
                {
                    while(c!='*') GETCHAR(c);
                    //at this point, we have found a character '*', so check next character again
                    GETCHAR(c);
                    if(c=='/'){flag = 1;}        
                }
                
                
            }
            else if(c!='/') continue;
        }

        //use the switch case to handle token cases
        switch(c)
        {
            case '&':
            {
                GETCHAR(c);
                if(c != '&'){
                    //this is a lex error, as there is no single & operator
                    printError(linenumber,c);   
                }
                else{
                    printf("AND "); CARRYON(c);
                }
            }
            case ',':
            {
                printf("COMMA "); CARRYON(c);
            }
            case '.':
            {
                printf("DOT "); CARRYON(c);
            }
            case '(':
            {
                printf("LPAREN "); CARRYON(c);
            }
            case ')':
            {
                printf("RPAREN "); CARRYON(c);
            }
            case '{':
            {
                printf("LBRACE "); CARRYON(c);
            }
            case '}':
            {
                printf("RBRACE "); CARRYON(c);
            }
            case ';':
            {
                printf("SEMICOLON "); CARRYON(c);
            }
            case '+':
            {
                printf("PLUS "); CARRYON(c);
            }
            case '-':
            {
                printf("MINUS "); CARRYON(c);
            }
            case '!':
            {
                printf("NOT "); CARRYON(c);   
            }
            case '*':
            {
                printf("TIMES "); CARRYON(c);
            }
            case '=':
            {
                GETCHAR(c);
                if(c!='='){
                    printf("ASSIGN "); continue;
                }
                else{
                    printf("EQUALITY ");CARRYON(c);
                }
                
            }
            case '<':
            {
                printf("LESS "); CARRYON(c);
            }
            default:
                break;
        }


        //if we detect an alphabet symbol first
        if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
        {
            int stringsize =1 ;
            linkedlist* idlist = malloc(sizeof(struct linkedlist));
            idlist->c = c;

            linkedlist* current = idlist;
            //build a character linked list
            while((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0' && c<='9')||c=='_')
            {
                GETCHAR(c);
                current->nextNode = malloc(sizeof(struct linkedlist));
                current = current->nextNode;
                current->c = c;
                stringsize++;
            }
            //dont accidently null terminate our 1 value
            if(stringsize !=1)
                current->c = '\0';

            //before doing extra processing, convert the linked list to a string
            char* alphastring = makestring(idlist,stringsize);


            //scan for all keywords
            if(stringcompare(alphastring,"main"))
            {
                printf("MAIN ");
            }
            else if(stringcompare(alphastring,"class"))
            {
                printf("CLASS ");
            }
            else if(stringcompare(alphastring,"extends"))
            {
                printf("EXTENDS "); 
            }
            else if(stringcompare(alphastring,"if"))
            {
                printf("IF ");      
            }
            else if(stringcompare(alphastring,"else"))
            {
                printf("ELSE ");    
            }
            else if(stringcompare(alphastring,"new"))
            {
                printf("NEW ");     
            }
            else if(stringcompare(alphastring,"null"))
            {
                printf("NUL ");     
            }
            else if(stringcompare(alphastring,"while"))
            {
                printf("WHILE ");   
            }
            else if(stringcompare(alphastring,"printNat"))
            {
                printf("PRINTNAT ");    
            }
            else if(stringcompare(alphastring,"readNat"))
            {
                printf("READNAT ");     
            }
            else if(stringcompare(alphastring,"nat"))
            {
                printf("NATTYPE ");     
            }
            else if(stringcompare(alphastring,"this"))
            {
                printf("THIS ");     
            }
            else
            {
                printf("ID(%s) ",alphastring);
            }

            continue;
        }

        //if we detect a number first
        if(c>='0' && c<='9')
        {

            int stringsize = 1;
            linkedlist* numlist = malloc(sizeof(struct linkedlist));
            numlist->c = c;

            linkedlist* current = numlist;

            //build the character linked list
            while(c>='0' && c<='9')
            {
                GETCHAR(c);
                current->nextNode = malloc(sizeof(struct linkedlist));
                current = current->nextNode;
                current->c = c;
                stringsize++;
                
            }

            //dont accidently null terminate our 1 value
            if(stringsize != 1)
                current->c = '\0';

            //now print the natliteral token
            
            printf("NATLITERAL(");
            current = numlist;
            int i = 0;
            while(i < stringsize-1)
            {
                printf("%c",current->c);
                current = current->nextNode;
                i++;
            }
            printf(") ");
            
            continue;
            
        }

        //ignore whitespace
        if(c=='\n')
        { linenumber++; 
          CARRYON(c); 
        }
        else if(c==' '||c=='\t'||c=='\r')
        {  CARRYON(c);}



        //if we made it this far, we have encountered an illegal character
        printError(linenumber, c);
    }
    printf("ENDOFFILE \n");
    fclose(fptr);
    return 0;
}