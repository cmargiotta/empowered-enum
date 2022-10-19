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

#define eenum(identifier, underlying_type, ...)                                                    \
    enum class identifier : underlying_type                                                        \
    {                                                                                              \
        __VA_ARGS__                                                                                \
    };                                                                                             \
    consteval auto identifier##_values()                                                           \
    {                                                                                              \
        using underlying = std::optional<underlying_type>;                                         \
        underlying __VA_ARGS__;                                                                    \
        return std::array {__VA_ARGS__};                                                           \
    }                                                                                              \
    struct identifier##_metadata                                                                   \
    {                                                                                              \
            static constexpr auto identifiers = eenum_::build_indexes<identifier>(                 \
                identifier##_values(), apply(TO_NAME_STRING, __VA_ARGS__) "");                     \
    };                                                                                             \
    constexpr auto identifier##_to_string(identifier value)                                        \
    {                                                                                              \
        return std::find_if(identifier##_metadata::identifiers.begin(),                            \
                            identifier##_metadata::identifiers.end(),                              \
                            [value](const auto& element) { return element.first == value; })       \
            ->second;                                                                              \
    }                                                                                              \
    constexpr auto string_to_##identifier(std::string_view&& value)                                \
    {                                                                                              \
        return std::find_if(identifier##_metadata::identifiers.begin(),                            \
                            identifier##_metadata::identifiers.end(),                              \
                            [&value](const auto& element) { return element.second == value; })     \
            ->first;                                                                               \
    }

#endif /* EENUM_HPP */
