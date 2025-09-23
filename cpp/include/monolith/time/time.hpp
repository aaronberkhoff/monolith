#pragma once

extern "C" {
    #include "SpiceUsr.h"
}

namespace monolith {

    class TimeParameter {
        public:
            int year;
            int month;
            int day;
            int hour;
            int minute;
            int second;
            double microsecond;

            // Default constructor
            TimeParameter()
                : year(2025), month(1), day(1), hour(0), minute(0), second(0), microsecond(0.0) {}

            TimeParameter(int year_, int month_, int day_, int hour_, int minute_ ,int second_, double microsecond_ = 0.0)
                : year(year_), month(month_), day(day_), hour(hour_), minute(minute_), second(second_), microsecond(microsecond_) {}

            SpiceDouble get_et() const;
    };

} // namespace monolith
