/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:47:15 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 14:55:59 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// & ------------- Command : + USER + ---------------------- 

// @ USER <username> <hostname> <servername> <realname> |  used at the beginning of a connection to specify the username, hostname, real name 

void    Server::user(User* user, std::string userName, std::string hostName, std::string serverName, std::string realName){
    (void)serverName;
    if (user->isAuthenticated())
        buildResponseToSend(NULL, user, repliesMessage("462", user) + ":You may not reregister");
    else if (userName.empty() || hostName.empty() || serverName.empty() || realName.empty())
        buildResponseToSend(NULL, user, repliesMessage("461", user) + "USER :Not enough parameters");
    else{
        if (hostName == "*")
            user->setHostName("localhost");
        else
            user->setHostName(hostName);
        user->setUserName(userName);
        user->setRealName(realName);
        if (user->Authenticate(_password)){
            saveLoginTime(user);
            welcome(user);
        }
    }
}