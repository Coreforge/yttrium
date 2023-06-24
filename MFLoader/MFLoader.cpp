#include "MFLoader.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>

using namespace ytr;

void MFLoader::loadManifest(const char* path){
    //const char* manifest = readTextFile(path);
    std::vector<std::string> manifest = readTextFile(path);
    std::string manifestStr; // c++ strings are easier to work with here
    int last = 0;   // start of the last line
    //std::stringstream manifestStream(manifest);
    //printf("opened Manifest. Content: %s\n",manifest);
    for(int l = 0; l < manifest.size(); l++){
        printf("Processing line %d: %s\n",l,manifest[l].c_str());
        for(int i = 0; i < manifest[l].length(); i++){
            if(manifest[l][i] == '\n' || manifest[l][i] == '#'){
                // reached end of line or found a '#', indicating a comment, before finding a colon , ignoring this line
                printf("reached eol or comment\n");
                break;
            }
            if(manifest[l][i] == ':'){
                printf("reached colon\n");
                std::string keyword = manifest[l].substr(0,i);  // get the keyword substring
                if(keyword == "shader"){
                    size_t next = manifest[l].find(' ',i+2);    // skipping colon and space
                    if(next == std::string::npos){
                        // invalid line, missing id and path
                        printf("Invalid line: %s:%d\n\t%s\n\tMissing shader ID and path to shader manifest\n",path,l,manifest[l].c_str());
                    }
                    std::string id = manifest[l].substr(i+2,next-i-2);  // -2 because the string starts 2 characters after i. The better way would be to find the first non-whitespace character, but that's more work
                    size_t start = manifest[l].find('"',next);
                    size_t end = manifest[l].find('"',start+1); // starting one character later so it doesn't just find the same one twice
                    std::string shaderMF = manifest[l].substr(start+1,end-start-1);
                    printf("start: %d end: %d\n",start,end);
                    printf("Loading Shader ID: %s Path: %s\n",id.c_str(),(getFileFolder(std::string(path))+shaderMF).c_str());
                    loadShaderManifest((getFileFolder(std::string(path))+shaderMF),id);

                } else {
                    printf("Manifest Parser: unknown keyword %s\n",keyword.c_str());
                }
            }
        }
    }
    //free((void*)manifest);
}

void MFLoader::loadShaderManifest(std::string path, std::string id){
    std::vector<std::string> manifest = readTextFile(path.c_str());
    for(int i = 0; i < manifest.size(); i++){
        // look for api type first
        size_t comment = manifest[i].find('#');
        size_t end = manifest[i].find_first_of('{');
        if(end == std::string::npos || end > comment){
            // found no valid '{', so this line is irrelavant
            continue;
        }
        end = manifest[i].find_last_not_of(' ',end);
        size_t start = manifest[i].find_first_not_of(' ');
        if(start == std::string::npos || start > comment){
            // nothing relevant here
            continue;
        }
    }
}

std::string MFLoader::getFileFolder(std::string path){
    size_t last = path.find_last_of('/');
    return path.substr(0,last+1);
}

std::vector<std::string> MFLoader::readTextFile(const char* path){
    std::ifstream fstream(path,std::ifstream::in);
    std::vector<std::string> lines;
    if(fstream.is_open() && fstream.good()){
        std::stringstream sstr;
        //sstr << fstream.rdbuf();
        while(!fstream.eof()){
            std::string tmp;
            std::getline(fstream,tmp);
            lines.emplace_back(tmp);
        }
        fstream.close();
    } else {
        printf("MFLoader: can't open file \"%s\"",path);
    }
    return lines;
}
