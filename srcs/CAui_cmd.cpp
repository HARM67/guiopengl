#include "CAui_cmd.hpp"

CAui_cmd	CAui_cmd::m_instance;

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

CAui_cmd::CAui_cmd()
{
	glfwSetMouseButtonCallback(CGraphic::Instance()->m_window, *mouse_button_callback);
}
