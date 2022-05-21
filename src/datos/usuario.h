#ifndef USUARIO
#define USUARIO

typedef struct{
    char* nombre;
    char* apellido;
    char* nickname;
    char* hash;
    char* salt;
    int admin;
} Usuario;

void generarSalt(char* salt);
void hashContrasena(char* contrasena, char* salt, char* hash);

void crearUsuario(Usuario* usuario, char* nombre, char* apellido, char* nickname, char* hash, char* salt, int admin);
void iniciarUsuario(Usuario* usuario, char* nombre, char* apellido, char* nickname, char* contrasena, int admin);
void setContrasena(Usuario* usuario, char* contrasena);
void liberarUsuario(Usuario* usuario);

#endif