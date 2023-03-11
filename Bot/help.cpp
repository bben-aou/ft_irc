/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:46:18 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 13:46:49 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

void    Server::help(User *user){
    buildBotResponse("bot@help", user , YEL "        Welcome to the IRC server help guide d(#_#)b "  RESET);
    buildBotResponse("", user, GRN "                     ======== Available Commands : ========" RESET);
    buildBotResponse("", user,  RED "        JOIN - PART - LIST -  NAMES - TOPIC - QUIT - TOPIC - PRIVMSG - KICK - MODE - INVITE " RESET);
    buildBotResponse("", user, CYN "  -   JOIN  - This command is used to join a specific channel         \033[0m            |\033[33m  Example: JOIN #channelname" RESET);
    buildBotResponse("", user, CYN "  -   PART  - This command is used to leave a specific channel      \033[0m              | \033[33m Example: PART #channelname : reason - optional - \033[0m");
    buildBotResponse("", user, CYN "  -   LIST  - This command is used to get a list channels            \033[0m             | \033[33m Example: LIST #channelname \033[0m");
    buildBotResponse("", user, CYN "  -   NAME  - This command is used to get a list of users on channels    \033[0m         | \033[33m Example: NAMES #channelname \033[0m");
    buildBotResponse("", user, CYN "  -   TOPIC - This command is used to get or set the topic of channels     \033[0m       | \033[33m Example: TOPIC #channelname : topic - optional - \033[0m");
    buildBotResponse("", user, CYN "  -   QUIT  - This command is used to disconnect from the IRC server      \033[0m        | \033[33m Example: QUIT  :  reason - optional - \033[0m");
    buildBotResponse("", user, CYN "  - PRIVMSG - This command is used to send a private message to a user or channel \033[0m| \033[33m Example: PRIVMSG #channelname :Hello everyone! \033[0m");
    buildBotResponse("", user, CYN "  -   KICK  - This command is used to remove a user from a channel         \033[0m       | \033[33m Example: KICK #channelname username : reason - optional - \033[0m");
    buildBotResponse("", user, CYN "  -   MODE  - This command is used to set the mode of a channel or user     \033[0m      | \033[33m Example: MODE #channelname +-mode username \033[0m");
    buildBotResponse("", user, CYN "  -  INVITE - This command is used to invite a user to a channel            \033[0m      | \033[33m Example: INVITE username #channelname \033[0m");

}