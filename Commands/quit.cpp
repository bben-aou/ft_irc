/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:06:27 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 15:05:03 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// & ------------- Command : + QUIT + ---------------------- 

// @ Syntax: QUIT [<message>] | Disconnects the user from the server.

void    Server::quit(User* user,std::string message){
    std::string quitMessage;
    std::vector<Channel>::iterator chanIt;

    if (message.empty())
        quitMessage = user->getNickName() + " is quitting the server now !";
    else
        quitMessage =  user->getNickName() + message;
    for (chanIt = _channels.begin(); chanIt != _channels.end(); ++chanIt){
        if (chanIt->checkMemberExistence(user->getNickName())){
            chanIt->deleteUserFromChannel(user->getNickName());
            buildResponseToSendToChanMembers(user, *chanIt, generatePrefix(user) + "QUIT :" + quitMessage);
             
            if (chanIt->beginMem() == chanIt->endMem()){ // channel becomes empty need to be deleted
                _channels.erase(chanIt);
                chanIt = _channels.begin();
                chanIt--;
            }
        }
    }
}