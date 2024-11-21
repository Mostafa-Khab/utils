#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <vector>

double f(long long n)
{
  if(!n || n == 1)
    return 1.0;

  return sqrt(2 * M_PI * n) * pow(n / exp(1), n);
}

long double c(long long a, long long b)
{
  assert(a >= b);
  return (double)f(a) / (f(b) * f(a - b));
}

struct vec2
{
  double x, y;
};


vec2 bezier(const std::vector<vec2>& points, double t)
{
  int n = points.size() - 1;
  vec2 r = {0};

  for(int i = 0; i <= n; ++i)
  {
    double coff = c(n, i) * pow(t, i) * pow(1 - t, n - i);
    r.x += coff * points[i].x;
    r.y += coff * points[i].y;
  }

  return r;
}

int main(int argc, const char* argv[])
{
  if(argc < 2)
  {
    printf("Usage: %s <n>", argv[0]);
    return 1;
  }

  int size = atoi(argv[1]);
  std::vector<vec2> points(size);
  
  for(int i = 0; i < size; ++i)
  {
    points[i].x = i;
    points[i].y = 3 * sin( i * M_PI / 2.0);
  }

  printf("\\draw ");
  for(int i = 0; i < size; ++i)
  {
    printf("(%f, %f)%s", points[i].x, points[i].y, (i == size - 1)? ";\n" : " -- ");
  }
  
  printf("\\draw ");
  for(int i = 0; i < size * 10; ++i)
  {
    vec2 r = bezier(points, i / 10.f / size);
    printf("(%f, %f)%s", r.x, r.y, (i == size * 10 - 1)? ";\n" : " -- ");
  }

  return 0;
}
