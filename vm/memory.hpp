#pragma once

#include<unordered_map>
#include<stdexcept>
#include<iostream>
#include<cstring>
#include<cstdint>
#include<utility>
#include<vector>

namespace csvm {
	template<typename T>
    class stack final {
	public:
		std::vector<T> elm;

		template<typename...ArgsT>
		inline void push(ArgsT &&...args)
		{
			elm.emplace_back(std::forward<ArgsT>(args)...);
		}

		inline bool pop(std::size_t i = 1) noexcept
		{
			if (elm.size() >= i) {
                while(i--)
                    elm.pop_back();
                return true;
            }
            return false;
		}

		bool pop_to(std::size_t i)
		{
            std::size_t elm_s = elm.size();
			if (i >= elm_s)
				return false;
			for(; i < elm_s ; ++i)
				elm.pop_back();
			return true;
		}

		T &top(std::size_t i = 0)
		{
			std::size_t elm_s = elm.size();
			if (i >= elm_s)
				throw std::runtime_error("stack: underflow while visit top(int).");
			return elm[elm_s - 1 - i];
		}

		inline int size()
		{
			return elm.size();
		}

		inline int empty()
		{
			return elm.empty();
		}
	};
}