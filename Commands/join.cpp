/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:36:41 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 14:57:33 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// ^ ------------------- Utils : JOIN -------------------

bool    Server::checkIfChannelNameValid(std::string channelName){
    if (channelName.size() < 2)
        return (false);
    if (channelName[0] != '#')
        return (false);
    return (true);
}

void    Server::listOfChannelMembers(Channel  & channel, User const * user) const{
    std::vector<std::string>::const_iterator it;
    bool               operatorMember;
    std::string        permissionCharacter;
    for (it = channel.beginMem() ; it != channel.endMem(); it++){
        operatorMember = channel.checkSuperUserPermission(*it);
        if (operatorMember)
            permissionCharacter = '@';
        else
            permissionCharacter = '+';
        buildResponseToSend(NULL, user, repliesMessage("353", user) +  " :" + permissionCharacter + *it);
        std::cout << channel.getChannelName() << std::endl;
    }
    buildResponseToSend(NULL,user, repliesMessage("366", user) + channel.getChannelName() + " :End of NAMES list");
}

// & ------------- Command : + JOIN + ----------------------

// @ Syntax: JOIN <channels> |  Makes the client join the channels

void    Server::join(User* user, std::vector<std::string> & argsVector){
    std::string     topicOfChannel;
    std::vector<Channel>::iterator chanIt;
    std::vector<std::string>::const_iterator argsIt;
    std::vector<std::string>::const_iterator userIt;

    
    if (argsVector.empty())
        buildResponseToSend(NULL, user, repliesMessage("461", user) + "JOIN :Not enough parameters");
    for (argsIt = argsVector.begin() ; argsIt != argsVector.end(); ++argsIt){ // iterate for all the arguments of argsVector
        for (chanIt = _channels.begin(); chanIt != _channels.end(); ++chanIt){ // iterate for all the channels to check if the new channel already exist
            if (chanIt->getChannelName() == *argsIt)
                break;
        }
        if (!checkIfChannelNameValid(*argsIt)){
            buildResponseToSend(NULL, user, repliesMessage("403", user) + *argsIt + " :No such channel");
            return ;
        }
        if (chanIt != _channels.end()){ // the cannel exist - No need to create a new one -
            for (userIt = chanIt->beginMem(); userIt != chanIt->endMem(); ++userIt){// check if the user is already in the channel
                if (*userIt == user->getNickName())
                    break;
            }
            if (userIt !=  chanIt->endMem()){ // the user already member of the channel 
                buildResponseToSend(NULL, user, repliesMessage("443", user) + user->getNickName()+ " " + chanIt->getChannelName() + " :is already on channel");
                return ; 
            }
            if (chanIt->getInviteOnlyChannelStatus()){
                buildResponseToSend(NULL, user, repliesMessage("473", user) + chanIt->getChannelName() + " :Cannot join channel (+i)");
                return;
            }
            if (!(chanIt->addUserToChannel(user->getNickName()))){
                buildResponseToSend(NULL, user, repliesMessage("471", user) + chanIt->getChannelName() + " :Cannot join channel (+l)");
                return ;
            }
             buildResponseToSend(user, user, "JOIN " + *argsIt);
            buildResponseToSendToChanMembers(user, *chanIt, generatePrefix(user) + "JOIN " + chanIt->getChannelName());
            topicOfChannel = chanIt->getChannelTopic();

            if (topicOfChannel.empty())
                buildResponseToSend(NULL, user, repliesMessage("331", user) + chanIt->getChannelName() + " :No topic is set");
            else
                buildResponseToSend(NULL, user, repliesMessage("332", user) + chanIt->getChannelName() + " :" + topicOfChannel);
            listOfChannelMembers(*chanIt, user); // Send the list Of channel Members 
        }
        else { // the channel doesn't exist - need to create it -
            _channels.push_back(Channel(*argsIt));
            _channels.back().addUserToChannel(user->getNickName());
            _channels.back().addUserToChannelOperators(user->getNickName());
            buildResponseToSend(NULL, user, repliesMessage("331", user) + _channels.back().getChannelName() + " :No topic is set");
            buildResponseToSend(user, user, "JOIN " + *argsIt);
            listOfChannelMembers(_channels.back(), user);
        }   
    }
}