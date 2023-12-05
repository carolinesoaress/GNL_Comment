/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carol <carol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:01:38 by cagoncal          #+#    #+#             */
/*   Updated: 2023/12/04 21:41:57 by carol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*generate_line_return(char *line)
{
	char	*line_to_return;
	int		i;

	i = 0;
	while (line && line[i] != '\0' && line[i] != '\n')
		i++;
	line_to_return = ft_cpy(line, i + 1);
	if (!line_to_return)
	{
		free(line);
		return (NULL);
	}
	return (line_to_return);
}

char	*get_remainder(char *line)
{
	char		*remainder;

	while (line && *line != '\0')
	{
		if (*line == '\n')
		{
			remainder = ft_strdup(line + 1);
			if (!remainder)
				return (NULL);
			return (remainder);
		}
		line++;
	}
	return (ft_strdup(""));
}

char	*read_line(int fd, char *remainder)
{
	char		*buffer;
	ssize_t		bytes_read;
	int			i;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(remainder, '\n') && bytes_read != 0)
	{
		i = 0;
		while (i < BUFFER_SIZE + 1)
			buffer[i++] = '\0';
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		remainder = ft_strjoin(remainder, buffer);
	}
	free(buffer);
	return (remainder);
}
/*Essa modificação permite que a função mantenha estados distintos para diferentes 
descritores de arquivo, o que pode ser útil em cenários onde você está lendo de vários 
arquivos simultaneamente e deseja manter o estado de cada um separadamente.*/
char	*get_next_line(int fd)
{
	/* Agora, remainder não é mais uma única variável estática, mas um array estático com 1024 elementos.
	Cada elemento do array representa o estado não processado para um descritor de arquivo específico.*/
	static char		*remainder[1024];
	char			*line;
	char			*line_to_return;

	/*: Quando ocorrem condições que impedem a leitura da 
	próxima linha (por exemplo, fd < 0, BUFFER_SIZE <= 0, ou erro na leitura)
	a função libera a memória associada ao remainder correspondente ao descritor de arquivo fd específico.*/
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(remainder[fd]);
		/*Define o remainder associado ao descritor de arquivo 
		fd como NULL para garantir que não haja mais dados remanescentes.*/
		remainder[fd] = NULL; 
		return (NULL);
	}
	line = read_line(fd, remainder[fd]);
	if (!line)
		return (NULL);
	remainder[fd] = get_remainder(line);
	line_to_return = generate_line_return(line);
	free(line);
	/*Verifica se tanto a linha quanto o remainder associado ao descritor de arquivo fd estão vazios
	Se ambos estiverem vazios, isso significa que o final do arquivo foi atingido. */
	if (*line_to_return == '\0' && *remainder[fd] == '\0')
	{
		free(line_to_return);
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	return (line_to_return);
}
