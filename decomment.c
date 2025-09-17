#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int state_left_slash(void);
int state_double_quote(void);
int state_single_quote(void);
int state_line_acc(void);
int state_line_rej(void);
int state_reject(void);
int state_aster(void);
int state_line_dquote(void);
int state_line_squote(void);
int slash_dquote(void);
int slash_squote(void);

int main(void)
{
    /*printf("main() ");*/
    char ch;
    ch = getchar();
    switch (ch)
    {
        case '/':
            state_left_slash();
            break;
        case '\"':
            printf("\"");
            state_double_quote();
            break;
        case '\'':
            printf("\'");
            state_single_quote();
            break;
        case '\n':
            state_line_acc();
            break;
        case EOF:
            exit(0);
        default:
            printf("%c", ch);
            main();
            break;
    }
    return 0;
}

int state_left_slash(void)
{
    /*printf("state_left_slash() ");*/
    char ch;
    ch = getchar();
    switch(ch)
    {
        case '*':
            printf(" ");
            state_reject();
            break;
        case '/':
            printf("//");
            state_left_slash();
            break;
        case '\"':
            printf("\"");
            /*state_double_quote();*/
            break;
        case '\'':
            printf("\'");
            /*state_single_quote();*/
            break;
        case '\n':
            printf("//");
            state_line_acc();
            break;
        case EOF:
            exit(0);
        default:
            printf("//");
            printf("%c",ch);
            main();
            break;  
    }
    return 0;

}
int state_double_quote(void)
{
    /*printf("double_quote() ");*/
    char ch;
    ch = getchar();
    switch(ch)
    {
        case '\n':
            state_line_dquote();
            break;
        case '\"':
            printf("\"");
            main();
            break;
        case '\\':
            slash_dquote();
            break;
        case EOF:
            exit(0);
        default:
            printf("%c",ch);
            state_double_quote();
            break;  
    }
    return 0;

}

int state_single_quote(void)
{
    /*printf("single_quote() ");*/
    char ch;
    ch = getchar();
    switch(ch)
    {
        case '\n':
            state_line_squote();
            break;
        case '\'':
            printf("\'");
            main();
            break;
        case EOF:
            exit(0);
        case '\\':
            slash_squote();
            break;
        default:
            printf("%c", ch);
            state_single_quote();
            break;  
    }
    return 0;

}
int state_line_acc(void)
{
    /*printf("line_acc() ");*/

    char ch;
    ch = getchar();
    switch(ch)
    {
        case '\n':
            /*printf("ch is: %c",ch);*/
            printf("\n");
            state_line_acc();
            break;
        case EOF:
            /*printf("ch is: %c",ch);*/
            exit(0);
        default:
            /*printf("ch is: %c",ch);*/
            printf("\n");
            printf("%c",ch);
            main();
            break;  
    }
    return 0;

}
int state_line_rej(void)
{
    /*printf("line_rej() ");*/

    char ch;
    ch = getchar();
    switch(ch)
    {
        case '\n':
            printf("\n");
            state_line_rej();
            break;
        case EOF:
            fprintf(stderr, "Error: Line: %d: unterminated comment", __LINE__);
            exit(EXIT_FAILURE);
        default:
            printf("\n");
            state_reject();
            break;  
    }
    return 0;

}
int state_reject(void)
{
    /*printf("reject() ");*/

    char ch;
    ch = getchar();
    switch(ch)
    {
        case '*':
            state_aster();
            break;
        case '\n':
            printf("\n");
            state_line_rej();
            break;
        case EOF:
            fprintf(stderr, "Error: Line: %d: unterminated comment", __LINE__);
            exit(EXIT_FAILURE); 
        default:
            state_reject();
            break;  
    }
    return 0;

}
int state_aster(void)
{
    /*printf("aster() ");*/

    char ch;
    ch = getchar();
    switch(ch)
    {
        case '/':
            /*printf("%c",ch);*/
            main();
            break;
        case '*':
            state_aster();
            break;
        case EOF:
            fprintf(stderr, "Error: Line: %d: unterminated comment", __LINE__);
            exit(EXIT_FAILURE);
        default:
            state_reject();
            break;
    }
    return 0;


}

int state_line_dquote(void)
{
    /*printf("line_dquote() ");*/

    char ch;
    ch = getchar();
    printf("\n");
    switch(ch)
    {
        case '\n':
            printf("\n");
            state_line_dquote();
            break;
        case EOF:
            exit(0);
        default:
            printf("%c", ch);
            state_double_quote();
            break;  
    }
    return 0;

}

int state_line_squote(void)
{
    /*printf("line_squote() ");*/

    printf("\n");
    char ch;
    ch = getchar();
    switch(ch)
    {
        case '\n':
            printf("\n");
            state_line_squote();
            break;
        case EOF:
            exit(0);
        default:
            printf("%c", ch);
            state_single_quote();
            break;  
    }
    return 0;

}
int slash_dquote(void)
{
    /*printf("slash_dquote() ");*/

    printf("\\");
    char ch;
    ch = getchar();
    switch(ch)
    {
        case '\\':
            slash_dquote();
            break;
        case '\n':
            state_line_dquote();
            break;
        case EOF:
            exit(0);
        default:
            state_double_quote();
            break;  
    }
    return 0;

}
int slash_squote(void)
{
    /*printf("slash_squote() ");*/

    printf("\\");
    char ch;
    ch = getchar();
    switch(ch)
    {
        case '\\':
            state_line_squote();
            break;
        case '\n':
            state_line_squote();
            break;
        case EOF:
            exit(0);
        default:
            state_single_quote();
            break;  
    }
    return 0;

}

