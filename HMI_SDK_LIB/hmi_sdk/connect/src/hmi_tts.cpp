﻿/**
* @file			hmi_tts
* @brief		TTS语音播放通道，处理SDL发送的TTS相关的RPC请求等
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#include <hmi_tts.h>
#include <iostream>
#include <string>
#include "json/json.h"
#include <global_first.h>

TTS::TTS() : Channel(300, "TTS") {

}

TTS::~TTS() {

}

void TTS::onRequest(Json::Value &request) {
  std::string method = request["method"].asString();
  int id = request["id"].asInt();
  if (method == "TTS.SetGlobalProperties") {
    sendResult(id, "SetGlobalProperties");
  } else if (method == "TTS.GetCapabilities") {
    sendResult(id, "GetCapabilities"); // capabilities:["TEXT"]
  } else if (method == "TTS.GetSupportedLanguages") {
    sendResult(id, "GetSupportedLanguages");
  } else if (method == "TTS.GetLanguage") {
    sendResult(id, "GetLanguage");
  } else if (method == "TTS.ChangeRegistration") {
    sendResult(id, "ChangeRegistration");
  } else if (method == "TTS.IsReady") {
    sendResult(id, "IsReady");
  } else if (method == "TTS.Speak") {
    Result result = m_pCallback->onRequest(request);
    //sendResult(id,"Speak",result);
  } else if (method == "TTS.StopSpeaking") {
    // ttsHandler action stop
    Result result = m_pCallback->onRequest(request);
    sendResult(id, "Speak", result);
  } else {
    Channel::onRequest(request);
  }
}

