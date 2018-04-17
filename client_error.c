/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:34:33 by zweng             #+#    #+#             */
/*   Updated: 2018/04/17 21:44:14 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_server.h"

void	client_error(int fd, char *cause, char *errnum,
					char *smsg, char *lmsg)
{
	char	buf[MAXLINE], body[MAXBUF];

	sprintf(body, "<html><title>ERROR</title>");
	sprintf(body, "%s%s: %s\r\n", body, errnum, smsg);
	sprintf(body, "%s<p>%s: %s\r\n", body, lmsg, cause);

	sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, smsg);
	write(fd, buf, ft_strlen(buf));
	sprintf(buf, "Content-type: text/html\r\n");
	write(fd, buf, ft_strlen(buf));
	sprintf(buf, "Content-length: %d\r\n\r\n", (int)ft_strlen(body));
	write(fd, buf, ft_strlen(buf));
	write(fd, body, ft_strlen(body));
}
