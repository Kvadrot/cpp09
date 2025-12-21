/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:51:49 by ufo               #+#    #+#             */
/*   Updated: 2025/12/21 17:23:03 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <cctype>

#ifndef PMERGE_HPP
#define PMERGE_HPP

class PmergeMe {
    private:

    public:
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe operator= (const PmergeMe& other);
        ~PmergeMe();
        
        void sortMe();
        
};

#endif