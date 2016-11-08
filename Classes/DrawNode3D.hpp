//
//  DrawNode3D.hpp
//  cermer3dTest
//
//  Created by gates on 2016/11/5.
//
//

#ifndef DrawNode3D_hpp
#define DrawNode3D_hpp

#include <stdio.h>

#include "cocos2d.h"

NS_CC_BEGIN

/**
 * Copy DrawNode for 3D geometry drawing.
 */
class DrawNode3D: public cocos2d::Node
{
public:
    /** creates and initialize a DrawNode3D node */
    static cocos2d::DrawNode3D* create();
    
    /**
     * Draw 3D Line
     */
    void drawLine(const cocos2d::Vec3 &from, const cocos2d::Vec3 &to, const Color4F &color);
    
    /**
     * Draw 3D cube
     * @param point to a vertex array who has 8 element.
     *        vertices[0]:Left-top-front,
     *        vertices[1]:Left-bottom-front,
     *        vertices[2]:Right-bottom-front,
     *        vertices[3]:Right-top-front,
     *        vertices[4]:Right-top-back,
     *        vertices[5]:Right-bottom-back,
     *        vertices[6]:Left-bottom-back,
     *        vertices[7]:Left-top-back.
     * @param color
     */
    void drawCube(cocos2d::Vec3* vertices, const Color4F &color);
    
    /** Clear the geometry in the node's buffer. */
    void clear();
    
    /**
     * @js NA
     * @lua NA
     */
    const BlendFunc& getBlendFunc() const;
    
    /**
     * @code
     * When this function bound into js or lua,the parameter will be changed
     * In js: var setBlendFunc(var src, var dst)
     * @endcode
     * @lua NA
     */
    void setBlendFunc(const BlendFunc &blendFunc);
    
    void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    
    // Overrides
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
    
CC_CONSTRUCTOR_ACCESS:
    DrawNode3D();
    virtual ~DrawNode3D();
    virtual bool init() override;
    
protected:
    struct V3F_C4B
    {
        cocos2d::Vec3     vertices;
        Color4B  colors;
    };
    void ensureCapacity(int count);
    
    GLuint      _vao;
    GLuint      _vbo;
    
    int         _bufferCapacity;
    GLsizei     _bufferCount;
    V3F_C4B*    _buffer;
    
    BlendFunc   _blendFunc;
    cocos2d::CustomCommand _customCommand;
    
    bool        _dirty;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(DrawNode3D);
};

NS_CC_END

#endif /* DrawNode3D_hpp */
