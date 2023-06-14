#include "StateMachine.h"

StateMachine::StateMachine()
	:m_adding(false), m_removing(false), m_replacing(false)
{}

void StateMachine::addState(std::unique_ptr<State>& newState, bool replacing)
{
	m_adding = true;
	m_replacing = replacing;
	m_newGameState = std::move(newState);
}

void StateMachine::removeState()
{
	m_removing = true;
}

void StateMachine::checkForUpdates()
{
	if (m_adding)//if need to add new state
	{
		if (!m_states.empty())//check the states not empty
		{
			if (m_replacing)//replace the current state with the new one
				m_states.pop();
			else//pause the current state and add new state to run
				;//m_states.top()->pause();
		}
		m_states.push(std::move(m_newGameState));
		m_adding = false;
	}

	if (m_removing && !m_states.empty())
	{
		m_states.pop();
		//if (!m_states.empty())
			;//m_states.top()->resume();
		m_removing = false;
	}
}

std::unique_ptr<State>& StateMachine::getCurrentState()
{
	return m_states.top();
}
