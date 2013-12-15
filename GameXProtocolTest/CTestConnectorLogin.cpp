//
//  CTestConnectorLogin.cpp
//  GameXProtocolTest
//
//  Created by 马 俊 on 13-11-27.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#include "CTestConnectorLogin.h"
#include "CTestManager.h"
#include "CCPomelo.h"

ADD_CASE(CTestConnectorLogin);

bool CTestConnectorLogin::onEnter()
{
    if (!CPomeloTestBase::onEnter()) return false;
    
    // --------------- prepare test
//    addTask([&](void)
//            {
//                setTaskName("prepare test");
//                const char *route = "gate.gateHandler.queryConnectorEntry";
//                json_t *msg = json_object();
//                json_object_set(msg, "userName", json_string("autoTest"));
//                json_object_set(msg, "password", json_string("at123"));
//                POMELO->request(route, msg,
//                                [&](Node* node, void* resp)
//                                {
//                                    CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
//                                    json_t* code = json_object_get(ccpomeloresp->docs, "code");
//                                    if (200 != json_integer_value(code))
//                                    {
//                                        setTaskState(TASK_FAIL);
//                                        return;
//                                    }
//                                    
//                                    const char* route = "gate.gateHandler.admin_kickAllOnlineUser";
//                                    json_t *msg = json_object();
//                                    POMELO->request(route, msg,
//                                                    [&](Node* node, void* resp)
//                                                    {
//                                                        CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
//                                                        //                                                        printf(json_dumps(ccpomeloresp->docs, JSON_COMPACT));
//                                                        json_t* code = json_object_get(ccpomeloresp->docs, "code");
//                                                        if (200 != json_integer_value(code))
//                                                        {
//                                                            setTaskState(TASK_FAIL);
//                                                            return;
//                                                        }
//                                                        
//                                                        setTaskState(TASK_OK);
//                                                    });
//                                });
//            });
    
    // --------------- connect to connector
    addTask([&](void)
            {
                setTaskName("connect to connector");
                const char *route = "gate.gateHandler.queryConnectorEntry";
                json_t *msg = json_object();
                json_object_set(msg, "userName", json_string("test1"));
                json_object_set(msg, "password", json_string("123"));
                POMELO->request(route, msg,
                                [&](Node* node, void* resp)
                                {
                                    CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                                    json_t* code = json_object_get(ccpomeloresp->docs, "code");
                                    if (200 != json_integer_value(code))
                                    {
                                        setTaskState(TASK_FAIL);
                                        return;
                                    }
                                    json_t* host = json_object_get(ccpomeloresp->docs, "host");
                                    json_t* port = json_object_get(ccpomeloresp->docs, "port");
                                    
                                    POMELO->stop();
                                    if (0 != POMELO->connect(json_string_value(host), (int)json_integer_value(port)))
                                    {
                                        setTaskState(TASK_FAIL);
                                    }
                                    
                                    const char* route = "connector.entryHandler.login";
                                    json_t *msg = json_object();
                                    json_object_set(msg, "userName", json_string("test1"));
                                    json_object_set(msg, "password", json_string("123"));
                                    POMELO->request(route, msg,
                                                    [&](Node* node, void* resp)
                                                    {
                                                        CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                                                        json_t* code = json_object_get(ccpomeloresp->docs, "code");
                                                        if (200 != json_integer_value(code))
                                                        {
                                                            setTaskState(TASK_FAIL);
                                                            return;
                                                        }
                                                        setTaskState(TASK_OK);
                                                    });
                                });
            });

    // --------------- get player info
    addTask([&](void)
            {
                setTaskName("get player info");
                const char* route = "connector.entryHandler.getPlayerInfo";
                json_t *msg = json_object();
                POMELO->request
                (route, msg,
                 [&](Node* node, void* resp)
                {
                    CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                    json_t* code = json_object_get(ccpomeloresp->docs, "code");
                    if (200 != json_integer_value(code))
                    {
                        setTaskState(TASK_FAIL);
                        return;
                    }
//                    printf(json_dumps(ccpomeloresp->docs, JSON_COMPACT));
                    setTaskState(TASK_OK);
                });

            });
    
    
    // --------------- gameplay clearHomeBuildings
    addTask([&](void)
            {
                setTaskName("gameplay clear all buildings");
                const char* route = "gameplay.admin.clearHomeBuildings";
                json_t *msg = json_object();
                POMELO->request
                (route, msg,
                 [&](Node* node, void* resp)
                 {
                     CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                     json_t* code = json_object_get(ccpomeloresp->docs, "code");
                     if (200 != json_integer_value(code))
                     {
                         setTaskState(TASK_FAIL);
                         return;
                     }
                     setTaskState(TASK_OK);
                 });
                
            });

    // --------------- gameplay build
    addTask([&](void)
            {
                setTaskName("gameplay build");
                const char* route = "gameplay.home.buildInHome";
                json_t *msg = json_object();
                json_object_set(msg, "bname", json_string("20101"));
                json_object_set(msg, "x", json_integer(10));
                json_object_set(msg, "y", json_integer(20));
                POMELO->request
                (route, msg,
                 [&](Node* node, void* resp)
                 {
                     CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                     json_t* code = json_object_get(ccpomeloresp->docs, "code");
                     if (200 != json_integer_value(code))
                     {
                         setTaskState(TASK_FAIL);
                         return;
                     }
                     m_bid = (int)json_integer_value(json_object_get(ccpomeloresp->docs, "bid"));
                     setTaskState(TASK_OK);
                 });
                
            });
    
    // --------------- gameplay build in same place
    addTask([&](void)
            {
                setTaskName("gameplay build in same place");
                const char* route = "gameplay.home.buildInHome";
                json_t *msg = json_object();
                json_object_set(msg, "bname", json_string("20101"));
                json_object_set(msg, "x", json_integer(10));
                json_object_set(msg, "y", json_integer(20));
                POMELO->request
                (route, msg,
                 [&](Node* node, void* resp)
                 {
                     CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                     json_t* code = json_object_get(ccpomeloresp->docs, "code");
                     if (200 == json_integer_value(code))
                     {
                         setTaskState(TASK_FAIL);
                         return;
                     }

                     setTaskState(TASK_OK);
                 });
                
            });
    
    // --------------- gameplay build anther
    addTask([&](void)
            {
                setTaskName("gameplay build anther");
                const char* route = "gameplay.home.buildInHome";
                json_t *msg = json_object();
                json_object_set(msg, "bname", json_string("20101"));
                json_object_set(msg, "x", json_integer(20));
                json_object_set(msg, "y", json_integer(20));
                POMELO->request
                (route, msg,
                 [&](Node* node, void* resp)
                 {
                     CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                     json_t* code = json_object_get(ccpomeloresp->docs, "code");
                     if (200 != json_integer_value(code))
                     {
                         setTaskState(TASK_FAIL);
                         return;
                     }
                     
                     setTaskState(TASK_OK);
                 });
                
            });
    
    // --------------- gameplay move building
    addTask([&](void)
            {
                setTaskName("gameplay move buidling");
                const char* route = "gameplay.home.moveBuilding";
                json_t *msg = json_object();
                json_object_set(msg, "bid", json_integer(m_bid));
                json_object_set(msg, "x", json_integer(30));
                json_object_set(msg, "y", json_integer(30));
                POMELO->request
                (route, msg,
                 [&](Node* node, void* resp)
                 {
                     CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                     json_t* code = json_object_get(ccpomeloresp->docs, "code");
                     if (200 != json_integer_value(code))
                     {
                         setTaskState(TASK_FAIL);
                         return;
                     }
                     setTaskState(TASK_OK);
                 });
                
            });
    
    // --------------- gameplay move building to wrong place
    addTask([&](void)
            {
                setTaskName("gameplay move building to wrong place");
                const char* route = "gameplay.home.moveBuilding";
                json_t *msg = json_object();
                json_object_set(msg, "bid", json_integer(m_bid));
                json_object_set(msg, "x", json_integer(20));
                json_object_set(msg, "y", json_integer(20));
                POMELO->request
                (route, msg,
                 [&](Node* node, void* resp)
                 {
                     CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                     json_t* code = json_object_get(ccpomeloresp->docs, "code");
                     if (200 == json_integer_value(code))
                     {
                         setTaskState(TASK_FAIL);
                         return;
                     }
                     setTaskState(TASK_OK);
                 });
                
            });

    // --------------- gameplay delete building
    addTask([&](void)
            {
                setTaskName("gameplay delete buidling");
                const char* route = "gameplay.home.removeBuilding";
                json_t *msg = json_object();
                json_object_set(msg, "bid", json_integer(m_bid));
                POMELO->request
                (route, msg,
                 [&](Node* node, void* resp)
                 {
                     CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                     json_t* code = json_object_get(ccpomeloresp->docs, "code");
                     if (200 != json_integer_value(code))
                     {
                         setTaskState(TASK_FAIL);
                         return;
                     }
                     setTaskState(TASK_OK);
                 });
                
            });
    
    // --------------- gameplay getHomeInfo
    addTask([&](void)
            {
                setTaskName("gameplay getHomeInfo");
                const char* route = "gameplay.home.getHomeInfo";
                json_t *msg = json_object();
                POMELO->request
                (route, msg,
                 [&](Node* node, void* resp)
                 {
                     CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                     json_t* code = json_object_get(ccpomeloresp->docs, "code");
                     if (200 != json_integer_value(code))
                     {
                         setTaskState(TASK_FAIL);
                         return;
                     }
                     printf("%s\n", json_dumps(ccpomeloresp->docs, JSON_COMPACT));
                     setTaskState(TASK_OK);
                 });
                
            });
    
	return true;
}
