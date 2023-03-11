/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notLoggedIn.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:33:27 by bben-aou          #+#    #+#             */
/*   Updated: 2023/03/11 13:39:35 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server/server.hpp"

void    Server::userIsNotLoggedIn(User* user) const{
    buildResponseToSend(NULL, user, repliesMessage("451", user) + ":You have not registered");
}