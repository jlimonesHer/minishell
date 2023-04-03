#include "../includes/minishell.h"
#include <sys/stat.h>
t_command	*parser(char *input);

int main()
{
    while (1)
    {
        char *input;
        t_command *a;
        int     i;
        int     j;

        i = 0;
        input = readline("> ");
        a = parser(input);
        add_history(input);
        j = 0;
        while (!a[j].last)
        {
            printf("Comando %d\n", j);
            i=0;
            while (a[j].argv && a[j].argv[i])
            {
                printf("%s\n", a[j].argv[i]);
                i++;
            }
            j++;
        }
    }
}
