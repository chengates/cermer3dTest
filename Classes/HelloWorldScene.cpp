#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width ,
                                origin.y + closeItem->getContentSize().height));
    closeItem->setScale(2.0f);

    
    // create and initialize a label
    
    auto label = Label::createWithTTF("Rotation Test", "fonts/Marker Felt.ttf", 24);
    auto label1 = Label::createWithTTF("Camera3DTests Test", "fonts/Marker Felt.ttf", 24);
    auto label2 = Label::create();
    label2->setString("點放美女放大縮小,按著美女移動\n點放其他文字標題,進出3D效果");
    label2->setSystemFontSize(20);
    label2->setTextColor(Color4B::BLUE);
    label2->setPosition(Vec2(origin.x + visibleSize.width/2,32));

    // add the label as a child to this layer MenuItemLabel
    auto labItem = MenuItemLabel::create(label,
                                          CC_CALLBACK_1(HelloWorld::menu1Callback, this));
    auto labItem1 = MenuItemLabel::create(label1,
                                           CC_CALLBACK_1(HelloWorld::menu2Callback, this));
    // position the label on the center of the screen
    labItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    labItem1->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label1->getContentSize().height*3));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,labItem,labItem1, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    this->addChild(label2,1);
    // add "girl" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    //============ 添加sprite觸控 ===========
    //Create a "one by one" touch event listener (processes one touch at a time)
    auto listener1 = EventListenerTouchOneByOne::create();
    // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
    listener1->setSwallowTouches(true);
    
    // Example of using a lambda expression to implement onTouchBegan event callback function
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        //Get the position of the current point relative to the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        //Check the click area
        if (rect.containsPoint(locationInNode))
        {
            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
            target->setOpacity(180);
            return true;
        }
        return false;
    };
    
    //
    //Process the touch move event
    listener1->onTouchMoved = [=](Touch* touch, Event* event)
    {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setOpacity(255); //Reset zOrder and the display sequence will change
        if (target == sprite)
        {
            Point touchPosi = touch->getLocation();
            Point locationInNode = target->convertToNodeSpaceAR(touchPosi);
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            log("sprite onTouchesMoveed..Point(%f.1, %f.1) Size(%f.1 , %f.1) ",
                locationInNode.x,locationInNode.y, s.width, s.height);
            sprite->setPosition(
                                Vec2(locationInNode.x/2+visibleSize.width/2,
                                     locationInNode.y/2+visibleSize.height/2)
                                );
        }
    };
    //Process the touch end event
    listener1->onTouchEnded = [=](Touch* touch, Event* event)
    {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
                target->setOpacity(255); //Reset zOrder and the display sequence will change
        if (target == sprite)
        {
            log("sprite onTouchesEnded.. ");
            static float scale = 1.0;
            if(scale == 1.0)
                scale = 2.0;
            else
                scale = 1.0;
            sprite->setScale(scale);

        }
    };
    //
    //Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite);
    //-- end of 添加sprite觸控
    

    return true;
}

void HelloWorld::menu1Callback(Ref* pSender)
{
    //Director::getInstance();
    log("rotation test");
    auto scene = CameraRotationTest::create();
    scene->title();
    scene->subtitle();
    //auto scene = std::function<cocos2d::Scene*()>TestSuite:: _testCallbacks[0]();
//    auto testCase = getTestCase(scene);
//    testCase->setTestSuite(this);
//    testCase->setTestCaseName(_childTestNames[_currTestIndex]);
    Director::getInstance()->replaceScene(scene);
    
}

void HelloWorld::menu2Callback(Ref* pSender)
{
    //Director::getInstance();
    log("Camera3DTests test");
    auto scene = Camera3DTestDemo::create();
    
    scene->subtitle();
    Director::getInstance()->replaceScene(scene);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
