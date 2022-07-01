#pragma once
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <type_traits>
#include <cassert>

namespace KHAS {
	class Interface {
	public:


		/// <summary>
		/// 
		/// </summary>
		using value_type = std::string;

	private:	

		/// <summary>
		/// 
		/// </summary>
		template <typename T>
		using TISValue_type = std::enable_if_t<std::is_same_v<T, value_type>>;

		/// <summary>
		/// 
		/// </summary>
		static inline std::stack<value_type> buffer_{};

		/// <summary>
		/// 
		/// </summary>
		static inline size_t fieldWidth_{ 120 };

		/// <summary>
		/// 
		/// </summary>
		static void init();

		/// <summary>
		/// 
		/// </summary>
		template <typename ...Args>
		static value_type bufferItem(Args&&... args);

		/// <summary>
		/// 
		/// </summary>
		template <typename OutType
			, typename = TISValue_type<OutType>>
		static OutType addLineTranslation(OutType&& str);

		/// <summary>
		/// 
		/// </summary>
		template <typename First, typename ...Rest>
		static bool isValidity(const First& str, const Rest& ... rest);

		/// <summary>
		/// 
		/// </summary>
		static bool isValidity() { return false;  }

		/// <summary>
		/// 
		/// </summary>
		static void initMenu();

	protected:

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="...args"></param>
		template <typename ...Args>
		static void push(Args&&... args);

	public:

		/// <summary>
		/// 
		/// </summary>
		explicit Interface();

		/// <summary>
		/// 
		/// </summary>
		void show();


	};

















	template <typename ...Args>
	void Interface
		::push(Args&&... args) {

		constexpr bool isSame{ (std::is_same_v<Args
		, KHAS::Interface::value_type> && ...) };
		/// ������� ���� �� ������������� ���� ����
		static_assert(isSame, "Input types do not match base type!");

		assert(isValidity(args...));

		(buffer_.push(std::forward<Args>(args)), ...);

	}

	template <typename ...Args>
	Interface::value_type Interface
		::bufferItem(Args&&... args) {

		constexpr bool isSame{ (std::is_same_v<Args
		, value_type> && ...) };
		/// ������� ���� �� ������������� ���� ����
		static_assert(isSame, "Input types do not match base type!");

		std::stringstream ss;
		(ss  <<  ... << addLineTranslation(std::forward<Args>(args)));
		std::cout << ss.str();

		return ss.str();
	}

	template<typename OutType, typename T2>
	inline OutType Interface
		::addLineTranslation(OutType&& str)
	{
		/// ������� ���� �� ������������� ���� ����
		static_assert(std::is_same_v<OutType, value_type>, "Input types do not match base type!");

		return std::forward<OutType>(str) + "\n";
	}

	template<typename First, typename ...Rest>
	inline bool Interface::isValidity(const First& str, const Rest & ...rest)
	{
		if constexpr (sizeof...(Rest) == 0) return true;
		return (str.size() <= (fieldWidth_ - 6)) && isValidity(rest...);
	}
}
