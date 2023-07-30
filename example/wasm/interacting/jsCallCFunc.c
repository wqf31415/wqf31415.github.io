#include <stdio.h>
#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
void sayHi()
{
  printf("Hi!\n");
}

EMSCRIPTEN_KEEPALIVE
int getInt()
{
  return 99;
}

EMSCRIPTEN_KEEPALIVE
float add(float a, float b)
{
  return a + b;
}

EMSCRIPTEN_KEEPALIVE
void greeting(char *name){
  printf("Hello, %s\n", name);
} 

int main() {
	printf("main...");
	return 0;
}