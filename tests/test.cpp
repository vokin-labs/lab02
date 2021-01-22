// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <experiment.hpp>
#include <scheduler.hpp>
#include <config.hpp>
#include <iostream>

TEST(Example, EmptyTest) {
  Scheduler scheduler(CacheSizes);
  scheduler.WarnUp();
  scheduler.RunAll(Experiment::TravelOrder::Direct);
  scheduler.PrintResult(std::cout);

  std::cout << std::endl;

  scheduler.WarnUp();
  scheduler.RunAll(Experiment::TravelOrder::Reverse);
  scheduler.PrintResult(std::cout);

  std::cout << std::endl;

  scheduler.WarnUp();
  scheduler.RunAll(Experiment::TravelOrder::Random);
  scheduler.PrintResult(std::cout);
  EXPECT_TRUE(true);
}
