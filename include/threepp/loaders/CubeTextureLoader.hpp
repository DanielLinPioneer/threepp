
#ifndef THREEPP_CUBETEXTURELOADER_HPP
#define THREEPP_CUBETEXTURELOADER_HPP

#include "threepp/textures/Texture.hpp"
#include "threepp/textures/CubeTexture.hpp"

#include <filesystem>
#include <memory>
using namespace std;
namespace threepp {

    class CubeTextureLoader {

    public:

        CubeTextureLoader() {};

        std::shared_ptr<CubeTexture> load(const list<filesystem::path>& filePath, bool flipY = true); 

        ~CubeTextureLoader() {}

    };

}// namespace threepp

#endif //THREEPP_CUBETEXTURELOADER_HPP
