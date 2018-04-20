/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:34:33 by zweng             #+#    #+#             */
/*   Updated: 2018/04/20 15:26:22 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_server.h"

void	client_error(int fd, char *cause, char *errnum,
					char *smsg, char *lmsg)
{
	char	header[MAXBUF], body[MAXBUF];

	sprintf(body, "<html><title>ERROR</title>");
	sprintf(body, "%s%s: %s\r\n", body, errnum, smsg);
	sprintf(body, "%s<p>%s: %s\r\n", body, lmsg, cause);

	sprintf(header, "HTTP/1.0 %s %s\r\n", errnum, smsg);
	sprintf(header, "%sContent-type: text/html\r\n", header);
	sprintf(header, "%sContent-length: %d\r\n\r\n", header,
			(int)ft_strlen(body));
	write(fd, header, ft_strlen(header));
	write(fd, body, ft_strlen(body));
}
