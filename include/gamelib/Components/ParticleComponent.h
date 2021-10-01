/*
//
// Joe Gamble - 15/04/2020
// Inspiration from TheCherno, instantiable particle system attempt
//

#ifndef MYNETGAME_PARTICLECOMPONENT_H
#define MYNETGAME_PARTICLECOMPONENT_H

#define _USE_MATH_DEFINES
#include "../apps/ASGEGame/Managers/SceneManager.hpp"
#include "gamelib/Random.h"

#include <cmath>


struct ParticleProps
{
    Vector3 pos;
    Vector3 velocity;
    Vector2 vel_variation;
    Vector4 color_begin;
    Vector4 color_end;

    float size_begin;
    float size_end;
    float size_variation;

    float life_time = 1.0F;
};

class ParticleSystem : public SceneObject
{
public:
    ParticleSystem();

    ParticleSystem(ParticleSystem const&) = delete;
    ParticleSystem& operator=(ParticleSystem const&) = delete;
    ParticleSystem(ParticleSystem&&)                 = delete;
    ParticleSystem& operator=(ParticleSystem&&) = delete;

    void onUpdate(ASGE::GameTime& gt);
    void onRender(ASGE::Renderer& renderer);
    void emit(const ParticleProps& particleProps);

private:
    struct Particle
    {
        Vector3 pos = {0, 0, 0};
        Vector3 velocity = {0, 0, 0};
        Vector4 color_begin = {0, 0, 0, 0};
        Vector4 color_end  = {0, 0, 0, 0};

        float rotation = 0.0F;
        float size_begin = 0.0F;
        float size_end = 0.0F;

        float life_time = 1.0F;
        float life_remaining = 0.0F;

        bool active = false;

        SpriteComponent particleSprite;
    };
    std::vector<Particle> m_ParticlePool;
    uint32_t m_PoolIndex = 999;
    //std::unique_ptr<ASGE::SHADER_LIB::Shader> m_ParticleShader;
};

#endif //MYNETGAME_PARTICLECOMPONENT_H

*/
