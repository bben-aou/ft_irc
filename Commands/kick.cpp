/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:56:32 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 14:58:24 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// & ------------- Command : + KICK + ---------------------- 

// @ Syntax: KICK <channel> <client> :[<message>] | Forcibly removes <client> from <channel>. This command may only be issued by channel operators

void    Server::kick(User * user, std::string channel, std::string target, std::string reason){
    std::vector<Channel>::iterator      chanIt;
    std::vector<User>::const_iterator  userIt;
    std::string msg;

    if (channel.empty() || target.empty()){
        buildResponseToSend(NULL, user, repliesMessage("461", user) + "KICK :Not enough parameters");
        return;
    }
    for (chanIt = _channels.begin(); chanIt != _channels.end(); ++chanIt){
        if (chanIt->getChannelName() == channel)
            break;
    }
    if (chanIt == _channels.end()){
        buildResponseToSend(NULL, user, repliesMessage("403", user) + channel + " :No such channel");
        return;
    }
    if (!(chanIt->checkSuperUserPermission(user->getNickName())))
        buildResponseToSend(NULL, user, repliesMessage("482", user) + channel + " ::You're not channel operator");
    else if (!(chanIt->deleteUserFromChannel(target)))
        buildResponseToSend(NULL, user, repliesMessage("441", user) + target + " " + channel + " :They aren't on that channel");
    else{
        if (reason.empty())
            msg = "KICK " + channel + " " + target ;
        else 
            msg = "KICK " + channel + " " + target + " " + reason;
        for (userIt = _users.begin(); userIt != _users.end() ; ++userIt){
                if (userIt->getNickName() == target)
                    break;
        }
        buildResponseToSend(user, &*userIt, msg); // to notify the user that kicked out of the channel
        buildResponseToSend(user, user, msg); // print msg to the operator who kicked out the user
        buildResponseToSendToChanMembers(user, *chanIt, msg); // notify all the channel members that user -target- kicked out 
    }
}