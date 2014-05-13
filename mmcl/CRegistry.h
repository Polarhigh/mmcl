#ifndef REGISTRY_H
#define REGISTRY_H

class CRegistry
{
public:
bool Init(void);
void Shutdown(void);
int ReadInt(char *key, int defvalue = NULL);
void WriteInt(char *key, int value);
char *ReadString(char *key, char *defvalue = NULL);
void WriteString(char *key, char *value);
bool Initialised();
private:

bool g_bRegisterValid;
HKEY g_hRegisterKey;

};
extern CRegistry Registry;
#endif