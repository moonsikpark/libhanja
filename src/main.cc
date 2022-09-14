// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include <iostream>
#include <map>

#include "hanja.h"

int main() {
  // todo:
  // https://namu.wiki/w/%EC%99%84%EC%84%B1%ED%98%95/%EC%A4%91%EB%B3%B5%20%ED%95%9C%EC%9E%90

  // todo: python script that parses various dictionary formats.
  std::string input;
  std::getline(std::cin, input);

  auto match = hanja::find_match(input);

  std::cout << match << std::endl;

  return 0;
}