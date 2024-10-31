#include <fstream>
#include <string>
#include <cmath>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#define BUFFER_SIZE 512 // bytes
#define OUTPUT_DIR "/tmp/"

unsigned char buffer[BUFFER_SIZE + 1] = {0};
unsigned char pixels[256 * 256] = {0};

std::string basename(const std::string& name)
{
  std::string r;
  int last = 0;
  for(int i = 0; i < name.size(); ++i) 
  {
    if(name[i] == '/')
      last = i + 1;
  }

  for(int i = last; i < name.size(); ++i)
  {
    r += name[i];
  }

  return r;
}

int main(int argc, const char* argv[])
{
  if(argc < 2)
  {
    fprintf(stderr, "Usage: %s [files]\n", argv[0]);
    return  1;
  }

  std::string filepath = argv[1];
  std::ifstream file(filepath);

  if(!file.is_open())
  {
    fprintf(stderr, "Failed to open file: %s\n", argv[1]);
    return  2; 
  }

  file.seekg(0, std::ios::end);
  size_t sz  = file.tellg();
  file.seekg(0, std::ios::beg);

  while(true)
  {
      size_t red = file.readsome((char*)buffer, BUFFER_SIZE);
      if(!red) break;

      for(size_t i = 0; i < red - 1; ++i)
      {
        unsigned char x = buffer[i];
        unsigned char y = buffer[i + 1];
        pixels[y * 256 + x] += 1;
      }
  }

  const float c = 256 / log(256);

  for(int i = 0; i < 256 * 256; ++i)
    pixels[i] = c * log(1 + pixels[i]);

  std::string out = (OUTPUT_DIR + basename(filepath) + ".sig.jpg");
  stbi_write_jpg(out.c_str(), 256, 256, 1, pixels, 90);

  perror("");

  printf("Signature save to %s\n", out.c_str());
    
  return 0;
}
