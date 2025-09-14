#include <stdio.h>

int main(void)
{
    int ch;
    ch = getchar();
    switch (ch)
    {
        case '/':
            state_left_slash();
            break;
        case '\"':
            state_double_quote();
            break;
        case '\'':
            state_single_quote();
            break;
        case 'n':
            state_line_acc();
            break;
        case EOF:
            break;
        default:
            printf(ch);
            int_main();
            break;
    }
    return 0;
}

int state_left_slash(void)
{
    int ch;
    ch = getchar();
    switch(ch)
    {
        case '*':
            printf(" ");
            state_reject();
            break;
        case '/':
            printf("/");
            state_left_slash();
            break;
        case '\"':
            printf("/");
            state_double_quote();
            break;
        case '\'':
            printf("/");
            state_single_quote();
            break;
        case 'n':
            printf("/");
            state_line_acc();
            break;
        default:
            printf("/");
            int_main();
            break;  
    }
}
int state_double_quote(void)
{
    printf("\"");
    int ch;
    ch = getchar();
    switch(ch)
    {
        case 'n':
            state_line_dquote();
            break;
        case '\"':
            printf("\"");
            int_main();
            break;
        case '\\':
            state_slash_dquote();
            break;
        default:
            state_double_quote();
            break;  
    }
}

int state_single_quote(void)
{
    printf("\'");
    int ch;
    ch = getchar();
    switch(ch)
    {
        case 'n':
            state_line_squote();
            break;
        case '\'':
            printf("\'");
            int_main();
            break;
        case '\\':
            state_slash_squote();
            break;
        default:
            state_single_quote();
            break;  
    }
}
int state_line_acc(void)
{
    printf("\n");
    int ch;
    ch = getchar();
    switch(ch)
    {
        case 'n':
            state_line_acc();
            break;
        default:
            int_main();
            break;  
    }
}
int state_line_rej(void)
{
    printf("\n");
    int ch;
    ch = getchar();
    switch(ch)
    {
        case 'n':
            state_line_rej();
            break;
        default:
            state_reject();
            break;  
    }
}
int state_reject(void)
{
    int ch;
    ch = getchar();
    switch(ch)
    {
        case '*':
            state_aster();
            break;
        case 'n':
            printf("\n");
            state_line_rej();
            break;
        case EOF:
            printf("Error: Line: %d: unterminated comment", __LINE__);
            break;
        default:
            state_reject();
            break;  
    }
}
int state_aster(void)
{
    int ch;
    ch = getchar();
    switch(ch)
    {
        case '/':
            int_main();
            break;
        case '*':
            state_aster();
            break;
        default:
            state_reject();
            break;  
    }
}

int state_line_dquote(void)
{
    printf("\n");
    int ch;
    ch = getchar();
    switch(ch)
    {
        case 'n':
            state_line_dquote();
            break;
        default:
            state_double_quote();
            break;  
    }
}

int state_line_squote(void)
{
    printf("\n");
    int ch;
    ch = getchar();
    switch(ch)
    {
        case 'n':
            state_line_squote();
            break;
        default:
            state_single_quote();
            break;  
    }
}
int slash_dquote(void)
{
    printf("\\");
    int ch;
    ch = getchar();
    switch(ch)
    {
        case '\\':
            state_slash_dquote();
            break;
        case 'n':
            state_line_dquote();
            break;
        default:
            state_double_quote();
            break;  
    }
}
int slash_squote(void)
{
    printf("\\");
    int ch;
    ch = getchar();
    switch(ch)
    {
        case '\\':
            state_line_squote();
            break;
        case 'n':
            state_line_squote();
            break;
        default:
            state_single_quote();
            break;  
    }
}

