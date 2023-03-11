/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandChecker.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:15:21 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 13:40:46 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

bool    Server::checkCommandValidation(std::string command) {
    if (command == "PASS")
        return (true);
    if (command == "NICK")
        return (true);
    if (command == "USER")
        return (true);
    if (command == "PONG")
        return (true);
    if (command == "JOIN")
        return (true);
    if (command == "INVITE")
        return (true);
    if (command == "PART")
        return (true);
    if (command == "NOTICE")
        return (true);
    if (command == "PRIVMSG")
        return (true);
    if (command == "QUIT")
        return (true);
    if (command == "KICK")
        return (true);
    if (command == "NAMES")
        return (true);
    if (command == "LIST")
        return (true);
    if (command == "TOPIC")
        return (true);
    if (command == "MODE")
        return (true);
    if (command == "BOT")
        return (true);
    return (false);
}