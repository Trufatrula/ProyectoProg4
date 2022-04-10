#ifndef USUARIO
#define USUARIO

typedef struct{
    char* nombre;
    char* apellido;
    char* nickname;
    char*contraseña;
    char* token;
    char* salt;

} Usuario;

char* autentificarUsuario(char* nick){
    char* token = "";

    return token;
}

#endif