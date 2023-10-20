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



#ifndef _WYPB_IO_HPP_
#define _WYPB_IO_HPP_

/** Implements the IO functions for logging.
 * Defaults to logging to stdout. Most functions are declared virtual so implementions can be varied according to needs of the application. The base class here does not implement any bounds checking on buffer sizes at all - it depends on the implemntations classes to do all that.
 * 
 * E.g.
 * WYPB_IO io_obj;
 * io_obj.init(128);
 * io_obj.write("Hello World!");
*/
class WYPB_IO
{
public:
    /** Constructor. 
     * This base class implementation does nothing.
    */
    WYPB_IO();

    /** Destructor. 
     * This base class implementation does nothing.
    */
    virtual ~WYPB_IO(void);

    /** Additional virtual function to perform any required initialisation in case the constructor is not sufficient. This base class implementation does nothing.
    */
    virtual void init(void);

    /** Writes the log message to IO.
     * This base class implementation simply writes to stdout. Only IO functions are implemented so no bounds checking is performed - implementations must perform their own checks on buffer sizes to avoid buffer overflows.
     * \param p_message The message to write.  
     * \return 0. Or non-0 value from WYPB_Exception.hpp. The behavior is expected to be overriden if this function is overriden.
    */
    virtual int write(const char* const p_message) noexcept;
};


#endif