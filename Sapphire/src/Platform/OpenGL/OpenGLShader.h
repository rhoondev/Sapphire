#pragma once

#include "Sapphire/Renderer/Shader.h"

#include <string>

namespace Sapphire
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string vertexSrc, const std::string fragmentSrc);
        ~OpenGLShader();

        void Bind() const;
        void Unbind() const;
    private:
        uint32_t m_RendererID;
    };
}

