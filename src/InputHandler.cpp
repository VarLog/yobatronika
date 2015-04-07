//
//  InputHandler.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 08.04.15.
//
//

#include "InputHandler.h"

using namespace Yoba;

std::shared_ptr<InputHandler> InputHandler::m_spInstance = nullptr;

std::shared_ptr<InputHandler> InputHandler::Instance()
{
    if(m_spInstance == nullptr)
    {
        m_spInstance = std::shared_ptr<InputHandler>(new InputHandler());
    }
    return m_spInstance;
}

void InputHandler::DeleteInstance() {
    m_spInstance.reset();
}

InputHandler::InputHandler() {};

void InputHandler::update() {}
void InputHandler::clean() {}
