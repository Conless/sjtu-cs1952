#ifndef READ_SUPPORT
#define READ_SUPPORT
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<assert.h>
#include<filesystem>
#define IMAGE_T std::vector<std::vector<double>>

IMAGE_T read_ppm();
IMAGE_T read_ppm(const std::string &filename);
void check(IMAGE_T mat);
#endif