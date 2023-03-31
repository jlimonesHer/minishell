#include "../includes/minishell.h"
#include <sys/stat.h>

int main()
{
    while (1)
    {
        char *input;
        t_command a;
        int     i;
        
        i = 0;
        input = readline("> ");
        a.argv = lexer(input);
        add_history(input);
        while (a.argv && a.argv[i])
        {
            printf("%s\n", a.argv[i]);
            i++;
        }
    }
}
