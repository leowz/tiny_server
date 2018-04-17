/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_server.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 19:50:40 by zweng             #+#    #+#             */
/*   Updated: 2018/04/17 21:46:48 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TINY_SERVER_H
# define TINY_SERVER_H

# include <sys/socket.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include "libft.h"
# include "ft_printf.h"

# define MAXLINE	(500)
# define MAXBUF		(3000)

int		open_listenfd(int port);
int		open_clientfd(char *ip, int port);
void	serve_static(int fd, char *filename, int filesize);
void	serve_dynamic(int fd, char *filename, char *cgiargs);
void	handle_request(int fd);
void	client_error(int fd, char *cause, char *errnum,
					char *smsg, char *lmsg);
#endif
