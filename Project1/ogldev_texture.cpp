#include <iostream>
#include "ogldev_util.h"
#include "ogldev_texture.h"
#include "3rdparty/stb_image.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
}


bool Texture::Load()
{
#ifdef USE_IMAGE_MAGICK

    try {
        m_image.read(m_fileName);
        m_image.write(&m_blob, "RGBA");
    }
    catch (Magick::Error& Error) {
        std::cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
        return false;
    }

#else // STB image

    stbi_set_flip_vertically_on_load(1);

    unsigned char* image_data = stbi_load(m_fileName.c_str(), &m_imageWidth, &m_imageHeight, &m_imageBPP, 0);

    if (!image_data) {
        printf("Can't load texture from '%s' - %s\n", m_fileName.c_str(), stbi_failure_reason());
        exit(0);
    }

    printf("Width %d, height %d, bpp %d\n", m_imageWidth, m_imageHeight, m_imageBPP);

#endif

    glGenTextures(1, &m_textureObj);
    glBindTexture(m_textureTarget, m_textureObj);
    if (m_textureTarget == GL_TEXTURE_2D) {
#ifdef USE_IMAGE_MAGICK
        glTexImage2D(m_textureTarget, 0, GL_RGBA, m_image.columns(), m_image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
#else
        switch (m_imageBPP) {
        case 1:
            glTexImage2D(m_textureTarget, 0, GL_RED, m_imageWidth, m_imageHeight, 0, GL_RED, GL_UNSIGNED_BYTE, image_data);
            break;

        case 3:
            glTexImage2D(m_textureTarget, 0, GL_RGB, m_imageWidth, m_imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
            break;

        case 4:
            glTexImage2D(m_textureTarget, 0, GL_RGBA, m_imageWidth, m_imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
            break;

        default:
            NOT_IMPLEMENTED;
        }
#endif
    }
    else {
        printf("Support for texture target %x is not implemented\n", m_textureTarget);
        exit(1);
    }
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(m_textureTarget, 0);
#ifndef USE_IMAGE_MAGICK
    stbi_image_free(image_data);
#endif

    return true;
}

void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);
}
