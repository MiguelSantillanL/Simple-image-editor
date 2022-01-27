# Simple-image-editor
Programa en C++ que permite Rotar, Agrandar y Reducir de tamaño una Imagen

## Requisitos 
* Es necesario tener Opencv para poder compilarlo con el código, en caso de no tenerlo, se puede usar el archivo [install-opencv.sh](https://github.com/MiguelSantillanL/Simple-image-editor/tree/main/OpenCV)
## Compilación
Para compilar usar el siguiente comando:
```bash
g++ -Wall Matriz_P.cpp Matriz_P.hpp Simple_Photoshop.hpp Simple_Photoshop.cpp Main.cpp -o app `pkg-config --cflags --libs opencv4`
./app
```

