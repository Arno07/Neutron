#pragma once

namespace Neutron {

    class Renderer {
    public:
        static void Init();
        static void Shutdown();

        static void SetClearColor(float r, float g, float b, float a);
        static void Clear();
    };

}