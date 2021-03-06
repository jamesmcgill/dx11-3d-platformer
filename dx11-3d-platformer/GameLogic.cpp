#include "pch.h"
#include "GameLogic.h"
#include "AppContext.h"
#include "AppResources.h"
#include "StepTimer.h"
#include "Entity.h"

#include "utils/Log.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//------------------------------------------------------------------------------
GameLogic::GameLogic(AppContext& context, AppResources& resources)
    : m_context(context)
    , m_resources(resources)
{
  TRACE
}

//------------------------------------------------------------------------------
void
GameLogic::reset()
{
  TRACE
  m_context.resetPlayer();
  m_context.resetCamera();

  m_hudDirty = true;

  m_context.updateViewMatrix();
}

//------------------------------------------------------------------------------
GameLogic::GameStatus
GameLogic::update(const DX::StepTimer& timer)
{
  UNREFERENCED_PARAMETER(timer);

  TRACE
  // float elapsedTimeS = float(timer.GetElapsedSeconds());

  performPhysicsUpdate(timer);
  performCollisionTests();

  return GameStatus::Playing;
}

//------------------------------------------------------------------------------
void
GameLogic::render()
{
  TRACE
  renderEntityModels();

  // auto& states			= *m_resources.m_states;

  // auto& spriteBatch = m_resources.m_spriteBatch;
  // spriteBatch->Begin(SpriteSortMode_Deferred, states.Additive());
  // spriteBatch->End();

  DX::DrawContext drawContext(m_context, m_resources);
  drawContext.begin(DX::DrawContext::Projection::Screen);
  drawHUD();
  drawContext.end();

  // Debug Drawing
  if (m_context.debugDraw)
  {
    drawContext.begin();
    renderEntitiesDebug();

    drawContext.setScreenProjection();
    drawDebugVariables();
    drawContext.end();
  }
}

//------------------------------------------------------------------------------
void
GameLogic::renderEntityModels()
{
  TRACE
  // size_t idx = 0;
  // for (auto& entity : m_context.entities)
  //{
  //	if (PLAYERS_IDX == idx)
  //	{
  //		renderPlayerEntity(entity);
  //	}
  //	else if (entity.isAlive)
  //	{
  //		renderEntityModel(entity);
  //	}
  //	++idx;
  //}
}

//------------------------------------------------------------------------------
void
GameLogic::renderEntitiesDebug()
{
  TRACE
  // for (auto& entity : m_context.entities)
  //{
  //	if (entity.isAlive)
  //	{
  //		renderEntityBound(entity);
  //	}
  //}
  // m_enemies.debugRender(m_resources.m_batch.get());
  // renderPlayerBoundary();
}

//------------------------------------------------------------------------------
void
GameLogic::performPhysicsUpdate(const DX::StepTimer& timer)
{
  UNREFERENCED_PARAMETER(timer);

  TRACE
  // float elapsedTimeS = float(timer.GetElapsedSeconds());

  //// Player input forces
  // auto& player = m_context.entities[PLAYERS_IDX];
  // m_context.playerAccel *= m_context.playerSpeed;

  // Vector3 frictionNormal = -player.velocity;
  // frictionNormal.Normalize();
  // m_context.playerAccel += m_context.playerFriction * frictionNormal;

  //// Ballistic entities
  // for (size_t i = BALLISTIC_IDX; i < BALLISTIC_END; ++i)
  //{
  //	const bool isPlayer = (i < PLAYERS_END);
  //	auto& e							= m_context.entities[i];

  //	// Integrate Position
  //	const Vector3& accel = (isPlayer) ? m_context.playerAccel : Vector3();

  //	e.position = 0.5f * accel * (elapsedTimeS * elapsedTimeS)
  //							 + e.velocity * elapsedTimeS + e.position;
  //	e.velocity = accel * elapsedTimeS + e.velocity;
  //}
}

//------------------------------------------------------------------------------
void
GameLogic::performCollisionTests()
{
  TRACE
  // for (size_t i = 0; i < NUM_ENTITIES; ++i)
  //{
  //	m_context.entities[i].isColliding = false;
  //}

  // auto& player = m_context.entities[PLAYERS_IDX];

  // auto onPlayerShotHitsEnemy =
  //	[	&score				= m_context.playerScore,
  //		&explosions		= m_resources.explosions,
  //		&soundEffects	= m_resources.soundEffects,
  //	  &m_hudDirty		= this->m_hudDirty
  //	](Entity& shot, Entity& testEntity)
  //{
  //	auto pos = shot.position + shot.model->bound.Center;
  //	explosions->emit(pos, Vector3());
  //	soundEffects[AudioResource::EnemyExplode]->Play();

  //	shot.isColliding			 = true;
  //	testEntity.isColliding = true;
  //	shot.isAlive					 = false;
  //	testEntity.isAlive		 = false;
  //	score += POINTS_PER_KILL;
  //	m_hudDirty = true;
  //};

  // auto onPlayerHit =
  //	[	&context			= m_context,
  //		&explosions		= m_resources.explosions,
  //		&soundEffects	= m_resources.soundEffects
  //	](Entity & player, Entity & enemy)
  //{
  //	auto pos = player.position + player.model->bound.Center;
  //	explosions->emit(pos, Vector3());
  //	soundEffects[AudioResource::PlayerExplode]->Play();

  //	pos = enemy.position + enemy.model->bound.Center;
  //	explosions->emit(pos, Vector3());
  //	soundEffects[AudioResource::EnemyExplode]->Play();

  //	player.isColliding = true;
  //	enemy.isColliding	= true;

  //	enemy.isAlive = false;
  //	LOG_VERBOSE("playerState: Normal->Dying");
  //	context.playerState				= PlayerState::Dying;
  //	context.playerDeathTimerS = PLAYER_DEATH_TIME_S;
  //};

  //// Pass 1 - PlayerShots		-> Enemies
  // for (size_t srcIdx = PLAYER_SHOTS_IDX; srcIdx < PLAYER_SHOTS_END; ++srcIdx)
  //{
  //	auto& srcEntity = m_context.entities[srcIdx];
  //	collisionTestEntity(
  //		srcEntity, ENEMIES_IDX, ENEMIES_END, onPlayerShotHitsEnemy);
  //}

  //// Player is invulnerable, no more collision tests
  // if (m_context.playerState == PlayerState::Reviving)
  //{
  //	return;
  //}

  //// Pass 2 - Player				-> Enemies
  // collisionTestEntity(player, ENEMIES_IDX, ENEMIES_END, onPlayerHit);

  //// Pass 3 - Player				-> EnemyShots
  // collisionTestEntity(player, ENEMY_SHOTS_IDX, ENEMY_SHOTS_END, onPlayerHit);
}

//------------------------------------------------------------------------------
// template <typename Func>
// void
// GameLogic::collisionTestEntity(
//	Entity& entity,
//	const size_t rangeStartIdx,
//	const size_t rangeOnePastEndIdx,
//	Func& onCollision)
//{
//	if (!entity.isAlive)
//	{
//		return;
//	}
//	TRACE
//
//	// TODO(James): Use the GCL <notnullable> to compile time enforce assertion
//	ASSERT(entity.model);
//	auto& srcBound = entity.model->bound;
//	auto srcCenter = entity.position + srcBound.Center;
//
//	for (size_t testIdx = rangeStartIdx; testIdx < rangeOnePastEndIdx;
//++testIdx)
//	{
//		ASSERT(m_context.entities[testIdx].model);
//		auto& testEntity = m_context.entities[testIdx];
//		if (!testEntity.isAlive)
//		{
//			continue;
//		}
//
//		auto& testBound = testEntity.model->bound;
//		auto testCenter = testEntity.position + testBound.Center;
//
//		auto distance = (srcCenter - testCenter).Length();
//		if (distance <= (srcBound.Radius + testBound.Radius))
//		{
//			onCollision(entity, testEntity);
//		}
//	}
//}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// void
// GameLogic::renderPlayerEntity(Entity& entity)
//{
//	TRACE
//	switch (m_context.playerState)
//	{
//		case PlayerState::Normal:
//			renderEntityModel(entity, XM_PI);
//			break;
//
//		case PlayerState::Dying:
//			// TODO(James): Render Player Death
//			break;
//
//		case PlayerState::Reviving:
//			// Flash the player every half second
//			if (
//				static_cast<int>(m_context.playerReviveTimerS * PLAYER_REVIVE_TIME_S)
//					% 2
//				!= 0)
//			{
//				renderEntityModel(entity, XM_PI);
//			}
//			break;
//	}
//}

//------------------------------------------------------------------------------
// void
// GameLogic::renderEntityModel(Entity& entity, float orientation)
//{
//	TRACE
//	// TODO(James): Use <notnullable> to enforce assertion
//	ASSERT(entity.model);
//	const auto& modelData		= entity.model;
//	const auto& boundCenter = entity.model->bound.Center;
//
//	Matrix world = Matrix::CreateTranslation(boundCenter).Invert()
//								 * Matrix::CreateFromYawPitchRoll(0.0f, 0.0f, orientation)
//								 * Matrix::CreateTranslation(entity.position + boundCenter);
//
//	modelData->model->Draw(
//		m_resources.m_deviceResources->GetD3DDeviceContext(),
//		*m_resources.m_states,
//		world,
//		m_context.worldToView,
//		m_context.viewToProjection);
//
//#if 0
//	// DEBUG BOUND
//	Matrix boundWorld = Matrix::CreateTranslation(entity.position +
//boundCenter); 	boundWorld.m[0][0] *= modelData->bound.Radius;
//	boundWorld.m[1][1] *= modelData->bound.Radius;
//	boundWorld.m[2][2] *= modelData->bound.Radius;
//
//	Vector4 color = entity.isColliding ? Vector4(1.0f, 0.0f, 0.0f, 0.4f)
//		: Vector4(0.0f, 1.0f, 0.0f, 0.4f);
//	m_debugBoundEffect->SetColorAndAlpha(color);
//
//	m_debugBoundEffect->SetView(worldToView);
//	m_debugBoundEffect->SetProjection(viewToProjection);
//	m_debugBoundEffect->SetWorld(boundWorld);
//	m_debugBoundEffect->Apply(context);
//
//	context->OMSetBlendState(m_states->AlphaBlend(), Colors::White, 0xFFFFFFFF);
//	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);
//	context->RSSetState(m_states->CullNone());
//
//	m_debugBound->Draw(
//		m_debugBoundEffect.get(), m_debugBoundInputLayout.Get(), true, true);
//#endif
//}

//------------------------------------------------------------------------------
// void
// GameLogic::renderEntityBound(Entity& entity)
//{
//	TRACE
//	// TODO(James): Use <notnullable> to enforce assertion
//	ASSERT(entity.model);
//	// const auto& modelData = entity.model;
//
//	auto bound	 = entity.model->bound;
//	bound.Center = bound.Center + entity.position;
//	DX::Draw(
//		m_resources.m_batch.get(),
//		bound,
//		(entity.isColliding) ? Colors::Red : Colors::Lime);
//
//	// Matrix world = Matrix::CreateTranslation(entity.position + boundCenter);
//	// world.m[0][0] *= modelData->bound.Radius;
//	// world.m[1][1] *= modelData->bound.Radius;
//	// world.m[2][2] *= modelData->bound.Radius;
//
//	// DEBUG BOUND
//	// Vector4 color = entity.isColliding ? Vector4(1.0f, 0.0f, 0.0f, 0.4f)
//	//																	 : Vector4(0.0f, 1.0f, 0.0f, 0.4f);
//	// m_debugEffect->SetColorAndAlpha(color);
//	// m_debugBoundEffect->SetWorld(world);
//
//	// m_debugBound->Draw(
//	//	m_debugBoundEffect.get(), m_debugBoundInputLayout.Get(), true, true);
//}

//------------------------------------------------------------------------------
// void
// GameLogic::renderPlayerBoundary()
//{
//	TRACE
//
//	auto& player			 = m_context.entities[PLAYERS_IDX];
//	const float xLimit = PLAYER_MAX_POSITION.x + player.model->bound.Radius;
//	const float yLimit = PLAYER_MAX_POSITION.y + player.model->bound.Radius;
//	const float zPlane = PLAYER_MAX_POSITION.z;
//
//	DX::DrawLine(
//		m_resources.m_batch.get(),
//		Vector3(-xLimit, yLimit, zPlane),
//		Vector3(xLimit, yLimit, zPlane));
//
//	DX::DrawLine(
//		m_resources.m_batch.get(),
//		Vector3(-xLimit, -yLimit, zPlane),
//		Vector3(xLimit, -yLimit, zPlane));
//
//	DX::DrawLine(
//		m_resources.m_batch.get(),
//		Vector3(-xLimit, -yLimit, zPlane),
//		Vector3(-xLimit, yLimit, zPlane));
//
//	DX::DrawLine(
//		m_resources.m_batch.get(),
//		Vector3(xLimit, -yLimit, zPlane),
//		Vector3(xLimit, yLimit, zPlane));
//}

//------------------------------------------------------------------------------
void
GameLogic::drawHUD()
{
  TRACE
  if (m_hudDirty)
  {
    m_hudDirty = false;
  }
}

//------------------------------------------------------------------------------
void
GameLogic::updateUIDebugVariables()
{
  TRACE
  float yPos = 0.0f;

  auto formatUI = [
    &yPos,
    font        = m_resources.fontMono8pt.get(),
    screenWidth = m_context.screenWidth
  ](ui::Text & uiText, const wchar_t* fmt, float fVar)
  {
    uiText.font         = font;
    uiText.text         = fmt::format(fmt, fVar);
    XMVECTOR dimensions = uiText.font->MeasureString(uiText.text.c_str());
    float width         = XMVectorGetX(dimensions);
    float height        = ceil(XMVectorGetY(dimensions));
    uiText.origin       = Vector2(width, 0.0f);
    uiText.position.x   = screenWidth;
    uiText.position.y   = yPos;
    uiText.color        = Colors::MediumVioletRed;
    yPos += height;
  };

  const wchar_t* title = (m_context.isMidiConnected)
                           ? L"MIDI CONTROLLER FOUND"
                           : L"NO MIDI CONTROLLER FOUND";
  formatUI(m_context.uiDebugVarsTitle, title, 0.0f);

  formatUI(
    m_context.uiCameraDist, L"Camera Dist: {}", m_context.cameraDistance);
  formatUI(m_context.uiPlayerSpeed, L"Player Speed: {}", m_context.playerSpeed);
  formatUI(
    m_context.uiPlayerFriction,
    L"Player Friction: {}",
    m_context.playerFriction);
  formatUI(
    m_context.uiPlayerMaxVelocity,
    L"Player Max Velocity: {}",
    m_context.playerMaxVelocity);
  formatUI(
    m_context.uiPlayerMinVelocity,
    L"Player Min Velocity: {}",
    m_context.playerMinVelocity);
}

//------------------------------------------------------------------------------
void
GameLogic::drawDebugVariables()
{
  TRACE
  auto drawUI = [& spriteBatch = m_resources.m_spriteBatch](ui::Text & uiText)
  {
    uiText.draw(*spriteBatch);
  };

  drawUI(m_context.uiDebugVarsTitle);
  drawUI(m_context.uiPlayerSpeed);
  drawUI(m_context.uiPlayerFriction);
  drawUI(m_context.uiPlayerMaxVelocity);
  drawUI(m_context.uiPlayerMinVelocity);
  drawUI(m_context.uiCameraDist);
}

//------------------------------------------------------------------------------
