#pragma once
#include "Enums.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <queue>
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
        using TISValue_type_t = std::enable_if_t<std::is_same_v<std::decay_t<T>, value_type>>;

        /// <summary>
        /// 
        /// </summary>
        template <typename ...Args>
        static constexpr bool TISValue_type_v = (std::is_same_v<std::decay_t<Args>, value_type> && ...);

        /// <summary>
        /// 
        /// </summary>
        static inline std::queue<value_type> buffer_{};

        /// <summary>
        /// 
        /// </summary>
        static inline std::queue<value_type> bufferStatusBar_{};

        /// <summary>
        /// 
        /// </summary>
        static inline size_t fieldWidth_{ 100 };

        /// <summary>
        /// 
        /// </summary>
        static inline InputCommand activeCommand_{ InputCommand::NoCommand };

    private:

        /// <summary>
        /// 
        /// </summary>
        template <typename OutType
            , typename = TISValue_type_t<OutType>>
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
        template <typename SizeStr, typename Str, typename = TISValue_type_t<Str>>
        static value_type textAlign(SizeStr size, Str&& str);

    protected:

        /// <summary>
        /// 
        /// </summary>
        template <typename ...Args>
        static void pushToBuffer(Args&&... args);

        /// <summary>
        /// 
        /// </summary>
        template <typename ...Args>
        static void push(Args&&... args);

        /// <summary>
        /// 
        /// </summary>
        template <typename Delim, typename = std::enable_if_t<std::is_same_v<Delim, value_type::value_type>>>
        static value_type delimiter(Delim del);

        /// <summary>
        /// 
        /// </summary>
        template <typename...Args>
        static value_type bufferItem(Args&& ...args);

        /// <summary>
        /// 
        /// </summary>
        static void showHeader();

        /// <summary>
        /// 
        /// </summary>
        void readCommand();

        /// <summary>
        /// 
        /// </summary>
        virtual void functionLaunch() = 0;

        /// <summary>
        /// 
        /// </summary>
        virtual void showMenu() const = 0;

        /// <summary>
        /// 
        /// </summary>
        static void show();

        /// <summary>
        /// 
        /// </summary>
        static void showStatusBar();

        /// <summary>
        /// 
        /// </summary>
        InputCommand getActiveCommand() const;

        /// <summary>
        /// 
        /// </summary>
        void clearActiveCommand();

    public:

        /// <summary>
        /// 
        /// </summary>
        explicit Interface() = default;

        ///
        ///
        /// 
        virtual ~Interface();

        /// <summary>
        /// 
        /// </summary>
        void view();


    };

















    template <typename ...Args>
    void Interface
        ::pushToBuffer(Args&&... args) {

        constexpr bool isSame{ (std::is_same_v<Args
        , KHAS::Interface::value_type> && ...) };
        /// ¬ходные типы не соответствуют типу базы
        static_assert(isSame, "Input types do not match base type!");

        assert(isValidity(args...));

        (buffer_.push(std::forward<Args>(args)), ...);

    }

    template <typename ...Args>
    void Interface
        ::push(Args&&... args) {

        constexpr bool isSame{ (std::is_same_v<Args
        , KHAS::Interface::value_type> && ...) };
        /// ¬ходные типы не соответствуют типу базы
        static_assert(isSame, "Input types do not match base type!");

        assert(isValidity(args...));

        (bufferStatusBar_.push(std::forward<Args>(args)), ...);

    }

    template <typename ...Args>
    Interface::value_type Interface
        ::bufferItem(Args&&... args) {

        constexpr bool isSame{ TISValue_type_v<Args...> };
        /// ¬ходные типы не соответствуют типу базы
        static_assert(isSame, "Input types do not match base type!");

        std::stringstream ss;

        ss << "# ";
        auto size_field{ (fieldWidth_ - 4) / sizeof...(Args) };

        ( ss << ... << textAlign(size_field, std::forward<Args>(args)));

        size_t rest_width{ fieldWidth_ - ss.str().size() };
        if (rest_width > 0) ss << std::setw(rest_width) << std::setfill(' ');
        ss << " #";

        assert(ss.str().size() <= fieldWidth_);

        return ss.str();
    }

    template<typename OutType, typename T2>
    inline OutType Interface
        ::addLineTranslation(OutType&& str)
    {
        /// ¬ходные типы не соответствуют типу базы
        static_assert(std::is_same_v<OutType, value_type>, "Input types do not match base type!");

        return std::forward<OutType>(str) + " ";
    }

    template<typename First, typename ...Rest>
    inline bool Interface::isValidity(const First& str, const Rest & ...rest)
    {
        if constexpr (sizeof...(Rest) == 0) return true;
        return (str.size() <= fieldWidth_) && isValidity(rest...);
    }


    template <typename SizeStr, typename Str, typename T3>
    Interface::value_type Interface
        ::textAlign(SizeStr size, Str&& str) {

        std::stringstream ss;

        auto&& str_ss{ std::forward<Str>(str) };

        size_t even{ str_ss.size() % 2 };

        assert(str_ss.size() <= size);

        ss << std::setw((size + str_ss.size()) / 2)
            << str_ss << std::setw((size - str_ss.size()) / 2) << "";

        return ss.str();
    }

    template <typename Delim, typename T2>
    static Interface::value_type Interface
        ::delimiter(Delim del) {
        Interface::value_type str(fieldWidth_, del );
        str.front() = '#';
        str.back() = '#';
        return str;
    }
}
