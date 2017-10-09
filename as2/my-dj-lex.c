/* i pledge my honor that i have not cheated, and will not cheat, on this assignment
Daniel Sawyer */
#include <stdio.h>
#include <stdlib.h>

#define TOKENMAX 1000
#define true 1
#define false 0

int lines = 1;

int isalpha0(char c);
int isdigit0(char c);
int isspecial(char c);
void ptoken(char *token) {printf("%s ",token);}

int isws(char c) {
    
    switch(c) {
        case ' ': return true;
        case '\n': lines++; return true;
        case '\t': return true;
        case '\r': return true;
    }

    if(c < 32)
        return true;
    else
        return false;
}

int main(int argc, char** argv) {

    FILE *fp;
    fp = fopen(argv[1], "r");
    if(!fp) {
        printf("\nFILE %s coulndt be opened\n", argv[1]);
        return 1;
    }

    char c, token[TOKENMAX];
    token[0] = '\0';
    int count = 0;
    c = getc(fp);
    while(c != EOF) {

        //main detection
        if(c == 'm' && token[0] == '\0') {
            token[count++] = c;
            token[count] = '\0';
            c = getc(fp);

            if(c == 'a') {
                token[count++] = c;
                token[count] = '\0';
                c = getc(fp);

                if(c == 'i') {
                    token[count++] = c;
                    token[count] = '\0';
                    c = getc(fp);

                    if(c == 'n') {
                        token[count++] = c;
                        token[count] = '\0';
                        c = getc(fp);

                        if(!(isalpha0(c) || isdigit0(c))) {
                            printf("MAIN ");
                            token[0] = '\0';
                            count = 0;
                        }

                    }
                }
            }
        }

        //class detector
        if(c == 'c' && token[0] == '\0') {
            token[count++] = c;
            token[count] = '\0';
            c = getc(fp);

            if(c == 'l') {
                token[count++] = c;
                token[count] = '\0';
                c = getc(fp);

                if(c == 'a') {
                    token[count++] = c;
                    token[count] = '\0';
                    c = getc(fp);

                    if(c == 's') {
                        token[count++] = c;
                        token[count] = '\0';
                        c = getc(fp);

                        if(c == 's') {
                            token[count++] = c;
                            token[count] = '\0';
                            c = getc(fp);

                            if(!(isalpha0(c) || isdigit0(c))) {
                                printf("CLASS ");
                                token[0] = '\0';
                                count = 0;
                            }
                        }

                    }
                }
            }
        }

        //if detector
        if(c == 'i' && token[0] == '\0') {
            token[count++] = c;
            token[count] = '\0';
            c = getc(fp);

            if(c == 'f') {
                token[count++] = c;
                token[count] = '\0';
                c = getc(fp);

                if(!(isalpha0(c) || isdigit0(c))) {
                    printf("IF ");
                    token[0] = '\0';
                    count = 0;
                }
            }
        }

        //while detector
        if(c == 'w' && token[0] == '\0') {
            token[count++] = c;
            token[count] = '\0';
            c = getc(fp);

            if(c == 'h') {
                token[count++] = c;
                token[count] = '\0';
                c = getc(fp);

                if(c == 'i') {
                    token[count++] = c;
                    token[count] = '\0';
                    c = getc(fp);

                    if(c == 'l') {
                        token[count++] = c;
                        token[count] = '\0';
                        c = getc(fp);

                        if(c == 'e') {
                            token[count++] = c;
                            token[count] = '\0';
                            c = getc(fp);

                            if(!(isalpha0(c) || isdigit0(c))) {
                                printf("WHILE ");
                                token[0] = '\0';
                                count = 0;
                            }
                        }
                    }
                }
            }
        }

        //printNat detector
        if(c == 'p' && token[0] == '\0') {
            token[count++] = c;
            token[count] = '\0';
            c = getc(fp);

            if(c == 'r') {
                token[count++] = c;
                token[count] = '\0';
                c = getc(fp);

                if(c == 'i') {
                    token[count++] = c;
                    token[count] = '\0';
                    c = getc(fp);

                    if(c == 'n') {
                        token[count++] = c;
                        token[count] = '\0';
                        c = getc(fp);

                        if(c == 't') {
                            token[count++] = c;
                            token[count] = '\0';
                            c = getc(fp);

                            if(c == 'N') {
                                token[count++] = c;
                                token[count] = '\0';
                                c = getc(fp);

                                if(c == 'a') {
                                    token[count++] = c;
                                    token[count] = '\0';
                                    c = getc(fp);

                                    if(c == 't') {
                                        token[count++] = c;
                                        token[count] = '\0';
                                        c = getc(fp);

                                        if(!(isalpha0(c) || isdigit0(c))) {
                                            printf("PRINTNAT ");
                                            token[0] = '\0';
                                            count = 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        //readNat detector
        if(c == 'r' && token[0] == '\0') {
            token[count++] = c;
            token[count] = '\0';
            c = getc(fp);

            if(c == 'e') {
                token[count++] = c;
                token[count] = '\0';
                c = getc(fp);

                if(c == 'a') {
                    token[count++] = c;
                    token[count] = '\0';
                    c = getc(fp);

                    if(c == 'd') {
                        token[count++] = c;
                        token[count] = '\0';
                        c = getc(fp);

                        if(c == 'N') {
                            token[count++] = c;
                            token[count] = '\0';
                            c = getc(fp);

                            if(c == 'a') {
                                token[count++] = c;
                                token[count] = '\0';
                                c = getc(fp);

                                if(c == 't') {
                                    token[count++] = c;
                                    token[count] = '\0';
                                    c = getc(fp);

                                    if(!(isalpha0(c) || isdigit0(c))) {
                                        printf("READNAT ");
                                        token[0] = '\0';
                                        count = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        //this detector
        if(c == 't' && token[0] == '\0') {
            token[count++] = c;
            token[count] = '\0';
            c = getc(fp);

            if(c == 'h') {
                token[count++] = c;
                token[count] = '\0';
                c = getc(fp);

                if(c == 'i') {
                    token[count++] = c;
                    token[count] = '\0';
                    c = getc(fp);

                    if(c == 's') {
                        token[count++] = c;
                        token[count] = '\0';
                        c = getc(fp);

                        if(!(isalpha0(c) || isdigit0(c))) {
                            printf("THIS ");
                            token[0] = '\0';
                            count = 0;
                        }
                    }
                }
            }
        }

        //extends else detector
        if(c == 'e' && token[0] == '\0') {
            token[count++] = c;
            token[count] = '\0';
            c = getc(fp);

            if(c == 'x') {
                token[count++] = c;
                token[count] = '\0';
                c = getc(fp);

                if(c == 't') {
                    token[count++] = c;
                    token[count] = '\0';
                    c = getc(fp);

                    if(c == 'e') {
                        token[count++] = c;
                        token[count] = '\0';
                        c = getc(fp);

                        if(c == 'n') {
                            token[count++] = c;
                            token[count] = '\0';
                            c = getc(fp);

                            if(c == 'd') {
                                token[count++] = c;
                                token[count] = '\0';
                                c = getc(fp);

                                if(c == 's') {
                                    token[count++] = c;
                                    token[count] = '\0';
                                    c = getc(fp);

                                    if(!(isalpha0(c) || isdigit0(c))) {
                                        printf("EXTENDS ");
                                        token[0] = '\0';
                                        count = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if(c == 'l') {
                token[count++] = c;
                token[count] = '\0';
                c = getc(fp);

                if(c == 's') {
                    token[count++] = c;
                    token[count] = '\0';
                    c = getc(fp);

                    if(c == 'e') {
                        token[count++] = c;
                        token[count] = '\0';
                        c = getc(fp);

                        if(!(isalpha0(c) || isdigit0(c))) {
                            printf("ELSE ");
                            token[0] = '\0';
                            count = 0;
                        }
                    }
                }
            }
        }

        //nat new null detector
        if(c == 'n' && token[0] == '\0') {
            token[count++] = c;
            token[count] = '\0';
            c = getc(fp);

            if(c == 'a') {
                token[count++] = c;
                token[count] = '\0';
                c = getc(fp);

                if(c == 't') {
                    token[count++] = c;
                    token[count] = '\0';
                    c = getc(fp);

                    if(!(isalpha0(c) || isdigit0(c))) {
                        printf("NATTYPE ");
                        token[0] = '\0';
                        count = 0;
                    }
                }
            }
            else if(c == 'e') {
                token[count++] = c;
                token[count] = '\0';
                c = getc(fp);

                if(c == 'w') {
                    token[count++] = c;
                    token[count] = '\0';
                    c = getc(fp);

                    if(!(isalpha0(c) || isdigit0(c))) {
                        printf("NEW ");
                        token[0] = '\0';
                        count = 0;
                    }
                }
            }
            else if(c == 'u') {
                token[count++] = c;
                token[count] = '\0';
                c = getc(fp);

                if(c == 'l') {
                    token[count++] = c;
                    token[count] = '\0';
                    c = getc(fp);

                    if(c == 'l') {
                        token[count++] = c;
                        token[count] = '\0';
                        c = getc(fp);

                        if(!(isalpha0(c) || isdigit0(c))) {
                            printf("NUL ");
                            token[0] = '\0';
                            count = 0;
                        }
                    }
                }
            }
        }

        //special character/operators
        if(c == '=') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }

            if(c = getc(fp) == '=') {
                printf("EQUALITY ");
                c = getc(fp);
            }
            else {
                printf("ASSIGN ");
            }
            continue;
        }

        if(c == '+') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("PLUS ");
            c = getc(fp);
            continue;
        }

        if(c == '-') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("MINUS ");
            c = getc(fp);
            continue;
        }

        if(c == '*') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("TIMES ");
            c = getc(fp);
            continue;
        }

        if(c == '+') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("PLUS ");
            c = getc(fp);
            continue;
        }

        if(c == '<') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("LESS ");
            c = getc(fp);
            continue;
        }

        if(c == '!') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("NOT ");
            c = getc(fp);
            continue;
        }

        if(c == '.') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("DOT ");
            c = getc(fp);
            continue;
        }

        if(c == ',') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("COMMA ");
            c = getc(fp);
            continue;
        }

        if(c == '{') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("LBRACE ");
            c = getc(fp);
            continue;
        }

        if(c == '}') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("RBRACE ");
            c = getc(fp);
            continue;
        }

        if(c == '(') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("LPAREN ");
            c = getc(fp);
            continue;
        }

        if(c == ')') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("RPAREN ");
            c = getc(fp);
            continue;
        }

        if(c == ';') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            printf("SEMICOLON ");
            c = getc(fp);
            continue;
        }

        if(isdigit0(c) && token[0] == '\0') {

            count = 0;
            token[count++] = c;
            token[count] = '\0';

            while(isdigit0(c = getc(fp))) {
                token[count++] = c;
                token[count] = '\0';
            }

            printf("NATLITERAL(%s) ", token);
            token[0] = '\0';
            count = 0;
            continue;
        }

        if(isws(c)) {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }
            c = getc(fp);
            continue;
        }

        if(c == '/') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }

            if(c = getc(fp) == '/') {
                c = getc(fp);
                while(c != '\n' && c != EOF)
                    c = getc(fp);
                if(c == '\n') lines++;
                c = getc(fp);
                continue;
            }
            else {
                printf("\nLex error on line %d: Illegal character %c\n", lines, '/');
                return 1;
            }
        }

        if(c == '&') {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }

            if(c = getc(fp) == '&') {
                printf("AND ");
                c = getc(fp);
                continue;
            }
            else {
                printf("\nLex error on line %d: Illegal character %c\n", lines, '&');
                return 1;
            }
        }

        //collects ID chars, else unrecognized char
        if(isalpha0(c) || isdigit0(c) || isspecial(c)) {
            token[count++] = c;
            token[count] = '\0';
            c = getc(fp);
        }
        else {
            if(token[0] != '\0') {
                printf("ID(%s) ", token);
                token[0] = '\0';
                count = 0;
            }

            printf("\nLex error on line %d: Illegal character %c\n", lines, c);
            return 1;
        }

    }
    printf("ENDOFFILE\n");

    return 0;
}

int isalpha0(char c) {
    switch(c) {
        case 'a': return true;
        case 'b': return true;
        case 'c': return true;
        case 'd': return true;
        case 'e': return true;
        case 'f': return true;
        case 'g': return true;
        case 'h': return true;
        case 'i': return true;
        case 'j': return true;
        case 'k': return true;
        case 'l': return true;
        case 'm': return true;
        case 'n': return true;
        case 'o': return true;
        case 'p': return true;
        case 'q': return true;
        case 'r': return true;
        case 's': return true;
        case 't': return true;
        case 'u': return true;
        case 'v': return true;
        case 'w': return true;
        case 'x': return true;
        case 'y': return true;
        case 'z': return true;
        case 'A': return true;
        case 'B': return true;
        case 'C': return true;
        case 'D': return true;
        case 'E': return true;
        case 'F': return true;
        case 'G': return true;
        case 'H': return true;
        case 'I': return true;
        case 'J': return true;
        case 'K': return true;
        case 'L': return true;
        case 'M': return true;
        case 'N': return true;
        case 'O': return true;
        case 'P': return true;
        case 'Q': return true;
        case 'R': return true;
        case 'S': return true;
        case 'T': return true;
        case 'U': return true;
        case 'V': return true;
        case 'W': return true;
        case 'X': return true;
        case 'Y': return true;
        case 'Z': return true;
        default : return false;
    }
}

int isdigit0(char c) {
    switch(c) {
        case '0': return true;
        case '1': return true;
        case '2': return true;
        case '3': return true;
        case '4': return true;
        case '5': return true;
        case '6': return true;
        case '7': return true;
        case '8': return true;
        case '9': return true;
        default : return false;
    }
}

int isspecial(char c) {
    switch(c) {
        case '=': return true;
        case '+': return true;
        case '-': return true;
        case '*': return true;
        case '<': return true;
        case '!': return true;
        case '.': return true;
        case ',': return true;
        case '{': return true;
        case '}': return true;
        case '(': return true;
        case ')': return true;
        case ';': return true;
        default : return false;
    }
}