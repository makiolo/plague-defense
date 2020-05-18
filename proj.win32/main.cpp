/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

/*
static uint32_t alloc_count = 0;

void* operator new(size_t size)
{
    alloc_count += 1;
    size_t sizeof_director = sizeof(Director);
    size_t sizeof_cfg = sizeof(Configuration);
    size_t sizeof_eventcustom = sizeof(EventCustom);
    if (size != MAX_LOG_LENGTH && size != sizeof_director && size != sizeof_cfg && size != sizeof_eventcustom && size > 8 && size != 56 && size != 64 && size != 32 && size != 28)
    {
        //CCLOG("Allocation %l bytes.", size);
    }
    return malloc(size);
}

void operator delete(void* ptr)
{
    // CCLOG("Deallocation ptr.");
    alloc_count -= 1;
}

struct MemoryChecker
{
    MemoryChecker()
    {
        
    }

    ~MemoryChecker()
    {
        CCLOG("Total count: %l", alloc_count);
    }
};
*/

int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
