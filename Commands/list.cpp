/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:44:01 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 14:59:07 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// & ------------- Command : + LIST + ---------------------- 

// @ Syntax: LIST [<channels>  | Lists all channels on the server

void    Server::list(User* user, std::vector<std::string>  & channels) const{
    std::vector<std::string>::const_iterator  chanArgsIt;
    std::vector<Channel>::const_iterator      chanIt;
    std::string       channelName;
    std::string       topic;
    
    buildResponseToSend(NULL, user, repliesMessage("321", user) + "Channel :Users Name");
    if (channels.empty()){
        for (chanIt = _channels.begin(); chanIt != _channels.end(); ++chanIt){
            if (!(chanIt->getSecretChannelStatus()) || (chanIt->checkMemberExistence(user->getNickName()))){
                channelName = "priv";
                topic = "";
                if (!(chanIt->getPrivateChannelStatus()) || chanIt->checkMemberExistence(user->getNickName())){
                    channelName = chanIt->getChannelName();
                    topic  = chanIt->getChannelTopic();
                }
                buildResponseToSend(NULL, user, repliesMessage("322", user) + channelName + " :" + topic);
            }
        }
    }
    else{
        for (chanArgsIt = channels.begin(); chanArgsIt != channels.end(); ++chanArgsIt){            
            for (chanIt = _channels.begin(); chanIt != _channels.end(); ++chanIt){
                if (chanIt->getChannelName() == *chanArgsIt){
                    if (!(chanIt->getSecretChannelStatus()) || (chanIt->checkMemberExistence(user->getNickName()))){
                    channelName = "priv";
                    topic = "";
                    if (!(chanIt->getPrivateChannelStatus()) || chanIt->checkMemberExistence(user->getNickName())){
                        channelName = chanIt->getChannelName();
                        topic  = chanIt->getChannelTopic();
                    }
                    buildResponseToSend(NULL, user, repliesMessage("322", user) + channelName + " :" + topic);
                    }
                }
            }
        }
    }
    buildResponseToSend(NULL, user, repliesMessage("323", user) + ":End of /LIST");
}