#ifndef USUARIO
#define USUARIO

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
    char* nombre;
    char* apellido;
    char* nickname;
    char* hash;
    char* salt;
    int admin;
} Usuario;

void generarSalt(char* salt);
void hashContrasena(const char* contrasena, char* salt, char* hash);

void crearUsuario(Usuario* usuario, char* nombre, char* apellido, char* nickname, char* hash, char* salt);
void iniciarUsuario(Usuario* usuario, char* nombre, char* apellido, char* nickname, char* contrasena);
void setContrasena(Usuario* usuario, char* contrasena);
void liberarUsuario(Usuario* usuario);

#ifdef __cplusplus
}
#endif

#endif