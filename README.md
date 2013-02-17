# C++ port of [Esprima](https://github.com/ariya/esprima)

This is a JavaScript parser with a syntax tree that mostly conforms to the [SpiderMonkey parser API](https://developer.mozilla.org/en-US/docs/SpiderMonkey/Parser_API).
It was a quick port that I did in a couple of hours and doesn't yet support unicode or regular expression validation.

## Usage

    #include "esprima.h"
    #include <iostream>

    int main(int argc, char *argv[]) {
      try {
        esprima::Pool pool;
        esprima::Program *program = esprima::parse(pool, "print('hello');");
      } catch (const esprima::ParseError &error) {
        std::cout << "error: " << error.description << std::endl;
      }
      return 0;
    }
