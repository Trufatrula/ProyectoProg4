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
void hashContrasena(const char* contrasena, const char* salt, char* hash);
void crearUsuario(Usuario* usuario,const char* nombre, const char* apellido, const char* nickname, const char* hash, const char* salt);
void iniciarUsuario(Usuario* usuario, const char* nombre, const char* apellido, const char* nickname, const char* contrasena);
void setContrasena(Usuario* usuario, const char* contrasena);
void liberarUsuario(Usuario* usuario);

#ifdef __cplusplus
}
#endif

#endif