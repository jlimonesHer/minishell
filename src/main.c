#include "../includes/minishell.h"

int main(void) 
{
    char *input;

    input = readline("Introduce una cadena: ");
    add_history(input);
    printf("Entrada del usuario: %s\n", input);
    free(input);

    return 0;
}