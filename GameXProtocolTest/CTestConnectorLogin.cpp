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

//    // --------------- gameplay build info
//    addTask([&](void)
//            {
//                setTaskName("gameplay build");
//                const char* route = "gameplay.gameplayHandler.build";
//                json_t *msg = json_object();
//                POMELO->request
//                (route, msg,
//                 [&](Node* node, void* resp)
//                 {
//                     CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
//                     json_t* code = json_object_get(ccpomeloresp->docs, "code");
//                     if (200 != json_integer_value(code))
//                     {
//                         setTaskState(TASK_FAIL);
//                         return;
//                     }
//                     setTaskState(TASK_OK);
//                 });
//                
//            });
    
    // --------------- gameplay getHomeInfo
    addTask([&](void)
            {
                setTaskName("gameplay getHomeInfo");
                const char* route = "gameplay.gameplayHandler.getHomeInfo";
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
