//
// Created by Antareep Saha Roy on 07/07/25.
//
#include "Neutron/Renderer/Texture2D.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

namespace Neutron {

    Texture2D::Texture2D(const std::string& path) {
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
        if (!data) {
            std::cerr << "Failed to load texture: " << path << std::endl;
            return;
        }

        GLenum format = (m_Channels == 4) ? GL_RGBA : GL_RGB;

        glGenTextures(1, &m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    Texture2D::~Texture2D() {
        glDeleteTextures(1, &m_ID);
    }

    void Texture2D::Bind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }

}