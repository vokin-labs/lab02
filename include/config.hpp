//
// Created by vokin-labs on 21.01.2021.
//

#ifndef LAB02_CONFIG_HPP
#define LAB02_CONFIG_HPP
#include <vector>

const std::size_t IterationsCount = 1000;
const std::size_t CacheLineSize = 64;
const std::vector<std::size_t> CacheSizes = {128 * 1024, 1024 * 1024, 3 * 1024 * 1024};
#endif  // LAB02_CONFIG_HPP
