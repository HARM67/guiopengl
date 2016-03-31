#include "CAui_cmd.hpp"

CAui_cmd		CAui_cmd::m_instance;
double			CAui_cmd::command[512];
unsigned char	CAui_cmd::b_key[512];

void	mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	CAui	*tmp;
	double xpos, ypos;

	glfwGetCursorPos(window, &xpos, &ypos);
	tmp = CAui::Instance()->why((float) xpos, (float)ypos);
	if (action == 1)
	{
		if (!tmp)
			return;
		CAui_cmd::Instance()->current = tmp;
		if (CAui_cmd::Instance()->focus)
			CAui_cmd::Instance()->focus->is_focus = 0;
		CAui_cmd::Instance()->focus = tmp;
		CAui_cmd::Instance()->focus->is_focus = 1;
		CAui::click_down.x = (float)xpos;
		CAui::click_down.y = (float)ypos;
		tmp->mouse_button_callback(button, action, mods);
		tmp->in_move = 1;
	}
	else if (CAui_cmd::Instance()->current && CAui_cmd::Instance()->current->in_move)
	{
		if (tmp)
			tmp->mouse_button_callback(button, action, mods);
		CAui_cmd::Instance()->current->in_move = 0;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < 512 && action == GLFW_PRESS)
	{
		CAui_cmd::command[key] = glfwGetTime();// + TIME_FIRST_KEY;
		CAui_cmd::b_key[key] = 1;
	}
	else if (key >= 0 && key < 512 && action == GLFW_RELEASE)
	{
		CAui_cmd::command[key] = glfwGetTime() + 0.1f;
		CAui_cmd::b_key[key] = 0;
	}
	if (CAui_cmd::Instance()->focus)
	{
		CAui_cmd::Instance()->focus->key_callback(CAui_cmd::b_key, CAui_cmd::command);
	}
}

void	cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	CAui	*tmp;

	if (CAui_cmd::Instance()->current)
		CAui_cmd::Instance()->current->cursor_position_callback(0, xpos, ypos);
	tmp = CAui::Instance()->why((float) xpos, (float)ypos);
	if (!tmp)
		return ;
	CAui_cmd::Instance()->current = tmp;
	tmp->cursor_position_callback(1, xpos, ypos);
}

CAui_cmd::CAui_cmd()
{
	glfwSetMouseButtonCallback(CGraphic::Instance()->m_window, *mouse_button_callback);
	glfwSetCursorPosCallback(CGraphic::Instance()->m_window, *cursor_position_callback);
	glfwSetKeyCallback(CGraphic::Instance()->m_window, key_callback);
}
