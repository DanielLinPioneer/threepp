#ifndef THREEPP_CUBE_TEXTURE_HPP
#define THREEPP_CUBE_TEXTURE_HPP
#include "threepp/textures/Texture.hpp"
namespace threepp {

    class CubeTexture: public Texture {
    public:
        CubeTexture(std::optional<Image> image = std::nullopt, int mapping = CubeReflectionMapping, int wraps = ClampToEdgeWrapping, int wrapt = ClampToEdgeWrapping,
            int magFilter = LinearFilter,int minFilter = LinearFilter, int format = RGBAFormat,  int type = UnsignedByteType,
            unsigned anisotropy = 1, int encoding =  LinearEncoding) :
        Texture(image, mapping, wraps, wrapt, magFilter, minFilter, format, type, anisotropy, encoding)
        {
            isCubeTexture = true;
        }
        static std::shared_ptr<CubeTexture> CubeTexture::create() {

           return std::shared_ptr<CubeTexture>(new CubeTexture());
        }
         
    };

}

#endif
