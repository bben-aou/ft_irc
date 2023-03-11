/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:58:40 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 14:56:51 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// & ------------- Command : + INVITE + ---------------------- 

//@ Syntax : INVITE <nickname> <channel> | Invites <nickname> to the channel <channel>

void    Server::invite(User * user, std::string invitedUser, std::string channel){
    if (invitedUser.empty() || channel.empty()){
        buildResponseToSend(NULL, user, repliesMessage("461", user) + "INVITE :Not enough parameters");
        return;
    }
    std::vector<Channel>::iterator  chanIt;
    std::vector<User>::iterator     userIt;
    
    for (chanIt = _channels.begin(); chanIt != _channels.end(); ++chanIt){
        if (chanIt->getChannelName() == channel)
            break;
    }
    if (chanIt == _channels.end()){
        buildResponseToSend(NULL, user, repliesMessage("401", user) + channel + " :No such nick/channel");
        return;
    }
    for (userIt = _users.begin(); userIt != _users.end(); ++userIt){
        if (userIt->getNickName() == invitedUser)
            break;
    }
    if (userIt == _users.end()){
        buildResponseToSend(NULL, user, repliesMessage("401", user) + invitedUser + " :No such nick/channel");
        return;
    }
    if (chanIt->checkMemberExistence(invitedUser)){
        buildResponseToSend(NULL, user, repliesMessage("443", user) + invitedUser + channel + " :is already on channel");
        return;
    }
    if (chanIt->checkMemberExistence(user->getNickName())){
        if (!chanIt->checkSuperUserPermission(user->getNickName())){
            buildResponseToSend(NULL, user, repliesMessage("482", user) + channel + " :You're not channel operator");
            return;
        }
        chanIt->addUserToChannel(invitedUser);
        buildResponseToSend(NULL, user, channel + " " + invitedUser);
    }
    else{
        buildResponseToSend(NULL, user, repliesMessage("442", user) + channel + " :You're not on that channel");
        return;
    }
}