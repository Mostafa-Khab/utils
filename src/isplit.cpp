#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <cstdio>
#include <string>
#include <memory>

#define OUPUT_DIR "/tmp/"

void Image_split(unsigned char* result, unsigned char* pixels, int x, int y, int c, int bit)
{
  for(int i = 0; i < y; ++i)
    for(int j = 0; j < x; ++j)
      for(int k = 0; k < c; ++k)
        result[(i * x + j) * c + k] = ((pixels[(i * x + j) * c + k] >> bit) & 1) << 7;
}

void Image_save(unsigned char* data, int w, int h, int c, const char* filepath) {
    const char* ext = &filepath[strlen(filepath) - 3];

    if(strcmp(ext, "png") == 0) {
       stbi_write_png(filepath, w, h, c, data, w * c);
    } else if(strcmp(ext, "jpg") == 0 || strcmp(&filepath[strlen(filepath) - 4], "jpeg") == 0) {
       stbi_write_jpg(filepath, w, h, c, data, 90);
    } else if(strcmp(ext, "tga")) {
       stbi_write_tga(filepath, w, h, c, data);
    } else if(strcmp(ext, "bmp")) {
       stbi_write_bmp(filepath, w, h, c, data);
    } else {
       fprintf(stderr, "No valid image format\n");
    }
}

int main(int argc, const char* argv[])
{
  if(argc < 2)
  {
    fprintf(stderr, "Usage: %s <image> <requested bit>", argv[0]);
    return -1;
  }

  std::string filepath    = argv[1];
  std::string file_no_ext(filepath.begin(), filepath.end() - 4);
  std::string ext(filepath.end() - 4, filepath.end());

  printf("%s\n", filepath.data());
  printf("%s\n", file_no_ext.data());
  printf("%s\n", ext.data());

  int bit              = argc > 2? atoi(argv[2]) : -1;

  int x, y, c;
  unsigned char* pixels = stbi_load(filepath.data(), &x, &y, &c, 0);

  std::unique_ptr<unsigned char> result(new unsigned char[x * y * c]);

  if(bit != -1)
  {
    Image_split(result.get(), pixels, x, y, c, bit);
    Image_save(result.get(), x, y, c, (OUPUT_DIR + file_no_ext + "." + std::to_string(bit) + ext).c_str());
    return 0;
  }



  return 0;
}
