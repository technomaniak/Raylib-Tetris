#include "OptionsMenu.h"
#include "Settings.h"
#include <iostream>

OptionsMenu::OptionsMenu(SoundManager &sounds1):
	optionsLoaded(false),
	sounds(sounds1),
	volume(sounds.GetMusicVolume()),
	volumeSliderTint(Color{ 0, 0, 0, 255 }),
	mouseOverMusicVolumeSlider(false),
	mouseClickedMusicVolumeSlider(false),
	mouseOverReturnButton(false),
	returnButtonCounter(0)
{
}

void OptionsMenu::LoadOptions()
{
	optionsLoaded = true;
}

void OptionsMenu::SetLoaded(bool val)
{
	optionsLoaded = val;
}

bool OptionsMenu::GetLoaded()
{
	return optionsLoaded;
}

void OptionsMenu::Tick()
{
	Draw();
	ReturnButton();
	VolumeSettings();
}

void OptionsMenu::Draw()
{
	ClearBackground(BLACK);

	// Volume
	raycpp::DrawRectangleLinesEx(settings::volumeSliderBorderPos, settings::volumeSliderBorderSize, 2, RAYWHITE);
	raycpp::DrawRectangle({ settings::volumeSliderPos.GetX(), settings::volumeSliderPos.GetY() + (settings::volumeSliderSize.GetY() / 100 * (100 - (int)(sounds.GetMusicVolume() * 100))) },
		{ settings::volumeSliderSize.GetX(), (settings::volumeSliderSize.GetY() / 100) * (int)(sounds.GetMusicVolume() * 100) }, RAYWHITE);
	raycpp::DrawText(TextFormat(" V\n O\n L\n U\n M\n E\n%i", (int)(sounds.GetMusicVolume() * 100)), settings::volumeSliderBorderPos - Vec2<int>{ 50, -3 }, 30, RAYWHITE);

	// Return Button
	raycpp::DrawRectangleLinesEx(settings::returnButtonPos, settings::returnButtonSize, 5, RAYWHITE);
	raycpp::DrawText("RETURN", { settings::returnButtonTextPos.GetX() - (settings::returnButtonSize.GetX() / 2) + (settings::returnButtonSize.GetX() - MeasureText("RETURN", settings::returnButtonTextSize) / 2),
		settings::returnButtonPos.GetY() - (settings::returnButtonSize.GetY() / 2) + (int)(settings::returnButtonSize.GetY() - MeasureTextEx(GetFontDefault(), "RETURN", (float)(settings::returnButtonTextSize / 2), 20).y) },
		settings::returnButtonTextSize, RAYWHITE);


}

void OptionsMenu::VolumeSettings()
{
	if (raycpp::GetMousePos() > settings::volumeSliderBorderPos - Vec2<int>{ 0, 25 }
	&& raycpp::GetMousePos() < settings::volumeSliderBorderPos - Vec2<int>{ 0, 15 } + settings::volumeSliderBorderSize)
	{
		if (mouseOverMusicVolumeSlider != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverMusicVolumeSlider = true;
		}
	}
	else
	{
		if (!mouseClickedMusicVolumeSlider)
		{
			mouseOverMusicVolumeSlider = false;
		}
	}

	if (mouseOverMusicVolumeSlider)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			mouseClickedMusicVolumeSlider = true;
		}
		if (mouseClickedMusicVolumeSlider && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			float mouseVolumePosForFucksSake = ((((float)settings::volumeSliderPos.GetY() + settings::volumeSliderSize.GetY()) - raycpp::GetMousePos().GetY() - 20) / settings::volumeSliderSize.GetY());

			if (mouseVolumePosForFucksSake < 0)
			{
				sounds.SetAllMusicVolume(0.0f);
			}
			else if (mouseVolumePosForFucksSake > 1)
			{
				sounds.SetAllMusicVolume(1.0f);
			}
			else
			{
				sounds.SetAllMusicVolume(mouseVolumePosForFucksSake);
			}
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			mouseClickedMusicVolumeSlider = false;
		}
	}
}

void OptionsMenu::ReturnButton()
{
	if (raycpp::GetMousePos() > settings::returnButtonPos - Vec2<int>{ 0, 25 }
	&& raycpp::GetMousePos() < settings::returnButtonPos - Vec2<int>{ 0, 25 } + settings::returnButtonSize)
	{
		if (mouseOverReturnButton != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverReturnButton = true;
		}
	}
	else
	{
		if (settings::returnButtonTextSize < settings::maxReturnButtonTextSize)
		{
			returnButtonCounter++;
			if (returnButtonCounter > 0)
			{
				settings::returnButtonTextSize += 5;
				returnButtonCounter = 0;
			}
		}
		mouseOverReturnButton = false;
	}
	if (mouseOverReturnButton)
	{
		if (settings::returnButtonTextSize > settings::minReturnButtonTextSize)
		{
			returnButtonCounter++;
			if (returnButtonCounter > 0)
			{
				settings::returnButtonTextSize -= 5;
				returnButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			SetLoaded(false);
		}
	}
}
