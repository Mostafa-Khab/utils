#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

void replace_dots(std::string& str)
{
  for(int i = 0; i < str.size(); ++i)
  {
    if(str[i] == '.')
      str[i] = '_';
  }
}

enum
{
  LINE_LENGTH = 18,
};

int main(int argc, const char* argv[])
{
  if(argc <= 1)
    return -1;

  for(int i = 1; i < argc; ++i)
  {
    std::string filepath = argv[i];
    std::ifstream file(filepath);

    if(!file.is_open())
    {
      std::cerr << "ERROR: Can't open file: " << filepath;
      continue;
    }

    size_t pos = file.tellg();
    file.seekg(0, std::ios::end);
    size_t total = file.tellg();
    file.seekg(pos);
    
    replace_dots(filepath);

    char buff[LINE_LENGTH + 1];
    std::cout << "const unsigned char " << filepath << "_data[] = {\n";
    while(true)
    {
      int reads = file.readsome(buff, LINE_LENGTH);
      if(!reads)
        break;

      std::cout << "    ";
      for(int i = 0; i < reads; ++i)
      {
        printf("0x%02X, ", (unsigned int)((unsigned char)buff[i]));
        /*std::cout << "0x" << std::setfill('0') 
                    << std::setw(2) << std::left << std::hex 
                    << (unsigned int)((unsigned char)buff[i]) << ", ";*/
      }
      std::cout << '\n';
    }

    std::cout << "};\n\n";
    std::cout << "const unsigned long long " << filepath << "_size = " << std::dec << total << ";\n\n\n";
  }

  return 0;
}
