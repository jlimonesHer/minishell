#include "../includes/minishell.h"
#include <sys/stat.h>

int main()
{
    while (1)
    {
        char *input;
        char **a;
        int     i;
        
        i = 0;
        input = readline("> ");
        a = lexer(input);
        add_history(input);
        while (a && a[i])
        {
            printf("%s\n", a[i]);
            i++;
        }
    }
}
