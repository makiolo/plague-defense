#ifndef _STEERINGBEHAVIOURS_H_
#define _STEERINGBEHAVIOURS_H_

// API
#if defined(_WIN32) || defined(WIN32)
#ifdef SteeringBehaviours_EXPORTS
#define STEERINGBEHAVIOURS_API __declspec(dllexport)
#else
#ifndef SteeringBehaviours_STATIC
#define STEERINGBEHAVIOURS_API __declspec(dllimport)
#else
#define STEERINGBEHAVIOURS_API
#endif
#endif
#else
#define STEERINGBEHAVIOURS_API
#endif

#include <myMath/h/myMath.h>

// ODR
struct SteeringOutput;
class Agent;
class Steering;
class SteeringFlee;
class SteeringSeek;
class SteeringPursue;
class SteeringAlign;
class SteeringEvade;
class SteeringSeparation;

#include "SteeringOutput.h"
#include "Agent.h"
#include "Steering.h"
#include "SteeringFlee.h"
#include "SteeringSeek.h"
#include "SteeringPursue.h"
#include "SteeringAlign.h"
#include "SteeringEvade.h"
#include "SteeringSeparation.h"

//typedef char* String;
typedef std::string String;

#endif // _STEERINGBEHAVIOURS_H_
