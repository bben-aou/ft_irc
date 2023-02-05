/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blind-eagle <blind-eagle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:28:52 by blind-eagle       #+#    #+#             */
/*   Updated: 2023/02/05 13:15:14 by blind-eagle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  SERVER_HPP
# define SERVER_HPP

#include "./User.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <poll.h>
#include <sys/socket.h>
#include <sstream>
#include <netinet/in.h>
#include <fcntl.h>
#include <limits>
#include <cstdlib>


class   Server{
    private :
        std::string  _serverName;
        std::string  _password;
        int          _port;
        int          _address_size;
        sockaddr_in  _server_address;
        
        std::vector<pollfd>  _fds;
        std::vector<User>    _users;

    public  :
        Server();
        Server(std::string serverName, int port, char *password);
        Server(Server& const server);
        ~Server();
        
};

#endif