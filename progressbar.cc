#include <climits>
#include <iostream>
#include <sstream>
#include <string>

#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using std::cout, std::endl;
using std::string;

void draw_bar(string pre, string post, size_t value, size_t max_value, size_t bar_length) {
  std::ostringstream stream;
  stream << 100 * value / max_value << "%";
  string percentage = stream.str();
  size_t border = bar_length * value / max_value;
  float overflow = float((bar_length * value % max_value) / (bar_length)) / (max_value / bar_length);
  cout << pre;
  cout << "\e[48;2;100;255;100m\e[38;2;40;40;40m";
  for (size_t i = 0; i < bar_length; i++) {
    if (i == border) {
      int rb = 10 + int((100 - 10) * overflow);
      int g = 90 + int((255 - 90) * overflow);
      int fg = overflow > 0.5 ? 40 : 200;
      cout << "\e[48;2;" << rb << ";" << g << ";" << rb << "m\e[38;2;" << fg << ";" << fg << ";" << fg << "m";
    }
    else if (i == border + 1) {
      cout << "\e[48;2;10;90;10m\e[38;2;200;200;200m";
    }

    if ((i >= (bar_length - percentage.length()) / 2) && 
        (i <= (bar_length + percentage.length()) / 2)) {
      cout << percentage.substr(i - (bar_length - percentage.length()) / 2, 1);
    } else {
      cout << " ";
    }
  }
  cout << "\e[0m";
  cout << post;

  return;
}

void clear_bar(size_t length) {
  for (size_t i = 0; i < length - 1; i++) {
    cout << "";
  }

  return;
}

bool keep_running = true;

void sigint_handler(int sigspec) {
  keep_running = false;
}

int main(int argc, char *argv[]) {
  char *var = getenv("COLUMNS");
  int columns = strtol(var ? var : "80", NULL, 10);

  string pre = "Download: [";
  string post = "]";

  size_t max_value = 623414;
  size_t value = 0;

  srand(time(NULL));

  size_t bar_length = columns - (pre.length() + post.length()) - 1;
  bool first = true;
  signal(SIGINT, sigint_handler);
  cout << "\e[?25l";
  do {
    if (!first) {
      clear_bar(columns);
    }

    draw_bar(pre, post, value, max_value, bar_length);

    value += std::min(size_t(rand()) * 14000 / RAND_MAX, max_value - value);
    timespec t = { 0, long(200e6) };
    nanosleep(&t, NULL);
    first = false;
    cout.flush();
  } while (value < max_value && keep_running);
  cout << "\e[?25h";

  clear_bar(columns);
  draw_bar(pre, post, value, max_value, bar_length);

  cout << endl;

  return 0;
}
