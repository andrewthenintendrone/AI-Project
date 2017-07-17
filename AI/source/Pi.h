#pragma once
#include <Windows.h>
#include <string>

// returns the value of Pi
float Pi()
{
    std::string circle =
        "                                                oooooooooooooooooooooooooooooooo                                                \n"
        "                                          oooooo                                oooooo                                          \n"
        "                                     ++ooo                                            ooo++                                     \n"
        "                                 ++oo``                                                  ``oo++                                 \n"
        "                              +oo``                                                          ``oo+                              \n"
        "                           +oo`                                                                  `oo+                           \n"
        "                        +oo`                                                                        `oo+                        \n"
        "                      /o.                                                                              .o/                      \n"
        "                    /o.                                                                                  .o//                   \n"
        "                  /o.                                                                                      ..o/                 \n"
        "                /o.                                                                                           .o/               \n"
        "              /o.                                                                                               .m              \n"
        "             :h                                                                                                  -o:            \n"
        "           :o-                                                                                                     -d           \n"
        "          :h                                                                                                        -o:         \n"
        "         d-                                                                                                           h:        \n"
        "       -o:                                                                                                             d-       \n"
        "      -d                                                                                                                :h      \n"
        "     -d                                                                                                                  :h     \n"
        "     M                                                                                                                    d-    \n"
        "    h:                                                                                                                     d-   \n"
        "   y/                                                                                                                       M   \n"
        "  .m                                                                                                                        /y  \n"
        "  M                                                                                                                          M  \n"
        " .m                                                                                                                          /y \n"
        " M                                                                                                                            M \n"
        "`N                                                                                                                            +s\n"
        "M                                                                                                                              M\n"
        "M                                                                                                                              M\n"
        "M                                                                                                                              M\n"
        "M                                                                                                                              M\n"
        "M                                                                                                                              M\n"
        "M                                                                                                                              o\n"
        "M                                                                                                                              M\n"
        "M                                                                                                                              M\n"
        "M                                                                                                                              M\n"
        "M                                                                                                                              M\n"
        "M                                                                                                                              M\n"
        "s+                                                                                                                            N`\n"
        " M                                                                                                                            M \n"
        " y/                                                                                                                          m. \n"
        "  M                                                                                                                          M  \n"
        "  y/                                                                                                                        m.  \n"
        "   M                                                                                                                       /y   \n"
        "   -d                                                                                                                     :h    \n"
        "    -d                                                                                                                    M     \n"
        "     h:                                                                                                                  d-     \n"
        "      h:                                                                                                                d-      \n"
        "       -d                                                                                                             :o-       \n"
        "        :h                                                                                                           -d         \n"
        "         :o-                                                                                                        h:          \n"
        "           d-                                                                                                     -o:           \n"
        "            :o-                                                                                                  h:             \n"
        "              m.                                                                                               .o/              \n"
        "               /o.                                                                                           .o/                \n"
        "                 /o..                                                                                      .o/                  \n"
        "                   //o.                                                                                  .o/                    \n"
        "                      /o.                                                                              .o/                      \n"
        "                        +oo`                                                                        `oo+                        \n"
        "                           +oo`                                                                  `oo+                           \n"
        "                              +oo``                                                          ``oo+                              \n"
        "                                 ++oo``                                                  ``oo++                                 \n"
        "                                     ++ooo                                            ooo++                                     \n"
        "                                          oooooo                                oooooo                                          \n"
        "                                                oooooooooooooooooooooooooooooooo                                                \n";

    float circumference = 0;
    float diameter = 0;
    for (auto c = circle.begin(); c != circle.end(); c++)
    {
        if (*c != ' ')
        {
            circumference++;
        }
        if (*c == '\n')
        {
            diameter++;
        }
    }
    return circumference / diameter;
}