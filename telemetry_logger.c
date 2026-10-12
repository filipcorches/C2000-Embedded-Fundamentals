#include <stdint.h>
#define VECTOR_LENGTH 5U

struct SensorNode 
{
    int32_t raw_reading;
    float filtered_value;
    uint16_t error_flags;
};

void processing(struct SensorNode *node, int16_t raw_input);
void update_vector(int16_t *vector, int16_t signal, uint16_t *i);

int main(void) 
{
    
    int16_t history_buffer[VECTOR_LENGTH] = {0}; 
    uint16_t head_index = 0;                     
    struct SensorNode my_sensor;               
    
    int16_t simulated_signal = 1000;            

    while(1) {
        // Simulate the sensor changing over time
        simulated_signal += 500;
        if (simulated_signal > 4095) 
        {
            simulated_signal = 500; 
        }

        // Process the raw reading 
        processing(&my_sensor, simulated_signal);

        // Save the reading into circular history buffer
        update_vector(history_buffer, simulated_signal, &head_index);

    }
}

void update_vector(int16_t *vector, int16_t signal, uint16_t *i)
{
    vector[*i] = signal;
    (*i)++;
    if (*i==VECTOR_LENGTH)
        *i = 0;
}

void processing(struct SensorNode *node, int16_t raw_input)
{
    node->raw_reading = (int32_t)raw_input;

    // Convert raw value into 0-3.3V
    node->filtered_value = (float)raw_input * (3.3f / 4095.0f);

    // if voltage bigger than 2.5V, get a warning
    if (node->filtered_value > 2.5f) 
    {
        node->error_flags |= (1U << 1); // Turn ON bit 1 (Warning)
    } 

    else 
    {
        node->error_flags &= ~(1U << 1); // Turn OFF bit 1
    }
}