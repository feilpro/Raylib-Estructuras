#pragma once
#include "PanelMensaje.h"
#include "Stack.h"
#include <string>

class MessageSystem
{
private:
	Stack<std::string> mensajes;
	PanelMensaje panel;

public:
    MessageSystem()
        : mensajes(10), // máximo 10 mensajes en pila
        panel(GetScreenWidth() - 310, 300, 60, 3) // esquina superior derecha
    {
    }

    void AgregarMensaje(const std::string& msg)
    {
        mensajes.push(msg);
    }

    void Update()
    {
        panel.update();

        // Solo cuando el panel está oculto, mostramos el siguiente mensaje
        if (panel.GetState() == hidden && !mensajes.isEmpty())
        {
            std::string msg = mensajes.pop();
            panel.Show(msg);
        }
    }

    void Draw()
    {
        panel.draw();
    }
};

