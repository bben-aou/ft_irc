/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:17:29 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 13:40:55 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

// ^  -------- Get the supposed command word or the message line (part/quit/privmsg/topic...) --------

std::string     Server::getCommandInLine(std::string line, int *posPointer) const{
    std::string     word;
    while (line[*posPointer] == ' ')
        *posPointer += 1;
    if (line[*posPointer] == ':'){
        *posPointer += 1;
        while (line[*posPointer] != '\r' && line[*posPointer]){
            word +=  line[*posPointer];
            *posPointer += 1;
        }
    }
    else{
        while (line[*posPointer] != ' ' && line[*posPointer] != '\r' && line[*posPointer]){
            word +=  line[*posPointer];
            *posPointer += 1;
        }
    }
    return (word);
}

// ^  -------- Get the arguments of command (user/join/list/names/mode...) --------


std::vector<std::string>     Server::getVectorOfArgs(std::string line, int* posPointer){
    std::string tmpStr;
    std::vector<std::string> argsVector;

    while (line[*posPointer] != '\r' && line[*posPointer])
    {
        tmpStr.clear();
        while (line[*posPointer] == ' ' ||  line[*posPointer] == ',')
            *posPointer += 1;
        if (line[*posPointer] == ':')
            return (argsVector);
        while (line[*posPointer] != ' ' && line[*posPointer] != ','  && line[*posPointer] != '\r' && line[*posPointer]){
            tmpStr = tmpStr + line[*posPointer];
            *posPointer = *posPointer + 1;
        }
        argsVector.push_back(tmpStr);
    }
    return (argsVector);
}