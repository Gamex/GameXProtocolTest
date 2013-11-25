//
//  CPomeloTestBase.cpp
//  GameXProtocolTest
//
//  Created by 马 俊 on 13-11-25.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#include "CPomeloTestBase.h"

#include <errno.h>

bool CPomeloTestBase::onEnter()
{
    struct sockaddr_in address;
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(m_port);
    address.sin_addr.s_addr = inet_addr(m_addr.c_str());
    
    if (client)
    {
        client = pc_client_new();
    }
    else
    {
        pc_client_stop(client);
        pc_client_destroy(client);
        client = pc_client_new();
    }
    int ret = pc_client_connect(client, &address);
    if(ret)
    {
        printf("pc_client_connect error:%d", errno);
        pc_client_destroy(client);
    }
    return  ret;
	return true;
}



bool CPomeloTestBase::onExit()
{
	return true;
}
