#pragma once
#include <vector>
#include "../Math/arithmetics.h"
#include "../Math/vector.h"

class Particle{
private:
    Vector<2> velocity;
    Vector<2> position;
    double radius;
    double mass;

public:
    Particle(Vector<2> _position, Vector<2> _velocity, double _radius, double _mass) :
        position(_position[X], _position[Y]),
        velocity(_velocity[X], _velocity[Y]),
        radius(_radius),
        mass(_mass)
    {}

    void move(double time){
        position += time * velocity;
    }
    void unmove(double time){
        position -= time * velocity;
    }
    void move_accelerate(Vector<2> acceleration, double time){
        auto velocity_add = time * acceleration;
        position += time * (velocity + velocity_add / 2);
        velocity += velocity_add;
    }
    void unmove_accelerate(Vector<2> acceleration, double time){
        auto velocity_add = time * acceleration;
        position -= time * (velocity - velocity_add / 2);
        velocity -= velocity_add;
    }

    double distance_from(double x, double y){
        return sqrt(pow(position[X] - x, 2) + pow(position[Y] - y, 2));
    }
    double distance_from(Particle& particle2){
        return sqrt(pow(position[X] - particle2.position[X], 2)
             + pow(position[Y] - particle2.position[Y], 2));
    }
    double distance_from(Wall& wall){
        Vector<2> norm = -position * wall.anchor
                         / (position * wall.direction)
                         * wall.direction;

        return norm.length();
    }
    bool collides_with(Particle& particle2){
        return distance_from(particle2) < (radius + particle2.radius);
    }
    bool collides_with(Wall& wall){
        return distance_from(wall) < radius;
    }

    friend class Environment;

    friend std::ostream& operator<<(std::ostream&, Particle&);
    friend Vector<2> calculate_velocity_correction(Particle&, Particle&);

    void process_collision(Particle& p2){
        Vector<2> velcor1 = calculate_velocity_correction(*this, p2);
        Vector<2> velcor2 = calculate_velocity_correction(p2, *this);

        velocity -= velcor1;
        p2.velocity -= velcor2;
    }
};

Vector<2> calculate_velocity_correction(Particle& p1, Particle& p2){
    double    mass_term     = 2 * p2.mass / (p1.mass + p2.mass);
    Vector<2> velocity_term = (p1.velocity - p2.velocity);
    Vector<2> position_term = (p1.position - p2.position);

    double dot_term = velocity_term * position_term;
    dot_term /= squared_magnitude(position_term);
    Vector<2> velocity_correction = dot_term * position_term;
    velocity_correction *= mass_term;

    return velocity_correction;
}

std::ostream& operator<< (std::ostream& stream, Particle& particle){
    stream  << "Position: (X: " << particle.position[X]
            << " | Y: "         << particle.position[Y]
            << ")\n"
            << "Velocity: (X: " << particle.velocity[X]
            << " | Y: "         << particle.velocity[Y]
            << ")\n\n";
    return stream;
}

