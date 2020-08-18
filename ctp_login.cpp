#include "API/ThostFtdcMdApi.h"
#include "API/ThostFtdcTraderApi.h"
#include "API/ThostFtdcUserApiDataType.h"
#include "API/ThostFtdcUserApiStruct.h"
#include "API/getconfig.h"
#include <string>
#include "windows.h"

void ctp_login(){
    //加载dll

    //建立api实例

    //调用login方法

    //logfile = fopen("syslog.txt", "w");

//    string g_chFrontaddr = getConfig("config", "FrontAddr");
//    CTraderApi *pUserApi = new CTraderApi;
//    pUserApi->CreateFtdcTraderApi(".\\flow\\");
//    LOG(pUserApi->GetApiVersion());
//    CSimpleHandler sh(pUserApi);
//    pUserApi->RegisterSpi(&sh);
//    pUserApi->SubscribePrivateTopic(THOST_TERT_QUICK);
//    pUserApi->SubscribePublicTopic(THOST_TERT_QUICK);
//    pUserApi->RegisterFront(const_cast<char *>(g_chFrontaddr.c_str()));
//    pUserApi->Init();
//    WaitForSingleObject(g_hEvent, INFINITE);
//    sh.ReqAuthenticate();
//    WaitForSingleObject(g_hEvent, INFINITE);
//    sh.ReqUserLogin();
//    WaitForSingleObject(g_hEvent, INFINITE); string g_chFrontMdaddr = getConfig("config", "FrontMdAddr");
//    CThostFtdcMdApi  *pUserMdApi = CThostFtdcMdApi::CreateFtdcMdApi(".\\flow\\md");
//    CSimpleMdHandler ash(pUserMdApi);
//    pUserMdApi->RegisterSpi(&ash);
//    pUserMdApi->RegisterFront(const_cast<char *>(g_chFrontMdaddr.c_str()));
//    pUserMdApi->Init();
//    WaitForSingleObject(xinhao, INFINITE);

//    sh.ReqQryInstrument();//查询合约 WaitForSingleObject(xinhao, INFINITE);
//    ash.SubscribeMarketData();//订阅行情
//    WaitForSingleObject(xinhao, 500);
//    sh.ReqQryInvestorPosition();//查询持仓
//    Sleep(1000);

//    return;
}

