//
// Joe Gamble - 15/04/2020
// Inspiration from TheCherno, instantiable particle system attempt
//
/*
#include "gamelib/Components/ParticleComponent.h"

#include <cmath>


ParticleSystem::ParticleSystem(Scene &currentscene, Vector3& pos, float radius)
{
    currentscene.getObjectPool()->addEmptyObject(pos);
}


ParticleSystem::ParticleSystem()
{
    m_ParticlePool.resize(1000);
}

void ParticleSystem::onUpdate(ASGE::GameTime &gt)
{
    for(auto& particle : m_ParticlePool)
    {
        if(!particle.active)
        {
            continue;
        }

        if(particle.life_remaining <= 0.0F)
        {
            particle.active = false;
            continue;
        }

        particle.life_remaining -= float(gt.deltaInSecs());
        particle.pos.operator+(particle.velocity.operator*(float(gt.deltaInSecs())));
        particle.rotation += 0.01F * float(gt.deltaInSecs());
    }
}

void ParticleSystem::onRender(ASGE::Renderer &renderer)
{
    for(auto& current : m_ParticlePool)
    {
        renderer.renderSprite(*current.particleSprite.getSprite());
    }
}

void ParticleSystem::emit(const ParticleProps &particleProps)
{

    std::mt19937 engine;
    std::uniform_int_distribution<std::mt19937::result_type> dis;

    Particle& particle = m_ParticlePool[m_PoolIndex];

    particle.particleSprite.getSprite()->colour(ASGE::COLOURS::BLUE);
    particle.active = true;
    particle.pos = particleProps.pos;
    particle.rotation = Random::getNumber(engine, dis) * 2.0F * float(M_PI);

    //Velocity
    particle.velocity = particleProps.velocity;
    particle.velocity.x = particleProps.vel_variation.x * (Random::getNumber(engine, dis) - 0.5F);
    particle.velocity.y = particleProps.vel_variation.y * (Random::getNumber(engine, dis) - 0.5F);

    //Color
    particle.color_begin = particleProps.color_begin;
    particle.color_end = particleProps.color_end;

    particle.life_time = particleProps.life_time;
    particle.life_remaining = particleProps.life_time;
    particle.size_begin = particleProps.size_begin + particleProps.size_variation *
(Random::getNumber(engine, dis) - 0.5F); particle.size_end = particleProps.size_end;

    m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();

}
*/