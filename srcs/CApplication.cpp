#include "CApplication.hpp"

CApplication::CApplication()
{
}

CApplication::~CApplication()
{
}

void	CApplication::init()
{
	m_surface = new CSurface();
	m_surface->Init();
}
