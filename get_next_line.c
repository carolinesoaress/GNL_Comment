/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carol <carol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:01:38 by cagoncal          #+#    #+#             */
/*   Updated: 2023/12/01 14:02:10 by carol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*Essa função recebe uma string line como entrada e retorna uma nova
string line_to_return que contém caracteres desde o início de line até o primeiro 
caractere de nova linha ('\n') ou até o final da string. Utiliza uma função auxiliar 
ft_cpy para copiar um número especificado de caracteres de uma string para outra.*/

char	*generate_line_return(char *line)
{
	char	*line_to_return;
	int		i;

	i = 0;
	while (line && line[i] != '\0' && line[i] != '\n') // Aqui eu vou percorrendo line até encontraro nulo ou \n o i fica nessa posição
		i++;
	line_to_return = ft_cpy(line, i + 1);  //Aqui mando copiar para line_to_return até a posição i + 1 para o \n
	if (!line_to_return) //Se a operação de cópia falhar (retornar NULL), libera a line original e retorna NULL
	{
		free(line);
		return (NULL);
	}
	return (line_to_return);
}
/*Esta função recebe uma string line como entrada e retorna uma nova string 
remainder que contém a porção de line após o primeiro caractere de nova linha 
('\n'). Se não houver um caractere de nova linha, retorna uma string vazia.*/

char	*get_remainder(char *line)
{
	char		*remainder;	//Porque essa váriável não é estática?

	while (line && *line != '\0')
	{
		if (*line == '\n')
		{
			remainder = ft_strdup(line + 1); //Ao encontrar o \n eu retorno uma string remainder já alocada 
			if (!remainder)		//Se a operação de duplicação falhar (retornar NULL), retorna NULL
				return (NULL);
			return (remainder);
		}
		line++;
	}
	return (ft_strdup(""));  //Se não houver um caractere de nova linha, retorna uma string vazia.
}
/*Esta função lê de um descritor de arquivo (fd) e anexa o conteúdo lido à string 
remainder existente até encontrar um caractere de nova linha ou atingir o final do arquivo*/
char	*read_line(int fd, char *remainder)
{
	char		*buffer;
	ssize_t		bytes_read;
	int			i;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)); //Aloca dinamicamente um buffer (buffer) para ler um pedaço de dados do arquivo.
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(remainder, '\n') && bytes_read != 0) //O loop externo while continua lendo e anexando a remainder até encontrar um 
	{														//caractere de nova linha ou até atingir o final do arquivo (bytes_read se torna 0).
		i = 0;
		while (i < BUFFER_SIZE + 1) //O loop interno while inicializa o buffer com zeros.
			buffer[i++] = '\0'; //PQ TENHO QUE DEIXAR O BUFFER COM ZEROS?
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1) //se ocorrer um erro durante a operação de leitura (bytes_read == -1), libera o buffer e retorna NULL.
		{
			free(buffer);
			return (NULL);
		}
		remainder = ft_strjoin(remainder, buffer); //Usa então ft_strjoin para concatenar o conteúdo do buffer com o remainder existente.
	}
	free(buffer);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char		*remainder; //A variável estática armazena o restante não processado dos dados do arquivo
	char			*line;		//anteriormente lidos,O uso de static faz com que a variável persista entre as chamadas da função.
	char			*line_to_return;

	/* Verifica algumas condições antes de prosseguir com a leitura da próxima linha.
	Se o descritor de arquivo for inválido (fd < 0), o tamanho do buffer for menor ou igual a zero
	(BUFFER_SIZE <= 0), ou se ocorrer um erro na leitura (read(fd, 0, 0) < 0), 
	a função libera a memória associada ao remainder e retorna NULL*/
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0) 
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	/*Chama a função read_line para obter uma linha do arquivo.
	 O remainder é passado como argumento para que os dados 
	não lidos de leituras anteriores sejam considerados.*/
	line = read_line(fd, remainder);
	if (!line) //Se a leitura da linha falhar (retornando NULL), a função também retorna NULL
		return (NULL);
	remainder = get_remainder(line); //Atualiza o remainder com os dados não processados após a última quebra de linha.
	line_to_return = generate_line_return(line);//obter uma linha completa a ser retornada,Essa função cria uma nova string contendo a linha até a quebra de linha ou o final da string.
	free(line); // Libera a memória alocada para a linha original, pois os dados já foram processados.

	/*Verifica se tanto a linha quanto o remainder estão vazios. Se ambos estiverem vazios,
	isso significa que o final do arquivo foi atingido, e a função libera a memória associada ao 
	line_to_return e ao remainder antes de retornar NULL.*/
	if (*line_to_return == '\0' && *remainder == '\0')
	{
		free(line_to_return);
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	return (line_to_return); //Retorna a linha completa (ou parte dela) que foi lida do arquivo.
}
