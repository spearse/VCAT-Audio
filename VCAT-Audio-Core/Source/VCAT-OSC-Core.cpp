/*
 ==============================================================================
 
 VCAT-OSC-Core.cpp
 Created: 11 Mar 2020 5:13:53pm
 Author:  Stephen Pearse
 
 ==============================================================================
 */

#include "VCAT-OSC-Core.h"

namespace VCAT{

JUCE_IMPLEMENT_SINGLETON(OSCCore)


OSCCore::OSCCore():
m_returnAddress("127.0.0.1"),
m_returnPort(8081),
m_setup(false),
m_logCallback([](const OSCMessage& msg){})
{
    
    m_receiver.addListener(this);
    m_receiver.connect(8080);
    
}

void OSCCore::registerNode(OSCNodePtr node){
    m_nodes.push_back(node);
}

void OSCCore::setupSender(String addr,int port){
    if(m_returnSender.connect(addr, port)){
        m_returnAddress = addr;
        m_returnPort = port;
        m_setup = true;
    }
}

void OSCCore::finished(String nodeName,bool state,String msg){
    if(!m_setup)return;
    OSCMessage responsemsg("/response");
    responsemsg.addInt32(state);
    responsemsg.addString(nodeName);
    if(state == false){
        responsemsg.addString(msg);
    }
    //Not a huge fan of this but it will work.
    OSCCore::getInstance()->sendMessage(responsemsg);
    
    
    
}
void OSCCore::setLogCallback(Callback callback){
    
    m_logCallback = callback;
    
}


void OSCCore::oscMessageReceived (const OSCMessage& message){
    m_logCallback(message);
    
    String addr = message.getAddressPattern().toString();
    for(auto node : m_nodes){
        
        if(*node == addr){
            node->run(message);
        }
    }
    
    
}

bool OSCCore::setup(){
    return m_setup;
}
void OSCCore::sendMessage(OSCMessage& msg){
    if(m_setup){
        m_returnSender.send(msg);
    }
}


}
