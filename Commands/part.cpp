/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:40:32 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 15:02:19 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// & ------------- Command : + PART + ---------------------- 

//@ Syntax: PART <channels> [<message>] | Causes a user to leave the channels in the comma-separated list <channels>

void    Server::part(User *user, std::vector<std::string> & chanArgs, std::string partReasonMessage){
    std::string reasonMessage;
    std::vector<User>::const_iterator   userIt;
    std::vector<Channel>::iterator      chanIt;
    std::vector<std::string>::iterator  chanArgsIt;

    if (partReasonMessage.empty())
        reasonMessage = "someone just left the channel";
    else
        reasonMessage = partReasonMessage;
    if (chanArgs.empty()){
        buildResponseToSend(NULL, user, repliesMessage("461", user) + "PART :Not enough parameters");
        return ;
    }

    for (chanArgsIt = chanArgs.begin(); chanArgsIt != chanArgs.end(); ++chanArgsIt){
        for(chanIt = _channels.begin(); chanIt != _channels.end(); ++chanIt){
            if (chanIt->getChannelName() == *chanArgsIt)
                break;
        }
        if (chanIt != _channels.end()){
            if (!(chanIt->deleteUserFromChannel(user->getNickName()))){
                buildResponseToSend(NULL, user, repliesMessage("442", user) + *chanArgsIt + " :You're not on that channel");
                return;
            }
            buildResponseToSend(user, user, "PART " + chanIt->getChannelName());
            buildResponseToSendToChanMembers(user, *chanIt, generatePrefix(user) + "PART " + chanIt->getChannelName() + " :" + reasonMessage);
            if (chanIt->beginMem() == chanIt->endMem()){
                _channels.erase(chanIt);
                chanIt = _channels.begin();
                chanIt--;
            }
        }
        else{
            buildResponseToSend(NULL, user, repliesMessage("403", user) + *chanArgsIt + " :No such channel");
            return;
        }
    }   
}