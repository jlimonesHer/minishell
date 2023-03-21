#include "../includes/minishell.h"

int main() {
    char *input;
    
    // Leer la entrada del usuario
    input = readline("Ingrese un comando: ");
    
    // Agregar la entrada al historial
    add_history(input);
    
    // Verificar el número de entradas en el historial
    printf("Se han guardado %d entradas en el historial.\n", history_length);
    
    return 0;
}