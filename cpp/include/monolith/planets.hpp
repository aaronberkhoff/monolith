#pragma once
#include <string>

class Planet {
public:
    std::string name;
    double mu;
    double radius;
    double j2;
    double j3;
    int spice_id;

    Planet() = default;

    Planet(const std::string& name_,
           double mu_,
           double radius_,
           double j2_,
           double j3_,
           int spice_id_)
        : name(name_), mu(mu_), radius(radius_),
          j2(j2_), j3(j3_), spice_id(spice_id_) {}

    virtual ~Planet() = default;
};

// ---------------- Earth ----------------
class Earth : public Planet {
public:
    Earth()
        : Planet("Earth",
                 398600.4415,  // km^3/s^2
                 6378.1363,    // km
                 0.0010826267,
                 -0.0000025327,
                 399) {}
};

// ---------------- Moon ----------------
class Moon : public Planet {
public:
    Moon()
        : Planet("Moon",
                 4902.800066,  // km^3/s^2
                 1737.4,       // km
                 0.0002027,
                 0.0,
                 301) {}
};
