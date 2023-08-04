/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:28:53 by tkong             #+#    #+#             */
/*   Updated: 2023/08/04 13:25:01 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>
#include <iostream>
#include <string>

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

void PmergeMe::sort_vec(const std::vector<size_t> &args) {
	std::vector<size_t> rem;
	{
		std::vector<std::vector<size_t> > pairs;
		for (size_t i=0; i+1<args.size(); i+=2) {
			pairs.push_back(std::vector<size_t>());
			pairs.back().push_back(std::max(args[i], args[i+1]));
			pairs.back().push_back(std::min(args[i], args[i+1]));
		}
		for (std::vector<std::vector<size_t> >::iterator i=pairs.begin(); i!=pairs.end(); ++i) {
			for (std::vector<std::vector<size_t> >::iterator j=i; ++j!=pairs.end(); ) {
				if (*i > *j) { std::swap(*i, *j); }
			}
		}
		for (size_t i=0; i<pairs.size(); ++i) {
			vec.push_back(pairs[i][0]);
			rem.push_back(pairs[i][1]);
		}
		if ((args.size()&1)==1) { rem.push_back(args.back()); }
	}
	nextnum(true);
	if (rem.size()!=0) { vec.insert(vec.begin(), rem[0]); }
	for (size_t i=1; i<rem.size(); ) {
		size_t num = nextnum();
		for (size_t j=std::min(i+num, rem.size()), k=i; --j>=i; ++k) {
			vec.insert(std::upper_bound(vec.begin(), vec.begin()+j+k, rem[j]), rem[j]);
			if (vec[j+k]==rem[j]) { --k; }
		}
		i+=num;
	}
}
void PmergeMe::sort_lst(const std::vector<size_t> &args) {
	std::list<size_t> rem;
	{
		std::list<std::list<size_t> > pairs;
		for (size_t i=0; i+1<args.size(); i+=2) {
			pairs.push_back(std::list<size_t>());
			pairs.back().push_back(std::max(args[i], args[i+1]));
			pairs.back().push_back(std::min(args[i], args[i+1]));
		}
		for (std::list<std::list<size_t> >::iterator i=pairs.begin(); i!=pairs.end(); ++i) {
			for (std::list<std::list<size_t> >::iterator j=i; ++j!=pairs.end(); ) {
				if (*i > *j) { std::swap(*i, *j); }
			}
		}
		for (size_t i=pairs.size(); i--; ) {
			lst.push_back(pairs.front().front()), pairs.front().pop_front();
			rem.push_back(pairs.front().front()), pairs.front().pop_front();
			pairs.pop_front();
		}
		if ((args.size()&1)==1) { rem.push_back(args.back()); }
	}
	nextnum(true);
	if (rem.size()!=0) { lst.insert(lst.begin(), rem.front()), rem.pop_front(); }
	size_t cnt = 1;
	while (rem.size()!=0) {
		size_t num = std::min(nextnum(), rem.size());
		cnt += num;
		std::list<size_t> buf;
		while (num--) { buf.push_front(rem.front()), rem.pop_front(); }
		std::list<size_t>::iterator end = lst.begin();
		for (size_t i=0; i<cnt; ++i) { ++end; }
		cnt += buf.size();
		while (buf.size()!=0) {
			std::list<size_t>::iterator ins = std::upper_bound(lst.begin(), end, buf.front());
			lst.insert(ins, buf.front()), buf.pop_front();
			if (ins==end) { --end; }
		}
	}
}
PmergeMe::u64 PmergeMe::gettime() const {
	static timeval tv;
	return (!gettimeofday(&tv, NULL) ? tv.tv_sec*1000000+tv.tv_usec : 0);
}
size_t PmergeMe::nextnum(bool clear) const {
	static std::vector<size_t> num;
	if (clear) { num.clear(), num.push_back(1), num.push_back(0); }
	else { num.push_back(num[num.size()-2]*2+num[num.size()-1]); }
	return num.back();
}

void PmergeMe::run(int ac, char **av) {
	std::string arg;
	for (size_t i=1; i<(size_t)ac; ++i) {
		arg += av[i];
		arg += ' ';
	}
	bool ing = false;
	std::vector<size_t> args;
	for (size_t i=0; i<arg.size(); ++i) {
		if (std::isdigit(arg[i])) {
			if (!ing) { ing = true; args.push_back(size_t()); }
			args.back() = (args.back()<<1)+(args.back()<<3)+(arg[i]-'0');
		} else if (std::isspace(arg[i])) {
			ing = false;
			if (args.size()!=0 && args.back()==0) {
				throw std::invalid_argument("Invalid argument");
			}
		} else {
			throw std::invalid_argument("Invalid argument");
		}
	}
	std::vector<size_t> tmp(args);
	std::cout << "Before: ";
	for (size_t i=0; i<tmp.size(); ++i) std::cout<<tmp[i]<<' '; std::cout<<std::endl;
	sort(tmp.begin(), tmp.end());
	std::cout << "After:  ";
	for (size_t i=0; i<tmp.size(); ++i) std::cout<<tmp[i]<<' '; std::cout<<std::endl;
	{
		PmergeMe::u64 elapse_vec, elapse_lst;
		elapse_vec = gettime();
		sort_vec(args);
		elapse_lst = gettime();
		elapse_vec = elapse_lst - elapse_vec;
		sort_lst(args);
		elapse_lst = gettime() - elapse_lst;
		std::cout << "Time to process a range of " << vec.size()
			<< " elements with std::vector : " << elapse_vec << " us" << std::endl;
		std::cout << "Time to process a range of " << lst.size()
			<< " elements with std::list : " << elapse_lst << " us" << std::endl;
	}
	std::vector<size_t>::iterator it_tmp=tmp.begin(), it_vec=vec.begin();
	std::list<size_t>::iterator it_lst=lst.begin();
	while (it_tmp!=tmp.end()) {
		if (*it_tmp!=*it_vec) {
			throw std::runtime_error("Inequality: std::vector");
		} else if (*it_tmp!=*it_lst) {
			throw std::runtime_error("Inequality: std::list");
		}
		++it_tmp, ++it_vec, ++it_lst;
	}
}
