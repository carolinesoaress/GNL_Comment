#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
    // Abre o arquivo para leitura
    int fd = open("texto.txt", O_RDONLY);

    // Verifica se a abertura do arquivo foi bem-sucedida
    if (fd < 0)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    // Variável para armazenar as linhas lidas
    char *line;

    // Lê o arquivo linha por linha usando a função get_next_line
    while ((line = get_next_line(fd)))
    {
        // Imprime a linha lida
        printf("%s\n", line);

        // Libera a memória alocada para a linha
        free(line);
    }

    // Fecha o arquivo
    close(fd);

    // Encerra o programa
    return 0;
}
