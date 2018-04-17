/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_clientfd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:17:14 by zweng             #+#    #+#             */
/*   Updated: 2018/04/17 18:55:16 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_server.h"

int		open_clientfd(char *ip, int port)
{
	int					clientfd;
	struct sockaddr_in	serveraddr;

	if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		ft_printf("client socket fail\n");
		return (-1);
	}
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(ip);
	serveraddr.sin_port = htons(port);
	if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr))
				< 0)
	{
		ft_printf("connect fail\n");
		return (-1);
	}
	return (clientfd);
}
