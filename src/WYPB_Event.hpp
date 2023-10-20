/*      
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements.  See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership.  The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.  You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.    
*/


#ifndef _WYPB_EVENT_HPP_
#define _WYPB_EVENT_HPP_

#include <ctime>
#include "WYPB_Player.hpp"

class WYPB_Player; /* Forward declaration. */

/** Struct for easy retrieval of WYPB_Event member attributes. 
*/
struct s_event_members {
    std::time_t time; /**< Time of the event in time_t format. The WYPB_Event class DOES NOT MODIFY THIS VALUE at all. So what you set is what you get when you retrieve it. Hence implementations can set it to whatever they want depending on their game model. It can be ignored, or in a step-wise simulation it can be a simple: step 1 set to 1, step 2 set to 2, etc.*/
    unsigned long type; /**< The type of WYPB_Event. Ignore or use depends on implmentation. */
    unsigned long subtype; /**< The subtype of WYPB_Event. Ignore or use depends on implmentation. */
    WYPB_Player* parent; /**< The parent that generated the WYPB_Event. Ignore or use depends on implmentation. */
};


/** Implements the WYPB_Event object. 
*/
class WYPB_Event
{
public:
    
    /** Constructor. 
     * Throws an integer exception if initialisation encounters an error. Note that this does not include throwing errors caught by the C++ std::exception class. Those must be caught seperately.   
     * 
     * Example: \n
     * try { \n
     *  WYPB_Event event_obj; \n
     * } catch (int e) { \n
     *  cout << "Exception: " << e << "\n"; \n
     * }
     * 
     * \param p_time Optional parameter to set the time of the event in time_t format. The WYPB_Event class DOES NOT MODIFY THIS VALUE at all. So what you set is what you get when you retrieve it from the object. Hence implementations can set it to whatever they want depending on their game model. It can be ignored, or in a step-wise simulation it can be a simple: step 1 set to 1, step 2 set to 2, etc.
     * \param p_type Optional parameter to set the type of WYPB_Event. Defaults to 0.
     * \param p_subtype Optional parameter to set the subtype of WYPB_Event. Defaults to 0.
     * \param p_parent Optional parameter to set the parent of WYPB_Event. Defaults to NULL.
    */
    WYPB_Event(const std::time_t p_time=0, const unsigned long p_type=0, const unsigned long p_subtype=0, WYPB_Player* const p_parent=NULL) noexcept;

    /** Returns the time set for the event.
     * 
     * \return time_t set for the event.
    */
    void get_event_members(s_event_members* const p_event_members) noexcept;

private:
    /** Time of the event defined using system-dependant time_t. Optional member - depending on how the game implements time it may be ignored altogether. Implementations can also use a stepwise counter here. E.g. 1st step of simulation m_time = 1. 2nd step of simulation m_time=2, etc.
     * 
    */
    std::time_t m_time;
    
    unsigned long m_type; /**< Type of event. Optional parameter for implementation to identify event type. */

    unsigned long m_subtype; /**< Sub-Type of event. Optional parameter for implementation to identify event type. */

    WYPB_Player *m_parent_player; /**< Parent player that generated this event. Optional parameter for implementation to identify parent. */

};

#endif