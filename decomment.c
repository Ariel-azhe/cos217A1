#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int state_left_slash(void);
int state_double_quote(void);
int state_single_quote(void);
int state_reject(void);
int state_aster(void);
int state_line_dquote(void);
int slash_dquote(void);
int slash_squote(void);
int escape_dquoted(void);
int state_escape_slash(void);
int escape_squoted(void);


int error_line = 0;
int comment_start = 0;
/*int comment_line = 0;*/

int main(void)
{
    int ch;
    /*printf("main() ");*/
    ch = getchar();
    if (ch == '\n')
    {
        error_line=error_line+1;
    }
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
            default:
                putchar(ch);
                main();
                break;
        }
    }
    return 0;
}

int state_left_slash(void)
{
    
    int ch;
    /*printf("state_left_slash() ");*/
    ch = getchar();
    if (ch == '\n')
    {
        error_line=error_line+1;
    }
    if (ch != EOF){
    switch(ch)
    {
        case '*':
            printf(" ");
            state_reject();
            comment_start = error_line;
            /*printf("Error line is : %d", error_line);*/
            break;
        case '/':
            printf("/");
            state_left_slash();
            break;
        case '\"':
            printf("/");
            printf("\"");
            state_double_quote();
            break;
        case '\'':
            printf("/");
            printf("\'");
            state_single_quote();
            break;
        case '\n':
            printf("//\n");
            break;
        default:
            printf("/");
            printf("%c",ch);
            main();
            break;  
    }
}
    return 0;

}

int state_escape_slash(void)
{
    int ch;
    printf("\\");
    /*printf("state_left_slash() ");*/
    ch = getchar();
    if (ch == '\n')
    {
        error_line=error_line+1;
    }
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
    int ch;
    printf("\\");
    /*printf("escape_dquoted() ");*/
    ch = getchar();
    if (ch == '\n')
    {
        error_line=error_line+1;
    }
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
    int ch;
    /*printf("double_quote() ");*/
    ch = getchar();
    if (ch == '\n')
    {
        error_line=error_line+1;
    }
    if (ch != EOF){
    switch(ch)
    {
        case '\"':
            printf("\"");
            main();
            break;
        case '\\':
            escape_dquoted();
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
    int ch;
    /*printf("single_quote() ");*/
    ch = getchar();
    if (ch == '\n')
    {
        error_line=error_line+1;
    }
    if (ch != EOF)
    {
    switch(ch)
    {
        case '\\':
            escape_squoted();
            break;
        case '\'':
            printf("\'");
            main();
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
    int ch;
    printf("\\");
    
    /*printf("escape_squoted() ");*/
    ch = getchar();
    if (ch == '\n')
    {
        error_line=error_line+1;
    }
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



int state_reject(void)
{
    int ch;

    /*printf("reject() ");*/
    ch = getchar();
    if (ch == '\n')
    {
        error_line=error_line+1;
    }
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
        fprintf(stderr, "Error: Line: %d: unterminated comment", comment_start);
        exit(EXIT_FAILURE); 
    }
    return 0;

}

int state_aster(void)
{
    int ch;
    
    /*printf("aster() ");*/
    ch = getchar();
    if (ch == '\n')
    {
        error_line=error_line+1;
    }
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
        case '\n':
            putchar(ch);
            state_reject();
            break;
        default:
            state_reject();
            break;
    }
}
    else 
    {
        fprintf(stderr, "Error: Line: %d: unterminated comment", comment_start);
        exit(EXIT_FAILURE);
    }
    return 0;


}

int state_line_dquote(void)
{
    int ch;
    /*printf("line_dquote() ");*/
    ch = getchar();
    if (ch == '\n')
    {
        error_line=error_line+1;
    }
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