/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blind-eagle <blind-eagle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:46:09 by blind-eagle       #+#    #+#             */
/*   Updated: 2023/02/16 12:22:05 by blind-eagle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Channel.hpp"


Channel::Channel(){
    this->_channelName           = "";
    this->_channelTopic          = "";
    this->_maxMembers            = 0;
    this->_channelMembers        = std::vector<std::string>();
    this->_channelOperators         = std::vector<std::string>();
    this->_privateChannel        = false;
    this->_secretChannel         = false;
    this->_allowOutMessages      = false;
    this->_operatorsTopicControl = true;
}

Channel::Channel(std::string channelName){
    this->_channelName           = channelName;
    this->_channelTopic          = "";
    this->_maxMembers            = 0;
    this->_channelMembers        = std::vector<std::string>();
    this->_channelOperators         = std::vector<std::string>();
    this->_privateChannel        = false;
    this->_secretChannel         = false;
    this->_allowOutMessages      = false;
    this->_operatorsTopicControl = true;
}

Channel::Channel(const Channel &obj){
    this->_channelName            = obj._channelName;          
    this->_channelTopic           = obj._channelTopic;       
    this->_maxMembers             = obj._maxMembers;         
    this->_channelMembers         = obj._channelMembers;       
    this->_channelOperators          = obj._channelOperators;        
    this->_privateChannel         = obj._privateChannel;       
    this->_secretChannel          = obj._secretChannel;        
    this->_allowOutMessages       = obj._allowOutMessages;     
    this->_operatorsTopicControl  = obj._operatorsTopicControl;
}

Channel&     Channel::operator = (const Channel &obj){
    this->_channelName            = obj._channelName;          
    this->_channelTopic           = obj._channelTopic;       
    this->_maxMembers             = obj._maxMembers;         
    this->_channelMembers         = obj._channelMembers;       
    this->_channelOperators          = obj._channelOperators;        
    this->_privateChannel         = obj._privateChannel;       
    this->_secretChannel          = obj._secretChannel;        
    this->_allowOutMessages       = obj._allowOutMessages;     
    this->_operatorsTopicControl  = obj._operatorsTopicControl;
    return (*this);
}

// * -getters :

std::string     Channel::getChannelName() const{
    return (_channelName);
}

std::string     Channel::getChannelTopic() const{
    return (_channelTopic);
}

std::vector<std::string>    Channel::getChannelMembers(){
    return (_channelMembers);
}

std::vector<std::string>    Channel::getChannelOperators(){
    return (_channelOperators);
}

unsigned int    Channel::getMaxMembers() const{
    return (_maxMembers);
}

bool            Channel::getPrivateChannelStatus() const{
    return (_privateChannel);
}
 
 
bool          Channel::getSecretChannelStatus() const{
    return (_secretChannel);
}

bool        Channel::getAllowOutMessageStatus() const{
    return (_allowOutMessages);
}

bool       Channel::getOperatorsTopicControlStatus()const{
    return (_operatorsTopicControl);
}


//* -setters- :



bool    Channel::setChannelName(std::string user, std::string channelName){
    if (checkSuperUserPermission(user)){
        _channelName = channelName;
        return (true);
    }
    return (false);
}

bool    Channel::setChannelTopic(std::string user, std::string channelTopic){
    if (checkSetTopicPermission(user)){
        _channelTopic = channelTopic;
        return (true);
    }
    return (false);
}

bool    Channel::setMaxMembers(std::string user, unsigned int maxChannelMember){
    if (checkSuperUserPermission(user)){
        _maxMembers = maxChannelMember;
        return (true);
    }
    return (false);
}

bool    Channel::setOperatorsTopicControl(std::string user, bool status){
    if (checkSuperUserPermission(user)){
        _operatorsTopicControl = status;
        return (true);
    }
    return (false);
}

bool    Channel::setPrivateChannel(std::string user, bool status){
    if (checkSuperUserPermission(user)){
        _privateChannel = status;
        return (true);
    }
    return (false);
}

bool    Channel::setSecretChannel(std::string user, bool status){
    if (checkSuperUserPermission(user)){
        _secretChannel = status;
        return (true);
    }
    return (false);
}

bool    Channel::setAllowOutMessage(std::string user, bool status){
    if (checkSuperUserPermission(user)){
        _allowOutMessages = status;
        return (true);
    }
    return (false);
}

//* -checkers- :

bool    Channel::checkSuperUserPermission(std::string user){
    
    std::vector<std::string>::const_iterator it;
    
    for(it = _channelOperators.begin(); it != _channelOperators.end(); it++){
        if(*it == user)
            return (true);
    }
    if (it == _channelOperators.end())
        return (false);
}

bool    Channel::checkMemberExistence(std::string memberName){
    std::vector<std::string>::const_iterator it;
    for(it = _channelMembers.begin(); it != _channelMembers.end(); it++){
        if (*it == memberName)
            return (true);
    }
    if (it == _channelMembers.end())
        return (false);
}

bool    Channel::checkSetTopicPermission(std::string user){
    std::vector<std::string>::const_iterator it;

    if(checkMemberExistence(user)){
        if (getOperatorsTopicControlStatus())
            if (checkSuperUserPermission(user))
                return (true);
    }
    return (false);
}

//* -Manage Channel- :

void    Channel::addUserToChannelOperators(std::string nickName){
    if (checkMemberExistence(nickName)){
        if (checkSuperUserPermission(nickName))
            return ;
        _channelOperators.push_back(nickName);
    }
}

void    Channel::deleteUserFromChannelOperators(std::string nickName){
    std::vector<std::string>::const_iterator it;
    if (checkMemberExistence(nickName)){
        for (it = _channelOperators.begin(); it != _channelOperators.end(); it++){
            if (*it == nickName){
                _channelOperators.erase(it);
                break;
            }
        }
    }
}