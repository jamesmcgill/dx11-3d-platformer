#pragma once

#include "AppStates/IAppState.h"

#include "AppStates/GamePlayState.h"

//------------------------------------------------------------------------------
class AppStates
{
public:
	// Available States
	GamePlayState playing;

public:
	AppStates(AppContext& context, AppResources& resources, GameLogic& logic);
	IAppState* currentState() const;
	IAppState* previousState() const;
	void changeState(IAppState* newState);

private:
	void loadAndEnterState();
	IAppState* m_currentState;
	IAppState* m_previousState = nullptr;
};

//------------------------------------------------------------------------------
