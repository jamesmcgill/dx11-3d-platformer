#include "pch.h"
#include "AppStates.h"

//------------------------------------------------------------------------------
AppStates::AppStates(
	AppContext& context, AppResources& resources, GameLogic& logic)
		: playing(*this, context, resources, logic)
		, m_currentState(&playing)
{
}

//------------------------------------------------------------------------------
IAppState*
AppStates::currentState() const
{
	assert(m_currentState);
	return m_currentState;
}

//------------------------------------------------------------------------------
IAppState*
AppStates::previousState() const
{
	assert(m_previousState);
	return m_previousState;
}

//------------------------------------------------------------------------------
void
AppStates::changeState(IAppState* newState)
{
	m_currentState->exit();

	m_previousState = m_currentState;
	m_currentState	= newState;
	loadAndEnterState();
}

//------------------------------------------------------------------------------
void
AppStates::loadAndEnterState()
{
	if (!m_currentState->isLoaded())
	{
		m_currentState->load();
	}
	m_currentState->enter();
}

//------------------------------------------------------------------------------
