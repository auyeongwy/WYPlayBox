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



#ifndef _WYPB_PLAYER_HPP_
#define _WYPB_PLAYER_HPP_

#include "WYPB_EventMgr.hpp"
#include "WYPB_Event.hpp"


class WYPB_EventMgr;
class WYPB_Event;


/** Implements a player object. 
*/
class WYPB_Player
{
public:
    
    /** Constructor. 
     * Throws an integer exception if initialisation encounters an error. Note that this does not include throwing errors caught by the C++ std::exception class. Those must be caught seperately.   
     * 
     * Example:
     * try {
     *  WYPB_Player player_obj;
     * } catch (int e) {
     *  cout << "Exception: " << e << "\n";
     * }
     * 
     * \throws Integer exception from WYPB_Exception.h. 
    */
    WYPB_Player();


    /** Virtual destructor.
    */
    virtual ~WYPB_Player();
    

    /** Returns ID of the WYPB_Player object.
     * \return ID of the WYPB_Player object.
    */
    unsigned long get_id(void) noexcept;


    /** Virtual function to process an event. Meant to be overridden in implementation.
     * \param p_event The WYPB_Event to be processed.
     * \param p_event_mgr If the player generates new events, send it back to this WYPB_EventMgr to queue.
    */
    virtual void process_event(const WYPB_Event* const p_event, WYPB_EventMgr * const p_event_mgr) noexcept;


    /** Virtual function to generate an event. Meant to be overridden in implementation.
     *  
    */
    //virtual WYPB_Event* generate_event(void) noexcept;


private:

    /** Static ID generator. Incrementally generates a new ID for each new WYPB_Player object up to 2^16.
    */
    static unsigned long m_generate_id;

    /** ID of the WYPB_Player object.
    */
    unsigned long m_id;
};

#endif