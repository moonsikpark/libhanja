// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include <iostream>
#include <map>

#include "convert.h"
#include "dictionary.h"
#include "scoped_timer.h"

int main() {
  // todo:
  // https://namu.wiki/w/%EC%99%84%EC%84%B1%ED%98%95/%EC%A4%91%EB%B3%B5%20%ED%95%9C%EC%9E%90

  // todo: python script that parses various dictionary formats.

  // todo: 음이 중복된다면?

  hanja::dictionary::Dictionary dict("/root/libhanja/build/hanja.txt");

  std::string input;
  while (true) {
    std::getline(std::cin, input);
    ScopedTimer timer;

    std::string match =
        hanja::convert::Convert(input, dict).to_korean_with_hanja("<", ">");

    std::cout << match << std::endl;
    std::cout << timer.elapsed().count() << " msec elapsed." << std::endl;
  }

  return 0;
}
