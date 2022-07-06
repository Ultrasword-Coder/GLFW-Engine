#pragma once

#include "framebuffer.hpp"

Sora::FrameBuffer::FrameBuffer(int width, int height, int channels)
{
    this->frame = Sora::Texture2D(width, height, channels);
}

Sora::FrameBuffer::~FrameBuffer() {}

void Sora::FrameBuffer::create()
{
    glGenFramebuffers(1, &this->frame_buffer_object);
    if (!glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "[Sora][FramebufferStatus][" << __FILE__ << "] Failed to create framebuffer!" << std::endl;
        Sora::terminate_engine();
    }
    // bind
    this->bind();
    // generate the texture
    this->frame.create();
    this->frame.bind();
    /* setting texture to hold multiple types of information

        Each 32 bit value of texture contains 24 bits of depth info and 8 bits of stencil info

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->frame.get_width(), this->frame.get_height(), 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    */
    // attach texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->frame.get_id(), 0);

    // render buffer object
    glGenRenderbuffers(1, &this->render_buffer_object);
    glBindRenderbuffer(GL_RENDERBUFFER, this->render_buffer_object);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->frame.get_width(), this->frame.get_height());
    this->unbind();
    // link render buffer to frame buffer
    glNamedFramebufferRenderbuffer(this->frame_buffer_object, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->render_buffer_object);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->render_buffer_object);
    if (glCheckNamedFramebufferStatus(this->frame_buffer_object, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "[Sora][RenderBufferStatus][" << __FILE__ << "] Failed to create + link Renderbuffer to framebuffer!" << std::endl;
        Sora::terminate_engine();
    }
    this->unbind();
}

void Sora::FrameBuffer::clean()
{
    glDeleteFramebuffers(1, &this->frame_buffer_object);
    this->frame.clean();
}

void Sora::FrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer_object);
}

void Sora::FrameBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint Sora::FrameBuffer::get_id()
{
    return this->frame_buffer_object;
}

uint Sora::FrameBuffer::get_render_id()
{
    return this->render_buffer_object;
}

Sora::Texture2D *Sora::FrameBuffer::get_frame()
{
    return &this->frame;
}
