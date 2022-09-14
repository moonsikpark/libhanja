// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include <map>

#include "dictionary.h"
#include "hanja.h"

int main() {
  std::string input{
      "金川에 사는 金氏네 金屬題品은 品質이 좋아서 金錢깨나 받겠어."};

  hanja::find_match(input);

  return 0;
}