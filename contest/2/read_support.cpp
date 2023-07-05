#include "read_support.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
IMAGE_T read_ppm(){
  //read from stdin
  std::string header;
  int width, height, max_value;
  std::cin >> header >> width >> height >> max_value;
  if (header != "P6" && header != "P5") {
    std::cerr << header << std::endl;
    std::cerr << "  Error: not a PPM file" << std::endl;
    exit(1);
  }
  // printf("width: %d, heights %d, max_value: %d\n", width, height, max_value);
  // fflush(stdout);
  std::cin.get(); // Consume the whitespace character (newline) after the max_value

  IMAGE_T image(height, std::vector<double>(width));
  double rgb_value;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      cin>>rgb_value;
      image[i][j] = rgb_value/255.0;
    }
  }

  return image;
}
IMAGE_T read_ppm(const std::string &filename) {
  std::ifstream input(filename, std::ios::binary);
  if (!input.is_open()) {
    std::cerr << "Error: failed to open the file " << filename << std::endl;
    fflush(stderr);
    exit(1);
  }
  std::string header;
  int width, height, max_value;
  input >> header >> width >> height >> max_value;
  if (header != "P6" && header != "P5") {
    std::cerr << header << std::endl;
    std::cerr << "  Error: not a PPM file" << std::endl;
    exit(1);
  }
  // printf("width: %d, heights %d, max_value: %d\n", width, height, max_value);
  // fflush(stdout);
  input.get(); // Consume the whitespace character (newline) after the max_value

  IMAGE_T image(height, std::vector<double>(width));

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      unsigned char rgb_value;
      input.read(reinterpret_cast<char *>(&rgb_value), sizeof(unsigned char));
      image[i][j] = rgb_value / 255.0;
    }
  }
  input.close();
  return image;
}
void check(IMAGE_T mat) {
  // check if the mat is correct
  printf("checking height: %d, width: %d\n", (int)mat.size(),
         (int)mat[0].size());
  for (int i = 0; i < mat.size(); i++) {
    for (int j = 0; j < mat[0].size(); j++) {
      if (mat[i][j] < 0 || mat[i][j] > 1) {
        printf("mat[%d][%d] = %f\n", i, j, mat[i][j]);
        fflush(stdout);
        exit(-1);
      }
      if (mat[i][j] > 0.1) {
        putchar((int)'#');
      } else {
        putchar((int)' ');
      }
    }
    putchar((int)'\n');
  }
}