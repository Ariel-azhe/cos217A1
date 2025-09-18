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


int error_line = 1;
int comment_start = 0;
/*int comment_line = 0;*/

/*takes no argument; automatically called at start of program
calls the start_state function to begin the DFA calls*/
int main(void)
{
    start_state();
    return 0;
}

/*gets the next character from input.
If at end of file, end program; otherwise, 
enter corresponding states if next char
is /, ", or ', and print all other chars as they are  */
int start_state(void)
{
    int ch;
    /*printf("start_state() ");*/
    ch = getchar();
    if (ch == '\n')
    {
        /*printf("new line");*/
        error_line=error_line+1;
    }
    if (ch != EOF)
    {
        switch (ch)
        {
            case '/':
                /*printf("left slash");*/
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
                start_state();
                break;
        }
    }
    return 0;
}
/*Gets the next character from input.
Previous char is /. 
Enter corresponding states if next char is 
*, /, ", or ', otherwise, print next char as it is
and return to start_state*/
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
            comment_start = error_line;
            state_reject();
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
            printf("/");
            printf("\n");
            start_state();
            break;
        default:
            printf("/");
            printf("%c",ch);
            start_state();
            break;  
    }

}
else
    {
        printf("/");
    }
    return 0;

}
/*Gets the next character from input.
Previous char is \.
Print literal value of next char if it is a special char; 
and return to start_state*/
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
            start_state();
            break;
        case '\"':
            printf("\"");
            start_state();
            break;
        case '\\':
            printf("\\");
            start_state();
            break;
        default:
            start_state();
            break;  
    }
}
    return 0;
}

/*Gets next char from input.
Previous char is \ and in comment.
Print literal value of next char if it is a special char; 
and return to double quoted comment state*/ 
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


/*Gets next char from input.
Inside double quoted comment
Enter corresponding states if next char
is \ or ", otherwise, print next char to output*/
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
            start_state();
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

/*Gets next char from input.
Inside single quoted comment
Enter corresponding states if next char
is \ or ", otherwise, print next char to output*/
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
            start_state();
            break;
        default:
            putchar(ch);
            state_single_quote();
            break;  
    }
}
return 0;
}

/*Gets next char from input.
Previous char is \ and in comment.
Print literal value of next char if it is a special char; 
and return to single quoted comment*/  
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


/*Get next char from input.
Unless comment terminated, 
print only new lines; 
exit with an error if EOF before comment termination*/
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
        fprintf(stderr, "Error: line %d: unterminated comment\n", comment_start);
        exit(EXIT_FAILURE); 
    }
    return 0;

}
/*Get next char in input.
In comment state, unless exited by /.
Exit with error if EOF before comment terminated*/
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
            start_state();
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
        fprintf(stderr, "Error: line %d: unterminated comment\n", comment_start);
        exit(EXIT_FAILURE);
    }
    return 0;


}