#include "glObject.h"

int glObject::m_cnt = 1;

glObject::glObject() : m_id(glObject::getCnt()), m_shader(0), m_vao(0), m_vbo(0)
{
}

glObject::~glObject()
{

}