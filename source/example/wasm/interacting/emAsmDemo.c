#include <stdio.h>
#include <emscripten.h>

int main(){
	EM_ASM({
		alert('Hello world');
		throw 'all done';
	});
	return 0;
}