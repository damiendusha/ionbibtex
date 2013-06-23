/*
* Copyright (C) 2013 Damien Dusha
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software Foundation,
* Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
* 
* -----------------------------------------------------------------------------
* The functions "CurlWriteMemoryCallback" and "GetURL" contain code
* written under the "CURL License" from the following source:
*
* http://curl.haxx.se/libcurl/c/getinmemory.html
*
* The CURL License is as follows:
* ----
* COPYRIGHT AND PERMISSION NOTICE
*
* Copyright (c) 1996 - 2013, Daniel Stenberg, <daniel@haxx.se>.
*
* All rights reserved.
*
* Permission to use, copy, modify, and distribute this software for any purpose
* with or without fee is hereby granted, provided that the above copyright
* notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN
* NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
* OR OTHER DEALINGS IN THE SOFTWARE.
*  
* Except as contained in this notice, the name of a copyright holder shall not
* be used in advertising or otherwise to promote the sale, use or other dealings
* in this Software without prior written authorization of the copyright holder.
* ----
*/

#include "CDataSourceURL.h"
#include "Utilities/IO/CTextFile.h"
#include "Utilities/StringUtilities/StringUtilities.h"

#include <curl/curl.h>

#include <iostream>
#include <stdlib.h>
#include <string.h>


struct MemoryStruct 
{
    char *memory;
    size_t size;
};


CDataSourceURL::CDataSourceURL(const std::string& filename)
    : CDataSource(filename)
{
}


CDataSourceURL::~CDataSourceURL()
{
}


bool CDataSourceURL::ParseDataSource(std::vector< std::string >& data)
{
    std::string web_data;
    if (!GetURL(m_resourceName, web_data))
    {
        return false;
    }

    // Split into individual lines
    data.clear();
    data = Utilities::SplitString(web_data, "\n");

    return true;
}

bool CDataSourceURL::GetURL(const std::string& url, std::string& output_data)
{
    output_data = std::string("");

    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;

    chunk.memory = (char*) malloc(1);   /* will be grown as needed by the realloc above */ 
    chunk.size = 0;                     /* no data at this point */ 

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */ 
    curl_handle = curl_easy_init();

    /* specify URL to get */ 
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str() );

    /* send all data to this function  */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, CDataSourceURL::CurlWriteMemoryCallback);

    /* we pass our 'chunk' struct to the callback function */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

    /* some servers don't like requests that are made without a user-agent
        field, so we provide one */ 
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    /* get it! */ 
    res = curl_easy_perform(curl_handle);

    /* check for errors */ 
    bool ok;
    if(res != CURLE_OK) 
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        ok = false;
    }
    else 
    {
        /*
        * Now, our chunk.memory points to a memory block that is chunk.size
        * bytes big and contains the remote file.
        *
        * Do something nice with it!
        *
        * You should be aware of the fact that at this point we might have an
        * allocated data block, and nothing has yet deallocated that data. So when
        * you're done with it, you should free() it as a nice application.
        */ 

        printf("%lu bytes retrieved\n", (long)chunk.size);
        output_data = std::string(chunk.memory);
        ok = true;
    }

    /* cleanup curl stuff */ 
    curl_easy_cleanup(curl_handle);

    if(chunk.memory)
        free(chunk.memory);

    /* we're done with libcurl, so clean it up */ 
    curl_global_cleanup();

    return ok;
}

size_t CDataSourceURL::CurlWriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = (char*) realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL) 
    {
        /* out of memory! */ 
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}
