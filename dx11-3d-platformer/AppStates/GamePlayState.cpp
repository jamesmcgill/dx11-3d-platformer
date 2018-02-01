#include "pch.h"
#include "AppStates.h"
#include "GamePlayState.h"
#include "AppContext.h"
#include "AppResources.h"
#include "GameLogic.h"

#include "utils/Log.h"

//------------------------------------------------------------------------------
extern void ExitGame();

//------------------------------------------------------------------------------
constexpr float CAMERA_SPEED_X			 = 1.0f;
constexpr float CAMERA_SPEED_Y			 = 1.0f;
constexpr float CAMERA_MIN_DIST			 = 30.0f;
constexpr float UNIT_DIAGONAL_LENGTH = 0.7071067811865475f;

constexpr size_t CAMERA_DIST_CONTROL				 = 16;
constexpr size_t PLAYER_SPEED_CONTROL				 = 17;
constexpr size_t PLAYER_FRICTION_CONTROL		 = 18;
constexpr size_t PLAYER_MAX_VELOCITY_CONTROL = 19;
constexpr size_t PLAYER_MIN_VELOCITY_CONTROL = 20;

//------------------------------------------------------------------------------
void
GamePlayState::handleInput(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	TRACE
	float elapsedTimeS = static_cast<float>(timer.GetElapsedSeconds());

	auto& kb = m_resources.kbTracker;
	auto& kbState = m_resources.kbTracker.lastState;
	using DirectX::Keyboard;

	if (kb.IsKeyPressed(Keyboard::Escape))
	{
		//m_states.changeState(&m_states.paused);
	}

	// Debug options
	if (kb.IsKeyPressed(Keyboard::F2))
	{
		m_context.debugDraw = !m_context.debugDraw;
	}

	const auto& midiMask	= m_resources.midiTracker.dirtyMask;
	const auto& midiState = m_resources.midiTracker.currentState;
	if (midiMask.test(CAMERA_DIST_CONTROL))
	{
		m_context.cameraDistance
			= static_cast<float>(midiState[CAMERA_DIST_CONTROL]) + CAMERA_MIN_DIST;
		m_context.updateViewMatrix();
		m_gameLogic.updateUIDebugVariables();
	}
	if (midiMask.test(PLAYER_SPEED_CONTROL))
	{
		m_context.playerSpeed
			= static_cast<float>(midiState[PLAYER_SPEED_CONTROL] * 2);
		m_gameLogic.updateUIDebugVariables();
	}
	if (midiMask.test(PLAYER_FRICTION_CONTROL))
	{
		m_context.playerFriction
			= static_cast<float>(midiState[PLAYER_FRICTION_CONTROL] * 2);
		m_gameLogic.updateUIDebugVariables();
	}
	if (midiMask.test(PLAYER_MAX_VELOCITY_CONTROL))
	{
		m_context.playerMaxVelocity
			= static_cast<float>(midiState[PLAYER_MAX_VELOCITY_CONTROL] * 2);
		m_gameLogic.updateUIDebugVariables();
	}
	if (midiMask.test(PLAYER_MIN_VELOCITY_CONTROL))
	{
		m_context.playerMinVelocity
			= static_cast<float>(midiState[PLAYER_MIN_VELOCITY_CONTROL]) / 10.f;
		m_gameLogic.updateUIDebugVariables();
	}
	m_resources.midiTracker.flush();

	if (kbState.W)
	{
		m_context.cameraRotationX -= elapsedTimeS * CAMERA_SPEED_X;
		m_context.updateViewMatrix();
	}
	else if (kbState.S)
	{
		m_context.cameraRotationX += elapsedTimeS * CAMERA_SPEED_X;
		m_context.updateViewMatrix();
	}

	if (kbState.A)
	{
		m_context.cameraRotationY -= elapsedTimeS * CAMERA_SPEED_Y;
		m_context.updateViewMatrix();
	}
	else if (kbState.D)
	{
		m_context.cameraRotationY += elapsedTimeS * CAMERA_SPEED_Y;
		m_context.updateViewMatrix();
	}
	if (kbState.R)
	{
		m_context.cameraRotationX = 0.0f;
		m_context.cameraRotationY = 0.0f;
		m_context.updateViewMatrix();
	}

	// Player Movement

	// NB. Must be reset, even while dead.
	m_context.playerAccel = DirectX::SimpleMath::Vector3();
	if (m_context.playerState == PlayerState::Dying)
	{
		return;
	}

	if (kbState.Up)
	{
		m_context.playerAccel.y = 1.0f;
	}
	else if (kbState.Down)
	{
		m_context.playerAccel.y = -1.0f;
	}

	if (kbState.Left)
	{
		m_context.playerAccel.x = -1.0f;
	}
	else if (kbState.Right)
	{
		m_context.playerAccel.x = 1.0f;
	}

	if (m_context.playerAccel.x != 0.0f && m_context.playerAccel.y != 0.0f)
	{
		m_context.playerAccel *= UNIT_DIAGONAL_LENGTH;
	}
}

//------------------------------------------------------------------------------
void
GamePlayState::update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	TRACE
}

//------------------------------------------------------------------------------
void
GamePlayState::render()
{
	TRACE
	m_gameLogic.render();
}

//------------------------------------------------------------------------------
void
GamePlayState::load()
{
	TRACE
}

//------------------------------------------------------------------------------
void
GamePlayState::unload()
{
	TRACE
}

//------------------------------------------------------------------------------
bool
GamePlayState::isLoaded() const
{
	return false;
}

//------------------------------------------------------------------------------
void
GamePlayState::enter()
{
	TRACE
}

//------------------------------------------------------------------------------
void
GamePlayState::exit()
{
	TRACE
}

//------------------------------------------------------------------------------
