#include <stdint.h>
#include <selector.h>

void __stack_chk_fail(void){}
void __stack_chk_guard(void){}

int main(void)
{
	uint8_t sel = get_selector();
    return sel;
}
