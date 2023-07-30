#include <stdio.h>
#include <emscripten.h>

int main(){
	emscripten_run_script("alert('hi')");
	return 0;
}