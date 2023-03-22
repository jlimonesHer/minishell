#include "../includes/minishell.h"
#include <sys/stat.h>
static void handler(int signal)
{
    if (signal == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        //rl_replace_line("", 0);
       // print_terminal();
        //rl_redisplay();
        //set_env_value("?", "1", &g_envp);
        //set_env_value("_", "1", &g_envp);
    }
}
int main()
{
    while (1)
    {
        char *input;
        input = readline("> ");
        add_history(input);
    }

    struct stat sb;
    if (stat("archivo.txt", &sb) == -1)
    {
        perror("stat() falló");
        return 1;
    }
    printf("Tamaño del archivo: %lld bytes\n", sb.st_size);
    printf("Propietario del archivo: %d\n", sb.st_uid);
    printf("Permisos del archivo: %o\n", sb.st_mode & 0777);
    return 0;
}
