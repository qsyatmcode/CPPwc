#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <tuple>
#include <algorithm>
#include <string_view>

long get_length(const char* fileName);
long get_lines(const char* fileName);
long get_words(const char* fileName);
long get_chars(const char* fileName);
long wc(const char* fileName, std::string_view option);
std::tuple<long, long, long> wc_default(const char* fileName);

int main(int argc, char* argv[]) {

  if(argc < 2) { // if no one argument
    std::cout << "No enough arguments" << std::endl;
    return EXIT_FAILURE;
  }

  if(argc < 3) { // if only one argument
    const char* fileName { argv[1] }; // if only filename, without options
    auto results = wc_default(fileName);
    std::cout << "\t" << std::get<0>(results)
        << "\t" << std::get<1>(results)
        << "\t" << std::get<2>(results)
        << "\t" << fileName << std::endl;
    return EXIT_SUCCESS;
  }

  std::string_view option { argv[1] };
  const char* fileName { argv[2] };

  long result = { 0 };
  if ((result = wc(fileName, option)) == -1) {
    std::cout << "Invalid option" << std::endl;
  }

  std::cout << "\t" << result << "\t" << fileName << std::endl;

  return EXIT_FAILURE;
}


long wc(const char* fileName, std::string_view option) {
  if (option == "-c") {
    return get_length(fileName);
  } else if(option == "-l") {
    return get_lines(fileName);
  } else if(option == "-w") {
    return get_words(fileName);
  } else if(option == "-m") {
    return get_chars(fileName);
  }
  else {
    return -1;
  }
}

std::tuple<long, long, long> wc_default(const char* fileName) {
  return { get_length(fileName), get_lines(fileName), get_words(fileName) };
}

long get_length(const char* fileName) {
  std::ifstream file(fileName, std::ios::binary | std::ios::ate);
  return file.tellg();
}

long get_lines(const char* fileName) {
  std::ifstream file(fileName, std::ios::in);
  long result { 0 };
  for(std::string line; std::getline(file, line); result++);
  return result;
}

long get_words(const char* fileName) {
  std::ifstream file(fileName, std::ios::in);
  std::istream_iterator<std::string> in{file}, end;
  return std::distance(in, end);
}

long get_chars(const char* fileName) {
  std::ifstream file(fileName, std::ios::in);
  long result { 0 };
  for(std::string line; std::getline(file, line);) {
    result += line.length();
  }
  return result;
}