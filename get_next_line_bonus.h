/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagoncal <cagoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:02:13 by cagoncal          #+#    #+#             */
/*   Updated: 2023/12/04 15:15:36 by cagoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

char		*ft_strchr(const char *str, int c);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strlen(const char *str);
char		*ft_strdup(const char *str);
char		*ft_cpy(char *line, int pos);
char		*generate_line_return(char *line);
char		*read_line(int fd, char *remainder);
char		*get_next_line(int fd);
char		*get_remainder(char *line);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10 
# endif

#endif