/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:23:01 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/14 16:23:02 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int    redirect_input(char *file_name)
{
    int fd;

    fd = open(file_name,  O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        return(fd);
    }
    return(fd);
}

int    redirect_output(char *file_name)
{
    int fd;

    fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
    if(fd == -1)
    {
        perror("open");
        return(fd);
    }
    return(fd);
}

int    redirect_append(char *file_name)
{
    int fd;

    fd = open(file_name,  O_RDWR | O_CREAT | O_APPEND, 0777);
    if(fd == -1)
    {
        perror("open");
        return(fd);
    }
    return(fd);
}