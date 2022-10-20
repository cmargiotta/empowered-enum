#ifndef EENUM_HPP
#define EENUM_HPP

#include <algorithm>
#include <array>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_map>

#include "tools.hpp"

namespace eenum_
{
    consteval std::string_view extract_name(std::string_view definition)
    {
        if (std::find(definition.begin(), definition.end(), '=') != definition.end())
        {
            // = found
            auto to_remove = 0;
            for (to_remove = 0; to_remove < definition.size(); ++to_remove)
            {
                if (definition[to_remove] == ' ' || definition[to_remove] == '\t'
                    || definition[to_remove] == '=')
                {
                    return definition.substr(0, to_remove);
                }
            }
        }

        // No = found, nothing to do
        return definition;
    }

    template<typename Enum, size_t len, typename... T>
    consteval auto build_indexes(std::array<std::optional<std::underlying_type_t<Enum>>, len> values,
                                 T... identifiers_)
    {
        std::array<std::pair<Enum, std::string_view>, values.size()> data;
        const std::array<std::string_view, sizeof...(T)>             identifiers {identifiers_...};

        std::underlying_type_t<Enum> last_value = 0;

        for (auto i = 0; i < values.size(); ++i)
        {
            if (values[i])
            {
                last_value = *values[i];
            }

            data[i] = std::make_pair(static_cast<Enum>(last_value), identifiers[i]);
            last_value++;
        }

        return data;
    }

}// namespace eenum_

#define TO_NAME_STRING(definition) eenum_::extract_name(#definition),

#define eenum(identifier, underlying_type, ...)                                                     \
    consteval auto identifier##_values()                                                            \
    {                                                                                               \
        std::optional<underlying_type> __VA_ARGS__;                                                 \
        return std::array {__VA_ARGS__};                                                            \
    }                                                                                               \
    class identifier                                                                                \
    {                                                                                               \
        public:                                                                                     \
            enum class data : underlying_type                                                       \
            {                                                                                       \
                __VA_ARGS__                                                                         \
            };                                                                                      \
        private:                                                                                    \
            data data_;                                                                             \
                                                                                                    \
            static constexpr auto metadata = eenum_::build_indexes<identifier::data>(               \
                identifier##_values(), apply(TO_NAME_STRING, __VA_ARGS__) "");                      \
        public:                                                                                     \
            constexpr identifier()                                       = default;                 \
            constexpr identifier(identifier&& other) noexcept            = default;                 \
            constexpr identifier(const identifier& other)                = default;                 \
            constexpr identifier& operator=(identifier&& other) noexcept = default;                 \
            constexpr identifier& operator=(const identifier& other)     = default;                 \
            constexpr identifier(data data_): data_ {data_}                                         \
            {                                                                                       \
            }                                                                                       \
            constexpr identifier& operator=(data data_)                                             \
            {                                                                                       \
                this->data_ = data_;                                                                \
                return *this;                                                                       \
            }                                                                                       \
            constexpr identifier(std::string_view&& value)                                          \
                : data_ {std::find_if(metadata.begin(),                                             \
                                      metadata.end(),                                               \
                                      [&value](const auto& element)                                 \
                                      { return element.second == value; })                          \
                             ->first}                                                               \
            {                                                                                       \
            }                                                                                       \
            constexpr identifier& operator=(const std::string& value)                               \
            {                                                                                       \
                *this = identifier {value};                                                         \
                return *this;                                                                       \
            }                                                                                       \
            constexpr operator data()                                                               \
            {                                                                                       \
                return data_;                                                                       \
            }                                                                                       \
            constexpr auto to_string()                                                              \
            {                                                                                       \
                return std::find_if(metadata.begin(),                                               \
                                    metadata.end(),                                                 \
                                    [this](const auto& element) { return element.first == data_; }) \
                    ->second;                                                                       \
            }                                                                                       \
            constexpr operator std::string_view()                                                   \
            {                                                                                       \
                return to_string();                                                                 \
            }                                                                                       \
            constexpr bool operator==(const test& other) const                                      \
            {                                                                                       \
                return data_ == other.data_;                                                        \
            }                                                                                       \
            constexpr bool operator==(data value) const                                             \
            {                                                                                       \
                return data_ == value;                                                              \
            }                                                                                       \
            operator std::string()                                                                  \
            {                                                                                       \
                return std::string {to_string()};                                                   \
            }                                                                                       \
    };                                                                                              \
                                                                                                    \
    auto& operator<<(auto& stream, identifier value)                                                \
    {                                                                                               \
        stream << value.to_string();                                                                \
        return stream;                                                                              \
    }

#endif /* EENUM_HPP */
