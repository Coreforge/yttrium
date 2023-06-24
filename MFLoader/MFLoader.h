#pragma once
#include <vector>
#include <string>

namespace ytr{

	class MFLoader{
		// Loads resources from general manifest files
		public:
			void loadManifest(const char* path);

		private:
			void loadShaderManifest(std::string path, std::string id);
			std::string getFileFolder(std::string path);    // returns the folder the specified file is in
			std::vector<std::string> readTextFile(const char* path); // loads a text file and returns its contents. In a separate function for easier support of other platforms

	};
}
