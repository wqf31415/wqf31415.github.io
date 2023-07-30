#include <stdio.h>
#include <emscripten.h>

EM_JS(void, call_alert, (), {
	alert('Hello world');
	throw 'all done';
});

int main(){
	call_alert();
	return 0;
}