#include <iostream>
#include <vector>
#include "FileReader.h"
#include "Object.h"
#include "Game.h"

int main() {
    Game game;
    game.startGame();  

    std::vector<Object> objectList;

    // Llamar a la función para leer objetos desde el archivo
    if (FileReader::readObjectsFromFile("ObjetosLeer.csv", objectList)) {
        std::cout << "Lectura exitosa. Objetos leídos:" << std::endl;

        // Mostrar los objetos leídos
        for (const auto& obj : objectList) {
            std::cout << "Tipo: " << obj.getType()
                << ", Posición: (" << obj.getPosition().x << ", " << obj.getPosition().y << ")"
                << ", Escala: " << obj.getScale()
                << ", Shift: " << obj.getShift() << std::endl;
        }
    }
    else {
        std::cerr << "Error al leer el archivo." << std::endl;
    }

    return 0;
}
