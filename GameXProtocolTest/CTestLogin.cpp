//
//  CTestLogin.cpp
//  GameXProtocolTest
//
//  Created by 马 俊 on 13-11-25.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#include "CTestLogin.h"
#include "CTestManager.h"
#include "CCPomelo.h"

ADD_CASE(CTestLogin);

bool CTestLogin::onEnter()
{
    if (!CPomeloTestBase::onEnter()) return false;
    
    // --------------- prepare test
    addTask([&](void)
            {
                setTaskName("prepare test");
                const char *route = "gate.gateHandler.queryEntry";
                json_t *msg = json_object();
                json_object_set(msg, "userName", json_string("autoTest"));
                json_object_set(msg, "password", json_string("at123"));
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
                                    
                                    const char* route = "gate.gateHandler.admin_kickAllOnlineUser";
                                    json_t *msg = json_object();
                                    POMELO->request(route, msg,
                                                    [&](Node* node, void* resp)
                                                    {
                                                        CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
//                                                        printf(json_dumps(ccpomeloresp->docs, JSON_COMPACT));
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
    
    // --------------- login ok
    addTask([&](void)
            {
                setTaskName("login ok");
                const char *route = "gate.gateHandler.queryEntry";
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

    // --------------- use kick without authority
    addTask([&](void)
            {
                setTaskName("use kick without authority");
                const char* route = "gate.gateHandler.admin_kickAllOnlineUser";
                json_t *msg = json_object();
                POMELO->request(route, msg,
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
    
    // --------------- login error username
    addTask([&](void)
            {
                setTaskName("login error username");
                const char *route = "gate.gateHandler.queryEntry";
                json_t *msg = json_object();
                json_object_set(msg, "userName", json_string("tes1"));
                json_object_set(msg, "password", json_string("123"));
                POMELO->request(route, msg,
                                [&](Node* node, void* resp)
                                {
                                    
                                    CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                                    json_t* code = json_object_get(ccpomeloresp->docs, "code");
                                    if (1003 != json_integer_value(code))
                                    {
                                        setTaskState(TASK_FAIL);
                                        return;
                                    }
                                    setTaskState(TASK_OK);
                                });
            });
    
    // --------------- login error password
    addTask([&](void)
            {
                setTaskName("login error password");
                const char *route = "gate.gateHandler.queryEntry";
                json_t *msg = json_object();
                json_object_set(msg, "userName", json_string("test13"));
                json_object_set(msg, "password", json_string("12"));
                POMELO->request(route, msg,
                                [&](Node* node, void* resp)
                                {
                                    
                                    CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                                    json_t* code = json_object_get(ccpomeloresp->docs, "code");
                                    if (1005 != json_integer_value(code))
                                    {
                                        setTaskState(TASK_FAIL);
                                        return;
                                    }
                                    setTaskState(TASK_OK);
                                });
            });
    
    
	return true;
}



bool CTestLogin::onExit()
{
    CPomeloTestBase::onExit();
	return true;
}




