#ifndef CRITICAL_PARAMETER_H
#define CRITICAL_PARAMETER_H

#include <stdint.h>

typedef enum
{
	NOMINAL,
	WARNING,
	ERROR
} ErrorState;

typedef enum
{
	ABOVE,
	BELOW
} ErrorDirection;

typedef struct
{
	// The current value of the parameter
	uint8_t value;

	// The threshold at which the parameter enters the error state
	uint8_t errorThreshold;

	// The threshold at which the parameter enters the warning state
	uint8_t warningThreshold;

	// The histeresis associated with the parameter's thresholds
	uint8_t histeresis;

	// The current state of the parameter
	ErrorState state;

	// The direction the parameter's value must be past the thresholds to trigger them
	ErrorDirection errorDirection;
} CriticalParameter;

void updateParameter( CriticalParameter* parameter, uint8_t newValue );

#endif // CRITICAL_PARAMETER_H