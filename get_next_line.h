/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carol <carol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:27:41 by cagoncal          #+#    #+#             */
/*   Updated: 2023/12/01 13:54:52 by carol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

char		*get_next_line(int fd);
char		*ft_strchr(const char *str, int c);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strlen(const char *str);
char		*read_line(int fd, char *remainder);
char		*ft_strdup(const char *str);
char		*ft_cpy(char *line, int pos);
char		*generate_line_return(char *line);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10 
# endif

#endif