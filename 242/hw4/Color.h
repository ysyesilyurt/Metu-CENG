#ifndef HW4_COLOR_H
#define HW4_COLOR_H

// engin : DO NOT MODIFY THIS FILE.

// Credits : https://stackoverflow.com/a/17469726/3227743

#include <ostream>

namespace Color {
    enum Code {
        // FG_BLACK = 30,
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_YELLOW   = 33,
        FG_BLUE     = 34,
        FG_MAGENTA  = 35,
        FG_CYAN     = 36,
        // FG_WHITE = 37,
        // SET_FG   = 38
        FG_DEFAULT  = 39,

        // BG_BLACK = 40,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_YELLOW   = 43,
        BG_BLUE     = 44,
        BG_MAGENTA  = 45,
        BG_CYAN     = 46,
        // BG_WHITE = 47,
        // SET_BG   = 48,
        BG_DEFAULT  = 49
    };

    // Environment
    static const Code STORM     = BG_MAGENTA;
    static const Code HILL      = FG_DEFAULT;

    // Players
    static const Code BERSERK   = FG_RED;
    static const Code TRACER    = FG_YELLOW;
    static const Code AMBUSHER  = FG_BLUE;
    static const Code PACIFIST  = FG_GREEN;
    static const Code DUMMY     = FG_DEFAULT;

    class Modifier {
        Code code;
    public:
        explicit Modifier(Code pCode) : code(pCode) { }
        friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

#endif //HW4_COLOR_H
