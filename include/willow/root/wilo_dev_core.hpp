#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<optional>
#include<map>
#include<functional>
#include<assert.h>
#include<algorithm>
#include<memory>
#include<atomic>
#include<set>
#include "logr.hpp"
#include "WiloConfig.h"
#include "wilo_APICodes.hpp"

#define WILO_ASSERT(result) assert(result==true)


namespace wlo {


	template<typename T>
	using BorrowedPointer = std::weak_ptr<T>;

	template<typename T>
	using UniquePointer = std::unique_ptr<T>;

	 template<typename T, typename ... Args>
	constexpr UniquePointer<T> CreateUniquePointer(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)... );
	}

	template<typename T>
	using SharedPointer = std::shared_ptr<T>;

	 template<typename T, typename ... Args>
	constexpr SharedPointer<T> CreateSharedPointer(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)... );
	}
    template<typename T>
    using Ref = std::reference_wrapper<T>;


	using byte = std::byte;

	using std::max;
	using std::min;
	using std::cout;
	using std::endl;
	using std::vector;
	using std::set;
	using std::map;

}
