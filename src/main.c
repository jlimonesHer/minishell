#include "../includes/minishell.h"
#include <sys/stat.h>

int main()
{
    while (1)
    {
        char *input;
        input = readline(">");
        add_history(input);
        printf("%s\n", input);
        ft_exit(input);
    }
}
