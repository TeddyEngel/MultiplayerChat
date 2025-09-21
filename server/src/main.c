#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdint.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>

#include "constants.h"
#include "network_constants.h"
#include "err_quit.h"
#include "packet.h"
#include "socket.h"
#include "writen.h"

int main(int ac, char** av)
{
	int i;
	int max_i;
	int max_fd;
	int listen_fd;
	int conn_fd;
	int sock_fd;
	int n_ready;
	int client[FD_SETSIZE];
	ssize_t n;
	fd_set r_set;
	fd_set all_set;
	char buf[MAXLINE];
	socklen_t cli_len;
	struct sockaddr_in cli_addr;
	struct sockaddr_in serv_addr;

	listen_fd = Socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_PORT);

	// TODO: Wrap Bind
	bind(listen_fd, (SA*)&serv_addr, sizeof(serv_addr));

	// TODO: Wrap listen
	listen(listen_fd, LISTENQ);

	max_fd = listen_fd;
	max_i = -1;
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1; // -1 indicates available
	FD_ZERO(&all_set);
	FD_SET(listen_fd, &all_set);

	while (42)
	{
		r_set = all_set;
		// TODO: Wrap Select
		n_ready = select(max_fd + 1, &r_set, NULL, NULL, NULL);

		if (FD_ISSET(listen_fd, &r_set)) // New Client Connection
		{
			cli_len = sizeof(cli_addr);
			// TODO: Wrap accept
			conn_fd = accept(listen_fd, (SA*)&cli_addr, &cli_len);

			for (i = 0; i < FD_SETSIZE; i++)
			{
				if (client[i] < 0)
				{
					client[i] = conn_fd; // Save descriptor
					break;
				}
			}

			if (i == FD_SETSIZE)
				err_quit("Too many clients");

			FD_SET(conn_fd, &all_set); // Add new descriptor to set
			if (conn_fd > max_fd)
				max_fd = conn_fd;
			if (i > max_i)
				max_i = i;

			if (--n_ready <= 0)
				continue; // No more readable descriptors
		}

		for (i = 0; i <= max_i; i++) // Check all clients for data
		{
			if ((sock_fd = client[i]) < 0)
				continue;
			if (FD_ISSET(sock_fd, &r_set))
			{
				// TODO: Wrap read
				if ((n = read(sock_fd, buf, MAXLINE)) == 0)
				{
					// Connection closed by client
					// TODO: Wrap close
					close(sock_fd);
					FD_CLR(sock_fd, &all_set);
					client[i] = -1;
				}
				else // TODO: Wrap writen
					writen(sock_fd, buf, n);

				if (--n_ready <= 0)
					break; // No more readable descriptors
			}
		}
	}
}
