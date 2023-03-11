/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendBootResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:50:21 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 13:50:53 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

void    Server::buildBotResponse(std::string prefix, User const * recipient, std::string data) const{
    std::string  dataToSend;
    dataToSend = prefix + data;
    sendResponse(recipient->getPollFds(), dataToSend);
}