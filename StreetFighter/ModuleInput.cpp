#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE)* MAX_KEYS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete keyboard;
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

/*MAQUINA DE ESTADOS*/

//1-. Crear states.h
//2-. Introducir los comandos

bool external_input(p2Qeue<PLAYER_inputs>& inputs, p2Qeue<PLAYER_inputs>& inputs2)
{
	//-- PLAYER 1 BOOLS

	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;
	static bool punch_low = false;
	static bool punch_mid = false;
	static bool punch_high = false;
	static bool kick_low = false;
	static bool kick_mid = false;
	static bool kick_high = false;

	//-- PLAYER 2 BOOLS

	static bool left_2 = false;
	static bool right_2 = false;
	static bool down_2 = false;
	static bool up_2 = false;
	static bool punch_low_2 = false;
	static bool punch_mid_2 = false;
	static bool punch_high_2 = false;
	static bool kick_low_2 = false;
	static bool kick_mid_2 = false;
	static bool kick_high_2 = false;

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYUP && event.key.repeat == 0) //-- KEY RELEASED
		{
			switch (event.key.keysym.sym)
			{

				//--INPUTS PLAYER 1

				//--MOVEMENT PLAYER 1

			case SDLK_ESCAPE:
				return false;
				break;
			case SDLK_s:
				inputs.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_w:
				up = false;
				break;
			case SDLK_a:
				inputs.Push(IN_LEFT_UP);
				left = false;
				break;
			case SDLK_d:
				inputs.Push(IN_RIGHT_UP);
				right = false;
				break;

				//-- ATTACKS PLAYER 1

			case SDLK_f:
				punch_low = false;
				break;
			case SDLK_g:
				punch_mid = false;
				break;
			case SDLK_h:
				punch_high = false;
				break;
			case SDLK_c:
				kick_low = false;
				break;
			case SDLK_v:
				kick_mid = false;
				break;
			case SDLK_b:
				kick_high = false;
				break;

				//-- INPUTS PLAYER 2

				//--MOVEMENT PLAYER 2

			case SDLK_KP_5:
				inputs.Push(IN_CROUCH_UP);
				down_2 = false;
				break;
			case SDLK_KP_8:
				up_2 = false;
				break;
			case SDLK_KP_4:
				inputs.Push(IN_LEFT_UP);
				left_2 = false;
				break;
			case SDLK_KP_6:
				inputs.Push(IN_RIGHT_UP);
				right_2 = false;
				break;

				//-- ATTACKS PLAYER 2

			case SDLK_u:
				punch_low_2 = false;
				break;
			case SDLK_i:
				punch_mid_2 = false;
				break;
			case SDLK_o:
				punch_high_2 = false;
				break;
			case SDLK_j:
				kick_low_2 = false;
				break;
			case SDLK_k:
				kick_mid_2 = false;
				break;
			case SDLK_l:
				kick_high_2 = false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0) //-- KEY IS PRESSED
		{
			switch (event.key.keysym.sym)
			{
				//-- INPUTS PLAYER 1

				//-- MOVEMENT PLAYER 1
			case SDLK_w:
				up = true;
				break;
			case SDLK_s:
				down = true;
				break;
			case SDLK_a:
				left = true;
				break;
			case SDLK_d:
				right = true;
				break;

				//--ATTACKS PLAYER 1

			case SDLK_f:
				punch_low = true;
				break;
			case SDLK_g:
				punch_mid = true;
				break;
			case SDLK_h:
				punch_high = true;
				break;
			case SDLK_c:
				kick_low = true;
				break;
			case SDLK_v:
				kick_mid = true;
				break;
			case SDLK_b:
				kick_high = true;
				break;

				//-- INPUTS PLAYER 2

				//--MOVEMENT PLAYER 2

			case SDLK_KP_5:
				down_2 = true;
				break;
			case SDLK_KP_8:
				up_2 = true;
				break;
			case SDLK_KP_4:
				left_2 = true;
				break;
			case SDLK_KP_6:
				right_2 = true;
				break;

				//-- ATTACKS PLAYER 2

			case SDLK_u:
				punch_low_2 = true;
				break;
			case SDLK_i:
				punch_mid_2 = true;
				break;
			case SDLK_o:
				punch_high_2 = true;
				break;
			case SDLK_j:
				kick_low_2 = true;
				break;
			case SDLK_k:
				kick_mid_2 = true;
				break;
			case SDLK_l:
				kick_high_2 = true;
				break;
			}
		}


		//-- PLAYER 1 

		//-- MOVEMENT INPUTS

		if (left && right)
			inputs.Push(IN_LEFT_AND_RIGHT);
		{
			if (left)
				inputs.Push(IN_LEFT_DOWN);
			if (right)
				inputs.Push(IN_RIGHT_DOWN);
		}

		if (up && down)
			inputs.Push(IN_JUMP_AND_CROUCH);
		else
		{
			if (down)
				inputs.Push(IN_CROUCH_DOWN);
			if (up)
				inputs.Push(IN_JUMP);
		}

		//-- ATTACK INPUTS

		if (punch_low)
		{
			inputs.Push(IN_PUNCH_LOW);
		}

		if (punch_mid)
		{
			inputs.Push(IN_PUNCH_MID);
		}

		if (punch_high)
		{
			inputs.Push(IN_PUNCH_HIGH);
		}

		if (kick_low)
		{
			inputs.Push(IN_KICK_LOW);
		}

		if (kick_mid)
		{
			inputs.Push(IN_KICK_MID);
		}

		if (kick_high)
		{
			inputs.Push(IN_KICK_HIGH);
		}

		//-- PLAYER 2 

		//-- MOVEMENT INPUTS

		if (left_2 && right_2)
			inputs2.Push(IN_LEFT_AND_RIGHT);
		{
			if (left_2)
				inputs2.Push(IN_LEFT_DOWN);
			if (right_2)
				inputs2.Push(IN_RIGHT_DOWN);
		}
		if (up_2 && down_2)
			inputs2.Push(IN_JUMP_AND_CROUCH);
		else
		{
			if (down_2)
				inputs2.Push(IN_CROUCH_DOWN);
			if (up_2)
				inputs2.Push(IN_JUMP);
		}

		//-- ATTACK INPUTS

		if (punch_low_2)
		{
			inputs2.Push(IN_PUNCH_LOW);
		}

		if (punch_mid_2)
		{
			inputs2.Push(IN_PUNCH_MID);
		}

		if (punch_high_2)
		{
			inputs2.Push(IN_PUNCH_HIGH);
		}

		if (kick_low_2)
		{
			inputs2.Push(IN_KICK_LOW);
		}

		if (kick_mid_2)
		{
			inputs2.Push(IN_KICK_MID);
		}

		if (kick_high_2)
		{
			inputs2.Push(IN_KICK_HIGH);
		}

	}
	return true;
}







// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
		return UPDATE_STOP;

	SDL_GetMouseState(&mouse_x, &mouse_y);
	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;

	App->input->external_inputs(App->player->inputs, App->player2->inputs2);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}