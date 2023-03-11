/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:46:47 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 15:00:57 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// & ------------- Command : + NAMES + ---------------------- 

// @ Syntax: NAMES [<channels>] | Returns a list of who is on the comma-separated list of <channels>

void    Server::names(User * user, std::vector<std::string> & channels){
    std::vector<Channel>::iterator      chanIt;
    std::vector<User>::iterator         userIt;
    std::vector<std::string>::iterator  strIt;
    std::string                         chanPrefix;
    if (!channels.empty()){
        for (strIt = channels.begin(); strIt != channels.end(); ++strIt){
            for (chanIt = _channels.begin(); chanIt != _channels.end(); ++chanIt){
                if (chanIt->getChannelName() == *strIt)
                    break;
            }
            if (chanIt == _channels.end()){
                buildResponseToSend(NULL, user, repliesMessage("366", user) + *strIt + " :End of /NAMES list");
                return;
            }
            for (userIt = _users.begin(); userIt != _users.end(); ++userIt){
                if (chanIt->getPrivateChannelStatus())
                    chanPrefix = "* ";
                else if (chanIt->getSecretChannelStatus())
                    chanPrefix = "@ ";
                else
                    chanPrefix = "= ";
                if (chanIt->checkMemberExistence(user->getUserName()) && (chanIt->getPrivateChannelStatus() || chanIt->getSecretChannelStatus())){
                    if(chanIt->checkMemberExistence(userIt->getNickName()))
                        buildResponseToSend(NULL, user, repliesMessage("353", user) + chanPrefix + *strIt + " : " + userIt->getNickName());
                }
                else if (!chanIt->getPrivateChannelStatus() && !chanIt->getSecretChannelStatus()){
                    if(chanIt->checkMemberExistence(userIt->getNickName()))
                        buildResponseToSend(NULL, user, repliesMessage("353", user) + chanPrefix + *strIt + " : " + userIt->getNickName());
                }
            }
            buildResponseToSend(NULL, user, repliesMessage("366", user) +  *strIt + " :End of NAMES list");
        }
    }
    else{
        if (_channels.empty()){
            buildResponseToSend(NULL, user, repliesMessage("366", user) + "" + " :End of NAMES list");
            return;
        }
        for (chanIt = _channels.begin(); chanIt != _channels.end(); ++chanIt){
            if (chanIt->getPrivateChannelStatus())
                chanPrefix = "* ";
            else if (chanIt->getSecretChannelStatus())
                chanPrefix = "@ ";
            else
                chanPrefix = "= ";
            if (!chanIt->checkMemberExistence(user->getNickName()) &&  (chanIt->getPrivateChannelStatus() || chanIt->getSecretChannelStatus())){
                buildResponseToSend(NULL, user, repliesMessage("366", user) + "*" + " :End of /NAMES list");
                continue;
            }
            else if ((chanIt->checkMemberExistence(user->getNickName())) || (!chanIt->getPrivateChannelStatus() && !chanIt->getSecretChannelStatus())){
                for (userIt = _users.begin(); userIt != _users.end(); ++userIt){
                    if (chanIt->checkMemberExistence(userIt->getNickName()))
                        buildResponseToSend(NULL, user, repliesMessage("353", user) + chanPrefix + chanIt->getChannelName() + " : " + userIt->getNickName());
                }
            }
            buildResponseToSend(NULL, user, repliesMessage("366", user) +  chanIt->getChannelName() + " :End of NAMES list");
        }
    }
}