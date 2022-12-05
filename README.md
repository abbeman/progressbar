# Progressbar

Simple, graphical progressbar in C++ using 24 bit color in the terminal using
raw ANSI control codes. For more information, see `man console_codes`. Make
sure your terminal can handle 24 bit colors. Tested in [xterm] and [st] terminals.

![Progressbar Demo](./progressbar.apng)

[st]: http://st.suckless.org

# Build

Make sure you have [cmake] and [ninja] or [make] installed, as well as some C++
compiler. Tested with [g++-11] and [clang-14].

[cmake]: https://cmake.org/cmake/help/latest/
[ninja]: https://ninja-build.org/manual.html
[make]: https://www.gnu.org/software/make/manual/html_node/index.html
[g++-11]: https://gcc.gnu.org/onlinedocs/gcc-11.3.0/gcc/
[clang-14]: https://clang.llvm.org/docs/UsersManual.html

## Build with ninja

```shell
$ pwd
/home/user/progressbar
$ mkdir build
$ cd build
$ cmake -G Ninja ..
$ ninja
$ ./progressbar
```

## Build with make

```shell
$ pwd
/home/user/progressbar
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./progressbar
```

# Run

The progressbar program will look at the environment variable `COLUMNS` to
determine how wide your current terminal is, you can either set it manually or
use the `resize` tool which is part of the [xterm] package in your favourite
distro to set up the environment from the current size of your terminal
emulator:

[xterm]: https://invisible-island.net/xterm/

```
$ eval $(resize)
$ ./progressbar             # Will fill the entire terminal width.
$ COLUMNS=40 ./progressbar  # Make a short progressbar.
```
