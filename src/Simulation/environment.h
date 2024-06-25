#pragma once
#include "wall.h"
#include "particle.h"

#define window_factor 10

float to_gl_coordinates(float a){
    return a / window_factor - 1;
}

class Environment{
private:
    std::vector<Particle*> particles{};
    Vector<2> local_gravity{0.0, -9.81};
    double delta;

public:
    Environment(double tick_speed) :
    delta(tick_speed)
    {}

    void add_particle(Vector<2> position, Vector<2> velocity, double radius, double mass){
        particles.push_back(new Particle(position, velocity, radius, mass));
    }

    double overall_energy(){
        double energy = 0.0;
        for (Particle* particle : particles){
            energy += particle->mass * (particle->position * -local_gravity); // breaks without braces... don't touch
            energy += 0.5 * particle->mass * squared_magnitude(particle->velocity);
        }
        return energy;
    }
    double overall_impulse(){
        Vector<2> impulse(0.0, 0.0);
        for (Particle* particle : particles){
            impulse += particle->mass * particle->velocity;
        }
        return impulse.length();
    }

    void wall_collision(Axes axis, Particle& particle, double hit_distance, double frame_acceleration){
        double hit_age;
        if (local_gravity[axis] != 0)
            hit_age = -particle.velocity[axis] / (2 * frame_acceleration)
                    + sqrt(pow(particle.velocity[axis] / (2 * frame_acceleration), 2)
                    + hit_distance / frame_acceleration);
        else
            hit_age = hit_distance / particle.velocity[axis];

        particle.unmove_accelerate(local_gravity, hit_age);
        particle.velocity[axis] *= -1;
        particle.move_accelerate(local_gravity, hit_age);
    }

    void particle_collision(Particle& particle1, Particle& particle2){
        double distance1 = particle1.distance_from(particle2);
        particle1.unmove_accelerate(local_gravity, delta);
        particle2.unmove_accelerate(local_gravity, delta);
        double distance2 = particle1.distance_from(particle2);

        double velocity = abs(distance1 - distance2) / delta;
        double hit_in = (distance2 - particle1.radius - particle2.radius) / velocity;

        particle1.move_accelerate(local_gravity, hit_in);
        particle2.move_accelerate(local_gravity, hit_in);

        particle1.process_collision(particle2);

        particle1.move_accelerate(local_gravity, delta - hit_in);
        particle2.move_accelerate(local_gravity, delta - hit_in);
    }

    void compute_frame(){
        for (Particle* particle : particles) {
            // particle->move(delta);
            particle->move_accelerate(local_gravity, delta);
            if (particle->position[Y] - particle->radius <= 0)
                wall_collision(Y, *particle, particle->position[Y] - particle->radius, local_gravity[Y]);
            else if (particle->position[Y] + particle->radius >= 20)
                wall_collision(Y, *particle, particle->position[Y] + particle->radius - 20, -local_gravity[Y]);

            if (particle->position[X] - particle->radius <= 0)
                wall_collision(X, *particle, particle->position[X] - particle->radius, local_gravity[X]);
            else if (particle->position[X] + particle->radius >= 20)
                wall_collision(X, *particle, particle->position[X] + particle->radius - 20, -local_gravity[X]);
        }

        int n = particles.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++)
                if (particles[i]->collides_with(*particles[j]))
                    particle_collision(*particles[i], *particles[j]);

            /*
            for (Object* object : objects)
                if (particles[i]->collides_with(*object))
                    *particles[i] <=> *object;
                    */
        }
    }

    void render_frame(GraphicsUnit& graphics){
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        graphics.shader->activate();

        for (Particle* particle : particles)
            graphics.draw_circle(
                    to_gl_coordinates(particle->position[X]),
                    to_gl_coordinates(particle->position[Y]),
                    particle->radius / window_factor);

        glfwSwapBuffers(graphics.window);
        glfwPollEvents();
    }
};
