#include <sstream>
#include <iomanip>

#include "monolith/time/time.hpp"


extern "C" {
    #include "SpiceUsr.h"
}


namespace monolith {

    // Convert to SPICE ET (seconds past J2000)
    SpiceDouble TimeParameter::get_et() const {

        // Format microseconds as fractional seconds
        double total_seconds = second + microsecond;

        // Build UTC string in ISO 8601 format
        std::ostringstream ss;
        ss << std::setfill('0')
           << std::setw(4) << year << "-"
           << std::setw(2) << month << "-"
           << std::setw(2) << day << "T"
           << std::setw(2) << hour << ":"
           << std::setw(2) << minute << ":"
           << std::fixed << std::setprecision(6) << total_seconds;  // microseconds precision

        std::string utc_str = ss.str();

        // Call SPICE function
        SpiceDouble et;
        utc2et_c(utc_str.c_str(), &et);
        return et;

    };

} // namespace monolith
