/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_server.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 19:50:40 by zweng             #+#    #+#             */
/*   Updated: 2018/04/17 18:58:25 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TINY_SERVER_H
# define TINY_SERVER_H

# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "libft.h"
# include "ft_printf.h"

int		open_listenfd(int port);
int		open_clientfd(char *ip, int port);
#endif
