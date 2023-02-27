#pragma once

namespace Sapphire
{
    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void Bind() const {}
        virtual void Unbind() const {}
    };
}