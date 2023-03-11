/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:00:06 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 15:05:51 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// & ------------- Command : + TOPIC + ---------------------- 

// @ Syntax: TOPIC <channel> [<topic>] | Allows the client to query or set the channel topic on <channel> 

void    Server::topic(User * user, std::string channel, std::string topic){
    std::vector<Channel>::iterator it;
    std::vector<std::string>::const_iterator chanMemberIt;
    if (channel.empty()){
        buildResponseToSend(NULL, user, repliesMessage("461", user) + "TOPIC :Not enough parameters");
        return;
    }
    for (it = _channels.begin(); it != _channels.end(); ++it){
        if (it->getChannelName() == channel)
            break;
    }
    if (!(it->checkMemberExistence(user->getNickName())) || it == _channels.end()){
        buildResponseToSend(NULL, user, repliesMessage("442", user) + channel + " :You're not on that channel");
        return;
    }
    if (topic.empty()){
        if (it->getChannelTopic().empty())
            buildResponseToSend(NULL, user, repliesMessage("331", user) + channel + " :No topic is set");
        else
            buildResponseToSend(NULL, user, repliesMessage("332", user) + channel + " :" + it->getChannelTopic());
    }
    else if (it->setChannelTopic(user->getNickName(), topic)){
        for (chanMemberIt = it->beginMem(); chanMemberIt != it->endMem(); ++chanMemberIt)
            buildResponseToSend(NULL, getUser(*chanMemberIt), repliesMessage("332", getUser(*chanMemberIt)) + channel + " :" + it->getChannelTopic());
    }
    else
    {
        buildResponseToSend(NULL, user, repliesMessage("482", user) + channel + " :You're not channel operator");
        return;    
    }
}