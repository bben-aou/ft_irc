/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blind-eagle <blind-eagle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:28:52 by blind-eagle       #+#    #+#             */
/*   Updated: 2023/02/12 02:00:39 by blind-eagle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  SERVER_HPP
# define SERVER_HPP

#include "./User.hpp"
#include <unistd.h>
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
#include <cstring>

#define MAXUSERS 500

class   Server{
    private :
        std::string  _serverName;
        std::string  _password;
        int          _port;
        int          _AddressSize;
        sockaddr_in  _ServerAddress;
        
        std::vector<pollfd>  _fds;
        std::vector<User>    _users;
        
        //! - Commands: 
        void    quit(User* user, std::string message);

    public  :
        Server();
        Server(std::string serverName, int port, char *password);
        Server(Server const &server);
        ~Server();

        Server& operator=(Server const &obj);
    // -getters- :
    
    int                     getPort() const;
    std::string             getServerName() const;
    std::string             getPassword() const;
    std::vector<pollfd>     getFds();


    // -Main Methods- :

    void    establishListening();
    void    handlingEvents();
    int     itsCommand(std::string line);
    int     parser(std::string buffer, int index);
    
    std::string     getWordInLine(std::string line,int* posPointer) const;

    bool    checkCommandValidation(std::string  command);
    
    // User*                   getUser(std::string nickName);
    // const User*             getUser(std::string nickName) const;
        
};

#endif