// Copyright 2020 Your Name <your_email>

#include <experiment.hpp>

#include <experiment.hpp>
#include <chrono>
#include <config.hpp>
#include <stdexcept>
#include <string>

Experiment::Experiment(char *argBuffer, std::size_t argBufferSize)
    : buffer(argBuffer), bufferSize(argBufferSize), travelOrderName() {}

std::size_t Experiment::Run(Experiment::TravelOrder order) {
  if (!(order >= Direct && order <= Random))
    throw std::runtime_error("Invalid order");

  if (!buffer) throw std::runtime_error("Buffer not set");

  travelOrderName = TravelOrders[order];
  std::size_t commonDuration{0};
  [[maybe_unused]] char k;

  for (std::size_t i = 0; i < IterationsCount; ++i) {
    if (order == Direct) {
      std::size_t index{0};
      for (std::size_t j = 0; j < bufferSize; j += CacheLineSize) {
        index += CacheLineSize;
        auto start = std::chrono::high_resolution_clock::now();
        k = buffer[index];
        auto stop = std::chrono::high_resolution_clock::now();
        commonDuration +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start)
                .count();
      }
    } else if (order == Reverse) {
      std::size_t index{bufferSize};
      for (std::size_t j = 0; j < bufferSize; j += CacheLineSize) {
        index -= CacheLineSize;
        auto start = std::chrono::high_resolution_clock::now();
        k = buffer[index];
        auto stop = std::chrono::high_resolution_clock::now();
        commonDuration +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start)
                .count();
      }
    } else {
      std::size_t index{0};
      for (std::size_t j = 0; j < bufferSize; j += CacheLineSize) {
        index = (std::rand() % bufferSize) / CacheLineSize * CacheLineSize;
        auto start = std::chrono::high_resolution_clock::now();
        k = buffer[index];
        auto stop = std::chrono::high_resolution_clock::now();
        commonDuration +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start)
                .count();
      }
    }
  }
  return commonDuration / IterationsCount / (bufferSize / CacheLineSize);
}

std::string Experiment::GetTravelOrder() const { return travelOrderName; }

std::size_t Experiment::GetBufferSize() const { return bufferSize; }
