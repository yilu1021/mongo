// engine_spidermonkey.h

#pragma once

#include "engine.h"

#if defined( MOZJS )

#define MOZILLA_1_8_BRANCH

#include "mozjs/jsapi.h"
#include "mozjs/jsdate.h"

#elif defined( OLDJS )

#ifdef WIN32
#include "jstypes.h"
#undef JS_PUBLIC_API
#undef JS_PUBLIC_DATA
#define JS_PUBLIC_API(t)    t
#define JS_PUBLIC_DATA(t)   t
#endif

#include "jsapi.h"
#include "jsdate.h"

#else

#include "js/jsapi.h"
#include "js/jsdate.h"

#endif

// -- SM 1.6 hacks ---
#ifndef JSCLASS_GLOBAL_FLAGS

#warning old version of spider monkey ( probably 1.6 ) you should upgrade to at least 1.7

#define JSCLASS_GLOBAL_FLAGS 0

JSBool JS_CStringsAreUTF8(){
    return false;
}

#endif
// -- END SM 1.6 hacks ---

namespace mongo {

    class SMScope;
    class Convertor;
    
    extern JSClass bson_class;
    extern JSClass bson_ro_class;

    extern JSClass object_id_class;
    extern JSClass timestamp_class;
    extern JSClass minkey_class;
    extern JSClass maxkey_class;

    // internal things
    void dontDeleteScope( SMScope * s ){}
    void errorReporter( JSContext *cx, const char *message, JSErrorReport *report );
    extern boost::thread_specific_ptr<SMScope> currentScope;
    
    // bson
    JSBool resolveBSONField( JSContext *cx, JSObject *obj, jsval id, uintN flags, JSObject **objp );


    // mongo
    void initMongoJS( SMScope * scope , JSContext * cx , JSObject * global , bool local );
    bool appendSpecialDBObject( Convertor * c , BSONObjBuilder& b , const string& name , JSObject * o );
}
