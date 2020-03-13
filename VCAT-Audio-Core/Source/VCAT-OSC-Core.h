/*
 ==============================================================================
 
 VCAT-OSC-Core.h
 Created: 11 Mar 2020 5:13:53pm
 Author:  Stephen Pearse
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>
#include <functional>
#include <vector>
#include <memory>
namespace VCAT {

class OSCNode;
typedef std::shared_ptr<OSCNode> OSCNodePtr;
typedef std::function<void(bool,String)> ResponseCallback;
typedef  std::function<void(const OSCMessage& msg)> Callback;


//helper Functions
inline String obtainString(const OSCMessage& msg,int index){
    
    String ret("");
    if(index < msg.size()){
        if(msg[index].isString()){
            ret = msg[index].getString();
        }
    }
    return ret;
}
inline int obtainInt(const OSCMessage& msg,int index){
    
    int ret(-666);
    if(index < msg.size()){
        if(msg[index].isInt32()){
            ret = msg[index].getInt32();
        }
    }
    return ret;
}
inline float obtainFLoat(const OSCMessage& msg,int index){
    
    float ret(-666);
    if(index < msg.size()){
        if(msg[index].isFloat32()){
            ret = msg[index].getFloat32();
        }
    }
    return ret;
}

inline String obtainMessageAsString(const OSCMessage& msg){
    
    String ret;
    for(auto element : msg){
       
        if(element.isInt32()){
            ret += String(element.getInt32());
        }else if(element.isFloat32()){
            ret += String(element.getFloat32());
        } else if(element.isString()){
            ret += String(element.getString());
        }else{
            ret += "UnkownType";
        }
        ret +=" ";
    }
    return ret;
    
}


class OSCCore : public OSCReceiver::Listener<juce::OSCReceiver::MessageLoopCallback>{
    
    OSCReceiver m_receiver;
    std::vector<OSCNodePtr> m_nodes;
    String m_returnAddress;
    int m_returnPort;
    OSCSender m_returnSender;
    bool m_setup;
    Callback m_logCallback;
public:
    
    OSCCore();
    
    void setupSender(String addr,int port);
    
    void oscMessageReceived (const OSCMessage& message);
    
    void registerNode(OSCNodePtr node);
    
    bool setup();
    
    void sendMessage(OSCMessage& msg);
    
    void finished(String nodeName,bool state,String msg);
    
    void setLogCallback(Callback callback);
    
    JUCE_DECLARE_SINGLETON(OSCCore,true)
    
};

class OSCNode {
    String m_id;
private:
    Callback m_function;
    ResponseCallback m_response;
    
public:
    bool operator == (const String& other){
        return m_id == other;
    }
    
    OSCNode(String _id, Callback _functionCallback):
    m_id(_id),
    m_function(_functionCallback)
    {
        
    }
    
    void run(const OSCMessage& msg){
        m_function(msg);
    }
    
    
    
};

}

