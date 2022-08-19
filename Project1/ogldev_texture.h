#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <GL/glew.h>

// In the youtube series I've switch to stb_image
//#define USE_IMAGE_MAGICK

#ifdef USE_IMAGE_MAGICK
#include <ImageMagick-6/Magick++.h>
#endif

class Texture
{
public:
    Texture(GLenum TextureTarget, const std::string& FileName);

    // Should be called once to load the texture
    bool Load();

    // Must be called at least once for the specific texture unit
    void Bind(GLenum TextureUnit);

    void GetImageSize(int& ImageWidth, int& ImageHeight)
    {
        ImageWidth = m_imageWidth;
        ImageHeight = m_imageHeight;
    }

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
    int m_imageWidth = 0;
    int m_imageHeight = 0;
    int m_imageBPP = 0;
#ifdef USE_IMAGE_MAGICK
    Magick::Image m_image;
    Magick::Blob m_blob;
#endif
};


#endif  /* TEXTURE_H */
