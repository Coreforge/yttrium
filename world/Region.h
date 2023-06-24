#pragma once

#include <vector>
#include <memory>
#include "worldObject.h"
namespace ytr{
	class Region{
		public:
			std::vector<worldObject*> objects;
			const char* key;
	};
}
