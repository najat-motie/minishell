/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:46:52 by nmotie-           #+#    #+#             */
/*   Updated: 2024/11/28 19:57:29 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

size_t				ft_strlen(const char *s);
int	ft_atoi(const char *str);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char  *s1, char  *s2);
char				**ft_split(char *s, char c);

#endif