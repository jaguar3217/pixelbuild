#include "GamePanel.hpp"

void GamePanel::SetTileToPaint(int tile)
{
	m_gp->SetTileToPaint(tile);
}

void GamePanel::OpenNewFile(wxString path)
{
	m_gp->OpenNewFile(path);
}

void GamePanel::SetMapSize(int width, int height)
{
	m_gp->SetMapSize(width, height);
}

char* GamePanel::GetLevel()
{
	return m_gp->GetLevel();
}
