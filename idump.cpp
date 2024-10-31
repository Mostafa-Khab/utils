#include <fstream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#define BUFFER_SIZE 512 // bytes
#define OUTPUT_DIR "/tmp/"

unsigned char buffer[BUFFER_SIZE + 1] = {0};
unsigned char pixels[256 * 256] = {0};

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

  //will seg fault?
  stbi_write_jpg(("/tmp/" + filepath + ".sig.jpg").c_str(), 256, 256, 1, pixels, 90);
  printf("Signature save to %s\n", ("/tmp/" + filepath + ".sig.jpg").c_str());
    
  return 0;
}
