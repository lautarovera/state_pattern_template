/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef HEADER_H
#define HEADER_H
    
#include "stdio.h"
#include "stdlib.h"
#include "project.h"
#include "serial.h"
    
typedef enum State
{
  PositionA,
  PositionB,
  PositionC,
  PositionD
}State;

typedef enum Input
{
  Unknown,
  Reset,
  Forward,
  Backward
}Input;

/* LUT with transitions */
extern const State lut[4][4];

/* Pointer to function to assign to the transition functions */
typedef void (*const StateOut)();

State current_state;
Input current_input;

extern StateOut fsm_update;



#endif
/* [] END OF FILE */
