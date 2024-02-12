#include "FrameBuffer.h"

void FrameBuffer::setupConfig(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT)
{
    /* setting for the frame buffer for ImGui  */
    glGenFramebuffers(1, &imguiframebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, imguiframebufferID);

    /* setting for the texture buffer for ImGui  */
    glGenTextures(1, &imguitexturebufferID);
    glBindTexture(GL_TEXTURE_2D, imguitexturebufferID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, imguitexturebufferID, 0);

    // check if the frame bufer is working
    if (!(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE))
        std::cout << "This is an error message that the frame buffer is incomplete" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void FrameBuffer::startBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, imguiframebufferID);
}

void FrameBuffer::endBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int FrameBuffer::gettextureID()
{
	return imguitexturebufferID;
}

void FrameBuffer::destroy()
{
    // destroying the frame buffer
    glDeleteTextures(1, &imguitexturebufferID);
    // destroying the frame buffer
    glDeleteFramebuffers(1, &imguiframebufferID);
    
}
