#ifndef CONDITION_H
#define CONDITION_H

enum ConditionType {
    HUMIDITY,
    TEMPERATURE,
    WATER,
    TIME_BASED
};

/**!
 * @struct Condition
 * @brief Represents a conditon interface to control a relay
 * 
 * This `struct` provides variables to control a relay in different condition
*/
struct Condition
{
    ConditionType type;
    float humidThreshold;
    float temperatureThreshold;
    float moistureThreshold;
    unsigned long duration; //Minutes
    unsigned long startTime; //24hour HHMM format
};


#endif //CONDITON_H