/**
@file myBT.h

Esta es la cabecera que debe ser incluida desde
fuera de la librería. Cumple la regla ODR.

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _MYBT_H_
#define _MYBT_H_

// ODR
#include "nlohmann/json.hpp"
#include "Common.h"
#include "For.h"
#include "ForTime.h"
#include "Parallel.h"
#include "Selector.h"
#include "SelectorProbability.h"
#include "Sequence.h"
#include "Action.h"
#include "Condition.h"
#include "While.h"
#include "Semaphore.h"
#include "And.h"
#include "Or.h"
#include "Subject.h"
#include "Actions/Aborted.h"
#include "Actions/Completed.h"
#include "Actions/Failed.h"
#include "Actions/Running.h"
#include "Actions/Wait.h"
#include "Conditions/AlwaysTrue.h"
#include "Conditions/AlwaysFalse.h"

#endif

