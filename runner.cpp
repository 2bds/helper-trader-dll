#include "stdafx.h"
#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) 
{	
  // »нициализируем библиотеку
  testing::InitGoogleTest(&argc, argv);
  // «апускаем все тесты, прилинкованные к проекту
  return RUN_ALL_TESTS();
}