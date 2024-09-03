#include "Scene.h"

Scene::Scene(SDL_Renderer* render_target, TTF_Font* font, Inspector* inspector, Stage* stage_p)
	: Script()       // Default initialization for Script base class
	, Curtain()      // Default initialization for Curtain base class
	, Jukebox()      // Default initialization for Jukebox base class
{
	setRenderer(render_target);
	setFont(font);
	add_inspector(inspector);

	stage = stage_p;
}



/*
TextField::TextField()
	: mRenderer(nullptr), mFont(nullptr), mRect{ 0, 0, 100, 30 }, mText(""), mTextColor{ 0, 0, 0, 255 }, mTexture(nullptr), mVisible(true)
{
	// Optionally, initialize SDL text input here
	SDL_StartTextInput();
}
Script::Script()
	: mTextField(),                  // Use the default constructor of TextField
	mMessageArea{ 100, 100, 100, 100 },     // Initialize SDL_Rect with default values
	mMessages(),                    // Initialize empty vector
	mVisible(false)                 // Default visibility is false
{
	// Optionally, you can set default values or perform additional initialization here
}
*/


void Scene::update(double delta)
{
	while (message_alert())
	{
		int choice = get_inspector()->processCommand(pop_message());

		switch (choice)
		{
		case 0:
			break;
		case 1:
			play_music();
			break;
		case 2:
			pause_music();
			break;
		case 3:
			stage->teleport_to_entrence(&player_array[0]);
			stage->teleport_to_entrence(&player_array[1]);
			stage->teleport_to_entrence(&player_array[2]);
			player_array[0].set_enter(false);
			player_array[1].set_enter(false);
			player_array[2].set_enter(false);
		default:
			break;
		}
	}
	
	pause->update("Pause.");
	//info.update("Hello. \n\n\n\nLet me tell you a story about\n\n \n\n3 rats\n\n\n\n. They lived their lives happily. One day, they found a hole inside the fancy...", delta);
	clock->update(delta);
	fade->update(std::to_string(clock->get_day()));

	if (!clock->day_time())
	{
		fade->in();
	}
	else if (clock->day_time())
	{
		fade->out();
	}
	/*
	if (button_music->get_clicked())
	{
		//sound->play();
		//play_music();
		toggle_music();

	}
	*/
	
}

void Scene::draw(SDL_Renderer* render_target)
{
	clock->draw(render_target);
	fade->draw(render_target);
	pause->draw(render_target);
	//info->draw(renderTarget);

	if (isVisible())render();

	//if (pause.is_on_screen()) button.render();
	if (pause->is_on_screen()) button_music->render();
}

void Scene::set_player_array(Acteur* player_array_p, int player_amount_p)
{
	player_array = player_array_p;
	player_amount = player_amount_p;
}

