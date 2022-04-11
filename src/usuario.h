#ifndef USUARIO
#define USUARIO

typedef struct{
    char* nombre;
    char* apellido;
    char* nickname;
    int admin;

} Usuario;

void generarSalt(char* salt);
void hashContrasena(char* contrasena, char* salt, char* hash);

#endif