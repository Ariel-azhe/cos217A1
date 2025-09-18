#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int state_left_slash(void);
int state_double_quote(void);
int state_single_quote(void);
int state_line_acc(void);
int state_reject(void);
int state_aster(void);
int state_line_dquote(void);
int state_line_squote(void);
int slash_dquote(void);
int slash_squote(void);
int escape_dquoted(void);
int state_escape_slash(void);
int escape_squoted(void);


int error_line = 0;
/*int comment_line = 0;*/

int main(void)
{
    char ch;
    printf("main() ");
    ch = getchar();
    if (ch != EOF)
    {
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
            default:
                printf("ch is: %c", ch);
                putchar(ch);
                main();
                break;
    }
    return 0;
}
}

int state_left_slash(void)
{
    /*printf("state_left_slash() ");*/
    char ch;
    ch = getchar();
    if (ch != EOF){
    switch(ch)
    {
        case '*':
            printf(" ");
            state_reject();
            error_line = __LINE__;
            break;
        case '/':
            printf("//");
            state_left_slash();
            break;
        case '\"':
            printf("\"");
            break;
        case '\'':
            printf("\'");
            break;
        case '\n':
            printf("//");
            state_line_acc();
            break;
        default:
            printf("//");
            printf("%c",ch);
            main();
            break;  
    }
}
    return 0;

}

int state_escape_slash(void)
{
    printf("\\");
    /*printf("state_left_slash() ");*/
    char ch;
    ch = getchar();
    if (ch != EOF){
    switch(ch)
    {
        case '\'':
            printf("\'");
            main();
            break;
        case '\"':
            printf("\"");
            main();
            break;
        case '\\':
            printf("\\");
            main();
            break;
        default:
            main();
            break;  
    }
}
    return 0;
}

int escape_dquoted(void)
{
    printf("\\");
    /*printf("state_left_slash() ");*/
    char ch;
    ch = getchar();
    if (ch != EOF){
    switch(ch)
    {
        case '\'':
            printf("\'");
            state_double_quote();
            break;
        case '\"':
            printf("\"");
            state_double_quote();
            break;
        case '\\':
            printf("\\");
            state_double_quote();
            break;
        default:
            state_double_quote();
            break;  
    }
}
    return 0;
}



int state_double_quote(void)
{
    /*printf("double_quote() ");*/
    char ch;
    ch = getchar();
    if (ch != EOF){
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
        default:
            printf("%c",ch);
            state_double_quote();
            break;  
    }
}
    return 0;

}

int state_single_quote(void)
{
    /*printf("single_quote() ");*/
    char ch;
    ch = getchar();
    if (ch != EOF)
    {
    switch(ch)
    {
        case '\n':
            state_line_squote();
            break;
        case '\'':
            printf("\'");
            main();
            break;
        case '\\':
            slash_squote();
            break;
        default:
            putchar(ch);
            state_single_quote();
            break;  
    }
}
return 0;

}

int escape_squoted(void)
{
    printf("\\");
    /*printf("state_left_slash() ");*/
    char ch;
    ch = getchar();
    if (ch != EOF){
    switch(ch)
    {
        case '\'':
            printf("\'");
            state_single_quote();
            break;
        case '\"':
            printf("\"");
            state_single_quote();
            break;
        case '\\':
            printf("\\");
            state_single_quote();
            break;
        default:
            state_single_quote();
            break;  
    }
    }
    return 0;
}


int state_line_acc(void)
{
    printf("line_acc() ");
    char ch;
    ch = getchar();
    if (ch != EOF){
    switch(ch)
    {
        case '\n':
            /*printf("ch is: %c",ch);*/
            printf("\n");
            state_line_acc();
            break;
        default:
            printf("ch is: %c",ch);
            printf("\n");
            printf("%c",ch);
            main();
            break;  
    }
}
    return 0;

}

int state_reject(void)
{
    /*printf("reject() ");*/

    char ch;
    ch = getchar();
    if (ch != EOF)
    {
    switch(ch)
    {
        case '*':
            state_aster();
            break;
        case '\n':
            printf("\n");
            state_reject();
            break;
        default:
            state_reject();
            break;  
    }
}
    else
    {
        fprintf(stderr, "Error: Line: %d: unterminated comment", error_line);
        exit(EXIT_FAILURE); 
    }
    return 0;

}

int state_aster(void)
{
    /*printf("aster() ");*/

    char ch;
    ch = getchar();
    if (ch != EOF)
    {
    switch(ch)
    {
        case '/':
            /*printf("%c",ch);*/
            main();
            break;
        case '*':
            state_aster();
            break;
        default:
            state_reject();
            break;
    }
}
    else 
    {
        fprintf(stderr, "Error: Line: %d: unterminated comment", error_line);
        exit(EXIT_FAILURE);
    }
    return 0;


}

int state_line_dquote(void)
{
    /*printf("line_dquote() ");*/

    char ch;
    ch = getchar();
    printf("\n");
    if (ch != EOF)
    {
    switch(ch)
    {
        case '\n':
            printf("\n");
            state_line_dquote();
            break;
        default:
            putchar(ch);
            state_double_quote();
            break;  
    }
}
    return 0;

}

int state_line_squote(void)
{
    /*printf("line_squote() ");*/

    printf("\n");
    char ch;
    ch = getchar();
    if (ch != EOF)
    {
    switch(ch)
    {
        case '\n':
            printf("\n");
            state_line_squote();
            break;
        default:
            putchar(ch);
            state_single_quote();
            break;  
    }
}
    return 0;

}
int slash_dquote(void)
{
    /*printf("slash_dquote() ");*/

    printf("\\");
    char ch;
    ch = getchar();
    if (ch != EOF)
    {
    switch(ch)
    {
        case '\\':
            slash_dquote();
            break;
        case '\n':
            state_line_dquote();
            break;
        default:
            state_double_quote();
            break;  
    }
}
    return 0;

}
int slash_squote(void)
{
    /*printf("slash_squote() ");*/

    printf("\\");
    char ch;
    ch = getchar();
    if (ch != EOF)
    {
    switch(ch)
    {
        case '\\':
            state_line_squote();
            break;
        case '\n':
            state_line_squote();
            break;
        default:
            state_single_quote();
            break;  
    }
}
    return 0;

}

