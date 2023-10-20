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

#ifndef _WYPB_SERIALIZE_HPP_
#define _WYPB_SERIALIZE_HPP_

#include "WYPB_Exception.hpp"


/** Implements serialization functions.
 * This class implements serialization features. To use, it must be inherited. The derived classes override the virtual functions save() and load() to specify the data to be saved and loaded. They do so by calling the functions do_save() and do_load(). \n
 * \n
 * Usage: \n
 * class My_Derived: public WYPB_Serialize \n
 * { \n
 * public: \n
 *  int save() \n
 *  { \n
 *      // Prepare data to be written \n
 *      do_save(size_of_data, data); \n
 *  } \n
 * \n
 *  int load() \n
 *  { \n
 *      // Prepare buffer for data to be loaded \n
 *      do_load(size_of_data, data); \n
 *  } \n
 * } \n
 * 
*/
class WYPB_Serialize
{
public:
    virtual int save()=0;
    virtual int load()=0;

protected:
    int do_save(const unsigned long p_size, const char * const p_data) noexcept;
    int do_load(const unsigned long p_size, char * p_data) noexcept;

};


#endif