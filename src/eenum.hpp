#ifndef EENUM_HPP
#define EENUM_HPP

#define eenum(identifier, underlying_type, ...)                                                    \
    enum class identifier : underlying_type                                                        \
    {                                                                                              \
        __VA_ARGS__                                                                                \
    };

#endif /* EENUM_HPP */
