#pragma once

#include <iostream>
#include "memory.hpp"
#include "framework.hpp"

namespace csvm {
	typedef csvm::var_t (*extend_function_t)(const std::vector<csvm::var_t> &);
	struct building_function_t {
		struct frame_t {
			int pc = 0, ss = 0;
			csvm::building_function_t *function = nullptr;

//			frame_t(csvm::building_function_t *ptr_fun)
//			{
//				if (ptr_fun == nullptr)
//					throw std::runtime_error("constructing object csvm::stack error. the ptr = nullptr.");
//				function = ptr_fun;
//			}

			frame_t(csvm::building_function_t *ptr_fun, int ss) : ss(ss)
			{
				if (ptr_fun == nullptr)
					throw std::runtime_error("constructing object csvm::stack error. the ptr = nullptr.");
				function = ptr_fun;
			}
		};
		csvm::stack<std::uint32_t> ins_stack;
		std::vector<csvm::var_t> data_seg; //type and vec_ui32 (consists of ui32)
	};
}