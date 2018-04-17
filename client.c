/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:58:57 by zweng             #+#    #+#             */
/*   Updated: 2018/04/17 19:08:35 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_server.h"

int		main(int ac, char **av)
{
	int 	clientfd, port, n;
	char	*ip, *line;

	if (ac != 3)
	{
		printf("useage: %s <ip> <port>\n", av[0]);
		return (1);
	}
	ip = av[1];
	port = ft_atoi(av[2]);

	if ((clientfd = open_clientfd(ip, port)) < 0)
	{
		printf("open client fail\n");
		return (1);
	}
	while ((n = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		printf("write %s\n", line);
		dprintf(clientfd, "%s\n", line);
		ft_strdel(&line);
	}
	close(clientfd);
	return (0);
}
