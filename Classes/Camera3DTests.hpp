//
//  Camera3DTests.hpp
//  cermer3dTest
//
//  Created by gates on 2016/11/5.
//
//

#ifndef Camera3DTests_hpp
#define Camera3DTests_hpp

#include <stdio.h>

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"

#include "DrawNode3D.hpp"
#include <string>
//
//----
namespace cocos2d {
    class Sprite3D;
    class Delay;
}

enum State
{
    State_None = 0,
    State_Idle = 0x01,
    State_Move = 0x02,
    State_Rotate = 0x04,
    State_Speak = 0x08,
    State_MeleeAttack = 0x10,
    State_RemoteAttack = 0x20,
    State_Attack = 0x40,
};
enum class CameraType
{
    Free = 0,
    FirstPerson = 1,
    ThirdPerson = 2,
};

enum class OperateCamType
{
    MoveCamera=0,
    RotateCamera=1,
};

class CameraBaseTest : public cocos2d::Scene
{
public:
    virtual std::string title() const { return ""; }
    virtual std::string subtitle() const { return ""; }

protected:
    cocos2d::BillBoard* bill1;
    cocos2d::BillBoard* bill2;
    cocos2d::Label* l1;
    cocos2d::Label* l2;
};

class CameraRotationTest : public CameraBaseTest {
    
public:
    CREATE_FUNC(CameraRotationTest);
    CameraRotationTest(void);
    virtual ~CameraRotationTest(void);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual void update(float dt) override;
    
    // overrides
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void menu1Callback(cocos2d::Ref* pSender);
protected:
    
    cocos2d::Node* _camControlNode;
    cocos2d::Node* _camNode;
    cocos2d::EventListenerTouchOneByOne* _lis;
};



// 设置委托的语法是:
//A a;
//a.setFunction( MakeDelegate(&someClass, &someMember) ); // 成员函数或
//a.setFunction( &somefreefunction ); // 静态函数

class Camera3DTestDemo : public CameraBaseTest
{
public:
    CREATE_FUNC(Camera3DTestDemo);
    Camera3DTestDemo(void);
    virtual ~Camera3DTestDemo(void);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    // overrides
    virtual std::string title() const override;
    void addNewSpriteWithCoords(cocos2d::Vec3 p,std::string fileName,bool playAnimation=false,float scale=1.0f,bool bindCamera=false);
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    
    void scaleCameraCallback(cocos2d::Ref* sender,float value);
    void rotateCameraCallback(cocos2d::Ref* sender,float value);
    void SwitchViewCallback(cocos2d::Ref* sender,CameraType cameraType);
    void updateCamera(float fDelta);
    void move3D(float elapsedTime);
    void updateState(float elapsedTime);
    bool isState(unsigned int state,unsigned int bit) const;
    void reachEndCallBack();
    
    bool onTouchesCommon(cocos2d::Touch* touch, cocos2d::Event* event, bool* touchProperty);
    bool onTouchesZoomOut(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchesZoomOutEnd(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onTouchesZoomIn(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchesZoomInEnd(cocos2d::Touch* touch, cocos2d::Event* event);
    
    bool onTouchesRotateLeft(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchesRotateLeftEnd(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onTouchesRotateRight(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchesRotateRightEnd(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void menu1Callback(cocos2d::Ref* pSender);
protected:
    void setTargetPos(cocos2d::Vec2& v);
    
    std::string    _title;
    cocos2d::Layer*         _layer3D;
    cocos2d::Sprite3D*      _sprite3D;
    cocos2d::Vec3           _targetPos;
    CameraType     _cameraType;
    cocos2d::MenuItem*      _incRot;
    cocos2d::MenuItem*      _decRot;
    unsigned int   _curState;
    cocos2d::Camera*      _camera;
    cocos2d::MoveTo* _moveAction;
    bool _bZoomOut;
    bool _bZoomIn;
    bool _bRotateLeft;
    bool _bRotateRight;
    cocos2d::Label* _RotateRightlabel;
    cocos2d::Label* _RotateLeftlabel;
    cocos2d::Label* _ZoomInlabel;
    cocos2d::Label* _ZoomOutlabel;
    
    int addFromLine = 0;
    int addGap=0;
};


#endif /* Camera3DTests_hpp */
