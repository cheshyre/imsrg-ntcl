// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/coupling/wigner_symbols.h"

#include <fstream>
#include <string>
#include <vector>

#include "fmt/core.h"

#include "imsrg/error.h"
#include "imsrg/openmp_runtime.h"
#include "imsrg/quantum_numbers/coupling/jj.h"
#include "imsrg/quantum_numbers/coupling/m_jj.h"

#include "tests/catch.hpp"

using imsrg::JJ;
using imsrg::M_JJ;

struct StoredWig3JSymbols {
  std::size_t number_of_symbols = 1;
  std::vector<JJ> jj1s = std::vector<JJ>(number_of_symbols, JJ(0));
  std::vector<JJ> jj2s = std::vector<JJ>(number_of_symbols, JJ(0));
  std::vector<JJ> jj3s = std::vector<JJ>(number_of_symbols, JJ(0));
  std::vector<M_JJ> m_jj1s = std::vector<M_JJ>(number_of_symbols, M_JJ(0));
  std::vector<M_JJ> m_jj2s = std::vector<M_JJ>(number_of_symbols, M_JJ(0));
  std::vector<M_JJ> m_jj3s = std::vector<M_JJ>(number_of_symbols, M_JJ(0));
  std::vector<double> values = std::vector<double>(number_of_symbols, 0.0);
};

struct StoredCGSymbols {
  std::size_t number_of_symbols = 1;
  std::vector<JJ> jj1s = std::vector<JJ>(number_of_symbols, JJ(0));
  std::vector<JJ> jj2s = std::vector<JJ>(number_of_symbols, JJ(0));
  std::vector<JJ> jj3s = std::vector<JJ>(number_of_symbols, JJ(0));
  std::vector<M_JJ> m_jj1s = std::vector<M_JJ>(number_of_symbols, M_JJ(0));
  std::vector<M_JJ> m_jj2s = std::vector<M_JJ>(number_of_symbols, M_JJ(0));
  std::vector<M_JJ> m_jj3s = std::vector<M_JJ>(number_of_symbols, M_JJ(0));
  std::vector<double> values = std::vector<double>(number_of_symbols, 0.0);
};

struct StoredWig6JSymbols {
  std::size_t number_of_symbols = 1;
  std::vector<JJ> jj1s = std::vector<JJ>(number_of_symbols, JJ(0));
  std::vector<JJ> jj2s = std::vector<JJ>(number_of_symbols, JJ(0));
  std::vector<JJ> jj3s = std::vector<JJ>(number_of_symbols, JJ(0));
  std::vector<JJ> jj4s = std::vector<JJ>(number_of_symbols, JJ(0));
  std::vector<JJ> jj5s = std::vector<JJ>(number_of_symbols, JJ(0));
  std::vector<JJ> jj6s = std::vector<JJ>(number_of_symbols, JJ(0));
  std::vector<double> values = std::vector<double>(number_of_symbols, 0.0);
};

static StoredWig3JSymbols ReadWig3JSymbolsFromFile();
static StoredCGSymbols ReadCGSymbolsFromFile();
static StoredWig6JSymbols ReadWig6JSymbolsFromFile();

TEST_CASE("Test calculated Wigner 3J symbols relative to stored values.") {
  const auto store = ReadWig3JSymbolsFromFile();

  imsrg::OpenMPRuntime::InitializeRuntime();
  const auto& wigner_engine = imsrg::WignerSymbolEngine::GetInstance();

  std::vector<double> values(store.number_of_symbols, 0.0);

  SECTION("single-threaded") {
    for (std::size_t i = 0; i < store.number_of_symbols; i += 1) {
      values[i] = wigner_engine.Wigner3J(store.jj1s[i], store.jj2s[i],
                                         store.jj3s[i], store.m_jj1s[i],
                                         store.m_jj2s[i], store.m_jj3s[i]);
    }
  }

  SECTION("multi-threaded") {
#pragma omp parallel for
    for (std::size_t i = 0; i < store.number_of_symbols; i += 1) {
      values[i] = wigner_engine.Wigner3J(store.jj1s[i], store.jj2s[i],
                                         store.jj3s[i], store.m_jj1s[i],
                                         store.m_jj2s[i], store.m_jj3s[i]);
    }
  }

  for (std::size_t i = 0; i < store.number_of_symbols; i += 1) {
    INFO("i = " << i);
    REQUIRE(values[i] == Approx(store.values[i]).margin(1e-5));
  }
}

TEST_CASE("Test calculated CG symbols relative to stored values.") {
  const auto store = ReadCGSymbolsFromFile();

  imsrg::OpenMPRuntime::InitializeRuntime();
  const auto& wigner_engine = imsrg::WignerSymbolEngine::GetInstance();

  std::vector<double> values(store.number_of_symbols, 0.0);

  SECTION("single-threaded") {
    for (std::size_t i = 0; i < store.number_of_symbols; i += 1) {
      values[i] = wigner_engine.ClebschGordan(store.jj1s[i], store.jj2s[i],
                                              store.jj3s[i], store.m_jj1s[i],
                                              store.m_jj2s[i], store.m_jj3s[i]);
    }
  }

  SECTION("multi-threaded") {
#pragma omp parallel for
    for (std::size_t i = 0; i < store.number_of_symbols; i += 1) {
      values[i] = wigner_engine.ClebschGordan(store.jj1s[i], store.jj2s[i],
                                              store.jj3s[i], store.m_jj1s[i],
                                              store.m_jj2s[i], store.m_jj3s[i]);
    }
  }

  for (std::size_t i = 0; i < store.number_of_symbols; i += 1) {
    INFO("i = " << i);
    REQUIRE(values[i] == Approx(store.values[i]).margin(1e-5));
  }
}

TEST_CASE("Test calculated Wigner 6j symbols relative to stored values.") {
  const auto store = ReadWig6JSymbolsFromFile();

  imsrg::OpenMPRuntime::InitializeRuntime();
  const auto& wigner_engine = imsrg::WignerSymbolEngine::GetInstance();

  std::vector<double> values(store.number_of_symbols, 0.0);

  SECTION("single-threaded") {
    for (std::size_t i = 0; i < store.number_of_symbols; i += 1) {
      values[i] =
          wigner_engine.Wigner6J(store.jj1s[i], store.jj2s[i], store.jj3s[i],
                                 store.jj4s[i], store.jj5s[i], store.jj6s[i]);
    }
  }

  SECTION("multi-threaded") {
#pragma omp parallel for
    for (std::size_t i = 0; i < store.number_of_symbols; i += 1) {
      values[i] =
          wigner_engine.Wigner6J(store.jj1s[i], store.jj2s[i], store.jj3s[i],
                                 store.jj4s[i], store.jj5s[i], store.jj6s[i]);
    }
  }

  for (std::size_t i = 0; i < store.number_of_symbols; i += 1) {
    INFO("i = " << i);
    REQUIRE(values[i] == Approx(store.values[i]).margin(1e-5));
  }
}

StoredWig3JSymbols ReadWig3JSymbolsFromFile() {
  const std::size_t number_of_symbols = 100000;
  StoredWig3JSymbols symbols = {number_of_symbols};

  std::string filename = "tests/data/wigner/list_3j.txt";
  std::ifstream input_file(filename);
  imsrg::CheckForError(!input_file.is_open(),
                       fmt::format("Unable to open file: {}\n", filename));

  int jj1 = 0;
  int jj2 = 0;
  int jj3 = 0;
  int m_jj1 = 0;
  int m_jj2 = 0;
  int m_jj3 = 0;
  for (std::size_t i = 0; i < number_of_symbols; i++) {
    input_file >> jj1 >> jj2 >> jj3 >> m_jj1 >> m_jj2 >> m_jj3 >>
        symbols.values[i];
    symbols.jj1s[i] = JJ(jj1);
    symbols.jj2s[i] = JJ(jj2);
    symbols.jj3s[i] = JJ(jj3);
    symbols.m_jj1s[i] = M_JJ(m_jj1);
    symbols.m_jj2s[i] = M_JJ(m_jj2);
    symbols.m_jj3s[i] = M_JJ(m_jj3);
  }

  return symbols;
}

StoredCGSymbols ReadCGSymbolsFromFile() {
  const std::size_t number_of_symbols = 100000;
  StoredCGSymbols symbols = {number_of_symbols};

  std::string filename = "tests/data/wigner/list_cg.txt";
  std::ifstream input_file(filename);
  imsrg::CheckForError(!input_file.is_open(),
                       fmt::format("Unable to open file: {}\n", filename));

  int jj1 = 0;
  int jj2 = 0;
  int jj3 = 0;
  int m_jj1 = 0;
  int m_jj2 = 0;
  int m_jj3 = 0;
  for (std::size_t i = 0; i < number_of_symbols; i++) {
    input_file >> jj1 >> jj2 >> jj3 >> m_jj1 >> m_jj2 >> m_jj3 >>
        symbols.values[i];
    symbols.jj1s[i] = JJ(jj1);
    symbols.jj2s[i] = JJ(jj2);
    symbols.jj3s[i] = JJ(jj3);
    symbols.m_jj1s[i] = M_JJ(m_jj1);
    symbols.m_jj2s[i] = M_JJ(m_jj2);
    symbols.m_jj3s[i] = M_JJ(m_jj3);
  }

  return symbols;
}

StoredWig6JSymbols ReadWig6JSymbolsFromFile() {
  const std::size_t number_of_symbols = 100000;
  StoredWig6JSymbols symbols = {number_of_symbols};

  std::string filename = "tests/data/wigner/list_6j.txt";
  std::ifstream input_file(filename);
  imsrg::CheckForError(!input_file.is_open(),
                       fmt::format("Unable to open file: {}\n", filename));

  int jj1 = 0;
  int jj2 = 0;
  int jj3 = 0;
  int jj4 = 0;
  int jj5 = 0;
  int jj6 = 0;
  for (std::size_t i = 0; i < number_of_symbols; i++) {
    input_file >> jj1 >> jj2 >> jj3 >> jj4 >> jj5 >> jj6 >> symbols.values[i];
    symbols.jj1s[i] = JJ(jj1);
    symbols.jj2s[i] = JJ(jj2);
    symbols.jj3s[i] = JJ(jj3);
    symbols.jj4s[i] = JJ(jj4);
    symbols.jj5s[i] = JJ(jj5);
    symbols.jj6s[i] = JJ(jj6);
  }

  return symbols;
}
