#include "utilities.h"

#include <stdint.h>
#include <atomic>


std::atomic<uint32_t> uid = 0;


int utilities::getUID()
{
	return uid++;
}
