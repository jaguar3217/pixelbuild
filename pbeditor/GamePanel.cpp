#include "GamePanel.hpp"

void GamePanel::SetTileToPaint(int tile)
{
	m_gp->SetTileToPaint(tile);
}

void GamePanel::OpenNewFile(wxString path)
{
	m_gp->OpenNewFile(path);
}

char* GamePanel::GetLevel()
{
	return m_gp->GetLevel();
}
