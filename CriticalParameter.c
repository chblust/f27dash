#include "CriticalParameter.h"

/**
 *Update a given parameter's state based on the given new value.
 * @param[in] parameter - the given parameter
 * @param[in] newValue - the given new value
 *
 */
void updateParameter( CriticalParameter* parameter, uint8_t newValue )
{
	parameter->value = newValue;

	// The logic speaks for itself, good luck
	if( parameter->state == NOMINAL )
	{
		if( parameter->errorDirection == ABOVE )
		{
			if( parameter->value >= parameter->errorThreshold )
			{
				parameter->state = ERROR;
			}
			else if( parameter->value >= parameter->warningThreshold )
			{
				parameter->state = WARNING;
			}
		}
		else // Error Direction must be BELOW
		{
			if( parameter->value <= parameter->errorThreshold )
			{
				parameter->state = ERROR;
			}
			else if( parameter->value <= parameter->warningThreshold )
			{
				parameter->state = WARNING;
			} 
		}
	}
	else if( parameter->state == ERROR )
	{
		if( parameter->errorDirection == ABOVE )
		{
			if( parameter->value <  (parameter->errorThreshold - parameter->histeresis) )
			{
				if( parameter->value >= parameter->warningThreshold )
				{
					parameter->state = WARNING;
				}
				else
				{
					parameter->state = NOMINAL;
				}
			}
		}
		else // Error direction must be BELOW
		{
			if( parameter->value > (parameter->errorThreshold + parameter->histeresis) )
			{
				if( parameter->value <= parameter->warningThreshold )
				{
					parameter->state = WARNING;
				}
				else
				{
					parameter->state = NOMINAL;
				}
			}
		}
	}
	else if( parameter->state == WARNING )
	{
		if( parameter->errorDirection == ABOVE )
		{
			if( parameter->value >= parameter->errorThreshold )
			{
				parameter->state = ERROR;
			}
			else if( parameter->value < (parameter->warningThreshold - parameter->histeresis) )
			{
				parameter->state = NOMINAL;
			}
		}
		else // Error direction must be below
		{
			if( parameter->value <= parameter->errorThreshold )
			{
				parameter->state = ERROR;
			}
			else if( parameter->value > (parameter->warningThreshold + parameter->histeresis) )
			{
				parameter->state = NOMINAL;
			}
		}
	}
}













