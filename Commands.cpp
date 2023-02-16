/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blind-eagle <blind-eagle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 02:53:28 by blind-eagle       #+#    #+#             */
/*   Updated: 2023/02/16 10:15:10 by blind-eagle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Server.hpp"

//! - Commands :

void    Server::quit(User* user,std::string message){
    // - first version - :
    std::string quitMessage;

    if (message.empty())
        quitMessage = "Alert : " + user->getNickName() + " Is quitting the server now!" 
        ;
    else 
        quitMessage = message;
    std::cout << quitMessage << std::endl;
}



